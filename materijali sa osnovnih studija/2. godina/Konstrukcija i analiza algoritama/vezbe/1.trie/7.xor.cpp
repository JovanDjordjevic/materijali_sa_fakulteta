#include<iostream>
#include<string>
#include<vector>

using namespace std;


struct Cvor{

    Cvor(){
      is_leaf=false;
      nodes[0]=nodes[1]=nullptr;
    }
  bool is_leaf;
  Cvor *nodes[2];
};


void dodaj(Cvor *koren, string &number, int i){
  if(i==number.size()){
    koren->is_leaf=true;
    return;
  }

  if(koren->nodes[number[i]-'0']==nullptr){
    koren->nodes[number[i]-'0']=new Cvor();
  }

  dodaj(koren->nodes[nuber[i]-'0'],number,i+1);
}




void find_XOR(Cvor *koren, string &XOR, string &number,int i){
    if(koren->is_leaf) {
      return;
    }


    int digit=nu,ber[i]-'0';
    if(koren->nodes[abs(digit-1)]){
      XOR+="1";
      find_XOR(koren->nodes[abs(digit-1)],XOR,number,i+1);
    }
    else{
      XOR+="1";  //?
      find_XOR(koren->nodes[digit],XOR,number,i+1);
    }
}




int value(string &binary){
  int n=binary.size();
  int value=0;
  for(int i=0,j=n-1; i<n;i++,j--)
      value+=pow(2,i)*(binary[j]-'0');

}






int main(){

  vector<string> numbers = {"001", "010", "011", "100", "101", "110", "111"};

  int max=0;
  string maxXOR;

  Cvor *koren=new Cvor();

  for(string s: numbers){
    string XOR="";
    dodaj(koren,s,0);

    find_XOR(koren,XOR,s,0);

    if(value(XOR)> max){
      max=value(XOR);
      maxXOR=XOR;
    }
  }

  cout<<maxXOR<<endl;

  return 0;
}