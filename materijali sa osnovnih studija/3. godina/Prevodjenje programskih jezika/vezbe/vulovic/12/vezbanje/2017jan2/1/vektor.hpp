#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>

using namespace std;

class Vektor{
    public:
    Vektor(){};
    Vektor(float broj);
    void dodaj(float broj);
    void stampaj();
    int getsize();
    float getkoord(int br);
    
    vector<float> elementi;
    
};

Vektor* operacija (Vektor* v1, Vektor* v2, int op);
Vektor* mnoz (Vektor* v1, float br);
