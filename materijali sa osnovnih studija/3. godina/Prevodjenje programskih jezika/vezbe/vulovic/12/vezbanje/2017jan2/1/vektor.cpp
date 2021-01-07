#include"vektor.hpp"

void Vektor::dodaj(float broj){
    elementi.push_back(broj);
}

void Vektor::stampaj(){
    cout<<"[";
    for(unsigned i=0;i<elementi.size();i++)
        cout<<elementi[i]<<", ";
    cout<<"]"<<endl;
}
int Vektor::getsize(){
    return elementi.size();
}

float Vektor::getkoord(int br){
    return elementi[br-1];
}


Vektor* operacija (Vektor* v1, Vektor* v2, int op){  //op=1 je +, op=2  je - 
   Vektor* rez=new Vektor();
   int n1=v1->getsize();
   int n2=v2->getsize();
   if(n1!=n2){
        cerr<<"greska u dimenziji vektora!\n";
        exit(EXIT_FAILURE);
   }
   
   for(int i=0; i<n1; i++){
        if(op==1)
            rez->dodaj(v1->elementi[i] + v2->elementi[i]);
        else if (op==2)
            rez->dodaj(v1->elementi[i] - v2->elementi[i]);
   }
   
   return rez;
}

Vektor* mnoz (Vektor* v1, float br){
   Vektor* rez=new Vektor();
   int n1=v1->getsize();
   
   for(int i=0;i<n1;i++){
        rez->dodaj(v1->elementi[i] * br);
   }
   
   return rez;
}
