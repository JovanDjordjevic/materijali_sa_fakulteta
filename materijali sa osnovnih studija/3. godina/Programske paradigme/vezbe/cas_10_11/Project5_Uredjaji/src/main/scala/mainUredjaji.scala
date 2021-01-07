import java.io.{File, PrintWriter}

import org.apache.spark.{SparkConf, SparkContext}

object mainUredjaji {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("myapp").setMaster("local[4]").set("spark.testing.memory", "21474180000")
    val ctx = new SparkContext(conf)

    ctx.textFile("uredjaji.txt")
        .map(linija => {                          //ovako se radi viselinijska anonimna funckija
          val niz = linija.split("\\s+")
          (niz(0), niz.drop(1).mkString(" "))    //marka je prvi elem niza, pravimo par (prvi, sviOstali)
        })
        .groupByKey()       //sve torke se grupisu po kljuci,tj od svih Lenovo, dobijamo jedan par ("Lenovo", svi_drugi_elemnti_svih_lenovo_parova)
        .foreach(par => {
          val f = new PrintWriter( new File( par._1.toLowerCase() + ".txt" ))   //hocemo sve od jednog p[roizvodjaca da pisemo u jedan fajl, prvi clan torke je proizvodjac
          f.write("--- " + par._1 + " ===\n")
          par._2.foreach( t => f.append(t + "\n") )
          f.close()
        })

    ctx.stop()
  }
}
