#include <iostream>
#include <vector>
#include <queue>


using namespace std;


class Graph{
 
  public:
    Graph(int v){
      V=v;
      susedi.resize(v);
      visited.resize(v);
      fill(visited.begin(),visited.end(),false);
      colors.resize(v);
      fill(colors.begin(),colors.end(),-1);
    }


    void add_edge(int u, int v){
      susedi[u].push_back(v);
    }


    bool bfs(int u, int color){

      queue<int>red;
      red.push(u);
      colors[u]=color;
      int pom;
     
      while(!red.empty()){
        pom=red.front();
        red.pop();
        visited[pom]=true;
        
        
        for(int sused : susedi[pom]){
          if(!visited[sused]){
            colors[sused]=abs(colors[pom]-1);
            red.push(sused);
          }
          else if(colors[pom]==colors[sused]) return false;
        }
      }
    return true;
    }


  private:
   int V;
   vector<vector<int>>susedi;
   vector<bool>visited;
   vector<int>colors;

};




int main(){

   Graph g(6);

  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 4);
  g.add_edge(4, 5);
  g.add_edge(5, 0);
  // Dodati ovu granu u graf i videti rezultat
  //g.add_edge(2, 0);

  cout << g.bfs(0,0) << endl;

  return 0;
}