#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Graph{
  

  public:
  Graph(int v){
    V=v;
    time=0;
    susedi.resize(v);
    visited.resize(v);
    fill(visited.begin(),visited.end(),false);
    parents.resize(v);
    fill(parents.begin(), parents.end(),-1);
    times.resize(v);
    fill(times.begin(),times.end(),-1);
    lower_times.resize(v);
    fill(lower_times.begin(),lower_times.end(),-1);
  }

  void add_edge(int u, int v){
    susedi[u].push_back(v);
    susedi[v].push_back(u);
  }



  void dfs(int u){
    visited[u]=true;
    times[u]=lower_times[u]=time;
    time++;
    int broj_dece=0;
    for(int sused : susedi[u]){
      if(!visited[sused]){
        parents[sused]=u;
        dfs(sused);
        broj_dece++;
        lower_times[u]=min(lower_times[u],lower_times[sused]);
        if(parents[u]==-1 && broj_dece>1)
            artikulacione_tacke.push_back(u);
        if(parents[u]!=-1 && times[u]<lower_times[sused])
           artikulacione_tacke.push_back(u);    
      }
      else if(sused!=parents[u]){
        lower_times[u]=min(lower_times[u],lower_times[sused]);
      }
    }

  }


  

  void print_artikulacione(){
    for(int x : artikulacione_tacke){
      cout<<x<<" ";
    }
    cout<<endl;
  }


  private:
  int V;
  vector<vector<int>> susedi;
  vector<bool>visited;
  vector<int>parents;                 //!!
  vector<int>times;                  //!!
  vector<int>lower_times;           //!!
  vector<int>artikulacione_tacke;     //!!
  int time;                             //!!
};





int main(){

  
  Graph g(5);

  g.add_edge(0, 2);
  g.add_edge(0, 3);
  g.add_edge(1, 0);
  g.add_edge(2, 1);
  g.add_edge(3, 4);
  //g.add_edge(2,4);

  g.dfs(0);
  g.print_artikulacione();



  return 0;
}