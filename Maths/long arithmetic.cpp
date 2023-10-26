#include <bits/stdc++.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

class BigInteger {
    public:
        int n = 0;
        static const long long p = 1e6;
        static const int cnt = 6;
        long long sign = 1;
        vector<long long> d;
        void norm();
    public:
        BigInteger() {};
        BigInteger(string s) {
            if(s[0] == '-') {
                sign = -1;
                s.erase(0, 1);
            }
            n = s.size();
            for(int i = n - cnt; i >= 0; i -= cnt) {
                d.push_back(stoi(s.substr(i, cnt)));
            }
            if(n % cnt != 0) {
                d.push_back(stoi(s.substr(0, n % cnt)));
            }
            n = d.size();
            norm();
        };
        BigInteger copy();
        bool operator >(const BigInteger &a);
        bool operator >=(const BigInteger &a);
        bool operator <(const BigInteger &a);
        bool operator <=(const BigInteger &a);
        bool operator ==(const BigInteger &a);
        bool operator !=(const BigInteger &a);
        friend ostream &operator <<(ostream &out, const BigInteger &a);
        friend istream &operator >>(istream &in, BigInteger &a);
        BigInteger operator +(const BigInteger &b);
        BigInteger operator +(int x);
        BigInteger operator -(const BigInteger &b);
        BigInteger operator -(int x);
        friend BigInteger operator -(const BigInteger &a);
        BigInteger operator /(int x);
        long long operator %(int x);
        BigInteger operator *(const BigInteger &b);
        BigInteger operator *(int x);
        BigInteger operator +=(const BigInteger &b);
        BigInteger operator +=(int x);
        BigInteger operator -=(const BigInteger &b);
        BigInteger operator -=(int x);
        BigInteger operator /=(int x);
        BigInteger operator *=(const BigInteger &b);
        BigInteger operator *=(int x);
        BigInteger operator ++();
        bool operator >(int x);
        bool operator >=(int x);
        bool operator <(int x);
        bool operator <=(int x);
        bool operator ==(int x);
        bool operator !=(int x);
};

void BigInteger::norm() {
    if(d.size() == 0) {
        n = 0;
        sign = 1;
        return;
    }
    n = d.size();
    for(int i = 0; i + 1 < n; i++) {
        if(d[i] < 0) {
            d[i + 1]--;
            d[i] += p;
        }
    }
    for(int i = 0; i + 1 < n; i++) {
        d[i + 1] += d[i] / p;
        d[i] %= p;
    }
    while(d.back() >= p) {
        d.push_back(d.back() / p);
        d[n - 1] %= p;
        n++;
    }
    while(d.size() > 0 && d.back() == 0) {
        d.pop_back();
        n--;
    }
    n = d.size();
}

ostream &operator << (ostream &out, const BigInteger &a) {
    if(a.n == 0) {
        out << 0;
        return out;
    }
    if(a.sign == -1) {
        out << "-";
    }
    out << a.d.back();
    char filler = out.fill('0');
    for(int i = a.n - 2; i >= 0; i--) {
        out << setw(a.cnt) << a.d[i];
    }
    return out;
}

istream &operator >> (istream &in, BigInteger &a) {
    string s;
    in >> s;
    if(s[0] == '-') {
        a.sign = -1;
        s.erase(0, 1);
    }
    a.n = s.size();
    for(int i = a.n - a.cnt; i >= 0; i -= a.cnt) {
        a.d.push_back(stoi(s.substr(i, a.cnt)));
    }
    if(a.n % a.cnt != 0) {
        a.d.push_back(stoi(s.substr(0, a.n % a.cnt)));
    }
    a.n = a.d.size();
    a.norm();
    return in;
}

BigInteger BigInteger::copy() {
    norm();
    BigInteger res;
    res.d = d;
    res.sign = sign;
    res.n = n;
    return res;
}

bool BigInteger::operator ==(const BigInteger &b) {
    norm();
    return (sign == b.sign && d == b.d);
}

bool BigInteger::operator !=(const BigInteger &b) {
    norm();
    return !(sign == b.sign && d == b.d);
}

bool BigInteger::operator <(const BigInteger &b) {
    if(sign == -1 && b.sign == 1) {
        return 1;
    }
    if(sign == 1 && b.sign == -1) {
        return 0;
    }
    if(sign == -1 && b.sign == -1) {
        if(n < b.n) {
            return 0;
        }
        if(n > b.n) {
            return 1;
        }
        for(int i = n - 1; i >= 0; i--) {
            if(d[i] < b.d[i]) {
                return 0;
            }
            if(b.d[i] < d[i]) {
                return 1;
            }
        }
        return 0;
    }
    if(n < b.n) {
        return 1;
    }
    if(n > b.n) {
        return 0;
    }
    for(int i = n - 1; i >= 0; i--) {
        if(d[i] < b.d[i]) {
            return 1;
        }
        if(b.d[i] < d[i]) {
            return 0;
        }
    }
    return 0;
}

bool BigInteger::operator <=(const BigInteger &b) {
    return (copy() < b) || (copy() == b);
}

bool BigInteger::operator >=(const BigInteger &b) {
    return !(copy() < b);
}

bool BigInteger::operator >(const BigInteger &b) {
    return !(copy() <= b);
}

BigInteger operator -(const BigInteger &a) {
    BigInteger res = a;
    res.sign *= -1;
    return res;
}

BigInteger BigInteger::operator +(const BigInteger &b) {
    if(sign == -1 && b.sign == -1) {
        return -(-*this + -b);
    }
    if(sign == -1 && b.sign == 1) {
        return -((-*this) - b);
    }
    if(sign == 1 && b.sign == -1) {
        return (*this - (-b));
    }
    BigInteger res;
    long long sz = min(n, b.n);
    for(int i = 0; i < sz; i++) {
        res.d.push_back(d[i] + b.d[i]);
    }
    for(int i = sz; i < n; i++) {
        res.d.push_back(d[i]);
    }
    for(int i = sz; i < b.n; i++) {
        res.d.push_back(b.d[i]);
    }
    res.norm();
    return res;
}

BigInteger BigInteger::operator +(int x) {
    BigInteger b(to_string(x));
    BigInteger res = (*this + b);
    return res;
}

BigInteger BigInteger::operator -(const BigInteger &b) {
    if(sign == -1 && b.sign == -1) {
        return -((-*this) - (-b));
    }
    if(sign == -1 && b.sign == 1) {
        return -((-*this) + b);
    }
    if(sign == 1 && b.sign == -1) {
        return (*this + (-b));
    }
    if(copy() < b) {
        BigInteger res;
        long long sz = min(n, b.n);
        for(int i = 0; i < sz; i++) {
            res.d.push_back(b.d[i] - d[i]);
        }
        for(int i = sz; i < b.n; i++) {
            res.d.push_back(b.d[i]);
        }
        res.norm();
        return -res;
    }
    BigInteger res;
    long long sz = min(n, b.n);
    for(int i = 0; i < sz; i++) {
        res.d.push_back(d[i] - b.d[i]);
    }
    for(int i = sz; i < n; i++) {
        res.d.push_back(d[i]);
    }
    res.norm();
    return res;
}

BigInteger BigInteger::operator -(int x) {
    BigInteger b(to_string(x));
    BigInteger res = (*this - b);
    return res;
}

BigInteger BigInteger::operator *(const BigInteger &b) {
    BigInteger res;
    res.d.resize(n + b.n);
    for(int i = 0; i < n; i++) {
        for(long long j = 0; j < b.n; j++) {
            res.d[i + j] += d[i] * b.d[j];
        }
    }
    res.sign = sign * b.sign;
    res.norm();
    return res;
}

BigInteger BigInteger::operator *(int x) {
    BigInteger res = *this;
    res.sign = sign;
    if(x < 0) {
        res.sign *= -1;
        x *= -1;
    }
    for(int i = 0; i < n; i++) {
        res.d[i] *= x;
    }
    res.norm();
    return res;
}

BigInteger BigInteger::operator /(int x) {
    vector<long long> curr = d;
    reverse(curr.begin(), curr.end());
    BigInteger res;
    long long s = 0;
    int i = 0;
    while(i < n && s < abs(x)) {
        s = s * p + curr[i];
        i++;
    }
    for(; i < n; i++) {
        res.d.push_back(s / abs(x));
        s = (s % abs(x)) * p + curr[i];
    }
    res.d.push_back(s / abs(x));
    reverse(res.d.begin(), res.d.end());
    res.sign = sign;
    if(x < 0) {
        res.sign *= -1;
    }
    res.norm();
    return res;
}

long long BigInteger::operator %(int x) {
    vector<long long> curr = d;
    reverse(curr.begin(), curr.end());
    long long s = 0;
    int i = 0;
    while(i < n && s < x) {
        s = s * p + curr[i];
        i++;
    }
    for(; i < n; i++) {
        s = (s % x) * p + curr[i];
    }
    s %= x;
    if(sign == -1) {
        s = (-s + x);
        s %= x;
    }
    return s;
}

BigInteger BigInteger::operator +=(const BigInteger &b) {
    *this = (*this + b);
    return *this;
}

BigInteger BigInteger::operator +=(int x) {
    *this = (*this + x);
    return *this;
}

BigInteger BigInteger::operator -=(const BigInteger &b) {
    *this = (*this - b);
    return *this;
}

BigInteger BigInteger::operator -=(int x) {
    *this = (*this - x);
    return *this;
}

BigInteger BigInteger::operator /=(int x) {
    *this = (*this / x);
    return *this;
}

BigInteger BigInteger::operator *=(const BigInteger &b) {
    *this = (*this * b);
    return *this;
}

BigInteger BigInteger::operator *=(int x) {
    *this = (*this * x);
    return *this;
}

BigInteger BigInteger::operator ++() {
    *this += 1;
    return *this;
}

bool BigInteger::operator >(int x) {
    BigInteger curr(to_string(x));
    curr.norm();
    return (*this > curr);
}

bool BigInteger::operator >=(int x) {
    BigInteger curr(to_string(x));
    curr.norm();
    return (*this >= curr);
}

bool BigInteger::operator <(int x) {
    BigInteger curr(to_string(x));
    curr.norm();
    return (*this < curr);
}

bool BigInteger::operator <=(int x) {
    BigInteger curr(to_string(x));
    curr.norm();
    return (*this <= curr);
}

bool BigInteger::operator ==(int x) {
    BigInteger curr(to_string(x));
    curr.norm();
    return (*this == curr);
}

bool BigInteger::operator !=(int x) {
    BigInteger curr(to_string(x));
    norm();
    return (*this != curr);
}
