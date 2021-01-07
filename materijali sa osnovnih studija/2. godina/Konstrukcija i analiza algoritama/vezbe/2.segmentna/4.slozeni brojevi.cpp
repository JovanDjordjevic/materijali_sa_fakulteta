#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

#define MAX 10000

using namespace std;

//u mainu su svis tavljeni na true, dakle ovde odredjujemo koji su prosti a koji nisu
//u intervalu [0,MAX]
void eratostenovo_sito(vector<bool>&prime){
    prime[1]=true;
    for(int p=2; p*p<=MAX;p++){
        if(prime[p]==true){
            for(int i=p*2;i<=MAX;i+=p)
                        prime[i]=false;
        }
    }
}



//us eg stablu stavljamo 0 ako je niz[i] prost a 1 inace, tako svi listovi 
//koji odgovaraju slozenim brojevima imaju vrednost 1, ostatak stabla govori o
//broju prostih u intervalu
void build_tree(vector<int>&niz, vector<int>&seg, vector<bool>&prime, int k, int x, int y){

  if(x==y){
      seg[k]=prime[niz[x]] ? 0 : 1;    //!!!
      return;
  }

  int m=(x+y)/2;
  build_tree(niz,seg,prime,2*k,x,m);
  build_tree(niz,seg,prime,2*k+1,m+1,y);
  
  seg[k]=seg[2*k]+seg[2*k+1];
}




int broj_slozenih(vector<int>&seg,int k, int x, int y, int a , int b){
   if(a>y || b<x) return 0;
   if(a>=x && b<=y) return seg[k];
   
   int m=(x+y)/2;

   return broj_slozenih(seg,2*k,x,m,a,b) + broj_slozenih(seg,2*k+1,m+1,y,a,b);
}



//..funckije za update




int main(){

    vector<int>niz= { 1, 12, 3, 5, 17, 9 };

    vector<bool> prime(MAX,true);

    eratostenovo_sito(prime);

    int n=niz.size();
    int height=ceil(log2(n));
    int size=2*pow(2,height);

    vector<int> seg(size);

    build_tree(niz,seg,prime,1,0,n-1);

    cout<<broj_slozenih(seg,1,0,n-1,0,4);

    return 0;
}