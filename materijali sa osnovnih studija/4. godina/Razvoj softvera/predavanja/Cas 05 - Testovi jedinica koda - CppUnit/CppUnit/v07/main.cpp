#include <iostream>
#include <cppunit/ui/text/TestRunner.h>
using namespace std;

#include "Vektor.test.h"

int main()
{
	CppUnit::TextTestRunner runner;
	runner.addTest( VektorTest::suite() );
	runner.run();
	return 0;
}
