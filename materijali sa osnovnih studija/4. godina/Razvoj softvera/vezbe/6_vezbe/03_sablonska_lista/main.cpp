//ne prevodi se, fale operatori, mrzi me

#include <iostream>
#include <string>

#include "list.hpp"
#include "Point.h"

int main()
{
    using namespace std;
    matf::list<int> ints;
    ints.push_back(1);
    ints.push_back(2);
    ints.push_back(3);
    ints.push_back(4);
    cout << ints << endl;

    matf::list<matf::Point> points;
    points.push_back(matf::Point{3, 4});
    points.push_back(matf::Point{13, -4});
    points.push_back(matf::Point{0, 0});
    cout << points << endl;

    return 0;
}