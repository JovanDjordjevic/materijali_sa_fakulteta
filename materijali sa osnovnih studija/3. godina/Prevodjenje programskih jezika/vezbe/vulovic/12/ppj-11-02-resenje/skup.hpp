#ifndef _SKUP_HPP_
#define _SKUP_HPP_

#include <set>
#include <iostream>


class Skup {
  public:
    Skup() ;
    Skup(int pocetak, int kraj);
  
    void dodaj(int x);
    void obrisi(int x);
  
    void stampaj() const;
    
    bool nadji(int x) const;
    
    bool podskup( const Skup* veci  ) const;
    
    int brojElemenata() const;
    
  private:
    std::set<int> _elementi;
    
    friend Skup*  unija(const Skup* prvi, const Skup* drugi);
  
    friend Skup*  presek(const Skup* prvi, const Skup* drugi);
    friend Skup*  razlika(const Skup* prvi, const Skup* drugi);
   
};

#endif
