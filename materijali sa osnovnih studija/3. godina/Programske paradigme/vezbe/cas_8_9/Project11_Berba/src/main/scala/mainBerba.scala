import java.io.File
import java.util.Scanner
import java.util.concurrent.{ConcurrentHashMap, ConcurrentLinkedDeque, ConcurrentLinkedQueue, ThreadLocalRandom}

class Student(drvoredi : ConcurrentLinkedQueue[(String, Int)], skladiste : ConcurrentHashMap[String, Int]) extends Thread{
  override def run(): Unit = {

    while( !drvoredi.isEmpty() ){
      var tmp = drvoredi.poll()
      for(i<- 0 until tmp._2){
        val obrano = ThreadLocalRandom.current().nextInt(30,50)
        skladiste.synchronized {
          skladiste.replace(tmp._1, skladiste.get(tmp._1) + obrano)
        }
      }
    }

    println("student zavrsio sa radom")
  }
}

object mainBerba {
  def main(args: Array[String]): Unit = {

    val sc1 : Scanner = new Scanner(new File("/home/student/Desktop/pp_vezbanje_novo/cas_8_9/drvoredi.txt"))
    val sc2 : Scanner = new Scanner(System.in)
    println("unesi broj studenata")
    val brStudenata = sc2.nextInt()

    val skladiste = new ConcurrentHashMap[String, Int]()
    val drvoredi = new ConcurrentLinkedQueue[(String, Int)]()

    skladiste.put("tresnje", 0)
    skladiste.put("kajsije", 0)
    skladiste.put("kruske", 0)
    skladiste.put("sljive", 0)

    while(sc1.hasNext()){
      drvoredi.add( (sc1.next(), sc1.nextInt()) )
    }

    val niti = new Array[Student](brStudenata)
    for(i<- 0 until brStudenata)
      niti(i) = new Student(drvoredi, skladiste)

    for(i<- 0 until brStudenata)
      niti(i).start()
    for(i<- 0 until brStudenata)
      niti(i).join()

    println(s" tresnje: ${skladiste.get("tresnje")}")
    println(s" kajsije: ${skladiste.get("kajsije")}")
    println(s" kruske: ${skladiste.get("kruske")}")
    println(s" sljive: ${skladiste.get("sljive")}")
  }
}
