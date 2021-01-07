#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using namespace std;


class Graph{
    public:
    Graph(int v){
        V=v;
        susedi.resize(v);
        visited.resize(v);
        fill(visited.begin(),visited.end(),false);
        parents.resize(v);
        fill(parents.begin(),parents.end(),-1);
    }


    void add_edge(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }



   void bfs(int cvor,int v){
       queue<int>red;
       red.push(cvor);
       visited[cvor]=true;
       int pom;
       while(!red.empty()){
           pom=red.front();
           red.pop();
           if(pom==v) return;
           for(int sused : susedi[pom]){
               if(!visited[sused]){
                   visited[sused]=true;
                   parents[sused]=pom;
                   red.push(sused);
               }
           }
       }
   }


   void print_path(int u, int v){
     

     bfs(u,v);
     if(parents[v]==-1) {
         cout<<"ne postoji put"<<endl;
     }

     stack<int> s;

     s.push(v);
     while(parents[v]!=-1){
         v=parents[v];
         s.push(v);
     }

     while(!s.empty()){
         cout<<s.top()<<" ";
         s.pop();
     }
     cout<<endl;


   }

    private:
    vector<int> parents;   //!!!!
    int V;
    vector<vector<int>> susedi;
    vector<bool>visited;
};



int main(){

     Graph g(8);

  g.add_edge(0, 1);
  g.add_edge(0, 3);
  g.add_edge(1, 2);
  g.add_edge(3, 4);
  g.add_edge(3, 7);
  g.add_edge(4, 5);
  g.add_edge(4, 6);
  g.add_edge(4, 7);
  g.add_edge(5, 6);
  g.add_edge(6, 7);

  int u, v;

  cin >> u >> v;

  g.print_path(u, v);


    return 0;
}