import org.apache.spark.{SparkConf, SparkContext}

object mainPreuzimanja {
  def main(args : Array[String]) : Unit = {
    val conf = new SparkConf().setAppName("myapp").setMaster("local[4]").set("spark.testing.memory","2147480000")
    val ctx = new SparkContext(conf)

    //.cache ne moramo da radimo, on radi kesiranje, tj cuvanje kod nas u memoriji, jer cemo vise puta pristupati ovom RDDu
    val preuzimanjaRDD = ctx.textFile("mavenLog.txt").cache()

    val zapoceta = preuzimanjaRDD.filter(linija => linija.startsWith("Downloading:")).count()
    val zavrsena = preuzimanjaRDD.filter(linija => linija.startsWith("Downloaded:")).count()

    ctx.stop()

    println("procenat zavrsenih: "+ (zavrsena*100)/zapoceta.toDouble )
  }
}
