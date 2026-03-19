#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string vigenereDecrypt(string ciphertext, string key) {
    string plaintext = "";
    string cleanKey = "";

    // 1. Chuẩn hóa khóa: Viết hoa toàn bộ
    for (char c : key) if (isalpha(c)) cleanKey += toupper(c);

    int keyIndex = 0;
    int keyLen = cleanKey.length();

    for (int i = 0; i < ciphertext.length(); i++) {
        char c = ciphertext[i];

        if (isalpha(c)) {
            char C = toupper(c); // Đưa về chữ hoa để tính toán
            char K = cleanKey[keyIndex % keyLen];

            // Công thức: P = (C - K + 26) mod 26
            char P = (C - K + 26) % 26 + 'A';

            plaintext += P;
            keyIndex++; // CHỈ tăng vị trí khóa khi gặp chữ cái
        }
        else {
            // Giữ nguyên các ký tự không phải chữ cái (dấu cách, dấu phẩy, v.v.)
            plaintext += c;
        }
    }
    return plaintext;
}

int main() {
    string key, cipher;

    cout << "Nhap khoa (Key): ";
    getline(cin, key);
    cout << "Nhap ban ma (Ciphertext): ";
    getline(cin, cipher);

    cout << "\n--- KET QUA GIAI MA ---\n";
    cout << vigenereDecrypt(cipher, key) << endl;

    return 0;
}