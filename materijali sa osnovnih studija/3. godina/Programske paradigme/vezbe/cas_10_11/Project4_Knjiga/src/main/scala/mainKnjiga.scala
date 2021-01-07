import org.apache.spark.{SparkConf, SparkContext}

object mainKnjiga {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("myapp").setMaster("local[4]").set("spark.testing.memory","21474890000")
    val ctx = new SparkContext(conf)

    //na kraju upisujemo u fajl tako da niz operacija koju izvrsavamo ovde nema povratnu vrednost
    ctx.textFile("knjiga.txt")
      .flatMap(linija => linija.split(" "))    //sad smo od knjige napravili listu svih reci
      .map( rec => (rec, 1))        //sad smo od svake reci napravili par sa 1(trenutni broj pojavljivanja)
      .reduceByKey( (_+_) )        //ReduceByKey radi reduce ali po kljucevima, znaci nama ce se reducovati svi parovi sa isitm prvim elementom u jedan par i tako za sve razlicite reci
      .sortBy( par => par._1 )     //sortiramo, moglo je i sortByKey(), onda nebi navodili sami par._1
      .saveAsTextFile("BrojPojavljivanja")   //ova funkc pravi FOLDER BrojPojavljivanja, a ne jedan fajl i u tom folderu cuva pouno fajlova, po jedan za svaki deo koji spark za nas dodeli nekom racunaru u klasteru

    ctx.stop()
  }
}
