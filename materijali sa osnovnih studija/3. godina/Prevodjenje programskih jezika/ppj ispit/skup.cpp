#include"skup.hpp"

Skup::Skup(int broj1,int broj2){
    for (int i=broj1; i<=broj2; i++){
        skup.push_back(i);
    }
}

void Skup::print(){
    cout<<"{";
    for(unsigned i=0;i<=skup.size();i++)
        cout<<skup[i]<<", ";
    cout<<"}"<<endl;
}

void Skup::ubaci(int broj){
    this->skup.push_back(broj);
}
