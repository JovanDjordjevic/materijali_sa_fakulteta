import org.apache.spark.{SparkConf, SparkContext}

object main {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("myapp").setMaster("local[4]")
    val ctx = new SparkContext(conf)

    var podaciRDD = ctx.textFile("biostats.csv")
      .map(linija => {
        val niz = linija.split(",")
        (niz(0), niz(1), niz(2), niz(3).toDouble,niz(4).toDouble)
      })
      .cache()

    var muskarci = podaciRDD
      .filter(t => t._2.equals("muski"))
      .map( t => t._5 * 0.45359237)

    val prosecna_tezina = muskarci.sum() / muskarci.count()

    var zene = podaciRDD
      .filter(t => t._2.equals("zenski"))
      .map( t => t._4 * 2.54)

    val prosecna_visina = zene.sum() / zene.count()

    ctx.stop()

    println(s"F: $prosecna_visina")
    println(s"M: $prosecna_tezina")

  }
}
