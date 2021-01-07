import org.apache.spark.{SparkConf, SparkContext}

object mainIksOks {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("myapp").setMaster("local[4]").set("spark.testing.memory","2147480000")
    val ctx = new SparkContext(conf)

    val fileRDD = ctx.textFile("partije.txt")
        //uzmemo prvi element torke indikator pobede prvog igraca, i onda tri clana koji nam govore o broju x, o, b
        .map(s => ( s.last.equals("W"), s.count(_.equals("x")),s.count(_.equals("o")),s.count(_.equals("b"))  ) )
        .cache()

    val rez1 = fileRDD.filter( t => t._1 == true).count() /fileRDD.count().toDouble * 100.0
    val rez2 = fileRDD.filter(t => t._1 == true && t._4 == 0).count()
    val rez3 = fileRDD.filter(t => t._1 == true && t._2 > 3).count()

    ctx.stop()

    println(rez1)
    println(rez2)
    println(rez3)

  }
}
