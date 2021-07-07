#define CATCH_CONFIG_MAIN
#include "catch/single_include/catch2/catch.hpp"
#include "test_class.hpp"

//nisam 10 mrzi me

TEST_CASE("averager", "[class]") 
{    
    SECTION("works with ints", "")
    {   
        averager<int> a;

        a.save_value(5);
        a.save_value(5);
        a.save_value(4);
        a.save_value(4);

        REQUIRE( a() == 4.5 );
    }

    SECTION("works with doubles", "")
    {   
        averager<double> a;

        a.save_value(1.2);
        a.save_value(2.3);
        a.save_value(3.4);
        a.save_value(4.5);

        REQUIRE( a() == 2.85 );
    }
}