import java.io.File
import java.util.Scanner
import java.util.concurrent.ThreadLocalRandom

class Ucesnik(ime : String, cena : Int, dobitnici: Array[String]) extends Thread{
  def getIme() : String = {return ime}

  override def run(): Unit = {
    dobitnici.synchronized{
      dobitnici.wait()
    }

    for(d <- dobitnici){
      if(d == ime){
        println(s"$ime je dobitnik, karta mu je kostala $cena a sad kosta ${cena*0.8}")
        return
      }
    }

  }
}

object mainTuristicka {
  def main(args: Array[String]): Unit = {
    val sc1 : Scanner = new Scanner( new File("/home/student/Desktop/pp_vezbanje_novo/cas_8_9/ucesnici.txt") )

    var dobitnici = new Array[String](5)
    val brUcesnika = sc1.nextInt()
    val ucesnici = new Array[Ucesnik](brUcesnika)

    for(i<- 0 until brUcesnika)
      ucesnici(i) = new Ucesnik(sc1.next() + " " + sc1.next(), sc1.nextInt(), dobitnici)

    for(i<- 0 until brUcesnika)
      ucesnici(i).start()

    println("izvlacenje u toku")
    Thread.sleep(3000)

    dobitnici.synchronized{
      val izvuceni = ThreadLocalRandom.current().ints(0, brUcesnika).distinct().limit(5).toArray
      for (j<-0 until izvuceni.length)
        dobitnici(j) = ucesnici( izvuceni(j) ).getIme()

      dobitnici.notifyAll()
    }

    for(i<- 0 until brUcesnika)
      ucesnici(i).join()
  }
}
