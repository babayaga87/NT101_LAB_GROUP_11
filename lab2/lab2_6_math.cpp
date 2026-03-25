#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

typedef __int128_t int128;

string to_string(int128 n) {
    if (n == 0) return "0";
    string s = "";
    while (n > 0) {
        s += (char)('0' + (n % 10));
        n /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

int128 mul_mod(int128 a, int128 b, int128 m) {
    int128 res = 0;
    a %= m;
    while (b > 0) {
        if (b % 2 == 1) res = (res + a) % m;
        a = (a * 2) % m;
        b /= 2;
    }
    return res;
}

int128 power(int128 a, int128 b, int128 m) {
    int128 res = 1;
    a %= m;
    while (b > 0) {
        if (b % 2 == 1) res = mul_mod(res, a, m);
        a = mul_mod(a, a, m);
        b /= 2;
    }
    return res;
}

bool is_prime(int128 n, int k = 15) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    int128 d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    static mt19937_64 gen(1337);
    for (int i = 0; i < k; i++) {
        int128 a = 2 + rand() % 1000000; 
        if (a >= n - 2) a = 2; 

        int128 x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;
        
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

int128 gcd(int128 a, int128 b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int128 generate_prime(int bits) {
    static mt19937_64 gen(time(0));
    uniform_int_distribution<unsigned long long> dist(0, 0xFFFFFFFFFFFFFFFFULL);
    
    while (true) {
        int128 p = 0;
        if (bits <= 64) {
            p = dist(gen) >> (64 - bits);
        } else {
            p = (int128(dist(gen)) << 25) | (dist(gen) >> 39); 
        }
        p |= 1; 
        if (is_prime(p)) return p;
    }
}

int main() {
    cout << "--- KET QUA THUC HIEN NHIEM VU 2.6 ---" << endl;

    // Yêu cầu 1: Sinh số nguyên tố
    cout << "1. Random Primes:" << endl;
    cout << "   8-bit: " << to_string(generate_prime(8)) << endl;
    cout << "   16-bit: " << to_string(generate_prime(16)) << endl;
    cout << "   64-bit: " << to_string(generate_prime(64)) << endl;

    // Yêu cầu 2: Tìm 10 số nguyên tố < M10 (2^89 - 1)
    int128 M10 = (int128(1) << 89) - 1;
    cout << "\n2. 10 Primes < M10 (" << to_string(M10) << "):" << endl;
    int count = 0;
    for (int128 i = M10 - 1; count < 10; i--) {
        if (is_prime(i)) {
            count++;
            cout << "   " << count << ": " << to_string(i) << endl;
        }
    }

    // Yêu cầu 3: GCD và Lũy thừa Modulo
    cout << "\n3. Math Operations:" << endl;
    cout << "   GCD(M10, 987654321): " << to_string(gcd(M10, 987654321)) << endl;
    cout << "   7^40 mod 19: " << to_string(power(7, 40, 19)) << endl;

    return 0;
}