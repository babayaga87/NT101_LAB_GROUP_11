#include <iostream>
#include <string>

using namespace std;

// Hàm tìm ước chung lớn nhất (để kiểm tra khóa a)
int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Hàm tìm nghịch đảo modulo: a^-1 mod 26
int modInverse(int a) {
    for (int x = 1; x < 26; x++) {
        if (((a % 26) * (x % 26)) % 26 == 1) return x;
    }
    return -1;
}

string encryptAffine(string text, int a, int b) {
    string res = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            // E(x) = (ax + b) mod 26
            res += (char)((((a * (c - base)) + b) % 26) + base);
        }
        else res += c;
    }
    return res;
}

string decryptAffine(string text, int a, int b) {
    string res = "";
    int a_inv = modInverse(a);
    if (a_inv == -1) return "Loi: Khong ton tai nghich dao modulo cho a!";

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            // D(x) = a^-1 * (x - b) mod 26
            int val = (a_inv * (c - base - b + 26)) % 26;
            res += (char)(val + base);
        }
        else res += c;
    }
    return res;
}

int main() {
    int a, b;
    string plaintext;

    cout << "--- AFFINE CIPHER ---" << endl;
    cout << "Nhap khoa a (phai nguyen to cung nhau voi 26): "; cin >> a;
    cout << "Nhap khoa b: "; cin >> b;

    if (gcd(a, 26) != 1) {
        cout << "Khoa a khong hop le!" << endl;
        return 0;
    }

    cin.ignore();
    cout << "Nhap ban ro: "; getline(cin, plaintext);

    string cipher = encryptAffine(plaintext, a, b);
    cout << "Ban ma: " << cipher << endl;

    string decrypted = decryptAffine(cipher, a, b);
    cout << "Ban ro sau khi giai ma: " << decrypted << endl;

    return 0;
}