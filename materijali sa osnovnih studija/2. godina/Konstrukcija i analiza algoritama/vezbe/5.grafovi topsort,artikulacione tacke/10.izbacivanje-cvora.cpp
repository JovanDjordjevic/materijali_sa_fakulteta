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
  }

  void add_edge(int u, int v){
    susedi[u].push_back(v);
    susedi[v].push_back(u);
  }

//ako je cvor list u dfs stablu onda  se sigurno moze izbaciti
  //u zadatku se trazi da se izbaci samo 1, a ovo je nejno resenje i ono ispisuje 
  //sve listove u dfs stablu

//moze i das e izbaci bilo koji koji nije artikulaciona tacka  
  void dfs(int u){
    visited[u]=true;
    bool is_leaf=true;
    for(int sused : susedi[u]){
      if(!visited[sused]){
        dfs(sused);
        is_leaf=false;
      }
    }

    if(is_leaf){
      cout<<u<<endl;
    }
  }




  private:
  int V;
  vector<vector<int>>susedi;
  vector<bool>visited;
};



int main(){

   
  Graph g(5);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 1);
  g.add_edge(4, 0);
  g.add_edge(4, 1);

  // g.add_edge(0, 1);
  // g.add_edge(0, 3);
  // g.add_edge(1, 2);
  // g.add_edge(2, 3);
    
    g.dfs(0);

  return 0;
}