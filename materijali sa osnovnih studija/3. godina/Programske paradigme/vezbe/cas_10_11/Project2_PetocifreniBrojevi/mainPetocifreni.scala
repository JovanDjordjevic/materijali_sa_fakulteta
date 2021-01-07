import org.apache.spark.{SparkConf, SparkContext}

object mainPetocifreni {
  def main(args: Array[String]): Unit = {

    val conf = new SparkConf().setAppName("myApp").setMaster("local[4]").set("spark.testing.memory","471859200")

    val ctx = new SparkContext(conf)

    //metod .textFile procita sve iz fajla koji prosledimo i vrati RDD od stringova iz tog fajla
    val datRDD = ctx.textFile("brojevi.txt")

    //posto u RDDu imamo stringove, dovoljno je da filtriramo samo one koji su duzine 5, ne moramo uopste da kastujemo u int
    val brojPetocifrenih = datRDD.filter(x => x.length == 5)
                                 .count()   //prebrojava koliko elemenata ima u nasem RDD i vraca Long!!
    ctx.stop()

    println(brojPetocifrenih)
  }
}
