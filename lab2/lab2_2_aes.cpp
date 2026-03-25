#include <iostream>
#include <openssl/aes.h>
#include <cstring> 

using namespace std;

int main() {
    unsigned char key[] = "1234567890123456";
    unsigned char pt[] = "UIT_LAB_UIT_LAB_UIT_LAB_UIT_LAB_";
    unsigned char out_ecb[32];
    unsigned char out_cbc[32];

    unsigned char iv[] = "0000000000000000"; 
    unsigned char iv_copy[16];
    memcpy(iv_copy, iv, 16);

    AES_KEY enc;
    AES_set_encrypt_key(key, 128, &enc);

    for(int i = 0; i < 32; i += 16)
        AES_ecb_encrypt(pt + i, out_ecb + i, &enc, AES_ENCRYPT);

    AES_cbc_encrypt(pt, out_cbc, 32, &enc, iv_copy, AES_ENCRYPT);

    cout << "ECB: ";
    for(int i = 0; i < 32; i++) printf("%02x", out_ecb[i]);
    cout << endl;

    cout << "CBC: ";
    for(int i = 0; i < 32; i++) printf("%02x", out_cbc[i]);
    cout << endl;

    return 0;
}
