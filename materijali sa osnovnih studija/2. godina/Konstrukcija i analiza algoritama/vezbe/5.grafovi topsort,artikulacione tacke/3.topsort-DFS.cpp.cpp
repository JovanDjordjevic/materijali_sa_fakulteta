#include<iostream>
#include<vector>
#include<stack>

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
    }

    void dfs(int u){
      visited[u]=true;
      for(int sused : susedi[u]){
        if(!visited[sused]) dfs(sused);
      }
      s.push(u);
    }



    void topsort(){
      for(int i=0;i<V;i++){
        if(!visited[i]) dfs(i);
      }

      while(!s.empty()){
        cout<<s.top()<<" ";
        s.pop();
      }
      cout<<endl;
    }
 


  private:
  int V;
  vector<vector<int>>susedi;
  vector<bool>visited;
  stack<int> s;  //!!
};



int main(){
  Graph g(6);

  // g.add_edge(5, 2);
  // g.add_edge(5, 0);
  // g.add_edge(4, 0);
  // g.add_edge(4, 1);
  // g.add_edge(2, 3);
  // g.add_edge(3, 1);

  g.add_edge(0, 1);
  g.add_edge(1, 4);
  g.add_edge(2, 4);
  g.add_edge(3, 0);
  g.add_edge(3, 2);
  g.add_edge(5, 2);
  g.add_edge(5, 4);

  g.topsort();

  return 0;
}