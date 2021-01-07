import org.apache.spark.{SparkConf, SparkContext}

object mainLog {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("MYAPP").setMaster("local[4]").set("spark.testing.memory","2147480000")
    val ctx = new SparkContext(conf)

    val poruke = ctx.textFile("log.txt")
        .filter(linija => (linija.startsWith("[warn]")) || (linija.startsWith("[error]")) ||(linija.startsWith("[info]")) && linija.contains("java") )
        .map(linija => {
          val niz = linija.split(" ")
          (niz(0), niz.drop(1).mkString(" "))
        })
        .groupByKey()
        .map(par => (par._1, par._2.size))
        .collect()

    ctx.stop()

    poruke.foreach( par=>println(par._1 + ": " + par._2) )
  }
}
