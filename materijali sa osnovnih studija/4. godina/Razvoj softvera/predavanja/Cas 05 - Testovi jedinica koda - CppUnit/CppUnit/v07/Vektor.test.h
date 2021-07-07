#ifndef _TEST_VEKTOR_H_
#define _TEST_VEKTOR_H_

#include <cppunit/extensions/HelperMacros.h>
#include "Vektor.h"

class VektorTest : public CppUnit::TestCase
{
      CPPUNIT_TEST_SUITE( VektorTest );
      CPPUNIT_TEST( constructorTest );
      CPPUNIT_TEST_SUITE_END();
	  
	  void constructorTest();
};

#endif /* _TEST_VEKTOR_H_ */
