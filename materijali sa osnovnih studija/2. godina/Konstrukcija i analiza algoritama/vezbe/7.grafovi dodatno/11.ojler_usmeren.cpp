//ni njen program ne ispisuje nista kad se doda ona grana u mainu

#include<iostream>
#include<vector>

using namespace std;

class Graph{
    public:
    vector<bool> visited;  //zbog kosaraju
Graph(int v){
    V=v;
    susedi.resize(v);
    visited.resize(v);
    fill(visited.begin(),visited.end(),false);
    ulazni_stepeni.resize(v);
    fill(ulazni_stepeni.begin(),ulazni_stepeni.end(),0);
}

void add_edge(int u,int v){
    susedi[u].push_back(v);
    ulazni_stepeni[v]++;
}

void dfs(int u){
    visited[u]=true;
    for(int sused : susedi[u]){
        if(!visited[sused]) dfs(sused);
    }
}
Graph reverse_edges(){
    Graph g(this->V);
    for(int i=0;i<V;i++)
        for(int sused : susedi[i])
            g.add_edge(sused,i);

   return g;         
}


bool kosaraju(){
    dfs(0);
    for(int i=0;i<V;i++)
            if(!visited[i]) return false;

    Graph g=reverse_edges();
    g.dfs(0);     
    for(int i=0;i<V;i++)
            if(!g.visited[i]) return false;   

  return true;
}

 

//znaci jeste ojlerov ako je jako povezan i ako je ulaznis tepen jednak izalznom za svaki cvor

bool ojler(){
    if(kosaraju()==false) return false;  //ako je jako povezan onda je ojlerov
  
    //ako ulazni stepen nije jednank izlaznom onda nema ciklus
    for(int i=0; i<V; i++)
        if(ulazni_stepeni[i]!=susedi[i].size())
                return false;

   return true;             
}




private:
vector<vector<int>>susedi;
int V;
vector<int>ulazni_stepeni;   
};



int main(){

  Graph g(5);

  // Jeste
  g.add_edge(0, 2);
  g.add_edge(0, 3);
  g.add_edge(1, 0);
  g.add_edge(2, 1);
  g.add_edge(3, 4);
  g.add_edge(4, 0);
  // Dodati ovu granu
  // g.add_edge(5, 6);

  //ovde zapravo ispitujemoda li ima ili nema ojlerov ciklus

  if(g.ojler()) cout<<"jeste"<<endl;
  else cout<<"nije"<<endl;

    return 0;
}