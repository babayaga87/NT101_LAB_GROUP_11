#include <iostream>
#include <openssl/aes.h>
using namespace std;

int main(){
    unsigned char key[16]="1234567890123456";
    unsigned char pt[32]="UIT_LAB_UIT_LAB_UIT_LAB_UIT_LAB_";
    unsigned char out[32];

    AES_KEY enc;
    AES_set_encrypt_key(key,128,&enc);

    for(int i=0;i<32;i+=16)
        AES_ecb_encrypt(pt+i,out+i,&enc,AES_ENCRYPT);

    cout<<"ECB: ";
    for(int i=0;i<32;i++) printf("%02x",out[i]);
}