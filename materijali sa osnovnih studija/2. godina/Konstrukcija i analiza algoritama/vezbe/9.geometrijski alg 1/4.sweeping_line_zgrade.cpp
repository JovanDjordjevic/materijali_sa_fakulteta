#include<iostream>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

int main(){

  int n;
  cin>>n;

  vector<pair<int,int>> dogadjaj;  //dosli do leve ivice - par(a,c)
                                   //ili dosli do desne ivice - par(b,-c)  

  int a,b,c;
  for(int i=0;i<n;i++){
    cin>>a>>b>>c;
    dogadjaj.push_back(make_pair(a,c));  //leva  ivica i pozitivna visina
    dogadjaj.push_back(make_pair(b,-c));  //desna ivica i negativna visina(neg cisinu koristimo samo da oznacimo da je desna u pitanju, necemo racunati sa neg visinom)    
  }
  
  sort(dogadjaj.begin(),dogadjaj.end());

  long long resenje=0;

  multiset<int> sweep; //multiset jer mozda ima vise zgrada sa istom visinom

  sweep.insert(0);  //bitno!
  sweep.insert(dogadjaj[0].second);  //ovaj dogadjaj je sigurno koordinata leve ivice i ubacujemo visinu u multiset
  int prosliX=dogadjaj[0].first;

  for(int i=1;i<dogadjaj.size();i++){
    a=dogadjaj[i].first;
    b=dogadjaj[i].second;

    resenje+= ((long long)a -prosliX) * (*(--sweep.end()));  //najveci el u multisetu se nalazi na kraju(tj pre .end() iteratora)
    
    prosliX=a;
    if(b<0) sweep.erase(sweep.find(-b));   //ne sme direktno seep.erase(-b) jer bi to obrisalo sve sto ima vrednost -b
    else sweep.insert(b);
  }

  
  cout<<resenje<<endl;

  return 0;
}