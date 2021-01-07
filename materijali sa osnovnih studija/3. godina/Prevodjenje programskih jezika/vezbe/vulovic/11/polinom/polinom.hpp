#ifndef _POLINOM_HPP
#define _POLINOM_HPP 1

#include <vector>
#include <iostream>

using namespace std;

class Polinom{
  public:
    Polinom()
    {}
    
    Polinom(vector<float> koef){
      koeficijenti = koef;
    }
    
    void dodaj(float c);
    
    void ispisi() const;
    
    //geter
    const vector<float>& get_koef() const;
    
    unsigned stepen() const;
    
    bool jednak(const Polinom & p) const;
    float vrednost( float x) const;
    
    void izvod();
    void integral( float x);
    
    friend Polinom* saberi(const Polinom& p1, const Polinom& p2 );
    friend Polinom* oduzmi(const Polinom& p1, const Polinom& p2 );
    friend Polinom* pomnozi(const Polinom& p1, const Polinom& p2 );
    friend Polinom* uminus(const Polinom& p1);
    
  private:
    void sredi_koeficijente(); // ili da bude public ili da se prethodne funkcije deklarisu kao prijateljske
    vector<float> koeficijenti;
};




#endif
