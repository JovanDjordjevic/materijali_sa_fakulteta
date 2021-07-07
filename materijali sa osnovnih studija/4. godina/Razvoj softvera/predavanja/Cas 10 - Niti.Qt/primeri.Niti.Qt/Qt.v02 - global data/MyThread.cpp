#include <iostream>
#include "MyThread.h"

using namespace std;

extern int globalData;

void MyThread::run()
{
    for( int i=0; i<1000; i++ ){
        int x = globalData;
        if( i%2 )
            cout << "Nit " << _ID << " : " << i << endl;
        x++;
        globalData = x;
    }
}
