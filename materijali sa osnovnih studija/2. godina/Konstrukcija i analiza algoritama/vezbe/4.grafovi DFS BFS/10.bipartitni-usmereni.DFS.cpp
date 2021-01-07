#include<iostream>
#include<vector>

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

   
    bool dfs(int cvor, int color){
		visited[cvor]=true;
		colors[cvor]=color;

		for(int sused : susedi[cvor]){
			if(colors[sused]==colors[cvor]) return false;
			if(!visited[sused]){
				if(!dfs(sused,abs(color-1))) return false;
			}
		}
		return true;
	}




	private:
	int V;
	vector<vector<int>>susedi;
	vector<bool> visited;
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
  //g.add_edge(2,0);
   

 cout<<g.dfs(0,0)<<endl;
	return 0;
}