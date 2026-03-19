#include <iostream>
#include <openssl/evp.h>
#include <cstring>
#include <vector>
#include <cstdlib>

using namespace std;

#define DATA_SIZE 1000

vector<unsigned char> generate_data() {
    vector<unsigned char> data(DATA_SIZE);
    for (int i = 0; i < DATA_SIZE; i++)
        data[i] = rand() % 256;
    return data;
}

int test_mode(const EVP_CIPHER *cipher_type) {
    vector<unsigned char> data = generate_data();

    unsigned char key[16] = "1234567890123456";
    unsigned char iv[16] = "0000000000000000";

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    vector<unsigned char> ciphertext(DATA_SIZE + 16);
    int len, ciphertext_len;

    // Encrypt
    EVP_EncryptInit_ex(ctx, cipher_type, NULL, key, iv);
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, data.data(), DATA_SIZE);
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    // Flip 1 bit (byte 26)
    ciphertext[25] ^= 1;

    // Decrypt
    ctx = EVP_CIPHER_CTX_new();

    vector<unsigned char> decrypted(DATA_SIZE + 16);
    int decrypted_len;

    EVP_DecryptInit_ex(ctx, cipher_type, NULL, key, iv);
    EVP_DecryptUpdate(ctx, decrypted.data(), &len, ciphertext.data(), ciphertext_len);
    decrypted_len = len;
    EVP_DecryptFinal_ex(ctx, decrypted.data() + len, &len);
    decrypted_len += len;

    EVP_CIPHER_CTX_free(ctx);

    // Compare
    int diff = 0;
    for (int i = 0; i < DATA_SIZE; i++) {
        if (data[i] != decrypted[i])
            diff++;
    }

    return diff;
}

int main() {
    cout << "ECB: " << test_mode(EVP_aes_128_ecb()) << endl;
    cout << "CBC: " << test_mode(EVP_aes_128_cbc()) << endl;
    cout << "CFB: " << test_mode(EVP_aes_128_cfb128()) << endl;
    cout << "OFB: " << test_mode(EVP_aes_128_ofb()) << endl;

    return 0;
}