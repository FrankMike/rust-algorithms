#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ll long long

uint64_t modpow(uint64_t base, uint64_t exp, uint64_t modulus) {
    base %= modulus;
    ull result = 1;
    while (exp > 0) {
        if (exp & 1)
            result = (__uint128_t) result * base % modulus;
        base = (__uint128_t) base * base % modulus;
        exp >>= 1;
    }
    return result;
}

bool check_composite(uint64_t n, uint64_t a, uint64_t d, uint s) {
    uint64_t x = modpow(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (uint r = 1; r < s; r++) {
        x = (__uint128_t) x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

bool rabin_miller(uint64_t n) {
    if (n < 2)
        return false;
    uint r = 0;
    uint64_t d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (uint a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) { // can test up to 64 bit numbers
        if (n == a)
            return true;
        if(check_composite(n, a, d, r))
            return false;
    }
    return true;
}

// O(sqrt(n))
bool trial_division(uint x) {
    ull upper = sqrt(x);
    for (uint d = 2; d <= upper; d++) {
        if (x % d == 0)
            return false;
    }
    return true;
}

bool fermat_probabilistic(ull n, int iter = 20) {
    if (n < 4)
        return n == 2 || n == 3;
    
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    for (uint i = 0; i < iter; i++) {
        ll a = 2 + rng() % (n - 3);
        if (modpow(a, n - 1, n) != 1)
            return false;
    }
    return true;
}

// O(n)
bool wilson_thereom_test(uint n) {
    uint result = 1;
    for (uint i = 2; i < n; i++)
        result = (result * i) % n;
    return result == n - 1;
}

int main() {
    cout << "53 " << fermat_probabilistic(53) << endl;
    cout << "256 " << fermat_probabilistic(256) << endl;
    cout << "32361122672259149 " << fermat_probabilistic(32361122672259149) << endl; // a Lucas prime
    cout << "8911 " << fermat_probabilistic(8911) << endl; // a Carmichael number
    cout << "42 " << wilson_thereom_test(42) << endl;
    cout << "127 " << wilson_thereom_test(127) << endl;
    cout << "8911 " << rabin_miller(8911) << endl;
    cout << "32361122672259149 " << rabin_miller(32361122672259149) << endl;
    cout << "561 " << trial_division(561) << endl;
}