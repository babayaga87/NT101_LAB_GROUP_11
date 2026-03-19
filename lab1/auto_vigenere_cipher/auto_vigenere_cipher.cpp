#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

// T?n su?t ch? cái ti?ng Anh chu?n (A-Z)
const double ENGLISH_FREQ[26] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094,
    0.06966, 0.0153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929,
    0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
    0.01974, 0.00074
};

string filterAlpha(string s) {
    string res = "";
    for (char c : s) if (isalpha(c)) res += toupper(c);
    return res;
}

double calculateIC(string s) {
    if (s.length() <= 1) return 0;
    vector<int> count(26, 0);
    for (char c : s) count[c - 'A']++;
    double ic = 0;
    for (int i = 0; i < 26; i++) {
        ic += (double)count[i] * (count[i] - 1);
    }
    return ic / (s.length() * (s.length() - 1));
}

double chiSquared(string s) {
    vector<int> count(26, 0);
    for (char c : s) count[c - 'A']++;
    double score = 0;
    for (int i = 0; i < 26; i++) {
        double expected = s.length() * ENGLISH_FREQ[i];
        score += pow(count[i] - expected, 2) / expected;
    }
    return score;
}

int main() {
    string rawCipher;
    cout << "Nhap Ciphertext: ";
    getline(cin, rawCipher);
    string cipher = filterAlpha(rawCipher);

    // 1. Tim do dai khoa bang IC
    int bestM = 1;
    double maxIC = 0;
    cout << "\nPhan tich IC de tim do dai khoa:\n";
    for (int m = 1; m <= 15; m++) {
        double avgIC = 0;
        for (int i = 0; i < m; i++) {
            string group = "";
            for (int j = i; j < cipher.length(); j += m) group += cipher[j];
            avgIC += calculateIC(group);
        }
        avgIC /= m;
        cout << "Do dai " << m << ": IC = " << fixed << setprecision(4) << avgIC << endl;
        if (avgIC > maxIC) { maxIC = avgIC; bestM = m; }
    }

    cout << "\n=> Do dai khoa kha thi nhat: " << bestM << endl;

    // 2. Tim tung ky tu cua khoa bang Chi-Squared
    string key = "";
    for (int i = 0; i < bestM; i++) {
        string group = "";
        for (int j = i; j < cipher.length(); j += bestM) group += cipher[j];

        double minChi = 1e9;
        int bestShift = 0;
        for (int shift = 0; shift < 26; shift++) {
            string shifted = "";
            for (char c : group) shifted += (c - 'A' - shift + 26) % 26 + 'A';
            double score = chiSquared(shifted);
            if (score < minChi) { minChi = score; bestShift = shift; }
        }
        key += (char)(bestShift + 'A');
    }

    cout << "=> Khoa tim duoc: " << key << endl;

    // 3. Giai ma thu voi khoa tim duoc
    string result = "";
    int keyIdx = 0;
    for (char c : rawCipher) {
        if (isalpha(c)) {
            char C = toupper(c);
            char K = key[keyIdx % key.length()];
            result += (char)((C - K + 26) % 26 + 'A');
            keyIdx++;
        }
        else result += c;
    }
    cout << "\n--- BAN RO DU DOAN ---\n" << result << endl;

    return 0;
}