#include <iostream>
using namespace std;

#include "MyThread.h"

#ifdef QT_NO_CONCURRENT
    !!! Nije podrzano !!!
#endif

int main(int argc, char **argv)
{
    cout << "prepare..." << endl;
    MyThread t1(1);
    MyThread t2(2);

    cout << "run..." << endl;
    t1.start();
    t2.start();

    cout << "wait..." << endl;
    t1.wait();
    t2.wait();

    cout << "end..." << endl;
    cin.get();

    return 0;
}
