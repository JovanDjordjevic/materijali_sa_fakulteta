#include <iostream>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
using namespace std;

int main()
{
	CppUnit::TextTestRunner runner;
	runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
	runner.run();
	return 0;
}
