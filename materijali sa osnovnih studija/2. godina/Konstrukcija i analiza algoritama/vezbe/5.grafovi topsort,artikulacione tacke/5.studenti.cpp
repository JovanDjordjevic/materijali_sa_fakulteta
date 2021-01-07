#include<iostream>
#include<vector>
#include<queue>

class graf{
public:
 graf(int v){
   this->v=v;
   visited.resize(v);
   fill(visited.bvegin(),visited.end(),false);
   susedi.resize(v);

   stepeni.resize(v);
   fill(stepeni.begin(),stepeni,end(),0);
 }

 void add_edge(int u,int v){
   susedi[u].push_back(v);
   stepeni[v]++;
 }



bool topsort(vector<int>&result){
 queue<int> nodes;
 for(int i=0;i<v;i++) if(stepeni[i]==0) nodes.push(i);

 int tmp;
 while(nodes.size()){
   tmp=nodes.front();
   nodes.pop();
   result.push_back(tmp);
   for(int node : susedi[tmp]){
	stepeni[node]--;
	if(stepeni[node]==0) nodes.push(node);
   }
 }

  for(int i;i<v;i++){
  	if(stepeni[i]!=0) return false;
  }
 
  return true;
}


private:
 vector<vector<int>>susedi;
 vector<bool> visied;
 int v;
 vector<int> stepeni;
};


int main(){

int n,k,x;
cin>>n;

graf g(n);

for(int i=0;i<n;i++){
  cin>>k;
  for(int j=0;j<k;j++){
	cin>>x;
	g.add_edge(x-1,i);
  }
}

vector<int>result;
if(g.topsort(result)) {
 cout<<"DA";
 for(int x : result) cout<<x;
}

else cout<<"NE";


return 0;
}