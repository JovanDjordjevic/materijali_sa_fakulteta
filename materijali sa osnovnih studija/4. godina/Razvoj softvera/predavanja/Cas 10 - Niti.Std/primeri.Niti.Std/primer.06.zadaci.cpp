#include <iostream>#include <vector>#include <queue>#include <thread>#include <mutex>using namespace std;class Zadaci{public:    Zadaci()    {}    void dodajZadatak( int n )    {        lock_guard<mutex> lock(zadaciMutex);        zadaci.push( n );    }    int uzmiZadatak()    {        lock_guard<mutex> lock(zadaciMutex);        if( zadaci.empty() )            return -1;        // 0 koristimo kao oznaku za kraj,        // ostavljamo je da bi i druge niti zavrsile sa radom        int n = zadaci.front();        if( n>0 )            zadaci.pop();        return n;    }private:    mutex  			zadaciMutex;    std::queue<int> zadaci;};void izvrsavanjeZadataka( Zadaci& zadaci, int _ID ){    while(true){        int zadatak = zadaci.uzmiZadatak();        if( !zadatak )            break;        if( zadatak > 0 ){            for( int i=1; i<=zadatak; i++ ){                cout << "Nit " << _ID << " : " << i << endl;				this_thread::sleep_for( chrono::milliseconds( 200 ));            }        }else			this_thread::sleep_for( chrono::milliseconds( 200 ));    }}void postavljanjeZadataka( Zadaci& zadaci ){    while(true){        cout << "Unesi pozitivan ceo broj: ";        int n;        cin >> n;        if( n<0 )            cout << "Greska!" << endl;        else{            zadaci.dodajZadatak(n);            if( n==0 )                break;        }    }}int main(int argc, char **argv){    int n = 5;    vector<thread> threads;	Zadaci zadaci;    cout << "Pokretanje niti..." << endl;    for( int i=0; i<n; i++ )        threads.emplace_back( izvrsavanjeZadataka, ref(zadaci), i );	postavljanjeZadataka(zadaci);    cout << "wait..." << endl;    for( thread& t: threads )        t.join();    cout << "Kraj." << endl;    return 0;}