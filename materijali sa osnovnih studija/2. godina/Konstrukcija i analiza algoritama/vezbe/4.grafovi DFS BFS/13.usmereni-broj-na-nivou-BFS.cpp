#include<iostream>
#include<queue>
#include<vector>

using namespace std;

class Graph{

public:
  Graph(int v){
    V=v;
    susedi.resize(v);
    visited.resize(v);
    fill(visited.begin(),visited.end(),false);
    levels.resize(v);
    //fil(levels.begin(),levels.end(),-1);
  }

  void add_edge(int u, int v){
    susedi[u].push_back(v);
  }


  void bfs(int u,int level){
    queue<int> red;
    red.push(u);

    int pom;
    levels[u]=0;

    while(!red.empty()){
      pom=red.front();
      red.pop();
      visited[pom]=true;
      

      for(int sused : susedi[pom]){
        if(!visited[sused]){
          levels[sused]=levels[pom]+1;
          red.push(sused);
        }
      }

    }


    int count=0;
    for(int x : levels){
      if(x==level) count++;
    }

    cout<<count<<endl;
  }






  private:
  int V;
  vector<vector<int>> susedi;
  vector<bool>visited;
  vector<int>levels;
};


int main(){

   Graph g(8);

  g.add_edge(0, 1);
  g.add_edge(0, 4);
  g.add_edge(0, 7);
  g.add_edge(4, 6);
  g.add_edge(4, 5);
  g.add_edge(4, 2);
  g.add_edge(7, 3);

  int level;

  cin >> level;

  g.bfs(0, level);
   

  return 0;
}