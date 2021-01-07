//izgleda dobro napisano ali ne izvrsava se ovaj dfs, ne razumem zaso

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph{
   public:
   Graph(int v){
	   V=v;
	   time=0;
	   susedi.resize(v);
	   visited.resize(v);
	   fill(visited.begin(),visited.end(),false);
	   times.resize(v);
	   fill(times.begin(),times.end(),-1);
	   lower_times.resize(v);
	   fill(lower_times.begin(),lower_times.end(),-1);
   }
   
   void add_edge(int u, int v){
	   susedi[u].push_back(v);
	   susedi[v].push_back(u);
   }



  void dfs(int u){
	  visited[u]=true;
	  times[u]=lower_times[u]=time;
	  time++;
	  int broj_dece=0;
	  for(int sused : susedi[u]){
		  if(!visited[sused]){
			  	parents[sused]=u;
				dfs(sused);
				broj_dece++;
				lower_times[u]=min(lower_times[u],lower_times[sused]);
				if(parents[u]==-1 && broj_dece>1)
						art_tacke.push_back(u);
				if(parents[u]!=-1 && times[u]<lower_times[sused]);
						art_tacke.push_back(u);		
		  }
		  else if(sused!=parents[u]){
			  	lower_times[u]=min(lower_times[u],lower_times[sused]);
		  }
	  }
  }
  



   //ako graf ima artikulacionu tacku onda ima samo 1 put rpeko nje 
   //pa nije bipovezan, ako posle dfsa ima neki neposecen to znaci da 
   //ima vise komponennti povezanosti pa opet ne moze biit bipovezan
   void bipovezan(){	   
	   dfs(0);
	   int broj_neposecenih=0;
	   for(bool b : visited){
		   if(!b) broj_neposecenih++;
	   }
	   if(art_tacke.size()>0 || broj_neposecenih>0)
		   cout<<"nije"<<endl;
	   else
	   		cout<<"jeste";
   }


   private:
   int V;
   vector<vector<int>>susedi;
   vector<int> visited;
   int time;
   vector<int> parents;
   vector<int> times;
   vector<int> lower_times;
   vector<int> art_tacke;
};



int main(){

   // Graph g(5);
  //
  // g.add_edge(1, 0);
  // g.add_edge(0, 2);
  // g.add_edge(2, 1);
  // g.add_edge(0, 3);
  // g.add_edge(3, 4);
  // g.add_edge(2, 4);

  Graph g(5);
  
  g.add_edge(1, 0);
  g.add_edge(0, 2);
  g.add_edge(2, 1);
  g.add_edge(0, 3);
  g.add_edge(3, 4);

  g.bipovezan();

	return 0;
}