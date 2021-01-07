#include<iostream>
#include<vector>
#include<list>
#include<cstdlib>


using namespace std;

struct Tacka{
  int x;
  int y;
};


bool saIsteStrane(Tacka t1,Tacka t2,Tacka t3,Tacka t4){
  int A=(t3.x-t1.x)*(t2.y-t1.y)-(t2.x-t1.x)*(t3.y-t1.y);
  int B=(t4.x-t1.x)*(t2.y-t1.y)-(t2.x-t1.x)*(t4.y-t1.y);

  if(A*B<0) return false;
  else return true;
}


int main(){
  
  Tacka a,b,c,d;
  
  cin>>a.x>>a.y;
  cin>>b.x>>b.y;
  cin>>c.x>>c.y;
  cin>>d.x>>d.y;

  if(saIsteStrane(a,b,c,d) && saIsteStrane(b,c,a,d) && saIsteStrane(a,c,b,d))
    cout<<"jeste unutra"<<endl;
  else
    cout<<"nije unutra"<<endl;  

  return 0;
}
