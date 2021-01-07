//greska u kompilaciji ne uemm da popravim

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct Tacka{
  int x;
  int y;
};

//hocemo da sortiramo rastuce po x pa rastuce po y
bool compare(Tacka &p1, Tacka &p2){
  if(p1.x==p2.x){
    return p1.y<p2.y;
  }
  return p1.x < p2.x;  
}


//poznate su nam a i b tacke kvadrata, trazimo ostale potencijalne, c i d iznad i c1 d1 ispod duzi ab
void nadji_koordinate(Tacka &a, Tacka &b,Tacka &c,Tacka &c1,Tacka &d,Tacka &d1){
  int deltaX=b.x-a.x;
  int deltaY=b.y-a.y;

  c.x=b.x + deltaY;
  c1.x=b.x - deltaY;

  c.y=b.y - deltaX;
  c1.y=b.y + deltaX;

  d.x=a.x + deltaY;
  d1.x=a.x - deltaY;

  d.y=a.y - deltaX;
  d1.y=a.y + deltaX;
}


bool proveri(vector<Tacka> &tacke, const Tacka &c,const Tacka &c1,const Tacka &d,const Tacka &d1){
  return binary_search(tacke.begin(),tacke.end(),c,compare) && binary_search(tacke.begin(),tacke.end(),d,compare)
         || binary_search(tacke.begin(),tacke.end(),c1,compare) && binary_search(tacke.begin(),tacke.end(),d1,compare);
}





bool ima_li_kvadrata(vector<Tacka> tacke){
  sort(tacke.begin(),tacke.end(),compare);
  int n=tacke.size();

  Tacka c,d,c1,d1;

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(i==j) continue;  //preskacemo par tacaka koji cine dve iste tacke
      nadji_koordinate(tacke[i],tacke[j],c,c1,d,d1);
      if(proveri(tacke,c,c1,d,d1))
          return true;
    }
  }

  return false;
}



int main(){
  vector<Tacka> tacke = { {0, 3}, {2, 2}, {6, 4}, {1, 1}, {2, 1}, {2, 5}, {3, 0}, {0, 0}, {3, 3} };
  
  cout<<ima_li_kvadrata(tacke)<<endl;

  return 0;
}