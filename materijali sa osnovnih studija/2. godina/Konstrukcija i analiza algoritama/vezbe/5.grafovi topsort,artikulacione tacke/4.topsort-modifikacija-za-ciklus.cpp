//izgleda sve dobro ali ne ispisuje mi dobar rezultat, njoj ispisuje dobar

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Graph{

public:
  Graph(int v){
	V=v;
	visited.resize(v);
	susedi.resize(v);
	fill(visited.begin(),visited.end(),false);
	stepeni.resize(v);
	fill(stepeni.begin(),stepeni.end(),0);

	found=false;                              //!!!!za ciklus
  }

 void add_edge(int u, int v){
   susedi[u].push_back(v);
   stepeni[u]++;
 }



void topsort(vector<int>&rez){
  queue<int>red;
  for(int i=0;i<V;i++){
    if(stepeni[i]==0) red.push(i);
  }
  int pom;
  while(!red.empty()){
    pom=red.front();
    red.pop();
    rez.push_back(pom);
    for(int sused : susedi[pom]){
      stepeni[sused]--;
      if(stepeni[sused]==0) red.push(sused);
    }
  }
}

void DFS(int cvor){
  if(visited[cvor]){
    cout<<cvor<<endl;
    found=true;
    return;
  }

  visited[cvor]=true;
  cout<<cvor<<" -> ";

  for(int sused : susedi[cvor]){
    if(!found){
      DFS(sused);
    }
  }
}




void find(){
  vector<int> rez;
  topsort(rez);

  bool topologic=true;

  for(int i=0;i<V;i++){
    if(stepeni[i]!=0) topologic=false;
  }

  if(topologic){
      for(int x : rez){
        cout<<x<<" ";
      }
      cout<<endl;
      return;
  }
  else{
     for(int i=0;i<V;i++){
       if(stepeni[i]!=0){
         DFS(i);
         return;
       }
     }
  }
}







private:
vector<vector<int>> susedi;
vector<bool> visited;
int V;
vector<int> stepeni;
bool found;
};


int main(){

Graph g(5);

  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(2, 3);
  g.add_edge(3, 4);
  g.add_edge(4, 1);
  g.add_edge(4, 2);
  // g.add_edge(0, 1);
  // g.add_edge(1, 4);
  // g.add_edge(2, 4);
  // g.add_edge(3, 0);
  // g.add_edge(3, 2);
  // g.add_edge(5, 2);
  // g.add_edge(5, 4);

  // g.add_edge(0, 1);
  // g.add_edge(1, 2);
  // g.add_edge(2, 3);
  // g.add_edge(3, 4);
  // g.add_edge(4, 3);
  // g.add_edge(4, 5);
  // g.add_edge(5, 6);

  g.find();

}