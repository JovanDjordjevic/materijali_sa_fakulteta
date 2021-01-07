#include<iostream>
#include<vector>
#include<stack>

using namespace std;

class Graph{
  public:
  Graph(int v){
    V=v;
    susedi.resize(v);
}

void add_edge(int u,int v){
    susedi[u].push_back(v);
}




void hirholcer(){
     stek.push(0);
     int v=0;
     int tmp;
     while(!stek.empty()){
         if(susedi[v].size() > 0) {
             stek.push(v);
             tmp=susedi[v].back();
             susedi[v].pop_back();
             v=tmp;
         }
         else{
             ojlerov_put.push_back(v);
             v=stek.top();
             stek.pop();
         }
     }

     for(int i=ojlerov_put.size()-1 ; i>=1 ; i--)
            cout<<ojlerov_put[i]<<" -> ";
    cout<<endl;
}



private:
vector<vector<int>>susedi;
int V;
stack<int> stek;      //!!!
vector<int>ojlerov_put;  //!!
};



int main(){

  Graph g(5);

  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(1, 3);
  g.add_edge(2, 0);
  g.add_edge(3, 4);
  g.add_edge(4, 1);

  g.hirholcer();

    return 0;
}