#include <iostream>
#include <assert.h>
using namespace std;

#include "Vektor.h"

void testVektor()
{
	Vektor v(1,2,3);
	assert( v.getX() == 1 );
	assert( v.getY() == 2 );
	assert( v.getZ() == 3 );
	assert( v.getX() == 3 );
	cout << "OK" << endl;
}

int main()
{
	testVektor();
	return 0;
}
