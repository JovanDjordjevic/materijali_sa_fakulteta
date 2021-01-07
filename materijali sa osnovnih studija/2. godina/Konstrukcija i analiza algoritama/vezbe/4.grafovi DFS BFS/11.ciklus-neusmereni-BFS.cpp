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
    parents.resize(v);                               //!!!
    fill(parents.begin(),parents.end(),-1);
  }

  
   void add_edge(int u, int v){
     susedi[u].push_back(v);
     susedi[v].push_back(u);
   }

   

   bool bfs(int u){
     queue<int>red;
     red.push(u);
     int pom;

     while(!red.empty()){
       pom=red.front();
       red.pop();
       visited[pom]=true;

       for(int sused : susedi[pom]){
         if(!visited[sused]){
           parents[sused]=pom;
           red.push(sused);
         }
         else if(parents[pom]!=sused) return true;  //!!bitna linija, nemoj da obrnes ovo sused i pom
       }
     }
     return false;
   }




  private:
  vector<int>parents;   //!!

  int V;
  vector<vector<int>>susedi;
  vector<bool>visited;
  
};




int main(){

  /*Graph g(4);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 2);
  g.add_edge(2, 0);
  g.add_edge(2, 3);
  g.add_edge(3, 3);*/

  Graph g(3);
  g.add_edge(0, 1);
  g.add_edge(1, 2);

  cout << g.bfs(0) << endl;


  return 0;
}


