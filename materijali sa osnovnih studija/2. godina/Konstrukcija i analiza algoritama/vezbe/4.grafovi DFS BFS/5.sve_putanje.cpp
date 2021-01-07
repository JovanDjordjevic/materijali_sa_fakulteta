#include<iostream>
#include<vector>

using namespace std;

class Graph{

public:
 Graph(int V){
   this->V=V;
   visited.resize(V,false);
   susedi.resize(V);
 }

 void add_edge(int u, int v){
   susedi[u].push_back(v);
 }

 void dfs(int u, int v, vector<int> put){   //put ovde nije sa & jer hocemo sve puteve, dakle treba nam da savaki rek poziv ima svoj put
  if(u==v){
    put.push_back(v);
    for(int x : put) cout<<x<< "-> ";
    cout<<endl;
    return;
  }
  
  visited[u]=true;
  put.push_back(u);

  for(int sused : susedi[u]){
    if(!visited[sused]) dfs(sused,v,put);
  }

  visited[u]=false;
 }




private:
vector<vector<int>>susedi;
int V;
vector<bool> visited;
};




int main(){

   int u, v;
  cin >> u >> v;

  Graph g(4);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(0, 3);
  g.add_edge(2, 0);
  g.add_edge(2, 1);
  g.add_edge(1, 3);

 vector<int> result;

 g.dfs(u,v,result);

  return 0;
}