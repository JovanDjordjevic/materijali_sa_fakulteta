#include "skup.hpp"


Skup::Skup()
{}

Skup::Skup(int pocetak, int kraj){
  for (int i = pocetak; i <= kraj; i++)
    _elementi.insert(i);
}

void Skup::dodaj(int x) {
  _elementi.insert(x);
}

void Skup::obrisi(int x){
  if( nadji(x) ) 
    _elementi.erase(x);
}

void Skup::stampaj() const{
  std::cout << "{";
  for(std::set<int>::iterator i = _elementi.begin(); i != _elementi.cend(); i++){
    if (i != _elementi.cbegin())
      std::cout << ", ";
    std::cout << *i;
  }
  std::cout << "}" << std::endl; 
}

bool Skup:: nadji(int x) const{
  return _elementi.find(x) != _elementi.end();
}


Skup*  unija(const Skup* prvi, const Skup* drugi){
  /* Kreiramo kopiju da bismo nju modifikovali*/		
  Skup *rezultat = new Skup(*prvi);   
										
	for(auto i = drugi->_elementi.cbegin(); i != drugi->_elementi.cend(); i++){
		rezultat->dodaj(*i);
	}
	
	return rezultat;
}

Skup*  presek(const Skup* prvi, const Skup* drugi){
  /* Kreiramo kopiju da bismo nju modifikovali*/		
  Skup *rezultat = new Skup(*prvi);   
	
	for(auto i = prvi->_elementi.cbegin(); i != prvi->_elementi.cend(); ){
		if( ! drugi->nadji(*i) ) // nije nadjen
		  rezultat->obrisi(*i);  //brisemo ga  
		++i;  
	}
	
	return rezultat;
}


Skup*  razlika(const Skup* prvi, const Skup* drugi){
  /* Kreiramo kopiju da bismo nju modifikovali*/		
  Skup *rezultat = new Skup(*prvi);   
	
	for(auto i = prvi->_elementi.cbegin(); i != prvi->_elementi.cend(); i++){
		if( drugi->nadji(*i) ) // nadjen je
		  rezultat->obrisi(*i);  //brisemo ga  
	}
	
	return rezultat;
}


bool Skup::podskup( const Skup* veci  ) const {
	for(auto i = _elementi.cbegin(); i != _elementi.cend(); i++){
		if( ! veci->nadji(*i) )		
		return false;
	}
	return true;
}

int Skup::brojElemenata() const{
  return _elementi.size();  
}

/*
int main() {
Skup s;

s.dodaj(1);
s.dodaj(111);
s.dodaj(12);
s.dodaj(21);

s.stampaj();

return 0;


}

*/
