name := "2_Zadatak"

version := "0.1"

scalaVersion := "2.12.11"

libraryDependencies ++= {
  val sparkVer = "2.4.0"
  Seq{
    "org.apache.spark" %% "spark-core" % sparkVer
  }
}