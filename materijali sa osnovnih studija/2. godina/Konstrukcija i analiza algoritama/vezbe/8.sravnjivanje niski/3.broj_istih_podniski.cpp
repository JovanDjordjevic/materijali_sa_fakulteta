#include<iostream>
#include<vector>
#include<set>

using namespace std;


int broj_jedinstvenih_podniski(const string &s){
    int n=s.size();
    int p=31;
    int m=1e9+9;
    
    vector<long long> p_pow(n);
    p_pow[0]=1;

    for(int i=1;i<n;i++)
        p_pow[i]=(p_pow[i-1]*p)%m;
   
    vector<long long> hash(n+1,0);
    
    for(int i=0;i<n;i++)
        hash[i+1]=(hash[i] + (s[i]-'a'+1)*p_pow[i])%m;

    int count=0;
    for(int l=1;l<=n;l++){
        set<long long> hs;   //set hes vrednosti segmenata duzine l
        for(int i=0; i<=n-l; i++){
            long long curr_hash=(hash[i+l]+m-hash[i])%m;
            curr_hash=(curr_hash*p_pow[n-i-1])%m;
            hs.insert(curr_hash);
        }
        count+=hs.size();
    }    

    return count;
}



int main(){

   string s;
   cin>>s;

   cout<<broj_jedinstvenih_podniski(s)<<endl;

   return 0;
}