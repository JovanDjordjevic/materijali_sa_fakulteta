#include<iostream>
#include<vector>

using namespace std;

class Graph{
    public:
Graph(int v){
    V=v;
    susedi.resize(v);
    visited.resize(v);
    fill(visited.begin(),visited.end(),false);
    stepeni.resize(v);
    fill(stepeni.begin(),stepeni.end(),0);
}

void add_edge(int u,int v){
    susedi[u].push_back(v);
    susedi[v].push_back(u);
    stepeni[u]++;
    stepeni[v]++;
}

void dfs(int u){
    visited[u]=true;
    for(int sused : susedi[u]){
        if(!visited[sused]) dfs(sused);
    }
}


//ne sipitujemokomponente povezanosti vec nas interesuje da li su svi cvorovi
//sa stpenom > 0 povezani, jer ojlerov put ide preko GRANA, a ne cvorova  
bool je_povezan(){ 

    int start;
    for(int i=0;i<V;i++)
        if(susedi[i].size() > 0){  //tad mu sigurno stepen >0
            start=i;
            break;   //ne mroamo da obilazimo sve
        }

    dfs(start);
    
    for(int i=0; i<V;i++){
        if(visited[i]==false && stepeni[i]>0)  return false;
    }    
 
 return true;
}




//0 ako nije ojlerov
//1 ako ima put a nema ciklus
//2 ako ima ciklus
int ojler(){
    int broj_cvorova_neparnog_stepena=0;
    for(int i=0;i<V;i++){
        if(stepeni[i]%2==1) 
            broj_cvorova_neparnog_stepena++;
    }
    if(broj_cvorova_neparnog_stepena>2) return 0;
    if(!je_povezan()) return 0;

    return broj_cvorova_neparnog_stepena==0 ? 2 : 1;
}







private:
vector<vector<int>>susedi;
vector<bool> visited;
int V;
vector<int>stepeni;   //graf ej neusemren pa su ovo i ulazni i izlazni
};



int main(){

  Graph g(5);

  // Ciklus
  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(2, 0);

  // Nije Ojlerov
  // g.add_edge(0, 1);
  // g.add_edge(1, 2);
  // g.add_edge(1, 4);
  // g.add_edge(2, 3);

  // Put
  // g.add_edge(0, 1);
  // g.add_edge(0, 2);
  // g.add_edge(0, 3);
  // g.add_edge(1, 2);
  // g.add_edge(1, 3);
  // g.add_edge(2, 3);
  // g.add_edge(2, 4);
  // g.add_edge(3, 4);

  int ojler=g.ojler();

  if(ojler==0) cout<<"nije ojlerov"<<endl;
  else if(ojler==1) cout<<"ima ojlerov put"<<endl;
  else cout<<"ima ciklus"<<endl;

    return 0;
}