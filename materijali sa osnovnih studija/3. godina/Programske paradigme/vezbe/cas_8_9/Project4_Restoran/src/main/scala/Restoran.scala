import java.util.Scanner
import java.util.concurrent.ThreadLocalRandom

//da bismo napravili nit:
// I nacin:  moramo da napravimo klasu koja nasledjuje klasu Thread i da u njoj
//           imeplementiramo metod run(), koji se izvrsava kada nasa instanca dobije procesorsko vreme (tj u mainu se pozove metod .start())
// II nacin: nasa klasa mora da implementira interfejs Runnable i tu da implementira metod run()
//           i onda uy mainu (?) moramo da napravimo instancu Thread kojij u konstruktoru prosledimo nasu klasu (?): Thread(class instance)

class Konobar(ime : String, brStolova : Int) extends Thread{
  override def run() : Unit = {
    for(i <- 0 until brStolova){
      //usluga stola i
      //u zadatkus e trazi da pozovemo sleep kao simulaciju uzluzivanja. Thread.sleep() prima arg u milisekundama
      //hocemo da bude random izmedju 1 i 3 sekundi,  ThreadLocalRandom.current() vraca random objekat jedinstven na nivou niti
      // i u njemu imamo metod nextInt() koji prima gornju i donju granicu random broja,
      // na kraju to mnozimo sa 1000 posto nam treba u milisekundama
      Thread.sleep( ThreadLocalRandom.current().nextInt(1,3)*1000)
      println(s"konobar $ime je usluzio sto $i")
    }
    println(s"konobar $ime je zavrsio smenu")
  }
}

object Restoran {
  def main(args : Array[String]) : Unit = {
    println("======restoran=======")

    val sc : Scanner = new Scanner(System.in)
    println("unesi br stolova")
    val brStolova : Int = sc.nextInt()

    //hocemo da podelimo ravnomenrno na 5 konobara,   .toInt je cast u integer
    val korak = Math.ceil(brStolova/5.0).toInt

    val milan = new Konobar("Milan", korak)
    val ivan = new Konobar("Ivan", korak)
    val rastko = new Konobar("Rastko", korak)
    val nemanja = new Konobar("Nemanja", korak)
    val strahinja = new Konobar("Strahinja", brStolova-4*korak)

    //pokretanje threadova, posto radimo I nacin, ovde pozivamo .start()

    milan.start()
    ivan.start()
    rastko.start()
    nemanja.start()
    strahinja.start()
  }
}
