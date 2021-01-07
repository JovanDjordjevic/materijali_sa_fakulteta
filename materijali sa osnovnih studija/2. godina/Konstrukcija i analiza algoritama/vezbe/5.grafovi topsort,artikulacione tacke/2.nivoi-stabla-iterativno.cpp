#include<iostream>
#include<vector>
#include<queue>

using namespace std;


struct Cvor{
   Cvor(){
     levo=desno=nullptr;
   }
  int vrednost;
  Cvor *levo;
  Cvor *desno;
};



void dodaj_cvor(Cvor **koren, int vrednost ){
  if(*koren==nullptr){
    *koren=new Cvor();
    (*koren)->vrednost=vrednost;
    return;
  }
  if(vrednost<(*koren)->vrednost) dodaj_cvor((*koren)->levo,vrednost);
  else dodaj_cvor((*koren)->desno, vrednost);
}
void free_tree(Cvor *koren){
  if(koren==nullptr) return;
  free_tree(koren->levo);
  free_tree(koren->desno);
  delete koren;
}




void bfs(Cvor *koren, vector<int> &levels){
  queue<Cvor*> red;
  int broj_cvorova=1;  //nigde nije koristila ovaj broj?
  red.push(koren);
  levels[koren->vrednosti]=0;
  int current_level=0;
  Cvor *pom;

  while(!red.empty()){
    pom=red.front();
    red.pop();
    if(pom->levo){
      levels[pom->levo->vrednost]=levels[pom->vrednost]+1;
      red.push(pom->levo);
    }
    if(pom->desno){
      levels[pom->desno->vrednost]=levels[pom->vrednost]+1;
      red.push(pom->desno);
    }
    if(levels[pom->vrednost]!=current_level){
      cout<<endl;
      current_level++;
    }
    cout<<pom->vrednost<<" ";
  }
}





int main(){

  Cvor *koren=nullptr;
  vector<int> vrednsoti={4,3,5,7,1,9,8,6};
  for(int x : vrednsoti){
    dodaj_cvor(&koren,x);
  }

  int n=vrednosti.size();
  vector<int> levels(n);  //mislim da bi ovde trebalo levels(max vrednost iz niza)

  bfs(koren,levels);

  free_tree(koren);

  return 0;
}