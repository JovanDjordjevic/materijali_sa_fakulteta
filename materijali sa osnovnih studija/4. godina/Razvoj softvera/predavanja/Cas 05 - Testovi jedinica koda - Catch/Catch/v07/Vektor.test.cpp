#include "../catch.hpp"
#include "Vektor.h"

#include <sstream>
using namespace std;

TEST_CASE( "Konstruktori", "[Vektor]" ) {
    SECTION( "Vektor()" ){
        Vektor v;
        // Neki od ovih testova moze da ne prodje
        CHECK( v.getX() == 0 );
        CHECK( v.getY() == 0 );
        CHECK( v.getZ() == 0 );
        //  Ovaj test bi morao da prodje
        Approx doubleTest = Approx(0).epsilon(0.0000001);
        CHECK( v.getX() == doubleTest );
        CHECK( v.getY() == doubleTest );
        CHECK( v.getZ() == doubleTest );
    }
    SECTION( "Vektor(double,double,double)" ){
        Vektor v(1,2,3);
        CHECK( v.getX() == 1 );
        CHECK( v.getY() == 2 );
        CHECK( v.getZ() == 3 );
    }
}

TEST_CASE( "Operatori", "[Vektor]" ){
	Vektor v(1,2,3);
    Vektor v1(2,2,3);
    Vektor v2(1,3,3);
    Vektor v3(1,2,2);
    Vektor v4(1.1,2.2,3.3);

	SECTION( "operator==" ) {
		CHECK( v == v );
		CHECK_FALSE( v == v1 );
		CHECK_FALSE( v == v2 );
		CHECK_FALSE( v == v3 );
	}

	SECTION( "operator!=" ) {
		CHECK_FALSE( v != v );
		CHECK( v != v1 );
		CHECK( v != v2 );
		CHECK( v != v3 );
	}

	SECTION( "operator<<" ) {
		ostringstream ostr;
		ostr << v4;
		CHECK( ostr );
        CHECK( ostr.str() == "(1.1,2.2,3.3)" );
	}

	SECTION( "operator<<" ) {
		istringstream istr( "(1.1,2.2,3.3)" );
		Vektor v5;
		istr >> v5;

		CHECK( v5 == v4 );
		CHECK( istr );
		
		char c;
		istr >> c;
		CHECK( !istr );
	}

}

TEST_CASE( "Razno 2", "[test][vektor]" ) {
	Vektor v(1,2,3);
	INFO("Na ovom primeru testa mogu da se isprobaju tagovi...");
	INFO("...pokrenite ./test -?");
	INFO("Naredni makro ispisuje vektor v:");
	CAPTURE( v );
    INFO("Sve ovo se ispisuje samo u slucaju greske, pa je namerno pravimo...");
	REQUIRE_FALSE( v ==  v );
}
