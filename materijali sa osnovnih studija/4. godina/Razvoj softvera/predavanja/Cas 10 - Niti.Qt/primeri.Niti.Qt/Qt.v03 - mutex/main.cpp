#include <iostream>
#include <vector>
using namespace std;

#include "MyThread.h"

#ifdef QT_NO_CONCURRENT
    !!! Nije podrzano !!!
#endif

int globalData = 0;

int main(int argc, char **argv)
{
    int n = 10;
    vector<MyThread*> threads;

    cout << "prepare..." << endl;
    for( int i=0; i<n; i++ )
        threads.push_back( new MyThread(i) );

    cout << "run..." << endl;
    for( int i=0; i<n; i++ )
        threads[i]->start();

    cout << "wait..." << endl;
    for( int i=0; i<n; i++ )
        threads[i]->wait();

    cout << "end..." << endl;
    for( int i=0; i<n; i++ )
        delete threads[i];
    threads.clear();

    cout << "globalData = " << globalData << endl;
    cin.get();
    return 0;
}
