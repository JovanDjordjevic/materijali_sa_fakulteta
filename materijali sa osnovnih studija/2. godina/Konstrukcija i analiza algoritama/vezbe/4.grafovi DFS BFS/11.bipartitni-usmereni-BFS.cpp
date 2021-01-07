#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class graf{
public:
 graf(int v){
  this->v=v;
  visited.resize(v);
  fill(visited.begin(),visited.end(),false);
  susedi.resize(v);
  
  colors.resize(v);
  fill(colors.begin(),colors.end(),-1);  //za ispitivanje biparittnosti
 }

void add_edge(int u, int v){ susedi[u].push_back(v); }


bool BFS(int u){
  queue<int> nodes;
  nodes.push(u);
  
  int tmp;
  colors[0]=0;
  while(!nodes.empty()){
    tmp=nodes.front();
    nodes.pop();
    visited[tmp]=true;
    
    auto pocetak=susedi[tmp].begin();
    auto kraj=susedi[tmp].end();
    while(pocetak!=kraj){
	if(colors[*pocetak]==colors[tmp])  {return false;}
	if(!visited[*pocetak]){
	  colors[*pocetak]=!colors[tmp];
	  nodes.push(*pocetak);
	}
      pocetak++;
    }
  }
  return true;
}


private:
 vector<vector<int>> susedi;
 vector<bool> visited;
 int v;
 vector<int>colors;   //

};



int main(){

...

g.BFS(0);  


}