#include <cppunit/extensions/HelperMacros.h>
#include "Vektor.h"

class VektorTest : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE( VektorTest );
	CPPUNIT_TEST( constructorTest );
	CPPUNIT_TEST_SUITE_END();

	void constructorTest();
};

CPPUNIT_TEST_SUITE_REGISTRATION( VektorTest );

void VektorTest::constructorTest() 
{
	Vektor v(1,2,3);
	CPPUNIT_ASSERT( v.getX() == 1 );
	CPPUNIT_ASSERT_MESSAGE( "Neispravno X!", v.getX() == 1 );
	CPPUNIT_ASSERT_EQUAL( 2.0, v.getY() );
	CPPUNIT_ASSERT_EQUAL_MESSAGE( "Neispravno Z!", 3.0, v.getZ() );
	CPPUNIT_ASSERT_DOUBLES_EQUAL( 1, v.getX(), 0.0001 );
	//CPPUNIT_FAIL( "Nije implementiran test!" );
}

