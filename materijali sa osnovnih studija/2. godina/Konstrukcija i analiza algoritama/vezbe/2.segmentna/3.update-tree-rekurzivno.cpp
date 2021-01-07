#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;


void build_tree(vector<int>&niz, vector<int>&seg,int k, int x, int y){
  if(x==y){
    seg[k]=niz[x];
    return;
  }
  int m=(x+y)/2;
  build_tree(niz,seg,2*k,x,m);
  build_tree(niz,seg,2*k+1,m+1,y);
  seg[k]=seg[2*k]+seg[2*k+1];
}



//x=0 i y=n-1 na pocetku, ovo oznacava interval u POCETNOM nizu koji obuhvata cvor k
void update(vector<int>&seg,int k, int x, int y, int poz, int vrednost){  //!!!!
  if(x==y){
    seg[k]=vrednost;
    return;
  }

 int m=(x+y)/2;

 if(poz<=m)
    update(seg,2*k,x,m,poz,vrednost);
 else
    update(seg,2*k+1,m+1,y,poz,vrednost);

  seg[k]=seg[2*k]+seg[2*k+1];  
}





int main(){
 
  vector<int> niz={1,2,3,4,5,6,7,8};
  int n=niz.size();
  int height=ceil(log2(n));
  int size=2*pow(2,height);
  vector<int> seg(size);
  build_tree(niz,seg,1,0,n-1);

  for(int x : seg){
    cout<<x<<" ";
  }
  cout<<endl;

  update(seg,1,0,n-1,2,8);
  //seg, k=1 trenutna poz, 0 do n-1 deo pcoetnog niza koji obuhvta cvor na poz k, poz=2
  //je poz na kloju upiosujemo novu vrednost =8
  
   for(int x : seg){
    cout<<x<<" ";
  }
  cout<<endl;

  return 0;
}