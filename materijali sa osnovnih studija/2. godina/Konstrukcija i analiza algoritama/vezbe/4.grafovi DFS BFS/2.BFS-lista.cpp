#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <queue>

using namespace std;
/*
struct graf(){
  vector<list<int>> lista;
  vector<bool>oznaceni;

 void ucitaj_graf(int n){
	if(n<=0) {//err}
	inicijalizacija(n);
        for(int i=0;i<n;i++){
	  int m;
	  cin>>m;
	  for(int j=0;j<m;j++){
		int sused;
		cin>>sused;
		lista[i].push(sused);
	  }
        }
 }


 
 void BFS(int cvor){
   queue<int> red;
   red.push(cvor);
   visited[cvor]=true;
   int tmp;
   while(!red.empty()){
	tmp=red.front();
	red.pop();
	for(auto it : lista[tmp]){
	  if(!visited[*it]){ visited[*it]=true; red.oush(*it);  }
	}
   }
 }



 void inicijalizacija(int n){
    for(int i=0;i<lista.size();i++) lista[i].clear();	
    lsita.clear();
    oznaceni.clear();
    lsita.resize(n);
    oznaceni.resize(n);
 }

};
*/

int main(){

   vector<int> v1;
   vector<int>v2;

   int num;
   string line;
   getline(cin,line);

   istringstream iss(line);
   while(iss>>num){
       v1.push_back(num);
   }

   for(int x : v1){
       cout<<x<<" ";
   }
   cout<<endl;



   getline(cin,line);

   istringstream iss(line);
   while(iss>>num){
       v2.push_back(num);
   }

   for(int x : v2){
       cout<<x<<" ";
   }
   cout<<endl;

    return 0;
}