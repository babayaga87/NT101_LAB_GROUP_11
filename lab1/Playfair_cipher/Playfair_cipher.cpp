#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// --- UTILS ---
string formatString(string s) {
    string res = "";
    for (char c : s) {
        if (isalpha(c)) res += toupper(c);
    }
    return res;
}

// --- PLAYFAIR CIPHER ---
class Playfair {
    char matrix[5][5];

public:
    void generateMatrix(string key) {
        string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // No J
        key = formatString(key);
        for (char& c : key) if (c == 'J') c = 'I';

        string combined = key + alphabet;
        string finalKey = "";
        for (char c : combined) {
            if (finalKey.find(c) == string::npos) finalKey += c;
        }

        int k = 0;
        cout << "\n--- Playfair Matrix (5x5) ---" << endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                matrix[i][j] = finalKey[k++];
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void findPosition(char c, int& r, int& col) {
        if (c == 'J') c = 'I';
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (matrix[i][j] == c) { r = i; col = j; return; }
    }

    string process(string text, bool encrypt) {
        text = formatString(text);
        if (encrypt) {
            string temp = "";
            for (int i = 0; i < text.length(); i++) {
                temp += text[i];
                if (i + 1 < text.length() && text[i] == text[i + 1]) temp += 'X';
            }
            if (temp.length() % 2 != 0) temp += 'X';
            text = temp;
        }

        string res = "";
        int r1, c1, r2, c2;
        int diff = encrypt ? 1 : 4; // Shift 1 for enc, Shift -1 (mod 5 is +4) for dec

        for (int i = 0; i < text.length(); i += 2) {
            findPosition(text[i], r1, c1);
            findPosition(text[i + 1], r2, c2);

            if (r1 == r2) { // Same row
                res += matrix[r1][(c1 + diff) % 5];
                res += matrix[r2][(c2 + diff) % 5];
            }
            else if (c1 == c2) { // Same column
                res += matrix[(r1 + diff) % 5][c1];
                res += matrix[(r2 + diff) % 5][c2];
            }
            else { // Rectangle
                res += matrix[r1][c2];
                res += matrix[r2][c1];
            }
        }
        return res;
    }
};

// --- VIGENERE CIPHER ---
string vigenereDecrypt(string text, string key) {
    text = formatString(text);
    key = formatString(key);
    string res = "";
    for (int i = 0, j = 0; i < text.length(); i++) {
        res += (text[i] - key[j % key.length()] + 26) % 26 + 'A';
        j++;
    }
    return res;
}

int main() {
    int choice;
    cout << "1. Playfair Cipher\n2. Vigenere Cipher\nChon thuat toan: ";
    cin >> choice;

    if (choice == 1) {
        Playfair pf;
        string key, text;
        int mode;

        cout << "Nhap Key: "; cin.ignore(); getline(cin, key);
        pf.generateMatrix(key);

        cout << "\n1. Ma hoa\n2. Giai ma\nChon che do: "; cin >> mode;
        cout << "Nhap van ban: "; cin.ignore(); getline(cin, text);

        if (mode == 1) cout << "Ket qua Ma hoa: " << pf.process(text, true) << endl;
        else cout << "Ket qua Giai ma: " << pf.process(text, false) << endl;

    }
    else if (choice == 2) {
        string key, text;
        cout << "Nhap Key: "; cin.ignore(); getline(cin, key);
        cout << "Nhap Ciphertext: "; getline(cin, text);
        cout << "Ket qua Giai ma: " << vigenereDecrypt(text, key) << endl;
    }

    return 0;
}