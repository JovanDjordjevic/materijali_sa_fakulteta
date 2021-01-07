#include"MojVektor.hpp"

using namespace std;

void MojVektor::dodaj(float broj){
    vektor.push_back(broj);
}

void MojVektor::print(){
    cout<<"<";
    for (unsigned i=0;i<vektor.size()-1;i++){
        cout<<vektor[i]<<", ";
    }
    cout<<vektor[vektor.size()-1]<<">"<<endl;
}

float MojVektor::skalarni(MojVektor* m){
    if(this->vektor.size() != m->vektor.size())
        cerr<<"greska u dimenziji!"<<endl;
    float rez=0;
    int n=this->vektor.size();
    for(int i=0;i<n;i++){
        rez+=this->vektor[i]*m->vektor[i];
    }
    
    return rez;
}

MojVektor& operacija(MojVektor& m1, MojVektor& m2, int op){
    //1+ 2-
    MojVektor* rez=new MojVektor(); 
    if(m1.vektor.size() != m2.vektor.size())
        cerr<<"greska u dimenziji!"<<endl;
    int n=m1.vektor.size();
    for(int i=0;i<n;i++){
        float x=0;
        if(op==1)
            x=m1.vektor[i] + m2.vektor[i];
        if(op==2)
            x=m1.vektor[i] - m2.vektor[i];
        rez->dodaj(x);
    }
    
    return *rez;
}


MojVektor& mnoz(MojVektor& m1, float broj){
   MojVektor *rez=new MojVektor(); 
   int n=m1.vektor.size();
    for(int i=0;i<n;i++){
        rez->dodaj(m1.vektor[i]*broj);
    }
    
    return *rez; 
}
