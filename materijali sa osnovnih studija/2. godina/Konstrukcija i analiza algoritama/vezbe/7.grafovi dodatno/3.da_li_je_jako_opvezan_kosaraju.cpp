#include<iostream>
#include<vector>
#include<stack>

using namespace std;


class Graph{

public:
vector<bool>visited;   //ovde nam je zgodno da je ovo public zbog koraka u alg
Graph(int v){
    V=v;
    susedi.resize(v);
    visited.resize(v);
    fill(visited.begin(),visited.end(),false);
}

void add_edge(int u, int v){
    susedi[u].push_back(v);
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
        for(int sused : susedi[i]){
            g.add_edge(sused,i);
        }
     return g;   
}




bool kosaraju(){
    dfs(0);
    for(bool b : this->visited){
        if(!b) return false;  //ako ima neposecenih onda nije jako povezan
    }
   
    Graph g=reverse_edges();

    g.dfs(0);
    for(bool b : g.visited){
        if(!b) return false;  
    }

   return true;
}





private:
int V;
vector<vector<int>>susedi;
};



int main(){

Graph g(5);

  // Jeste
  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 0);
  g.add_edge(2, 4);
  g.add_edge(4, 2);

  // Nije
  // g.add_edge(0, 1);
  // g.add_edge(1, 2);
  // g.add_edge(2, 3);


if(g.kosaraju()) cout<<"jeste"<<endl;
else cout<<"nije"<<endl;



return 0;
}