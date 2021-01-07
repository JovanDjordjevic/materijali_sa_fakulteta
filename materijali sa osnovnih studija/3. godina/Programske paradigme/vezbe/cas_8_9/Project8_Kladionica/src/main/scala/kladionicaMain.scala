import java.io.File
import java.util.Scanner
import java.util.concurrent.ThreadLocalRandom

import scala.collection.mutable
import scala.collection.mutable.ArrayBuffer

class Kladionicar(ime : String, novac : Int, tiket : mutable.HashMap[String, Char], utakmice : mutable.HashMap[String, (Float, Float, Float, Char)]) extends Thread{

  var zarada : Float = 0

  override def run() : Unit = {
    //cekanje da se utakmice odigraju
    //to se radi sinhronizacijom, dakle zakljucavamo svakog kladionicara na promenljivoj utakmice i pozivamo wait()
    utakmice.synchronized{
      utakmice.wait(  )
    }

    //racuna zaradu, iz uslkova zadatk a to radimo tako sto saberemo kvote pogodjenih utakmica i mnozimo sa novcem i delimo sa br pogodjenih
    var pogodjeno : Int = 0
    var ukupnaKvota : Float = 0

    for (t<-tiket){
      //t._2 je rezultat koji je kladionicar pretpostavio, to poredimo sa novim charom na certvrtom mestu value torke u mapi utakmica
      if(t._2 == utakmice(t._1)._4 ){
        println(s"$ime je pogodio rezultat utakmice ${t._1}: ${utakmice(t._1)._4}")
        pogodjeno += 1
        if(utakmice(t._1)._4 == '1')
          ukupnaKvota += utakmice(t._1)._1
        else if(utakmice(t._1)._4 == 'x')
          ukupnaKvota += utakmice(t._1)._2
        else
          ukupnaKvota += utakmice(t._1)._3
      }

      if(pogodjeno > 0 )
        zarada = ukupnaKvota * novac / pogodjeno

    }
  }

  def getZarada() : Float = zarada
  def getIme() : String = ime

  override def toString: String = {
    return ime + " " + novac.toString
  }
}


object kladionicaMain {
  def main(args : Array[String]) : Unit = {
    println("=====kladionica=====")

    val sc1 : Scanner = new Scanner(new File("/home/student/Desktop/pp_vezbanje_novo/cas_8_9/utakmice.txt"))
    val sc2 : Scanner = new Scanner(new File("/home/student/Desktop/pp_vezbanje_novo/cas_8_9/kladionicari.txt"))

    //hocemo u nekoj mapi (koja moze za konkurentno izvrsavanje) da cuvamo utakmice, podatke o njima i ishode
    //stacimo da je kljuc mape String "tim1-tim2" a value (kvotaZa1, kvotaZaX, kvotaZa2, ishodUtakmica) pri cemu
    //cemo taj ishod izracunati ovde kao random
    //metode za HashMap iz scala.collection.mutable:
    // get(k,v)
    //size  - vraca velicinu
    //contains(k) - da li sadrzi kljuc k

    //psotoje tipovi Tuple1, Tuple2, Tuple3, Tuple4....   - AZURABILNE TORKE!!!
    //i-tom elementu pristupamo sa   imeTorke._i  ...

    //primeti da postoji HashMap i u scala.collecttion.mutable i u .immutable !!
    val utakmice = new mutable.HashMap[String, (Float, Float, Float, Char)]()
    while(sc1.hasNextLine()){
      //oznacicemo da utakmica jos nije odigrana sa '-'
      utakmice.put( sc1.nextLine(), (sc1.nextFloat(), sc1.nextFloat(), sc1.nextFloat(), '-') )
      sc1.nextLine()   //procitamo \n koji se nalazi nakon poslednje kvote u redu da bi se lepo procitao sledeci podatak
    }

    val kladionicari = new ArrayBuffer[Kladionicar]
    while(sc2.hasNext()){
      val ime = sc2.next()
      val novac = sc2.nextInt()
      val tiket = new mutable.HashMap[String, Char]()
      for (i<- 0 until 5){
        sc2.nextLine()   //nakons to se procita novac mi nismo pozicionirani na pocetak reda sa imenom utakmice, pa moramo da procitamo i taj \n
        tiket.put(sc2.nextLine(), sc2.next()(0)  )
      }
      kladionicari.append(new Kladionicar(ime, novac, tiket, utakmice))
    }

    for(k<-kladionicari)
      k.start()

    println("utakmice se trenutno igraju")
    Thread.sleep(5000)

    val res = Array('1','x','2')
    for (u <- utakmice)
      //u mapu utakmica sada upisujemo za svaki kljuc, value koji je cetvorka gde su prva tri elementa ista kao do sada
      //a cetvrti element nasumicno biramo iz niza res
      //u mapi ._1 je kljuc a ._2 je value, a u value mozemo da ulancamo jos tih ._ jer je u pitanju torka
      //primeti da ideksiranje krece od 1
      utakmice(u._1) = (u._2._1,  u._2._2,  u._2._3, res(ThreadLocalRandom.current().nextInt(0,3)) )

    //obavestavamo sve niti
    //upromenljiva utakmice je promenljiva na kojoj su zakljucani sve niti, tako da ovde u synchronized bloku
    //pozivamo metod notifyAll() koji obavestava sve niti da mogu da nastave sa izvrsavanjem. postoji i metod .notify()
    //koji c epo nekoj heuristici obavestiti samo jednu nit
    utakmice.synchronized{
      utakmice.notifyAll()
    }

    //nakon sto se u mainu obaveste niti da mogu da nastave sa radom, potrebno je i da ih sacekamo da zavrse
    for(k<-kladionicari)
      k.join()

    var isplata : Float = 0
    for(k<- kladionicari) {
      isplata += k.getZarada()
      println(s"${k.getIme()} ceka na isplatu ${k.getZarada()} dinara")
    }

    println(s"kladiopnica ukupno isplacuje $isplata dinara")
  }
}
