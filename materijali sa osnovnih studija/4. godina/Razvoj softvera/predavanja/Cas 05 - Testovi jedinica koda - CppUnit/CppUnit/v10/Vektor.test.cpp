#include <cppunit/extensions/HelperMacros.h>

#include "Vektor.h"
#include <sstream>
using namespace std;

class VektorTest : public CppUnit::TestCase
{
      CPPUNIT_TEST_SUITE( VektorTest );
      CPPUNIT_TEST( constructorTest );
      CPPUNIT_TEST( eqTest );
      CPPUNIT_TEST( streamTest );
      CPPUNIT_TEST_SUITE_END();
	  
	  void constructorTest();
	  void eqTest();
	  void streamTest();
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

void VektorTest::eqTest() 
{
	Vektor v(1,2,3);
	Vektor v1(2,2,3);
	Vektor v2(1,1,3);
	Vektor v3(1,2,2);
	
//	CPPUNIT_ASSERT_EQUAL( v, v );	// ne moze, ne postoji <<
	CPPUNIT_ASSERT( v == v );
	CPPUNIT_ASSERT(!( v == v1 ));
	CPPUNIT_ASSERT(!( v == v2 ));
	CPPUNIT_ASSERT(!( v == v3 ));
	CPPUNIT_ASSERT( v != v1 );
	CPPUNIT_ASSERT( v != v2 );
	CPPUNIT_ASSERT( v != v3 );
	CPPUNIT_ASSERT(!( v != v ));	
//	CPPUNIT_FAIL( "Namerno!" );
}

void VektorTest::streamTest()
{
	ostringstream ostr;
	Vektor v1(1.1,2.2,3.3);
	ostr << v1;
	
	istringstream istr(ostr.str());
	Vektor v2;
	istr >> v2;

	CPPUNIT_ASSERT( ostr.str() == "(1.1,2.2,3.3)" );
	CPPUNIT_ASSERT( v1 == v2 );
}

