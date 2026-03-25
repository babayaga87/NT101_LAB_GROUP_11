#include <iostream>
#include <openssl/aes.h>
#include <cstring>
using namespace std;

int main(){
    unsigned char key[16]="1234567890123456";
    unsigned char pt[32]="UIT_LAB_UIT_LAB_UIT_LAB_UIT_LAB_";
    unsigned char out_ecb[32], out_cbc[32];
    unsigned char iv[16] = {0}; 

    AES_KEY enc;
    AES_set_encrypt_key(key, 128, &enc);

    for(int i=0; i<32; i+=16)
        AES_ecb_encrypt(pt+i, out_ecb+i, &enc, AES_ENCRYPT);

    unsigned char tmp_iv[16]; 
    memcpy(tmp_iv, iv, 16);
    AES_cbc_encrypt(pt, out_cbc, 32, &enc, tmp_iv, AES_ENCRYPT);

    cout << "ECB: ";
    for(int i=0; i<32; i++) printf("%02x", out_ecb[i]);
    
    cout << "\nCBC: ";
    for(int i=0; i<32; i++) printf("%02x", out_cbc[i]);
    cout << endl;

    return 0;
}