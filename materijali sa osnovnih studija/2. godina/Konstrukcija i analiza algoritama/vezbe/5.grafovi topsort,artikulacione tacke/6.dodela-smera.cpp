#include<iostream>
#include<vector>
#include<queue>

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
    topsort_pozicije.resize(v);
    fill(topsort_pozicije.begin(),topsort_pozicije.end(),-1);   //!!!
  }

  void add_directed_edge(int u, int v){
      susedi[u].push_back(v);
      stepeni[v]++;
      pair<int,int> p(u,v);   //!!
      edges.push_back(p);     //!!
  }
  void add_undirected_edge(int u,int v){
    pair<int,int> p(u,v);   //!!
    undirected_edges.push_back(p);     //!!
  }


  void topsort(){
    queue<int> red;
    for(int i=0;i<V;i++){
      if(stepeni[i]==0) red.push(i);
    }
    int curr_poz=0;
    int pom;
    while(!red.empty()){
      pom=red.front();
      red.pop();
      topsort_pozicije[pom]=curr_poz;
      curr_poz++;
      for(int sused : susedi[pom]){
        stepeni[sused]--;
        if(stepeni[sused]==0) red.push(sused);
      }
    }
  }
 


  bool dfs(int cvor){
    visited[cvor]=true;
    for(int sused : susedi[cvor]){
      if(visited[sused]) return true;
      else if(dfs(sused)) return true;
    }
    visited[cvor]=false;
    return false;
  }




   void usmeri(){
    
      topsort();
      
      for (auto p : undirected_edges){
        if(topsort_pozicije[p.first] < topsort_pozicije[p.second]){
          add_directed_edge(p.first,p.second);
          added_edges.push_back(p);
        }
        else{
          add_directed_edge(p.second,p.first);
          pair<int,int> tmp(p.second,p.first);
          added_edges.push_back(tmp);
        }
      }
      if(dfs(0))                       //zasto bas od 0?
          cout<<"ima ciklus"<<endl;
      else
          cout<<"nema ciklus"<<endl;    

     //ispis svih grana...
   }


   





  private:
  int V;
  vector<vector<int>> susedi;
  vector<int> visited;
  vector<int> stepeni;            //!!!
  vector<int> topsort_pozicije;    //!!
  vector<pair<int,int>>edges;       //!!!!
  vector<pair<int,int>>undirected_edges;  //!!!
  vector<pair<int,int>>added_edges;   //!!!
};




int main(){

  Graph g(6);

  g.add_directed_edge(0, 1);
  g.add_directed_edge(0, 5);
  g.add_directed_edge(1, 2);
  g.add_directed_edge(1, 3);
  g.add_directed_edge(1, 4);
  g.add_directed_edge(2, 3);
  g.add_directed_edge(2, 4);
  g.add_directed_edge(3, 4);

  g.add_undirected_edge(0, 2);
  g.add_undirected_edge(0, 3);
  g.add_undirected_edge(4, 5);

  g.usmeri();

  return 0;
}