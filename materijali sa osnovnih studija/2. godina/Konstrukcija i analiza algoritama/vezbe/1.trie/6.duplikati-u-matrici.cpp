#include<iostream>
#include<vector>
#define MAX 100

using namespace std;

struct Cvor{

  Cvor(){
    count=0;
    nodes[0]=nullptr;
    nodes[1]=nullptr;
  }

  int count;
  Cvor *nodes[2];   //jer je matrica binarna pa cvor moze imati najvise 2 deteta
};




//ovo je njeno resenje i ispisuje i 3 i 5, a ne samo 5 kao sto se trazi u zadatku
void dodaj_red(Cvor *koren, int red[MAX],int n,int i, int number){

    if(i==n){
      koren->count++;
      if(koren->count > 1){
        cout<<"Red duplikat: "<<number<<endl;   
      }
      return;
    }


  if(koren->nodes[red[i]]==nullptr){
    koren->nodes[red[i]]=new Cvor();
  }

  dodaj_red(koren->nodes[red[i]],red,n,i+1,number);
}








int main(){
  
 int matrix[MAX][MAX] = {
    {1, 0, 0, 1, 0},
		{0, 1, 1, 0, 0},
		{1, 0, 0, 1, 0},
		{0, 0, 1, 1, 0},
		{0, 1, 1, 0, 0}
  };

  int n=5;

  Cvor *koren=new Cvor();
  
  for(int i=0;i<n;i++){
    dodaj_red(koren,matrix[i],n,0,i+1);
        //n je duzina reda, 0  je poz u redu do koje smo stigli, i+1 je redni broj reda
  }


  
  
  return 0;
}
