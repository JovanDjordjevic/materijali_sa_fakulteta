import java.util.Scanner

class Sabirac(poc : Int, kraj : Int, v1 : Array[Float], v2 : Array[Float]) extends Thread{
  override def run(): Unit = {
    for (i<- poc until kraj)
      v1(i) += v2(i)
  }
}

object mainVektori {

  def main(args : Array[String]) : Unit = {
    val sc : Scanner = new Scanner(System.in)

    println("unesi dimenziju vektora")
    val n : Int = sc.nextInt()

    var v1 : Array[Float] = new Array(n)
    var v2 : Array[Float] = new Array(n)

    println("unesi prvi vektor")
    for( i <- 0 until n)
      v1(i) =  sc.nextFloat()
    println("unesi drugi vektor")
    for( i <- 0 until n)
      v2(i) =  sc.nextFloat()

    println("unesi broj niti")
    val brNiti : Int = sc.nextInt()

    val niti = new Array[Sabirac](brNiti)
    val korak = Math.ceil( n.toDouble / brNiti.toDouble ).toInt

    for(i<- 0 until brNiti)
      niti(i) = new Sabirac(i*korak, Math.min( (i+1)*korak, n), v1, v2)

    for(i<- 0 until brNiti)
      niti(i).start()
    for(i<- 0 until brNiti)
      niti(i).join()

    for( elem <- v1)
      print(s"$elem ")
  }
}
