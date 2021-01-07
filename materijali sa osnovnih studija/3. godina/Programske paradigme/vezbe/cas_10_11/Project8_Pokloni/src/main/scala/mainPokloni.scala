
import org.apache.spark.{SparkConf, SparkContext}

import scala.compat.Platform

object mainPokloni {
  def main(args : Array[String]) : Unit = {
    val conf = new SparkConf().setAppName("myapp").setMaster("local[4]").set("spark.testing.memory","2147480000")
    val ctx = new SparkContext(conf)

    val dobitnici = ctx.textFile("zaposleni.txt")
        .filter(linija => linija.contains("IT_PROG"))
        .map(linija =>{
          val niz = linija.split(" ")
          (niz(0), niz(1), niz(3))                //npr hocemo za svaku osobu iz IT sektora da izvucemo ime, prezime i username
        })
        .takeSample( false, 3, Platform.currentTime )        //takeSample odmah vraca niz, to je akcija,
                //argumenti za sample su: 1) da li isti moze vise puta   2)koliko elemenata biramo    3)seed za random brojeve

    ctx.stop()

    dobitnici.foreach(dobitnik => println(dobitnik._1 + " " + dobitnik._2 + " " + dobitnik._3 + " ") )
  }
}
