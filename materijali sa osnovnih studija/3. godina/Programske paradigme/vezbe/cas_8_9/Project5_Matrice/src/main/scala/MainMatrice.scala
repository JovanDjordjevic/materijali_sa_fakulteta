import java.util.Scanner
import java.io.File
import java.io.PrintWriter

class Mnozilac (vrsta1 : Array[Int], matrica2 : Array[Array[Int]], rezultat : Array[Int]) extends Thread{
  val m : Int = vrsta1.length
  val k : Int = rezultat.length

  override def run() {
    for(i<- 0 until k)
      rezultat(i) = SkProizvod(i)
  }

  def SkProizvod(j : Int) : Int = {
    var res : Int = 0
    for (i<- 0 until m)
      res += vrsta1(i) * matrica2(i)(j)

    return res
  }
}


object MainMatrice {
  def main(args : Array[String]) : Unit = {
    val sc1 : Scanner = new Scanner(new File("/home/student/Desktop/pp_vezbanje_novo/cas_8_9/matrica1.txt"))
    val sc2 : Scanner = new Scanner(new File("/home/student/Desktop/pp_vezbanje_novo/cas_8_9/matrica2.txt"))
    //PrintWriter je java klasa za upis u fajl (?)
    val pw : PrintWriter = new PrintWriter(new File("/home/student/Desktop/pp_vezbanje_novo/cas_8_9/rezultat.txt"))

    //(n x m1) * (m2 x k) = (n x k) ako m1==m2
    val n : Int = sc1.nextInt()
    val m1 : Int = sc1.nextInt()

    val m2 : Int = sc2.nextInt()
    val k : Int = sc2.nextInt()

    if(m1 != m2){
      println("greska u dimenzijama")
      return
    }

    //u klasi Array imamo metod .ofDim[tip](dimenzija1, dimenzija2) koji pravi matricu (?)
    val matrica1 = Array.ofDim[Int](n,m1)
    val matrica2 = Array.ofDim[Int](m2,k)
    val rezultat = Array.ofDim[Int](n,k)

    //ucitavanje
    for(i<- 0 until n)
      for(j <- 0 until m1)
        matrica1(i)(j) = sc1.nextInt()

    for(i<- 0 until m2)
      for(j <- 0 until k)
        matrica2(i)(j) = sc2.nextInt()

    //print provera()
    /*for(i<- 0 until n) {
      for(j <- 0 until m1)
        print(matrica1(i)(j) +" ")
      println()
    }

    for(i<- 0 until m2) {
      for (j <- 0 until k)
        print(matrica2(i)(j) + " ")
      println()
    }*/

    val mnozioci= new Array[Mnozilac](n)
    for (i<- 0 until n)
      mnozioci(i) = new Mnozilac(matrica1(i), matrica2, rezultat(i))

    for (i<-0 until n)
      mnozioci(i).start()

    //posto za razliku od proslog zadatka, posle pokretanja threadova imamo jos neke operacije u mainu koje zavise od rezultata tih threadova
    //potrebno je da sacekamo da se threadovi zavrse da nebi imali zombi procese, to radimo sa .join() !!
    for(i<- 0 until n)
      mnozioci(i).join()

    //ispisujemo u nasu datoteku
    pw.append(s"$n $k\n")
    for(i<- 0 until n) {
      for (j <- 0 until k)
        pw.append(s"${rezultat(i)(j)} ")
      pw.append("\n")
    }
    pw.close()

  }
}
