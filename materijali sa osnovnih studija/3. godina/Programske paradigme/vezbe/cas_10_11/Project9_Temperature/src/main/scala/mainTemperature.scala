
import org.apache.spark.{SparkConf, SparkContext}

import scala.compat.Platform

object mainTemperature {
  def main(args : Array[String]) : Unit = {
    val conf = new SparkConf().setAppName("myapp").setMaster("local[4]").set("spark.testing.memory","2147480000")
    val ctx = new SparkContext(conf)

    ctx.textFile("temperature.txt")
        .map(linija =>{
          val niz = linija.split("")
          //primetimo da hocemo godinu kao kljuc i da koristimo niz(3) zato sto ako pogledamo u fajlu, na poceku imamo prazan stering u svakom redu, jer red pocinje razmakom
          //hocemo i da temperaturu imamo odmah kao broj pa mozemo odmah da konvertujemo ovde
          ( niz(3), (niz(1), niz(2), niz(4).toFloat) )
        })
        //ovaj zadatak smo mogli kao do sad sa groupBYKey pa .map itd... ali imamo   i funkciju koja objedinjeje sve to
        //ne razumem bas sta je uradio ovde, vidi na githubu
        .aggregateByKey((0.0, 0))((ak, vr) => (ak._1 + vr._3 , ak._2 + 1 ),
                        (a1 ,a2) => (a1._1 + a2._1, a1._2 + a2._2))
        .sortByKey()
        .collect()
        .foreach(p => println(p._1 +" " + p._2))


    ctx.stop()

  }
}
