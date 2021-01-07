#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>

using namespace std;

class MojVektor{
    public:
        
    MojVektor(){};
    void dodaj(float broj);
    void print();
    float skalarni(MojVektor* m);
    
    vector<float> vektor;
};

MojVektor& operacija(MojVektor& m1, MojVektor& m2, int op);
MojVektor& mnoz(MojVektor& m1, float broj);
