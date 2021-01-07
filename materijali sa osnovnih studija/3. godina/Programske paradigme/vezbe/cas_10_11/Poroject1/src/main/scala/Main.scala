import org.apache.spark.{SparkConf, SparkContext}

object Main {
  def main(args: Array[String]): Unit = {

    //pravimo spark context objekat, prvo napravimo ovako konfigurisemo neke parametre
    var conf = new SparkConf()
      .setAppName("moja_aplikacija")  //ime
      .setMaster("local[4]")          //ovo je master url, tj adresa klastera. ako prosledimo "local[broj]" za nas ce biti simuliran klaster sa 4 racunara
      .set("spark.testing.memory","2147360000")

    //onda taj conf proseldimo ovde za kreiranje objekta
    val ctx = new SparkContext(conf)

    println("unesi n")
    //mozemo ovako a mozemo i standardno sa Scanner objektom
    val n = scala.io.StdIn.readInt()

    val niz = (2 to n by 2).toArray

    //RDD - Resilinet Distributed Dataset, to je dataset otporan na neke probleme dostrobuiranog izvrsavanja
    //RDD i context za nas simuliraju rad sa klasterom, tj oni sami dele nas dataset na parcice i rasporedjuju koji racunar sta radi,
    //mi uospte ne mroamo da se bavimo time
    // to pravimo od kolekcije(ili cega vec) nad kojim zelimo da vrsimo distribuirane operacije
    // tako sto nad nasim spark context objektom pozovemo parallelize() metod
    val nizRDD = ctx.parallelize(niz)

    //sad nad ovim RDD-om mozemo da radimo map,filter,take,zip itd da transformisemo dataset u ono sto na treba
    //te sve operacije takodje vracaju neki novi RDD tako da ih mozemo ulancavati. primetimo da se ove transformacije izvrsavaju lenjo,
    //dakle tek kad nad RDD-om pozovemo neku akciju kao sto je npr collect(), tek tad se ivrsavaju transformacije, dakle do trenutka poziva akcije
    //sve ove ulancane transformacije u O(1)
    val rez = nizRDD.map(x => x*x)
                    .collect()        //collect od transformisanog dataseta pravi neki niz, posto je to poslednja stvar koja se izvrsava, rezultat ce biti neki Array[] i to cuvamo u promenljivu

    //mogli smo ovde npr umesto collect da stavimo .take(10) ako hocemo prvih 10 kvadrata, to odmah vraca Array[] tako da posle toga ne moramo da pozivamo collect

    //sad kada smo zavrsili sa kontekstom i u memoriji imamo izvucene podatke u rez, mozemo da prekinemo kontekst
    ctx.stop()

    println( rez.mkString(", "))
  }
}
