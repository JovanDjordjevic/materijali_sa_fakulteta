//includove tipa #include <sstream> treba da pisemo pre ovog define (?)

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

#include "Vektor.h"

//u primerima na casu koristio je CHECK  umesto  REQUIRE
//razlika je samo u tome sto ako neka provera padne, REQUIRE ce da prekine ceo test case
//dok ce CHECK da da warning i da nastavi dalje

//TEST_CASE( "ime testa", "[neki][tagovi]")
TEST_CASE( "Konstruktor", "[Vektor]" ) {
	Vektor v(1,2,3);
	REQUIRE( v.getX() == 1 );
	REQUIRE( v.getY() == 2 );
	REQUIRE( v.getZ() == 3 );
    //  namerno, da vidimo kako izgleda kada se  pogresi
	REQUIRE( v.getX() == 3 );   
}

//mozemo ovde imati vise test caseova:
/*
TEST_CASE( "Test2", "[tag]" ) {
	...   
}
*/
