#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex ekran;

void myThreadFn( int tId )
{
    for( int i=0; i<10; i++ ){
		ekran.lock();
        cout << "Nit " << tId << " : " << i << " : ";
		for( unsigned i=0; i<40000; i++ )
			if( i%1000 == 0 )
				cout << tId;
		cout << "\n";
		ekran.unlock();
	}
}

int main(int argc, char **argv)
{
    cout << "Pripremi i kreni..." << endl;
	thread t1( myThreadFn, 1 );
	thread t2( myThreadFn, 2 );

	ekran.lock();
	cout << "...sacekaj..." << endl;
	ekran.unlock();
	
    t1.join();
    t2.join();

    cout << "Kraj." << endl;
    return 0;
}
