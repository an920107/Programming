#include <bits/stdc++.h>
using namespace std;

#define MAX_SIZE 1000

class BigNumber {
private:
    char arr[MAX_SIZE];
    int length;
    bool negtive;
    void push(char);
    char pop();
    void insert(char, int);
    char erase(int);
    void stripZero();
    void swap(BigNumber&, BigNumber&);
    BigNumber subArr(int, int);

public:
    BigNumber();
    BigNumber(const string&);
    BigNumber operator=(string&);
    BigNumber operator+(BigNumber);
    BigNumber operator-(BigNumber);
    BigNumber operator*(BigNumber);
    BigNumber operator/(BigNumber);
    bool operator>(BigNumber);
    bool operator<(BigNumber);
    bool operator==(BigNumber);
    bool operator>=(BigNumber);
    bool operator<=(BigNumber);
    friend istream& operator>>(istream&, BigNumber&);
    friend ostream& operator<<(ostream&, BigNumber);
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    BigNumber x, y;
    char opt;
    cin >> x >> opt >> y;
    switch (opt) {
        case '+': cout << x + y; break;
        case '-': cout << x - y; break;
        case '*': cout << x * y; break;
        case '/': cout << x / y; break;
        default: break;
    }
    cout << "\n";
    
    return 0;
}

BigNumber::BigNumber() {
    memset(arr, 0, MAX_SIZE);
    length = 1;
    negtive = false;
}

BigNumber::BigNumber(const string& in) {
    memset(arr, 0, MAX_SIZE);
    length = 0;
    negtive = false;
    for (auto iter = in.rbegin(); iter != in.rend(); iter ++) {
        push(*iter - 48);
    }
}

void BigNumber::push(char in) {
    arr[length ++] = in;
}

char BigNumber::pop() {
    char tmp = arr[-- length];
    arr[length] = 0;
    return tmp;
}

void BigNumber::swap(BigNumber& x, BigNumber& y) {
    BigNumber res = x;
    x = y, y = res;
}

void BigNumber::insert(char in, int index) {
    for (int i = length ++; i > index; i --) {
        arr[i] = arr[i - 1];
    }
    arr[index] = in;
}

char BigNumber::erase(int index) {
    char tmp = arr[index];
    length --;
    for (int i = index; i < length; i ++) {
        arr[i] = arr[i + 1];
    }
    arr[length] = 0;
    return tmp;
}

void BigNumber::stripZero() {
    for (int i = length - 1; i > 0; i --) {
        if ((*this).arr[i] != 0) return;
        pop();
    }
}

BigNumber BigNumber::subArr(int begin, int len) {
    BigNumber tmp;
    for (int i = 0; i < len; i ++) {
        tmp.push((*this).arr[begin + i]);
    }
    return tmp;
}

BigNumber BigNumber::operator=(string& str) {
    return BigNumber(str);
}

BigNumber BigNumber::operator+(BigNumber obj) {
    BigNumber tmp = *this;
    char carry = 0;
    while (tmp.length > obj.length) obj.push(0);
    while (tmp.length < obj.length) tmp.push(0);
    for (int i = 0; i < tmp.length; i ++) {
        tmp.arr[i] += obj.arr[i] + carry;
        carry = tmp.arr[i] >= 10;
        tmp.arr[i] -= 10 * carry;
    }
    tmp.stripZero();
    return tmp;
}

BigNumber BigNumber::operator-(BigNumber obj) {
    BigNumber tmp = *this;
    char borrow = 0;
    while (tmp.length > obj.length) obj.push(0);
    while (tmp.length < obj.length) tmp.push(0);
    if (tmp < obj) {
        swap(tmp, obj);
        tmp.negtive = true;
    }
    for (int i = 0; i < tmp.length; i ++) {
        tmp.arr[i] -= obj.arr[i] + borrow;
        borrow = tmp.arr[i] < 0;
        tmp.arr[i] += 10 * borrow;
    }
    tmp.stripZero();
    return tmp;
}

BigNumber BigNumber::operator*(BigNumber obj) {
    BigNumber tmp = *this, res;
    char carry = 0;
    res.length = tmp.length + obj.length;
    for (int i = 0; i < tmp.length; i ++) {
        for (int j = 0; j <= obj.length; j ++) {
            res.arr[i + j] += tmp.arr[i] * obj.arr[j] + carry;
            carry = res.arr[i + j] / 10;
            res.arr[i + j] %= 10;
        }
    }
    res.stripZero();
    return res;
}

BigNumber BigNumber::operator/(BigNumber obj) {
    BigNumber tmp = *this, max_div = obj, res;
    while (obj.length < tmp.length) obj.insert(0, 0);
    while (tmp >= max_div) {
        for (int times = 1; times <= 10; times ++) {
            if (obj * BigNumber(to_string(times)) > tmp) {
                res.push(-- times);
                tmp = tmp - obj * BigNumber(to_string(times));
                obj.erase(0);
                break;
            }
        }
    }
    reverse(res.arr, res.arr + res.length);
    res.stripZero();
    return res;
}

bool BigNumber::operator>(BigNumber obj) {
    BigNumber tmp = *this;
    while (tmp.length > obj.length) obj.push(0);
    while (tmp.length < obj.length) tmp.push(0);
    for (int i = tmp.length - 1; i >= 0; i --) {
        if (tmp.arr[i] > obj.arr[i]) return true;
        if (tmp.arr[i] < obj.arr[i]) return false;
    }
    return false;
}

bool BigNumber::operator<(BigNumber obj) {
    BigNumber tmp = *this;
    while (tmp.length > obj.length) obj.push(0);
    while (tmp.length < obj.length) tmp.push(0);
    for (int i = tmp.length - 1; i >= 0; i --) {
        if (tmp.arr[i] < obj.arr[i]) return true;
        if (tmp.arr[i] > obj.arr[i]) return false;
    }
    return false;
}

bool BigNumber::operator==(BigNumber obj) {
    return !(*this > obj) && !(*this < obj);
}

bool BigNumber::operator>=(BigNumber obj) {
    return *this > obj || *this == obj;
}

bool BigNumber::operator<=(BigNumber obj) {
    return *this < obj || *this == obj;
}

istream& operator>>(istream& is, BigNumber& obj) {
    string str;
    is >> str;
    obj = BigNumber(str);
    obj.stripZero();
    return is;
}

ostream& operator<<(ostream& os, BigNumber obj) {
    if (obj.negtive) os << "-";
    for (int i = obj.length - 1; i >= 0; i --) {
        os << char(obj.arr[i] + 48);
    }
    return os;
}
