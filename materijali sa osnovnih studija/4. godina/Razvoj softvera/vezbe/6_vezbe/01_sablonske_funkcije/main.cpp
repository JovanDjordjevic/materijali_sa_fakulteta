#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

#include "GenericFunctions.h"
#include "Point.h"

int main(){

    using namespace std;

    //za ispisivanje true/false umesto 0/1
    cout.setf(ios_base::boolalpha);

    matf::Point p1{3,3}, p2{-10, 15};

    cout << matf::max(2,3) << endl;
    cout << matf::max(2.2, 2.7) << endl;
    //fali oeprator za poredjenje tacaka
    //cout << matf::max(p1, p2).str() << endl;
    vector<int> vs(5u);
    matf::iota(begin(vs), end(vs), 1);
    for (const auto& v : vs)
    {
        cout << v << ", ";
    }
    cout<<endl;

    vector<matf::Point> ws(4u);
    matf::iota(begin(ws), end(ws), matf::Point{});
    for (const auto& w : ws)
    {
        cout << w.str() << ", ";
    }
    cout<<endl;

    cout <<matf::accumulate(begin(vs), end(vs), int{}) << endl;
    cout << (matf::accumulate(begin(ws), end(ws), matf::Point{}) ).str() << endl;

    return 0;
}