import org.apache.spark.{SparkConf, SparkContext}

object mainSkalarniProizvod {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("myApp").setMaster("local[4]").set("spark.testing.memory","2147380000")
    val ctx = new SparkContext(conf)

    //ne mzoemo kao u proslom zadatku samo .textFile jer on vraca stringove, a nama su koordinate vektora odvojene zarezom,
    //tako da moramo da pozovemo nekakvu split funckiju. Ako bismo imali u fajlu npr prvih nekoliko koordinata u jednom
    //a ostatak kootdinata u drugom redu, nakon splita koji radi za svaku liniju dobili bismo listu sa dve liste u sebi
    //[[prve_koord],[druge_koord]], a zelimo  da imamo samo listu [sve__koord], tako da umesto map funckije koristimo flatMap
    //koja nakon mapiranja funkcije, sve iz njenog rezultata smesta u jedan niz
    //flatMap ce nam vratiti RDD u kom su stringovi tako da je potrebno da ih mapiramo u intove da bismomogli da racunamo
    val v1RDD = ctx.textFile("vektor1.txt")
                   .flatMap(linija => linija.split(", "))
                   .map(s => s.toInt)

    val v2RDD = ctx.textFile("vektor2.txt")
                   .flatMap(_.split(", "))      //kraca sintaksa, uvedemo wildcard _ i nad njim vrsimo operaciju
                   .map(_.toInt)

    //da bi svaki racunar iz klastera imao pristup paru elemenata na datom indeksu, zipujemo ove dve RDD liste
    //mogli smo i sum() umesto reduce, ali hteo je da nam pokaze i ovo
    //primeti da je a u reduce akumulator a b je tekuca vrednost iz niza, nije par, jer nakon map nemamo vise parove
    val sp = v1RDD.zip(v2RDD)
                  .map(par => par._1 * par._2)
                  .reduce( (a,b)=> a+b )          //mogla je i kraca sintaksa,  .reduce( (_+_) )
    ctx.stop()

    println(sp)
  }
}
