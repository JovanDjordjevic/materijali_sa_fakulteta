import java.io.File
import java.util.Scanner

class Brojac(datoteka : String) extends Thread{
  override def run(): Unit = {
    var brojac : Int = 0

    val path : String = "/home/student/Desktop/pp_vezbanje_novo/cas_8_9/" + datoteka
    val sc : Scanner = new Scanner(new File( path ))

    while(sc.hasNextInt()){
      val tmp = sc.nextInt()
      if( tmp >= 10000 && tmp<= 99999)
        brojac += 1
    }

    println(s"u datoteci $datoteka ima $brojac petocifrenih brojeva")
  }
}

object mainPetocifreni {
  def main(args : Array[String]) : Unit = {

    val sc : Scanner = new Scanner(System.in)
    println("unesi ime dve datoteke")

    val brNiti : Int = 2

    val niti : Array[Brojac] = new Array(brNiti)
    for(i<-0 until brNiti)
      niti(i) = new Brojac( sc.next() )

    for(i<-0 until brNiti)
      niti(i).start()
    for(i<-0 until brNiti)
      niti(i).join()

  }
}
