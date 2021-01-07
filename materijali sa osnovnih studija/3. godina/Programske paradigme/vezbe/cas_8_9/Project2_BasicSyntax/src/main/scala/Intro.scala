object Intro {

  def main(args : Array[String]) : Unit = {
      var x : Int = 6   //ovo je promenljivo
      x+=10
      print("x= " + x)

      val c : Int = 6     //ovo je const


      if (x==5)
        println ("5")
      else if (x==6)
        println("6")
      else
        println(">6")


      val predmet : String = "Programske paradigme i smer"
      println("niska: " + predmet + " duzina "+ predmet.length())
      val godine : String =
        """
          |viselinijski
          |string
          |""".stripMargin
      println(godine)


      //interpolacija niski, za ispis, obavezno karakter s pre ""!!!
      var trajanje : Int = 1
      println(s"vezbe na predmetu $predmet traju $trajanje h")


      var i : Int = 0
      var vreme : Int = 0
      while(i<3){
        i+=1
        vreme += 45
      }
      println(s"vreme $vreme")


      for (i<- 1 to 13)   // [1,13]
        print(i + " ")
      println()
      for (i<- 1 until 13) //[1,13)
        print(i + " ")
      println()
      for (i <- Range(1,13))  //sto [), radi kao range u pythonu
        print(i + " ")
      println()
      for (i <- Range(1,13,2))  //range sa korakom
        print(i + " ")
      println()
      for (i <- Range(20,13,-3))  //range sa negativnim korakom
        print(i + " ")
      println()


      var predmeti : Array[String] = new Array[String](5)
      predmeti(0) = "PPI"
      predmeti(1) = "RBP"
      predmeti(2) = "URBP"
      predmeti(3) = "P1"
      predmeti(4) = "P2"
      println("Predmeti "+predmeti)  //ovo stampa OBJEKAT I NJEGOVU ADRESU, za ispis elemenata moramo petljom
      //nizovi nemaju .length() nego .length
      for (i<- 0 until predmeti.length)
          print(predmeti(i) + " ")
      println()
      //kolekciska petlja
      for (p <- predmeti)
        println(p)


      //funkcije osnovna sintasa
      //def name([args list]) : returnType = {...}    Unit je zapravo void
      def writeOutSorted(predmeti : Array[String]) : Unit={
        println("sortirani:")
        //.sortWith kao argument prima funkciju po kojoj zelimo da poredimo elemente kolekcije
        for (p<- predmeti.sortWith(cmpString))
        //koriscenje lambda funkcije za isti ovaj problem:
        //for(p <- predmeti.sortWith( (p1,p2) => { if(p1.compareTo(p2)<0) true else false } ) )
          println(p)
      }
      def cmpString(p1 : String, p2 :String) : Boolean ={
        if (p1.compareTo(p2)<0) return true
        else return false
      }
  }

}
