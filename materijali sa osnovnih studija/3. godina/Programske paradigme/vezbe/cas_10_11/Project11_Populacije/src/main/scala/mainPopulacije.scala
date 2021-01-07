import org.apache.spark.{SparkConf, SparkContext}

object mainPopulacije {
  val conf = new SparkConf().setAppName("myapp").setMaster("local[4]").set("spark.testing.memory","2147480000")
  val ctx = new SparkContext(conf)

  val rez = ctx.textFile("populacije.csv")
      .map(linija => linija.split("\"?,\"?"))
      .map(arr => (arr(2), (arr(3).toDouble*1000, arr(4).toDouble*1000, arr(5).toDouble*1000, arr(6).toDouble*1000, arr(7).toDouble*1000) ) )
      //sad imamo par ( region, (torka sa 6 clanova gde su populacije po godinama)  )
      .reduceByKey( (acc, t) => (acc._1 + t._1, acc._2 + t._2, acc._3 + t._3, acc._4 + t._4, acc._5 + t._5 ) )
      .sortByKey()
      .map(t => (t._1, (t._2._1.toInt, t._2._2.toInt, t._2._3.toInt, t._2._4.toInt, t._2._5.toInt, ) ))
      .collect()

  ctx.stop()

  rez.foreach( t => println(t) )
}
