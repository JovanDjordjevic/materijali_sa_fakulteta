//rezultat u vom zadatku zavisi od redosleda unosa tacaka
#include<iostream>
#include<vector>
#include<list>
#include<cstdlib>

#define MAX 100

using namespace std;

struct Tacka{
  int x;
  int y;
};


//da li su t3 i t4 sa site strane prave koju odredjuju t1 i t2
//ako nisu A3*A4 bice < 0
bool saIsteStrane(Tacka t1, Tacka t2, Tacka t3, Tacka t4){

  int A3= (t3.x-t1.x)*(t2.y-t1.y) - (t2.x-t1.x)*(t3.y-t1.y);
  int A4= (t4.x-t1.x)*(t2.y-t1.y) - (t2.x-t1.x)*(t4.y-t1.y);

  if(A3*A4<0) return false;
  else return true;
}


//da bi mnogougao bio konveksan potrebno i dovoljno je da kada se povuce prava kroz bilo koja dva susedna temena
//mnogougla, sva ostala temena budu sa iste strane te prave
int main(){

  Tacka mnogougao[MAX];
  
  int i,j,n;
  cin>>n;

  for(int i=0;i<n;i++)
    cin>>mnogougao[i].x>>mnogougao[i].y;


  int konveksan=1;  //da bismo imali odsecanje ako naidjemo na neke koji ne daju konveksni

  for(i=0; konveksan && i<n-1; i++){
    for(j=0; konveksan && j<n-1; j++)
        konveksan = konveksan && saIsteStrane(mnogougao[i],mnogougao[i+1],mnogougao[j],mnogougao[j+1]);
    for(j=i+2; konveksan && j<n-1;j++)
        konveksan = konveksan && saIsteStrane(mnogougao[i],mnogougao[i+1],mnogougao[j],mnogougao[j+1]);
    if(i!=0 && i!=n-1 && i+1!=0 && i+1!=n-1)
       konveksan = konveksan && saIsteStrane(mnogougao[i],mnogougao[i+1],mnogougao[0],mnogougao[n-1]);
  }

  for(j=1; konveksan && j<n-2; j++)
      konveksan=konveksan && saIsteStrane(mnogougao[0],mnogougao[n-1],mnogougao[j],mnogougao[j+1]);
  
  if(konveksan)
    cout<<"jeste konveksan"<<endl;
  else
    cout<<"nije konveksan"<<endl;  

  

  return 0;
}
