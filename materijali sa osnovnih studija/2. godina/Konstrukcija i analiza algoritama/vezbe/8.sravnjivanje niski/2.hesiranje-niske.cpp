#include<iostream>
#include<vector>

using namespace std;

long long izracunajHash(string &s){

//niske su od malih slova eng abecede kojih ima 26, to je velicina ulaza, 
//a pozeljno je da p bude velicine ulaza i da bude prost broj zato uzimamo prvi prost broj 
//veci od 26 tj 31. da smo imali i mala i veliaks lova uzeli bismo 53

int p=31;  
int m=1e9+9;
long long hash=0;

for(int i=s.size()-1; i>=0 ;i--){
    hash=(hash*p+(s[i]-'a'+1))%m;
}
return hash;
}



int main(){

  vector<string> reci={"ana", "a", "ananas","b","algoritamsravnjivanjaniski" };

  for(string s : reci){
      cout<<"rec: "<<s<<" hash: "<<izracunajHash(s)<<endl;
  }

   return 0;
}