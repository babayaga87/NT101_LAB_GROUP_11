#include <iostream>
#include <algorithm>
using namespace std;

long long modexp(long long a,long long b,long long m){
    long long r=1;
    while(b){
        if(b&1) r=r*a%m;
        a=a*a%m;
        b>>=1;
    }
    return r;
}

int main(){
    cout<<"GCD: "<<__gcd(48,18)<<endl;
    cout<<"7^40 mod 19: "<<modexp(7,40,19)<<endl;
}