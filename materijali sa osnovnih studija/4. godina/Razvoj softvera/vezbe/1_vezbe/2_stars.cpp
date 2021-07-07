#include <iostream>
#include <string>
#include <vector>

using namespace std;

// u zadatku pravimo nesto ovako:
// **************
// * linija     *
// * janfawafwf * 
// **************

int main(){

    vector<string> lines;
    size_t max_length = 0u;

    //ako hocemo da jedan red bude smesten u jednu promenljivu, ne smemo da radimo
    //while (cin >> s) jer cin za string cita do prve beline
    //ovo nase cita dokle god je standardni ulaz validan, tj dok ne dojde do EOF
    while (std::cin){
        string line;
        //imamo ugradjenu funkciju getline, prvi arg je odakle cita, drugi arg je gde upisuje
        getline(std::cin, line);

        //nisku mozemo gledati kao kolekciju karaktera, samim tim ima size(), empty(), begin(), end()...
        //nad niskama mozemo ipriemnjivati neke algoritme koji rade za kolekcije, npr accumulate itd...
        if(line.empty()){ continue; }  //npr zelimo da ignorise prazne linije
        if(line.size() > max_length){
            max_length = line.size();
        }
        lines.push_back(line);
    }

    string bar(max_length + 4, '*');  //niska sa inicijalizacijom, daje se duzina i kar od koga se pravi

    cout << bar << endl;
    for(const string &line : lines){
        string padding(max_length - line.size(), ' ');
        cout << "* " << line << padding << " *" << endl;
    }
    cout << bar << endl;

    return 0;
}