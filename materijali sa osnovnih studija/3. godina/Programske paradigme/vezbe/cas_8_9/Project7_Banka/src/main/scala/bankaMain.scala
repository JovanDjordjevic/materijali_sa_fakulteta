import java.io.File
import java.util.Scanner
import java.util.concurrent.{ConcurrentLinkedQueue, ThreadLocalRandom}
import java.util.concurrent.atomic.AtomicLong


class Klijent(ime : String, pozajmica : Int){
  var dug : Float = 0

  def getIme() : String = { return ime }
  def getPozajmica() : Int = { return pozajmica }
  def getDug() : Float = { return dug }
  def setDug(dug : Float) : Unit = { this.dug = dug }
}

  class Sluzbenica(kamata : Float, kapital : AtomicLong, redKlijenata : ConcurrentLinkedQueue[Klijent], zaduzeniKlijenti : ConcurrentLinkedQueue[Klijent]) extends Thread{
  override def run() : Unit = {
    while(true){
      val k : Klijent = redKlijenata.poll()
      //poll vrati null ako nema klijenata pa tu izlazimo iz niti
      if( k == null) return

      println(s"klijent ${k.getIme()} razgovara sa sluzbenicom")
      //spavanje niti simulira razgovor sluzbenice i klijenta
      Thread.sleep(ThreadLocalRandom.current().nextInt(1,5)*1000)

      //obavezno moramo sinhronizovati deo koji je kriticna sekcija, iako je kapital AtomicLong, on ne
      //moze sam da nas zastiti od npr slucaja da jedna sluzb1 procita vrednost, pa sluzb2 procita vrednost
      //i onda sluzb1 azurira vrednost, tada bi sluzb2 potencijalno radila sa neispravnom vrednoscu
      kapital.synchronized {
        if (k.getPozajmica() > kapital.get())
          println(s"klijent ${k.getIme()} ne moze dobiti pozajmicu")
        else {

          k.setDug(k.getPozajmica() * (100 + kamata.toFloat) / 100)
          val novKapital = kapital.get() - k.getPozajmica()
          kapital.set(novKapital)
          println(s"klijent ${k.getIme()} je dobio kredit u iznosu od ${k.getPozajmica()}, duzan je ${k.getDug()}")
          zaduzeniKlijenti.add(k)
        }
      }
    }
  }
}


object bankaMain {
  def main(args : Array[String]) : Unit = {
    println("=====banka=====")

    val sc1 : Scanner = new Scanner(System.in)

    //posto ce sluzbenice (to su niti) pristupati istoj vrednosti kapitala, tj to ce biti kriticna sekcija,
    //nije dovoljno korsititi standardni long, vec mora Atomic Long  (slicno i za ostale tipove podataka)
    //nad ovakvim vrednostima sve operacije su atomicne, imamo metode:
    // .get() - dohvata vrednost koja se nalazi trenutno u tom atomic longu
    // .set(v) - psotavlja vrednost
    // .getAndAdd(v) - dodaje (+) v na tekucu vrednost i vraca vrednost PRE uvecanja
    // .addAndGet(v) - obrnuto
    // .getAndIncrement()  .incrementAndGet()  .getAndDecrement()  .decrementAndGet
    // .compareAndSet(expected_val, new_val) - postavlja new_value ako je stara vrednost = expected_value
    println("pocetni kapital banke: ")
    val kapital = new AtomicLong( sc1.nextLong() )

    //posto je kapital objekat a ne vrednost jer smo koristili AtomicLong
    val sacuvaniKapital : Float = kapital.get()

    println("unesi kamatnu stopu")
    val kamata : Float = sc1.nextFloat()

    println("broj sluzbenica")
    val sluzbeniceBr : Int = sc1.nextInt()

    //posto se i redu klijenata pristupa iz vise niti, koristimo ConcurrentLinkedQueue, tu imamo metode:
    // .add(e)  - dodaje e na kraj
    // .poll()  - vraca element sa pocetka reda
    // .peek()  - vrati element sa pocetka reda ali ga ne izbaci iz reda
    // .remove(e) - skida element e iz reda(znaci vrati ga i izbaci ga)
    // .isEmpty() - da li je prazan
    val sc2 : Scanner = new Scanner(new File("/home/student/Desktop/pp_vezbanje_novo/cas_8_9/red_klijenata.txt"))
    val redKlijenata = new ConcurrentLinkedQueue[Klijent]()
    //prvimo jos jedan red u koji stavljamo zaduzene da bi na kraju mogli da saveremo profit banke
    val zaduzeniKlijenti = new ConcurrentLinkedQueue[Klijent]()

    while(sc2.hasNext())
      redKlijenata.add(new Klijent(sc2.next(), sc2.nextInt()))

    val sluzbenice = new Array[Sluzbenica](sluzbeniceBr)
    for (i<-sluzbenice.indices) //mogli smo i standardnu for pelju, ovo indices vraca Range objekat svih indeksa niza
      sluzbenice(i) = new Sluzbenica(kamata,kapital, redKlijenata, zaduzeniKlijenti)

    for(sluzbenica <- sluzbenice)
      sluzbenica.start()

    for(sluzbenica <- sluzbenice)
      sluzbenica.join()

    //na kraju obracun
    var dug : Float = 0
    //treba koristiti iterator kada iteriramo kroz kolekciju (?)
    val iterator = zaduzeniKlijenti.iterator()
    while(iterator.hasNext())
      dug += iterator.next().getDug()

    println(s"zarada nase banke $dug, ostalo kapitala: ${kapital.get()}") //${dug - sacuvaniKapital}")
  }

}
