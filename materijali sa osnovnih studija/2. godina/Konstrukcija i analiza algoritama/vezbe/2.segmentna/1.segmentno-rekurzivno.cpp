#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;



void build_tree(vector<int> &niz, vector<int> &seg, int k, int x, int y){
   
   if(x==y){
      seg[k]=niz[x];   //seg[k]!!!!!!!
      return;
   }

   int m=(x+y)/2;

   build_tree(niz,seg,2*k,x,m);
   build_tree(niz,seg,2*k+1,m+1,y);

  seg[k]=seg[2*k]+seg[2*k+1];
  return;
}



int main(){

  vector<int> niz = { 1, 2, 3, 4, 5, 6, 7, 8 };

  int n=niz.size();

  int height=ceil(log2(n));
  int size=2*pow(2,height);

  vector<int> seg(size);

  build_tree(niz,seg,1,0,n-1);
        //niz, seg, k=1 tj indeks od kog se upisuje u segmentno, x=0,y=n-1
        // to je interval pocetnog niza koji obuhvata cvor sa k-toj poziciji seg stabla
  for(int x : seg){
    cout<<x<<" ";
  }

  return 0;
}
