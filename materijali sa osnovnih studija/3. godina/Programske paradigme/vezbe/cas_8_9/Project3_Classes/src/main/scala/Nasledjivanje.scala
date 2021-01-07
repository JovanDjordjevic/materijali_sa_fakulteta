/*
ako nema konstruktor:  class ime{...}
ako ima konstruktor:   class ime(args) {...}  ,args su argumenti konstruktora new
*/

class Film{
  //NOTE: zadavanjem default vrednosti za polja klase implicitno se pravi i default kosntruktor
  var naslov : String = ""    //ovde = znaci default vrednost atribut klase
  var trajanje : Int = 0
  var godina : Int = 0

  //pravimo nas konstruktor. Pravilo u Scali je da se konstruktor zove this !!!!!
  //takodje, za kosntruktor se ne navodi povratni tip :Tip !!!!!
  def this(naslov : String, trajanje : Int, godina : Int)= {
    this()
    this.naslov = naslov
    this.trajanje = trajanje
    this.godina = godina
  }

  //u Scali ne moramo da pisemo kljucnu rec return ako je return poslednja nareda u funkciji, ali ja sam pisao oba nacina
  //ako metod ima samo jednu naredbu ne moramo da pisemo ni {}
  def getNaslov() : String = { return this.naslov }
  def getTrajanje() : Int = { this.trajanje }
  def getGodina() : Int =  this.godina

  override def toString() : String = {
    return "Film " + this.naslov + ", trajanje " + this.trajanje + " minuta. Film je iz: " + this.godina + " godine"
  }
}


class CrtaniFilm extends  Film{
  var autor : String = ""

  def this(naslov : String, trajanje : Int, godina : Int, Autor : String)={
    this()
    this.naslov = naslov
    this.trajanje = trajanje
    this.godina = godina
    this.autor = autor
  }

  def getAutor() : String = {return this.autor }

  override def toString() : String = { return super.toString() + " Autor: " + this.autor }

}



object Nasledjivanje {
  def main(args : Array[String]) : Unit = {

    val f : Film = new Film("Tarzan", 90, 1990)
    println("f: "+f)
    println(f.getNaslov() + " " + f.getTrajanje() + " " +  f.getGodina())

    val c : CrtaniFilm = new CrtaniFilm("Tarzan animirani",36,1999,"Walt Disney")
    println(c)
  }

}
