#include <cppunit/extensions/HelperMacros.h>

#include "Vektor.h"
#include <sstream>
using namespace std;

class VektorTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( VektorTest );
	CPPUNIT_TEST( constructorTest );
	CPPUNIT_TEST( eqTest );
	CPPUNIT_TEST( streamTest );
	CPPUNIT_TEST_SUITE_END();

	Vektor v,v1,v2,v3;
	
public:
	void setUp()
	{
		// ovo se izvrsava pre svakog testa
		v = Vektor(1,2,3);
		v1 = Vektor(2,2,3);
		v2 = Vektor(1,3,3);
		v3 = Vektor(1,2,2);
		
//		cerr << "Neka inicijalizacija, tako da svi testovi rade isto...\n";
	}

	void tearDown() { 
		// ovo se izvrsava posle svakog testa
//		cerr << "Eventualna deinicijalizacija...\n";
	}
	
	void constructorTest() 
	{
		Vektor v(1,2,3);
		CPPUNIT_ASSERT( v.getX() == 1 );
		CPPUNIT_ASSERT_MESSAGE( "Neispravno X!", v.getX() == 1 );
		CPPUNIT_ASSERT_EQUAL( 2.0, v.getY() );
		CPPUNIT_ASSERT_EQUAL_MESSAGE( "Neispravno Z!", 3.0, v.getZ() );
		CPPUNIT_ASSERT_DOUBLES_EQUAL( 1, v.getX(), 0.0001 );
	//	CPPUNIT_FAIL( "Nije implementiran test!" );
	}

	void eqTest() 
	{
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

	void streamTest()
	{
		ostringstream ostr;
		Vektor v1(1.1,2.2,3.3);
		ostr << v1;
		
		istringstream istr(ostr.str());
		Vektor v2;
		istr >> v2;

		CPPUNIT_ASSERT( ostr.str() == "(1.1,2.2,3.3)" );
		CPPUNIT_ASSERT( v1 == v2 );
		CPPUNIT_ASSERT( istr );
		
		char c;
		istr >> c;
		CPPUNIT_ASSERT( !istr );
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( VektorTest );

