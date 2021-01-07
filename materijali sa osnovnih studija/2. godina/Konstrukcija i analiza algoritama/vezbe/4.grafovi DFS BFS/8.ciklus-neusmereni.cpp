#include<iostream>
#include<vector>

using namespace std;

class Graf{
  public:
    Graf(int V){
      this->V=V;
      susedi.resize(V);
      visited.resize(V);
      fill(visited.begin(),visited.end(),false);
    }


    void add_edge(int u,int v){
      susedi[u].push_back(v);
      susedi[v].push_back(u);
    }


    bool dfs(int cvor, int parent){
      visited[cvor]=true;
      for(int sused : susedi[cvor]){
        if(visited[sused]){ 
           if(sused!=parent) return true;
        }
        else if(dfs(sused,cvor)) return true;
      }
    return false;
    }




  private:
   int V;
   vector<vector<int>>susedi;
   vector<bool> visited;
};


int main(){

  Graf g(4);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 2);
  g.add_edge(2, 0);
  g.add_edge(2, 3);
  g.add_edge(3, 3);

  /*Graf g(5);
  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(2,3);
  g.add_edge(2,4);*/


  //pocinjemo od cvora 0 i njegov parent je -1
 cout << g.dfs(0, -1) <<endl;


  return 0;
}