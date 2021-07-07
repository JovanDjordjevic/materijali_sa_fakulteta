#include <iostream>
#include "MyThread.h"

using namespace std;

void MyThread::run()
{
    for( int i=0; i<10; i++ )
        cout << "Nit " << _ID << " : " << i << endl;
}
