#include "../catch.hpp"
#include "Vektor.h"

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
