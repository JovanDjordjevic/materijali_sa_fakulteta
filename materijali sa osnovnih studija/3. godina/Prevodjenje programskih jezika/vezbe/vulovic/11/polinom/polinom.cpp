#include "polinom.hpp"

void Polinom::dodaj(float c){
  
  koeficijenti.push_back(c);
}

void Polinom::ispisi() const{
//   cout << "VELICINA: " << koeficijenti.size() << endl;
  for(unsigned  i=0; i< koeficijenti.size(); i++){
//     cout <<"Pisem :"<< i  << "\t\n";
    if(koeficijenti[i] == 0)
      continue;
    
    if( i!=0 && koeficijenti[i] >0)
       cout << "+ ";
    cout << koeficijenti[i];
    if (i>0)
      cout << "x";
    if(i>1)
      cout <<"^"<<i;
    cout  << " " ;
  }
  
  if(koeficijenti.size()==1 && koeficijenti[0] == 0)
    cout << 0;
  
  cout << endl;
}

const vector<float>& Polinom::get_koef() const{
  return koeficijenti;  
}


unsigned Polinom::stepen() const{
  return koeficijenti.size()-1;
}

void Polinom::sredi_koeficijente(){
  int velicina = koeficijenti.size();
  
  for(int i = velicina-1; i>0; i--)
      if( koeficijenti[i] == 0)
        velicina--;
  
  koeficijenti.resize(velicina);
}


bool Polinom::jednak(const Polinom & p) const{
  if (stepen() != p.stepen())
    return false;
    
  for (unsigned i =0; i<= stepen(); i++)
    if(koeficijenti[i] != p.koeficijenti[i] )
      return false;  

  return true;
}




float Polinom::vrednost( float x) const
{
    float rezultat = 0;
    int i = stepen();
    for (; i >= 0; i--)
		  rezultat = rezultat * x + koeficijenti[i];
		  
    return rezultat;
}


void Polinom::izvod()
{
  
  if (stepen() > 0) {
	  unsigned nov_stepen = stepen() - 1;

	  for ( unsigned i = 0; i <= nov_stepen; i++)
	    koeficijenti[i] = (i + 1) * koeficijenti[i + 1];
	 
   koeficijenti.resize(nov_stepen+1);   
  } 
  else
	  koeficijenti[0] = 0;
}

void Polinom::integral( float x)
{
  unsigned nov_stepen = stepen() + 1;
  koeficijenti.resize(nov_stepen+1);
  
  for ( unsigned i = nov_stepen; i >0; i--)
    koeficijenti[i] = 1.0 / i * koeficijenti[i - 1];
  koeficijenti[0] = x;
}





/* Definicije prijateljskih funkcija */

Polinom* saberi(const Polinom& p1, const Polinom& p2 ){
  
  unsigned stepen = max(p1.stepen(), p2.stepen());  
  vector<float> r_koef( stepen + 1);  
  
  for(unsigned i =0; i<= stepen; i++){   
     if( i > p1.stepen() )  
       r_koef[i] = 0;
     else
       r_koef[i] = p1.get_koef()[i];
  
     if( i <= p2.stepen() )    
       r_koef[i] += p2.get_koef()[i];
  }
  
  Polinom * rezultat = new Polinom(r_koef); 
  rezultat->sredi_koeficijente();
  
  return rezultat;
}

Polinom* oduzmi(const Polinom& p1, const Polinom& p2 ){
  unsigned stepen = max(p1.stepen(), p2.stepen());  
  vector<float> r_koef( stepen + 1);  
  
  for(unsigned i =0; i<= stepen; i++){   
     if( i > p1.stepen() )  
       r_koef[i] = 0;
     else
       r_koef[i] = p1.get_koef()[i];
  
     if( i <= p2.stepen() )    
       r_koef[i] -= p2.get_koef()[i];
  }
   
  Polinom * rezultat = new Polinom(r_koef); 
  rezultat->sredi_koeficijente();
  
  return rezultat;
}


Polinom* pomnozi(const Polinom& p1, const Polinom& p2 ){
  unsigned stepen = p1.stepen() + p2.stepen();  
  vector<float> r_koef( stepen + 1,0);  
 
  for(unsigned i =0; i<= p1.stepen(); i++) 
    for(unsigned j=0; j<= p2.stepen(); j++ ){
       r_koef[i+j] += p1.get_koef()[i] * p2.get_koef()[j];
    }
  Polinom * rezultat = new Polinom(r_koef); 
  rezultat->sredi_koeficijente();
  
  return rezultat;
}


Polinom* uminus(const Polinom& p1){
  Polinom * rezultat = new Polinom(p1);
  
  for(unsigned i =0; i<= rezultat->stepen(); i++)
    rezultat->koeficijenti[i] *= -1;
  
  return rezultat;
}

