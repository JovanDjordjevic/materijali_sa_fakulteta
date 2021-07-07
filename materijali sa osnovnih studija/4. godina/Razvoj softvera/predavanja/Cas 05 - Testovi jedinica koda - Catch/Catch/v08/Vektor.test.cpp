#include "../catch.hpp"

#include "Vektor.h"
#include <sstream>
using namespace std;

TEST_CASE( "Razno", "[test]" ) {
	// ne postoji poseban makro za proveru jednakosti
	// ali postoji posebna konstrukcija za poredjenje realnih brojeva
	
    // ovaj test ne prolazi
    CHECK( (10.0/3) == Approx(3.33) );

    // ovaj test prolazi
	Approx floatTest = Approx(3.33).epsilon(0.01);
	CHECK( (10.0/3) == floatTest );	// dopusten procenat odstupanja
	
	// REQUIRE_FAIL(...);
	// REQUIRE_NOTHROW(...);
	// REQUIRE_THROWS(...);
}


TEST_CASE( "Vektor", "[vektor]" ) {
	// ovde stavimo ono sto zelimo da se izvrsi pre svake sekcije
	Vektor v,v1,v2,v3;
	v = Vektor(1,2,3);
	v1 = Vektor(2,2,3);
	v2 = Vektor(1,3,3);
	v3 = Vektor(1,2,2);
	

	SECTION( "constructors" ) {
		Vektor v(1,2,3);
		// proverava i prekida u slucaju neuspeha
		REQUIRE( v.getX() == 1 );
		REQUIRE_FALSE( v.getX() == 2 );
		// proverava i u slucaju neuspeha to belezui ali nastavlja izvrsavanje
		CHECK( v.getX() == 1 );
	}
	
	SECTION( "fails" ) {
		Vektor v(1,2,3);
		REQUIRE( v.getX() == 1 );
		REQUIRE( (v.getX() >=0 && v.getX() <= 10) );
		CHECK( v.getX() == 1 );
	}
	
	SECTION( "streaming" ) {
		ostringstream ostr;
		Vektor v1(1.1,2.2,3.3);
		ostr << v1;
		
		istringstream istr(ostr.str());
		Vektor v2;
		istr >> v2;

		REQUIRE( ostr.str() == "(1.1,2.2,3.3)" );
		REQUIRE( v1 == v2 );
		REQUIRE( istr );
		
		char c;
		istr >> c;
		REQUIRE( !istr );
	}
	
	SECTION( "equality" ) {
		REQUIRE( v == v );
		REQUIRE(!( v == v1 ));
		REQUIRE(!( v == v2 ));
		REQUIRE(!( v == v3 ));
		REQUIRE( v != v1 );
		REQUIRE( v != v2 );
		REQUIRE( v != v3 );
		REQUIRE(!( v != v ));	
	}
	
	// ovde stavimo eventualnu deinicijalizaciju 
	// koja se izvrsava posle svake sekcije
}

TEST_CASE( "Razno 2", "[test][vektor]" ) {
	Vektor v(1,2,3);
	INFO("Primer testa da bismo videli kako rade tagovi");
	CAPTURE( v );
	REQUIRE_FALSE( v ==  v );
}


