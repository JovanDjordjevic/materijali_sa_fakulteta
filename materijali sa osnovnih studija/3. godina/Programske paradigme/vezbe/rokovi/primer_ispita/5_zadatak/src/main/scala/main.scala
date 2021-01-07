import org.apache.spark.{SparkConf, SparkContext}

object main {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setMaster("local[4]").setAppName("5_zadatak")
    val ctx = new SparkContext(conf)

    val dataRDD = ctx.textFile("insurance.csv")
        .filter(linija => !linija.contains("geo_sirina"))
        .map( linija => {
          val niz = linija.split(',')
          (niz(0).toInt, niz(1), niz(2), niz(3).toFloat, niz(4).toFloat, niz(5), niz(6)  )
        })
        .filter(t => t._3.equals("PALM BEACH COUNTY") && t._6.equals("Residential") && t._7.equals("Wood"))
        .cache()

    val x = dataRDD
        .map(t => (t._4))
        .sum()

    val y = dataRDD
      .map(t => (t._5))
      .sum()

    val n = dataRDD.count()

    ctx.stop()

    println(x/n, y/n)

  }
}
