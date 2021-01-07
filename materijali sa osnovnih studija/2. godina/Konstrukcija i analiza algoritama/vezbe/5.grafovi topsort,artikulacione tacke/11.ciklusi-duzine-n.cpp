
//ovde nesto en valja, ne racuna ni njoj dobro

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


class Graph{

  public: 
  Graph(int v){
    V=v;
    broj_ciklusa=0;
    susedi.resize(v);
    visited.resize(v);
    fill(visited.begin(),visited.end(),false);
  }

  void add_edge(int u, int v){
    susedi[u].push_back(v);
    susedi[v].push_back(u);
  }
 

 void dfs(int u,int start, int n){
   visited[u]=true;
   if(n==0){
     if( find(susedi[u].begin(),susedi[u].end(),start)!=susedi[u].end() ){
       broj_ciklusa++;
     }
     visited[u]=false;  //!!
     return;
   }

   for(int sused : susedi[u]){
     if(!visited[u]) dfs(sused,start,n-1);
   }

   visited[u]=false;  //!!
 }
 

  
  int izborj_cikluse(int n){
    for(int i=0; i<V ;i++){
      if(!visited[i]){
        dfs(i,i,n-1);
        visited[i]=true;
      }
    }
    return broj_ciklusa/2;
  }



  private:
  int V;
  vector<vector<int>>susedi;
  vector<bool>visited;
  int broj_ciklusa;
};



int main(){

  int n;
  cin >> n;

  Graph g(4);

  g.add_edge(0, 1);
  g.add_edge(0, 3);
  g.add_edge(1, 2);
  // g.add_edge(1, 4);
  g.add_edge(2, 3);
  g.add_edge(2, 3);
  // g.add_edge(3, 4);

  cout << g.izborj_cikluse(n) << "\n";
  return 0;
}