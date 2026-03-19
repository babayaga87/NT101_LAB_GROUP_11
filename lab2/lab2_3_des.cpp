#include <iostream>
#include <bitset>
#include <openssl/des.h>
using namespace std;

string to_bin(unsigned char* d){
    string s="";
    for(int i=0;i<8;i++) s+=bitset<8>(d[i]).to_string();
    return s;
}

int main(){
    DES_cblock key="87654321";
    DES_key_schedule sch;
    DES_set_key_unchecked(&key,&sch);

    unsigned char p1[8]="STAYHOME";
    unsigned char p2[8]="STAYHOMA";
    unsigned char c1[8],c2[8];

    DES_ecb_encrypt((DES_cblock*)p1,(DES_cblock*)c1,&sch,DES_ENCRYPT);
    DES_ecb_encrypt((DES_cblock*)p2,(DES_cblock*)c2,&sch,DES_ENCRYPT);

    string b1=to_bin(c1),b2=to_bin(c2);

    int diff=0;
    for(int i=0;i<64;i++) if(b1[i]!=b2[i]) diff++;

    cout<<"Diff bits: "<<diff<<endl;
    cout<<"Percent: "<<diff/64.0*100<<"%"<<endl;
}