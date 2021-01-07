#include<iostream>
#include<vector>
#include<stack>

using namespace std;


class Graph{

public:
Graph(int v){
    V=v;
    susedi.resize(v);
    time=0;
    times.resize(v);
    fill(times.begin(),times.end(),-1);
    lower_times.resize(v);
    fill(lower_times.begin(),lower_times.end(),-1);    
    u_steku.resize(v);
    fill(u_steku.begin(),u_steku.end(),false);
}

void add_edge(int u, int v){
    susedi[u].push_back(v);
}



void dfs(int u){
    times[u]=lower_times[u]=time;
    time++;

    stek.push(u);
    u_steku[u]=true;

    for(int sused : susedi[u]){
        if(times[sused] == -1){    //ovaj uslov je ekvivalentan tome da !visited[sused]
            dfs(sused);
            lower_times[u]=min(lower_times[u],lower_times[sused]);
        }
        else if(u_steku[sused]==true){
            lower_times[u]=min(lower_times[u],lower_times[sused]);
        }
    }


    if(times[u]==lower_times[u]){   //ovo je uslov da bi u bio abzni cvor jake komponente
            while(1){
                int v=stek.top();
                stek.pop();
                cout<<v<<" ";
                u_steku[v]=false;
                if(v==u){           //ako smo dosli do korena onda smo obisli celu jaku komponentu
                    cout<<endl;
                    break;
                }
            }
    }

}




private:
int V;
vector<vector<int>>susedi;
int time;
vector<int>times;
vector<int>lower_times;
stack<int> stek;           //!!!
vector<bool> u_steku;   //!!!
};



int main(){

Graph g(8);

  g.add_edge(0, 1);
  g.add_edge(0, 2);
  g.add_edge(1, 0);
  g.add_edge(1, 3);
  g.add_edge(2, 3);
  g.add_edge(3, 4);
  g.add_edge(3, 5);
  g.add_edge(4, 2);
  g.add_edge(4, 5);
  g.add_edge(4, 6);
  g.add_edge(5, 7);
  g.add_edge(6, 5);
  g.add_edge(7, 6);

  // g.add_edge(0, 1);
  // g.add_edge(0, 2);
  // g.add_edge(0, 7);
  // g.add_edge(1, 3);
  // g.add_edge(1, 4);
  // g.add_edge(2, 5);
  // g.add_edge(4, 6);
  // g.add_edge(5, 8);
  // g.add_edge(6, 1);
  // g.add_edge(8, 0);

  // g.add_edge(0, 1);
  // g.add_edge(1, 2);
  // g.add_edge(2, 3);
  // g.add_edge(3, 1);
  // g.add_edge(3, 0);

  // g.add_edge(0, 1);
  // g.add_edge(1, 2);
  // g.add_edge(2, 3);
  // g.add_edge(3, 0);
  // g.add_edge(5, 0);
  // g.add_edge(5, 4);

  g.dfs(0);

return 0;
}