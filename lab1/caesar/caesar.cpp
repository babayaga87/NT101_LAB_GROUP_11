#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string encryptCaesar(string text, int key) {
    string result = "";
    // Đảm bảo key luôn nằm trong khoảng 0-25
    key = key % 26;
    if (key < 0) key += 26;

    for (char& c : text) {
        // Chỉ mã hóa các chữ cái, giữ nguyên khoảng trắng và dấu câu
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            // Áp dụng công thức: C = (p + k) mod 26
            result += (char)(((c - base + key) % 26) + base);
        }
        else {
            result += c;
        }
    }
    return result;
}

// Hàm giải mã
string decryptCaesar(string text, int key) {
    // Giải mã thực chất là dịch chuyển ngược lại (26 - key)
    return encryptCaesar(text, 26 - (key % 26));
}

// Hàm brute-force
void bruteForceCaesar(string ciphertext) {
    cout << "\n--- KET QUA BRUTE-FORCE ---" << endl;
    // Thử lần lượt toàn bộ 25 khóa có thể có
    for (int k = 1; k < 26; ++k) {
        cout << "Key = " << k << ": \n" << decryptCaesar(ciphertext, k) << "\n" << endl;
    }
}

int main() {
    int choice, key;
    string text;

    cout << "--- CAESAR CIPHER TOOL ---" << endl;
    cout << "1. Ma hoa (Encrypt)" << endl;
    cout << "2. Giai ma (Decrypt)" << endl;
    cout << "3. Brute-force" << endl;
    cout << "Chon chuc nang (1/2/3): ";

    if (!(cin >> choice)) {
        cout << "Loi dau vao!" << endl;
        return 1;
    }
    cin.ignore(); // Xóa ký tự newline còn lại trong buffer sau khi nhập số

    if (choice == 1 || choice == 2) {
        cout << "Nhap van ban: ";
        getline(cin, text);
        cout << "Nhap khoa k: ";
        cin >> key;

        if (choice == 1) {
            cout << "\nCiphertext: \n" << encryptCaesar(text, key) << endl;
        }
        else {
            cout << "\nPlaintext: \n" << decryptCaesar(text, key) << endl;
        }
    }
    else if (choice == 3) {
        cout << "Nhap ciphertext can brute-force: ";
        getline(cin, text);
        bruteForceCaesar(text);
    }
    else {
        cout << "Lua chon khong hop le!" << endl;
    }

    return 0;
}