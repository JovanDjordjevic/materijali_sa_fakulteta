#include<iostream>
#include<vector>
#include<queue>

using namespace std;


class Graph{
   public:
   Graph(int v){
       V=v;
       susedi.resize(v);
       stepeni.resize(v);
       fill(stepeni.begin(),stepeni.end(),0);
   }

   void add_edge(int u, int v){
       susedi[u].push_back(v);
       stepeni[v]++;  
   }

  
   void topsort_kan(){
       queue<int> red;
       for(int i=0;i<V;i++){
           if(stepeni[i]==0) red.push(i);
       }
       int pom; 
       while(!red.empty()){
           pom=red.front();
           red.pop();
           
            cout<<pom<<" ";

           for(int sused : susedi[pom]){
               stepeni[sused]--;
               if(stepeni[sused]==0) red.push(sused);
           }
       }
   }



    private:
    int V;
    vector<vector<int>>susedi;
    vector<int> stepeni;
};




int main(){

   Graph g(6);

  g.add_edge(0, 1);
  g.add_edge(1, 4);
  g.add_edge(2, 4);
  g.add_edge(3, 0);
  g.add_edge(3, 2);
  g.add_edge(5, 2);
  g.add_edge(5, 4);

  g.topsort_kan();


    return 0;
}