#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

struct Cvor{              //ovde nam znaci da imamo celu rec u listu
  Cvor(){                 //i nodes je obicna mapa jer nam je bitan poredak
    word="";
  }
  string word;
  map<char,Cvor*>nodes;
};


void dodaj(Cvor *koren, string &rec, int i){
  if(i==rec.size()){
    koren->word=rec;
    return;
  }

  auto it=koren->nodes.find(rec[i]);
  if(it==koren->nodes.end()){
    koren->nodes[rec[i]]=new Cvor();
  }

  dodaj(koren->nodes[rec[i]],rec,i+1);
}





void leksikografsko(Cvor *koren){
    if(koren->word!="")
          cout<<koren->word<<endl;    //nema return jer mozda ima rec i posle ovog cvora

    auto pocetak=koren->nodes.begin();
    auto kraj=koren->nodes.end();

    while(pocetak!=kraj){
        leksikografsko(pocetak->second);
        pocetak++;
    }

}         




int main(){


vector<string> words =
	{
		"lexicographic", "sorting", "of", "a", "set", "of", "keys", "can",
		"be", "accomplished", "with", "a", "simple", "trie", "based",
		"algorithm", "we", "insert", "all", "keys", "in", "a", "trie",
		"output", "all", "keys", "in", "the", "trie", "by", "means", "of",
		"preorder", "traversal", "which", "results", "in", "output", "that",
		"is", "in", "lexicographically", "increasing", "order", "preorder",
		"traversal", "is", "a", "kind", "of", "depth", "first", "traversal"
	};

  Cvor *koren=new Cvor();

  for(string s: words){
    dodaj(koren,s,0);
  }


  leksikografsko(koren);

  return 0;
}
