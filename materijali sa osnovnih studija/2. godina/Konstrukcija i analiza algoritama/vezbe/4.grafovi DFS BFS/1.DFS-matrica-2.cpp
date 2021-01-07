#include<iostream>
#include<vector>

using namespace std;

struct graf{
vector<vector<int>> matrica;
vector<bool> oznaceni;

  void ucitaj_graf(int n){
    inicijalizacija(n);
    for(int i=0;i<n;i++){
	matrica[i].resize(n);
	oznaceni[i]=false;
	for(int j=0;j<n;j++) cin >> matrica[i][j];
    }
  }
  
  void DFS(int cvor){
   if(cvor<0 || cvor>=oznaceni.size())  {//obrada greske}
   cout<<"dolazna numeracija"<<cvor<<" ";
   oznaci(cvor);
   for(int j=0;j<matrica[cvor].size();j++)
	if(psotoji_grana(cvor,j) && !oznacen[j])
		DFS(j);
   //cout...
  }
  

  void inicijalizacija(int n){
      for(int i=0;i<matrica.size();i++)  matrica[i].clear();
	
	matrica.clear();
	oznaceni.clear();
	matrica.resize(n);
	oznaceni.resize(n);
  }

   void oznaci(int cvor){ oznaceni[cvor]=true; }
   bool postoji_grana(int i, int j) { return matrica[i][j] }
}



int main(){

...
...
}