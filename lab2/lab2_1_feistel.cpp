#include <iostream>
#include <bitset>
using namespace std;

int F(int right, int subkey){
    return (right ^ subkey) & 0x0F;
}

pair<int,int> feistel_round(int L, int R, int subkey){
    return {R, L ^ F(R, subkey)};
}

void track(int msg, int key){
    int L=(msg>>4)&0x0F;        
    int R=msg&0x0F;

    int subkeys[4]={key&0x0F,(key>>4)&0x0F,(key+1)&0x0F,(key+2)&0x0F};

    cout<<"Init: "<<bitset<4>(L)<<" "<<bitset<4>(R)<<endl;

    for(int i=0;i<4;i++){
        auto t=feistel_round(L,R,subkeys[i]);
        L=t.first; R=t.second;
        cout<<"Round "<<i+1<<": "<<bitset<4>(L)<<" "<<bitset<4>(R)<<endl;
    }
}

int main(){
    track(0xAB,0x12);
    track(0xAC,0x12);
}
