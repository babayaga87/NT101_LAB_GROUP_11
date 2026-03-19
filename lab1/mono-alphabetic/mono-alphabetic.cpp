#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map> // Đã đổi sang unordered_map siêu tốc độ
#include <cmath>

using namespace std;

// Biến toàn cục
unordered_map<string, double> quadgram_map;

// 1 & 2. Hàm đọc file (Giữ nguyên)
string readFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return "";
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

bool loadQuadgrams(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    string line;
    double total_count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string quadgram;
        double count;
        if (ss >> quadgram >> count) {
            quadgram_map[quadgram] = count;
            total_count += count;
        }
    }
    file.close();
    for (auto& pair : quadgram_map) {
        pair.second = log10(pair.second / total_count);
    }
    return true;
}

// 3. Hàm chuẩn hóa văn bản
string normalizeText(const string& text) {
    string result = "";
    for (char c : text) {
        if (isalpha((unsigned char)c)) result += toupper((unsigned char)c);
    }
    return result;
}

// 4. Hàm giải mã SIÊU TỐC (Chỉ dùng nội bộ cho chuỗi đã chuẩn hóa để tăng tốc)
string fastDecrypt(const string& text, const string& key) {
    string plaintext = text;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < text.length(); ++i) {
        int index = key.find(text[i]);
        if (index != string::npos) plaintext[i] = alphabet[index];
    }
    return plaintext;
}

// 4b. Hàm giải mã giữ nguyên định dạng (Dùng lúc in kết quả cuối cùng)
string decryptSubstitution(const string& ciphertext, const string& key) {
    string plaintext = "";
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (char c : ciphertext) {
        if (isalpha((unsigned char)c)) {
            bool isLower = islower((unsigned char)c);
            int index = key.find(toupper((unsigned char)c));
            if (index != string::npos) {
                char p = alphabet[index];
                plaintext += isLower ? tolower((unsigned char)p) : p;
            }
        }
        else {
            plaintext += c;
        }
    }
    return plaintext;
}

// 5. Hàm tính điểm (Không gọi chuẩn hóa ở đây nữa)
double calculateFitness(const string& normalized_text) {
    double score = 0.0;
    if (normalized_text.length() < 4) return score;

    for (size_t i = 0; i < normalized_text.length() - 3; ++i) {
        string quadgram = normalized_text.substr(i, 4);
        if (quadgram_map.count(quadgram)) {
            score += quadgram_map[quadgram];
        }
        else {
            score -= 10.0;
        }
    }
    return score;
}

// 6. Thuật toán Hill Climbing Tối ưu
void solveCipherAuto(const string& ciphertext) {
    string globalBestKey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    double globalBestScore = -1e9;

    random_device rd;
    mt19937 g(rd());

    // CỰC KỲ QUAN TRỌNG: Chỉ chuẩn hóa văn bản 1 lần duy nhất ở đây!
    string normCipher = normalizeText(ciphertext);

    int numRestarts = 10;
    cout << "\nDang bat dau thuat toan Hill Climbing (" << numRestarts << " lan chay ngau nhien)..." << endl;

    for (int restart = 0; restart < numRestarts; ++restart) {
        string currentKey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        shuffle(currentKey.begin(), currentKey.end(), g);

        double currentScore = calculateFitness(fastDecrypt(normCipher, currentKey));

        int maxIterations = 2000;
        int noImprovementCount = 0;

        for (int i = 0; i < maxIterations; ++i) {
            string testKey = currentKey;

            // Đổi chỗ
            int idx1 = g() % 26;
            int idx2 = g() % 26;
            swap(testKey[idx1], testKey[idx2]);

            // Dùng fastDecrypt và truyền normCipher để tiết kiệm tài nguyên
            double testScore = calculateFitness(fastDecrypt(normCipher, testKey));

            if (testScore > currentScore) {
                currentScore = testScore;
                currentKey = testKey;
                noImprovementCount = 0;

                // IN TIẾN ĐỘ CHẠY LÊN MÀN HÌNH
                cout << "Lan chay " << restart + 1 << " | Diem tang len: " << currentScore << " | Khoa hien tai: " << currentKey << endl;
            }
            else {
                noImprovementCount++;
            }

            if (noImprovementCount > 500) break;
        }

        if (currentScore > globalBestScore) {
            globalBestScore = currentScore;
            globalBestKey = currentKey;
            cout << "\n=> Hoan thanh lan " << restart + 1 << ", Cap nhat Best Score toan cuc: " << globalBestScore << "\n\n";
        }
    }

    cout << "\n================ KET QUA GIAI MA ================" << endl;
    cout << "Khoa tot nhat tim duoc: " << globalBestKey << endl;
    cout << "\n--- Ban ro hoan chinh --- \n" << decryptSubstitution(ciphertext, globalBestKey) << endl;
}

int main() {
    if (!loadQuadgrams("english_quadgrams.txt")) return 1;
    cout << "Da nap thanh cong du lieu Quadgram." << endl;

    string filename = "2-2_cipher_text-pastecode_io.txt";
    string ciphertext = readFile(filename);

    if (ciphertext.empty()) {
        cout << "Loi doc file ciphertext." << endl;
        return 1;
    }

    solveCipherAuto(ciphertext);
    return 0;
}