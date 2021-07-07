#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
using namespace std;

#include "Vektor.h"

void testVektor()
{
	try {
		Vektor v(1,2,3);
		CPPUNIT_ASSERT( v.getX() == 1 );
		CPPUNIT_ASSERT( v.getY() == 2 );
		CPPUNIT_ASSERT( v.getZ() == 3 );
		CPPUNIT_ASSERT( v.getZ() == 4 );
		cout << "OK" << endl;
	}catch( exception& e ){
		cerr << "ERROR: " << e.what() << endl;
	}
}

int main()
{
	testVektor();
	return 0;
}
