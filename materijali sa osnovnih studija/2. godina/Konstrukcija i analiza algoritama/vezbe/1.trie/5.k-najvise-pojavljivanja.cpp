#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<queue>

using namespace std;

struct Cvor{
    Cvor(){
      word="";
      count=0;
    }
  string word;
  int count;
  unordered_map<char,Cvor*>nodes;
};


struct cmp{                                          //!!!!!!!!!!!!!!!
  bool operator()(Cvor *n1,Cvor *n2){
    return n1->count < n2->count;
  }
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






void ubaci_u_heap(Cvor *koren, priority_queue<Cvor *, vector<Cvor*>,cmp>&heap){       //!!!!!!
   if(koren->word!=""){
     heap.push(koren);
   }

  auto begin = koren->nodes.begin();
  auto end = koren->nodes.end(); 
  while (begin != end)
  {
    ubaci_u_heap(begin->second, heap);
    begin++;
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

    priority_queue<Cvor*, vector<Cvor*>,cmp>heap;

    ubaci_u_heap(koren,heap);
    int k=3;   //moze bilo koje k


    while(k!=0  && heap.size()!=0){

      Cvor *tmp=heap.top();
      heap.pop();
      cout<<tmp->word<<" se pojavljuje "<<tmp->count<<" puta"<<endl;
      k--;
    }


  
  return 0;
}