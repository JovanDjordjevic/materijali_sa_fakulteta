#include<iostream>
#include<vector>
#include <unordered_map>
#include<string>

using namespace std;


struct Cvor{
  Cvor(){
    is_leaf=false;
  }
  bool is_leaf;
  unordered_map<char,Cvor*> nodes;
};

void dodaj(Cvor *koren,string &rec, int i){
    if(i==rec.size()){
      koren->is_leaf=true;
      return;
    }
    auto it=koren->nodes.find(rec[i]);
    if(it==koren->nodes.end()){
      koren->nodes[rec[i]]=new Cvor();
    }
    dodaj(koren->nodes[rec[i]],rec,i+1);
}






void LCP(Cvor *koren, string &lcp){              //!!!!!!!!!!
  while(!koren->is_leaf && koren->nodes.size()==1){
      auto element=koren->nodes.begin();
      lcp+=element->first;
      koren=element->second;
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


 string lcp="";
 LCP(koren,lcp);

 cout<<lcp<<endl;

  return 0;
}


