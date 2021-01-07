#include<iostream>
#include<vector>
#include<climits>

using namespace std;


class Graph{
  
  public:
   Graph(int V){
      this->V=V;
      susedi.resize(V);
      visited.resize(V);
      fill(visited.begin(),visited.end(), false);
      min_edges=INT_MAX;
   }

  void add_edge(int u,int v){
    susedi[u].push_back(v);
  }

  int get_min_edges(){
    return min_edges;
  }
   

   void DFS(int u, int v, int current_edges){
     if(u==v){
       if(current_edges<min_edges){
         min_edges=current_edges;
       }
       return;
     }

     visited[u]=true;
     for(int sused: susedi[u]){
       if(!visited[sused]){
         DFS(sused,v,current_edges+1);
       }
     }
    visited[u]=false;
   }


  private:
   int V;
   vector<vector<int>> susedi;
   vector<bool> visited;
   int min_edges;
};




int main(){
 
 int u, v;

  cin >> u >> v;

  Graph g(5);

  g.add_edge(0, 1);
  g.add_edge(1, 0);
  g.add_edge(0, 4);
  g.add_edge(4, 0);
  g.add_edge(1, 2);
  g.add_edge(2, 1);
  g.add_edge(2, 4);
  g.add_edge(4, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 2);
  g.add_edge(3, 4);
  g.add_edge(4, 3);

  // g.add_edge(0, 1);
  // g.add_edge(0, 4);
  // g.add_edge(1, 2);
  // g.add_edge(2, 4);
  // g.add_edge(2, 3);
  // g.add_edge(3, 4);

g.DFS(u,v,0);
cout<<g.get_min_edges()<<endl;


  return 0;
}