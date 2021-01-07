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

  int max=segmenti[0].getEnd();
  int n=segmenti.size();

  for(int i=1;i<n;i++){
    if(segmenti[i].getEnd()<=max)
        cout<<"["<<segmenti[i].getBegin()<<", "<<segmenti[i].getEnd()<<"]\n";
    else
      max=segmenti[i].getEnd();
  }



  return 0;
}