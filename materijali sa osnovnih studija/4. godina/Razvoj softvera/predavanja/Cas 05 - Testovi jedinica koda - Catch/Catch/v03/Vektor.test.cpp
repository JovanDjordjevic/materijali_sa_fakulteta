#include "../catch.hpp"
#include "Vektor.h"

TEST_CASE( "Konstruktor", "[Vektor]" ) {
	Vektor v(1,2,3);
	REQUIRE( v.getX() == 1 );
	REQUIRE( v.getY() == 2 );
	REQUIRE( v.getZ() == 3 );
    //  namerno, da vidimo kako izgleda kada se pogresi
	REQUIRE( v.getX() == 3 );   
}
