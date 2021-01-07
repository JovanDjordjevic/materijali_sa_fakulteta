#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>

using namespace std;

struct Cvor{
    Cvor(){
        is_leaf=false;
    }
    bool is_leaf;
    unordered_map<char,Cvor*>nodes;
};




void dodaj(Cvor *koren, string &rec, int i){
    
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






bool pronadji(Cvor *koren, string &rec, int i){
    if(i==rec.size()){
        return koren->is_leaf;
    }

   auto it=koren->nodes.find(rec[i]);
   if(it==koren->nodes.end()){
       return false;
   }
   
   return pronadji(koren->nodes[rec[i]],rec,i+1);

}






int main(){

 
    vector<string> niz={"rec1","rec2","jos","reci"};

    Cvor* koren=new Cvor();

    for(int i=0;i<niz.size();i++){
        dodaj(koren,niz[i],0);
    }

   for(int i=0;i<niz.size();i++){
       if(pronadji(koren,niz[i],0)){
           cout<<i<<". rec nadjena"<<endl;
       }
       else{
           cout<<i<<" greska"<<endl;
       }
    }


    return 0;
}
