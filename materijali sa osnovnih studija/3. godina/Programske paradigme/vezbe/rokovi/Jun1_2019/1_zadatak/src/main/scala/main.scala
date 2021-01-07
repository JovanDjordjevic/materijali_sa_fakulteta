import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentLinkedQueue

class Pretrazivac(id_niti : Int, rec : String, putanje : ConcurrentLinkedQueue[String]) extends Thread{
  override def run(){
    while(!putanje.isEmpty()){
      putanje.synchronized {
        val tekuca = putanje.poll()
        if (tekuca == null) return
        val tmp_scanner = new Scanner(new File(tekuca))
        var broj_linija = 0
        var found = false
        while (tmp_scanner.hasNext()) {
          val linija = tmp_scanner.nextLine()
          broj_linija += 1
          if (linija.contains(rec)) {
            found = true
            println(s"$rec se nalazi u $broj_linija liniji u fajlu $tekuca")
          }
        }
        if (!found) println(s"fajl $tekuca ne sadrzi rec")
        println(s"nit $id_niti je zavrsila")
      }
    }
  }
}

object main {
  def main(args : Array[String]) : Unit = {
    val sc = new Scanner(System.in)

    println("unesi rec za pretragu")
    val rec = sc.next()

    val sc1 = new Scanner(new File("fajlovi.txt"))
    val putanje = new ConcurrentLinkedQueue[String]
    while(sc1.hasNext()){
      putanje.add(sc1.nextLine)
    }

    println("unesi broj niti")
    val n = sc.nextInt()
    if(n > putanje.size()){
      println("broj niti nije validan")
      System.exit(1)
    }

    val pretrazivaci = new Array[Pretrazivac](n)
    for(i <- 0  until n){
      pretrazivaci(i) = new Pretrazivac(i+1, rec, putanje)
    }

    for(i<-0 until n){
      pretrazivaci(i).start()
    }
    for(i<-0 until n){
      pretrazivaci(i).join()
    }


  }
}
