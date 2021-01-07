#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<climits>

using namespace std;

struct Cvor{
  int largest;
  int sec_largest;
};


void build_tree(vector<int> &niz, vector<Cvor>&seg, int k, int x, int y){
  
  if(x==y){
    seg[k].largest=niz[x];
    seg[k].sec_largest=INT_MIN;
    return;
  }

  int m=(x+y)/2;

  build_tree(niz,seg,2*k,x,m);
  build_tree(niz,seg,2*k+1,m+1,y);

  seg[k].largest=max(seg[2*k].largest,seg[2*k+1].largest);
  seg[k].sec_largest=min( max(seg[2*k].largest,seg[2*k+1].sec_largest) 
       , max(seg[2*k].sec_largest , seg[2*k+1].largest)  );
}



Cvor max_proizvod(vector<Cvor> &seg, int k, int x, int y, int a, int b){
   
    Cvor rez;
    rez.largest=INT_MIN;
    rez.sec_largest=INT_MIN;
  
    if(x> b || y<a) return rez;
    if(x>=a && y<=b ) return seg[k];

    int m=(x+y)/2;

    Cvor levo=max_proizvod(seg,2*k,x,m,a,b);
    Cvor desno= max_proizvod(seg,2*k+1,m+1,y,a,b);

    rez.largest=max(levo.largest , desno.largest);
    rez.sec_largest=min(  max(levo.largest,desno.sec_largest) , max(levo.sec_largest,desno.largest) );
    return rez;
}







int main(){

   vector<int> niz = { 1, 3, 4, 2, 5 };
   int n=niz.size();
   int height=ceil(log2(n));
   int size=2*pow(2,height);
 
   vector<Cvor> seg(size);
   
   build_tree(niz,seg,1,0,n-1);


   Cvor rez=max_proizvod(seg,1,0,n-1,0,2);
                  //k=1, x=0 y=n-1,  a=0 b=2 je interval u pocetnom nizu na kom trazimo max proizovd
  

  /*for ( Cvor c: seg){
    cout<<"("<<c.largest<<","<<c.sec_largest<<")  ";
  }*/

  cout<<rez.largest*rez.sec_largest<<endl;

  return 0;
}