import org.apache.spark.{SparkConf, SparkContext}

object mainProcesi {
  def main(args : Array[String]) : Unit = {
    val conf = new SparkConf().setAppName("myapp").setMaster("local[4]").set("spark.testing.memory","2147480000")
    val ctx = new SparkContext(conf)

    val fileRDD = ctx.textFile("procesi.txt")
                     .map(linija => linija.split("\\s*,\\s*"))

    val sviProcesi = fileRDD
        .map(parts => (parts(1).toInt, parts(2).toInt))
        .reduce( (acc,v) => (acc._1 + v._1, acc._2 + v._2) )

    val sistemskiProcesi = fileRDD
      .filter( linija => linija.length > 3 )                  //jer sistemski imaju dodatnu oznaku sys
      .map(parts => (parts(1).toInt, parts(2).toInt))
      .reduce( (acc,v) => (acc._1 + v._1, acc._2 + v._2) )

    ctx.stop()

    println(sviProcesi)
    println(sistemskiProcesi)
  }
}
