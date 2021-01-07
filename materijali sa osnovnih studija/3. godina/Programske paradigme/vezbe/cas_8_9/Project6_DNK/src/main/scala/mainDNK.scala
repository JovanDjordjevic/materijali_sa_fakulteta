import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentHashMap
import scala.collection.mutable.ArrayBuffer

//brojac ce biti klasa koja ce uzeti indeks pocetka i krajja niza linija iz nase datoteke i prebrojavati ATGC i ubaciti u mapu
class Brojac(poc : Int, kraj : Int, linije : ArrayBuffer[String], mapaKaraktera : ConcurrentHashMap[Char, Int]) extends Thread{
  //uzimamo linije [poc, kraj)
  override def run() : Unit = {
    for(i <- poc until kraj){
      //count zahteva funck koja slika char u bool, ovaj izraz sa _ je skracena lambda funkc (_ je zapravo argument lambda funkc)
      // koja tekuci char u liniji poredi sa odgovarajucim slovom
      val a : Int = linije(i).count( _=='a' )
      val g : Int = linije(i).count( _=='g' )
      val c : Int = linije(i).count( _=='c' )
      val t : Int = linije(i).count( _=='t' )

      //ConcurrentHashMap predstavlja implementaciju hash mape gde tacno jedna nit u sito vreme moze da pristupi mapi
      //ALI mapa ne garantuje pravilno izvrsavanje kada se preklapaju operacija citanja i pisanja, tj kada jedna nit cita a druga pise
      //od toga se stitimo tako sto koristimo sinhornizaciju za kriticnu sekciju sa   staSinhronizujemo.synchronized{ naredbe }
      mapaKaraktera.synchronized {
        //replace menja vrednost za dati key sa necim drugim
        //ovde procitamo iz mape koliko trenutno u njoj ima pojavljivanja za 'a', na to dodamo onoliko koliko smo sad procitalui u petlji iznad
        //i to ubacimo u replace funkc
        mapaKaraktera.replace('a', mapaKaraktera.get('a') + a)
        mapaKaraktera.replace('g', mapaKaraktera.get('g') + g)
        mapaKaraktera.replace('c', mapaKaraktera.get('c') + c)
        mapaKaraktera.replace('t', mapaKaraktera.get('t') + t)
      }
    }
  }
}


object mainDNK {
  def main(args : Array[String]) : Unit = {
    println("===== dnk counter =======")

    val sc1 : Scanner = new Scanner(new File("/home/student/Desktop/pp_vezbanje_novo/cas_8_9/bio_podaci.txt"))
    val sc2 : Scanner = new Scanner(System.in)

    println("unesi br niti:")
    //ako nam trebaju neke informacije o trenutnom sistemu tokom izvrsavanja te podatke vadimo iz Runtime.getRuntime()...
    println("broj procesora na sistemu je: " + Runtime.getRuntime.availableProcessors())
    val brojNiti = sc2.nextInt()

    val brojaci = new Array[Brojac](brojNiti)
    //linije iz fajla ucitavamo u ArrayBuffer, to je niz promenljive duzine, mogli smo i da prvo prebrojimo linije
    //u fajlu i onda da uradimo Array[String](broj_linija) ali ovako je lepse i brze
    val linije = new ArrayBuffer[String]()

    while(sc1.hasNextLine())
      linije.append(sc1.nextLine())

    val n : Int = linije.length
    println(s"broj linija u fajlu:  $n")

    //konstruktor za cocnurrent hash map prima 3 argumenta:
    //1) pocetni kapacitet
    //2) loadFActor (?)
    //3) concurency level tj broj niti koji ce da pristupa toj mapu konkurento (?)
    val mapaKaraktera = new ConcurrentHashMap[Char, Int](4, 4,brojNiti)
    mapaKaraktera.put('a', 0)
    mapaKaraktera.put('g', 0)
    mapaKaraktera.put('c', 0)
    mapaKaraktera.put('t', 0)

    val korak : Int = Math.ceil(n.toDouble / brojNiti.toDouble).toInt

    //inicijalizujemo brojace, za kraj moramo uzeti minimum izmedju onoga sto se izracuna sa (i+1)*korak i
    //broja linija u datoteci, dakle da se zastitimo od mogucih gresaka u prekoracenju u zavisnosti koliko niti korisnik izabere
    for(i <- 0 until brojNiti)
      brojaci(i) = new Brojac(i*korak, Math.min((i+1)*korak, n), linije, mapaKaraktera)

    for(i <- 0 until brojNiti)
      brojaci(i).start()

    for(i <- 0 until brojNiti)
      brojaci(i).join()

    //pro tip za debagovanje, pokrenemo aplikaciju sa 1 niti da bismo videli tacan rezultat!
    println("Count baza:")
    println("a: " + mapaKaraktera.get('a'))
    println("g: " + mapaKaraktera.get('g'))
    println("c: " + mapaKaraktera.get('c'))
    println("t: " + mapaKaraktera.get('t'))
  }
}
