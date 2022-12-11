#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "StringTools.hpp"
#include <absl/numeric/int128.h>

class BigInt{
    std::string digits;
public:
 
    //Constructors:
    BigInt(unsigned long long n = 0);
    BigInt(std::string &);
    BigInt(const char *);
 
    //Helper Functions:
    friend void divide_by_2(BigInt &a);
    friend bool Null(const BigInt &);
    friend int Length(const BigInt &);
    int operator[](const int)const;
 
               /* * * * Operator Overloading * * * */
 
    //Post/Pre - Incrementation
    BigInt &operator++();
    BigInt operator++(int temp);
    BigInt &operator--();
    BigInt operator--(int temp);
 
    //Addition and Subtraction
    friend BigInt &operator+=(BigInt &, const BigInt &);
    friend BigInt operator+(const BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt &operator-=(BigInt &, const BigInt &);
 
    //Comparison operators
    friend bool operator==(const BigInt &, const BigInt &);
    friend bool operator!=(const BigInt &, const BigInt &);
 
    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);
    friend bool operator<(const BigInt &, const BigInt &);
    friend bool operator<=(const BigInt &, const BigInt &);
 
    //Multiplication and Division
    friend BigInt &operator*=(BigInt &, const BigInt &);
    friend BigInt operator*(const BigInt &, const BigInt &);
    friend BigInt &operator/=(BigInt &, const BigInt &);
    friend BigInt operator/(const BigInt &, const BigInt &);
 
    //Modulo
    friend BigInt operator%(const BigInt &, const BigInt &);
    friend BigInt &operator%=(BigInt &, const BigInt &);
 
    //Power Function
    friend BigInt &operator^=(BigInt &,const BigInt &);
    friend BigInt operator^(BigInt &, const BigInt &);
     
    //Square Root Function
    friend BigInt sqrt(BigInt &a);
 
    //Read and Write
    friend std::ostream &operator<<(std::ostream &,const BigInt &);
    friend std::istream &operator>>(std::istream &, BigInt &);
 
    //Others
    friend BigInt NthCatalan(int n);
    friend BigInt NthFibonacci(int n);
    friend BigInt Factorial(int n);
};
 
BigInt::BigInt(std::string & s){
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0;i--){
        if(!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}
BigInt::BigInt(unsigned long long nr){
    do{
        digits.push_back(nr % 10);
        nr /= 10;
    } while (nr);
}
BigInt::BigInt(const char *s){
    digits = "";
    for (int i = strlen(s) - 1; i >= 0;i--)
    {
        if(!isdigit(s[i]))
            throw("ERROR");
        digits.push_back(s[i] - '0');
    }
}
 
bool Null(const BigInt& a){
    if(a.digits.size() == 1 && a.digits[0] == 0)
        return true;
    return false;
}
int Length(const BigInt & a){
    return a.digits.size();
}
int BigInt::operator[](const int index)const{
    if(digits.size() <= index || index < 0)
        throw("ERROR");
    return digits[index];
}
bool operator==(const BigInt &a, const BigInt &b){
    return a.digits == b.digits;
}
bool operator!=(const BigInt & a,const BigInt &b){
    return !(a == b);
}
bool operator<(const BigInt&a,const BigInt&b){
    int n = Length(a), m = Length(b);
    if(n != m)
        return n < m;
    while(n--)
        if(a.digits[n] != b.digits[n])
            return a.digits[n] < b.digits[n];
    return false;
}
bool operator>(const BigInt&a,const BigInt&b){
    return b < a;
}
bool operator>=(const BigInt&a,const BigInt&b){
    return !(a < b);
}
bool operator<=(const BigInt&a,const BigInt&b){
    return !(a > b);
}
 
BigInt &BigInt::operator++(){
    int i, n = digits.size();
    for (i = 0; i < n && digits[i] == 9;i++)
        digits[i] = 0;
    if(i == n)
        digits.push_back(1);
    else
        digits[i]++;
    return *this;
}
BigInt BigInt::operator++(int temp){
    BigInt aux;
    aux = *this;
    ++(*this);
    return aux;
}
 
BigInt &BigInt::operator--(){
    if(digits[0] == 0 && digits.size() == 1)
        throw("UNDERFLOW");
    int i, n = digits.size();
    for (i = 0; digits[i] == 0 && i < n;i++)
        digits[i] = 9;
    digits[i]--;
    if(n > 1 && digits[n - 1] == 0)
        digits.pop_back();
    return *this;
}
BigInt BigInt::operator--(int temp){
    BigInt aux;
    aux = *this;
    --(*this);
    return aux;
}
 
BigInt &operator+=(BigInt &a,const BigInt& b){
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if(m > n)
        a.digits.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n;i++){
        if(i < m)
            s = (a.digits[i] + b.digits[i]) + t;
        else
            s = a.digits[i] + t;
        t = s / 10;
        a.digits[i] = (s % 10);
    }
    if(t)
        a.digits.push_back(t);
    return a;
}
BigInt operator+(const BigInt &a, const BigInt &b){
    BigInt temp;
    temp = a;
    temp += b;
    return temp;
}
 
BigInt &operator-=(BigInt&a,const BigInt &b){
    if(a < b)
        throw("UNDERFLOW");
    int n = Length(a), m = Length(b);
    int i, t = 0, s;
    for (i = 0; i < n;i++){
        if(i < m)
            s = a.digits[i] - b.digits[i]+ t;
        else
            s = a.digits[i]+ t;
        if(s < 0)
            s += 10,
            t = -1;
        else
            t = 0;
        a.digits[i] = s;
    }
    while(n > 1 && a.digits[n - 1] == 0)
        a.digits.pop_back(),
        n--;
    return a;
}
BigInt operator-(const BigInt& a,const BigInt&b){
    BigInt temp;
    temp = a;
    temp -= b;
    return temp;
}
 
BigInt &operator*=(BigInt &a, const BigInt &b)
{
    if(Null(a) || Null(b)){
        a = BigInt();
        return a;
    }
    int n = a.digits.size(), m = b.digits.size();
    std::vector<int> v(n + m, 0);
    for (int i = 0; i < n;i++)
        for (int j = 0; j < m;j++){
            v[i + j] += (a.digits[i] ) * (b.digits[j]);
        }
    n += m;
    a.digits.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++)
    {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.digits[i] = v[i] ;
    }
    for (int i = n - 1; i >= 1 && !v[i];i--)
            a.digits.pop_back();
    return a;
}
BigInt operator*(const BigInt&a,const BigInt&b){
    BigInt temp;
    temp = a;
    temp *= b;
    return temp;
}
 
BigInt &operator/=(BigInt& a,const BigInt &b){
    if(Null(b))
        throw("Arithmetic Error: Division By 0");
    if(a < b){
        a = BigInt();
        return a;
    }
    if(a == b){
        a = BigInt(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    std::vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i]  < b;i--){
        t *= 10;
        t += a.digits[i] ;
    }
    for (; i >= 0; i--){
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t;cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a.digits.resize(cat.size());
    for (i = 0; i < lgcat;i++)
        a.digits[i] = cat[lgcat - i - 1];
    a.digits.resize(lgcat);
    return a;
}
BigInt operator/(const BigInt &a,const BigInt &b){
    BigInt temp;
    temp = a;
    temp /= b;
    return temp;
}
 
BigInt &operator%=(BigInt& a,const BigInt &b){
    if(Null(b))
        throw("Arithmetic Error: Division By 0");
    if(a < b){
        a = BigInt();
        return a;
    }
    if(a == b){
        a = BigInt(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    std::vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digits[i] < b;i--){
        t *= 10;
        t += a.digits[i];
    }
    for (; i >= 0; i--){
        t = t * 10 + a.digits[i];
        for (cc = 9; cc * b > t;cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a = t;
    return a;
}
BigInt operator%(const BigInt &a,BigInt &b){
    BigInt temp;
    temp = a;
    temp %= b;
    return temp;
}
 
BigInt &operator^=(BigInt & a,const BigInt & b){
    BigInt Exponent, Base(a);
    Exponent = b;
    a = 1;
    while(!Null(Exponent)){
        if(Exponent[0] & 1)
            a *= Base;
        Base *= Base;
        divide_by_2(Exponent);
    }
    return a;
}
BigInt operator^(BigInt & a,BigInt & b){
    BigInt temp(a);
    temp ^= b;
    return temp;
}
 
void divide_by_2(BigInt & a){
    int add = 0;
    for (int i = a.digits.size() - 1; i >= 0;i--){
        int digit = (a.digits[i] >> 1) + add;
        add = ((a.digits[i] & 1) * 5);
        a.digits[i] = digit;
    }
    while(a.digits.size() > 1 && !a.digits.back())
        a.digits.pop_back();
}
 
BigInt sqrt(BigInt & a){
    BigInt left(1), right(a), v(1), mid, prod;
    divide_by_2(right);
    while(left <= right){
        mid += left;
        mid += right;
        divide_by_2(mid);
        prod = (mid * mid);
        if(prod <= a){
            v = mid;
            ++mid;
            left = mid;
        }
        else{
            --mid;
            right = mid;
        }
        mid = BigInt();
    }
    return v;
}
 
std::istream &operator>>(std::istream &in,BigInt&a){
    std::string s;
    in >> s;
    int n = s.size();
    for (int i = n - 1; i >= 0;i--){
        if(!isdigit(s[i]))
            throw("INVALID NUMBER");
        a.digits[n - i - 1] = s[i];
    }
    return in;
}
 
std::ostream &operator<<(std::ostream &out,const BigInt &a){
    for (int i = a.digits.size() - 1; i >= 0;i--)
        out << (short)a.digits[i];
    return out;
}

struct Monkey
{
    char op = '+';
    BigInt opValue = "0";
    BigInt divTest = "0";
    int64_t testPassDest = 0;
    int64_t testFailDest = 0;
    std::vector<BigInt> items;
    int64_t inspected = 0;
};

int main ()
{
    constexpr int64_t maxRounds1 = 20;
    constexpr int64_t maxRounds2 = 10000;
    std::vector<Monkey> monkeys1;
    std::vector<Monkey> monkeys2;

    std::string line;
    std::ifstream input("../../../2022/inputs/day11.txt");
    while (std::getline(input, line))
    {
        std::getline(input, line);
        std::vector<std::string> strItems = cc::StrSplit(line.substr(17), ", ");
        std::vector<BigInt> items;
        std::transform(strItems.begin(), strItems.end(), std::back_inserter(items), [](const std::string& strItem){ return std::stoll(strItem); });
        std::getline(input, line);
        char op = line[23];
        BigInt opValue = line.ends_with("old") ? -1 : std::stoll(cc::StrSplit(line, " ").back());
        std::getline(input, line);
        BigInt divTest = std::stoll(cc::StrSplit(line, " ").back());
        std::getline(input, line);
        int64_t testPassDest = std::stoll(cc::StrSplit(line, " ").back());
        std::getline(input, line);
        int64_t testFailDest = std::stoll(cc::StrSplit(line, " ").back());
        monkeys1.push_back({.op = op, .opValue = opValue, .divTest = divTest, .testPassDest = testPassDest, .testFailDest = testFailDest, .items = items});
        std::getline(input, line); // Consume empty line
    }
    input.close();
    monkeys2 = monkeys1;

    for (int64_t round = 0; round < maxRounds1; ++round) 
    {
        int64_t i = 0;
        for (auto& monkey : monkeys1)
        {
            //std::cout << "Monkey " << i++ << ":\n";
            while (monkey.items.size())
            {
                BigInt item = *monkey.items.begin();
                monkey.items.erase(monkey.items.begin());
                //std::cout << "  Monkey inspects an item with a worry level of " << item << ".\n";

                BigInt worry = "0";
                BigInt opVal = monkey.opValue == -1 ? item : monkey.opValue;
                switch(monkey.op)
                {
                case '+':
                    worry = item + opVal;
                    //std::cout << "    Worry level increases by " << opVal << " to " << worry << ".\n";
                    break;
                case '*':
                    worry = item * opVal;
                    //std::cout << "    Worry level is multiplied by " << opVal << " to " << worry << ".\n";
                    break;
                }

                //std::cout << "    Monkey gets bored with item. Worry level is divided by 3 to " << worry / 3 << ".\n";
                if (((worry / 3) % monkey.divTest) == "0")
                {
                    monkeys1[monkey.testPassDest].items.push_back(worry / 3);
                    //std::cout << "    Current worry level is not divisible by " << monkey.divTest << ".\n";
                    //std::cout << "    Item with worry level " << worry / 3 << " is thrown to monkey " << monkey.testPassDest << ".\n";
                }
                else
                {
                    monkeys1[monkey.testFailDest].items.push_back(worry / 3);
                    //std::cout << "    Current worry level is not divisible by " << monkey.divTest << ".\n";
                    //std::cout << "    Item with worry level " << worry / 3 << " is thrown to monkey " << monkey.testFailDest << ".\n";
                }

                monkey.inspected++;
            }
        }
    }

    for (int64_t round = 0; round < maxRounds2; ++round)
    {
        std::cout << "Round: " << round << "\n";
        for (auto& monkey : monkeys2)
        {
            while (monkey.items.size())
            {
                BigInt item = *monkey.items.begin();
                monkey.items.erase(monkey.items.begin());

                BigInt worry = "0";
                BigInt opVal = monkey.opValue == -1 ? item : monkey.opValue;
                switch(monkey.op)
                {
                case '+':
                    worry = item + opVal;
                    break;
                case '*':
                    worry = item * opVal;
                    break;
                }

                if ((worry % monkey.divTest) == "0")
                {
                    monkeys2[monkey.testPassDest].items.push_back(worry);
                }
                else
                {
                    monkeys2[monkey.testFailDest].items.push_back(worry);
                }

                monkey.inspected++;
            }
        }
    }

    BigInt max = "0", runnerUp = "0";
    for (auto& monkey : monkeys1)
    {
        if (monkey.inspected > max)
        {
            runnerUp = max;
            max = monkey.inspected;
        }
        else if (monkey.inspected > runnerUp)
        {
            runnerUp = monkey.inspected;
        }
    }
    std::cout << "Monke biz 1: " << max * runnerUp << "\n";
    max = "0";
    runnerUp = "0";
    for (auto& monkey : monkeys2)
    {
        if (monkey.inspected > max)
        {
            runnerUp = max;
            max = monkey.inspected;
        }
        else if (monkey.inspected > runnerUp)
        {
            runnerUp = monkey.inspected;
        }
    }
    std::cout << "Monke biz 2: " << max * runnerUp << "\n";
}
