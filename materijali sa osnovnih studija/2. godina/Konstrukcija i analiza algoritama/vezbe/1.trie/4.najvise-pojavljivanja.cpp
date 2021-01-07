#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>

using namespace std;

struct Cvor{
  Cvor(){
    word="";
    count=0;    //novo u odnosu na prosli
  }

  string word;
  int count;
  unordered_map<char, Cvor*> nodes;  //ode moze unorder jer nam ne treba poredak
};


void dodaj(Cvor *koren, string &rec, int i){
  if(i==rec.size()){
    koren->word=rec;
    koren->count++;
    return;
  }
  auto it=koren->nodes.find(rec[i]);
  if(it==koren->nodes.end()){
    koren->nodes[rec[i]]=new Cvor();
  }
  dodaj(koren->nodes[rec[i]],rec,i+1);
}






 
void nadji_max(Cvor *koren, string &maxrec,int &max){    //!!!!!!
    if(koren->word!=""){
      if(koren->count>max){
        maxrec=koren->word;
        max=koren->count;
      }
    }
 

  auto pocetak=koren->nodes.begin();
  auto kraj=koren->nodes.end();

  while(pocetak!=kraj){
      nadji_max(pocetak->second,maxrec,max);
      pocetak++;
  }

}






int main(){


  vector<string> words = {"code", "coder", "coding", "codable", "codec", "codecs", "coded",
		"codeless", "codec", "codecs", "codependence", "codex", "codify",
		"codependents", "codes", "code", "coder", "codesign", "codec",
		"codeveloper", "codrive", "codec", "codecs", "codiscovered"};

  Cvor *koren=new Cvor();
  for(string s : words){
    dodaj(koren,s,0);
  }

  string maxrec="";
  int max=0;

  nadji_max(koren,maxrec,max);

  cout<<maxrec<<endl;

  return 0;
}