#include "list.hpp"
#include <iostream>

int main(){

    matf::list xs;
    
    xs.push_back(3);
    xs.push_back(4);
    xs.push_back(5);

    xs.push_front(2);
    xs.push_front(1);
    xs.push_front(0);

    xs.pop_front();

    std::cout << "xs: " << xs << "\n";

    auto ys = xs; //ovde se poziva konstuktor kopije koji smo napravili, NIJE dodela, zato sto auto ys zapravo poziva konstruktor
    // uato ys(xs); je drugi zapis za konstruktor kopije, moze i auto ys{xs}
    //da je pisalo:    auto ys;   ys = xs;   to bi bilo kopiranje
    std::cout << "ys: " << ys << "\n";

    matf::list zs; // 
    zs = ys;       //ovde JESTE operator dodele, a ne konstruktor kopije    

    std::cout << "zs: " << zs << "\n";

    //primetimo da sledecim pozivom postizemo da ws ima sadrzaj liste xs a da je xs sada prazna lista
    auto ws = std::move(xs);    // desilo se da je pozvan konsruktor pomeranja
    std::cout << "ws: " << ws << "\n";

    matf::list ds;
    ds = std::move(ws); //operator dodele sa semantikom pomeranja
    std::cout << "ws: " << ws << "\n";
    std::cout << "ds: " << ds << "\n";

    return 0;
}