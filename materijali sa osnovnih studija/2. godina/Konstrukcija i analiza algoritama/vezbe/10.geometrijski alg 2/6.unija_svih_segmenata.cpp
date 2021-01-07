#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

class Segment{
  public: 
  Segment(int a, int b){
    begin=a;
    end=b;
  }
  int getBegin(){return begin;}
  int getEnd(){return end;}

  private:
  int begin;
  int end;
};



//treba nam rastuce po pcoecima ali OPADAJUCE po krajevima
bool compare(Segment &s1,Segment &s2){
   if(s1.getBegin() ==s2.getBegin())
        return s1.getEnd() > s2.getEnd();
   return s1.getBegin() < s2.getBegin();     
}




int main(){
  vector<Segment> segmenti = {{1, 2}, {1, 5}, {2, 7}, {3, 9}, {2, 4}, {6, 8}, {5, 8}};

  sort(segmenti.begin(),segmenti.end(),compare);

  int n=segmenti.size();
  int desno=segmenti[0].getEnd();
  int suma=segmenti[0].getEnd()-segmenti[0].getBegin();

  for(int i=1;i<n;i++){

    //ako je seg unutar drugog seg onda ne racunamo nejgovu duzinu, ako seg prevazilazi trenutni max(desno)
    //onda 2 slucaja: IF ceo novi seg je van starog, pa dodajuemo cellu njegou duzinu
    //ELSE levi kraj je unutar segmenta pa dodajemo njegov kraj-desno

    if(segmenti[i].getEnd() > desno ){
          if(segmenti[i].getBegin() > desno){
            suma+=segmenti[i].getEnd()-segmenti[i].getBegin();
            desno=segmenti[i].getEnd();
          }
          else{
            suma+=segmenti[i].getEnd()-desno;
            desno=segmenti[i].getEnd();
          }
    }
  }


  cout<<suma<<endl;


  return 0;
}