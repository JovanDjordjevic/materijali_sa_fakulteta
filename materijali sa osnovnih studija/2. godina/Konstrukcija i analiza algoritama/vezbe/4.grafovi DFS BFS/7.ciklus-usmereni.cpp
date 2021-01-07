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

   void add_edge(int u, int v){
     susedi[u].push_back(v);
   }
    
bool DFS(int u){
  
  visited[u]=true;
  for(int sused : susedi[u]){
    if(visited[sused]) return true;
    if(DFS(sused)) return true;

  }
 visited[u]=false;   //!!!!
 return false;
}


  private:
  int V;
  vector<vector<int>> susedi;
  vector<bool>visited;
};


int main(){

 Graf g(4);
  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 2);
  g.add_edge(2, 0);
  g.add_edge(2, 3);
  g.add_edge(3, 3);

  /*Graf g(3);
  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(0, 2);*/

  cout<<g.DFS(0)<<endl;

  return 0;
}