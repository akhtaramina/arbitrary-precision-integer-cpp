#ifndef HUGENUMBER_H
#define HUGENUMBER_H

#include <vector>
#include <string>
#include <iostream>
class HugeNumber {
public:
    HugeNumber();
    HugeNumber(const std::string &strDigit);
    HugeNumber(char arrDigit[], int n);
    HugeNumber(const std::vector<int> &vectDigit, bool isNegative);
    HugeNumber operator+(const HugeNumber &other) const;
    HugeNumber operator-(const HugeNumber &other) const;
    HugeNumber operator*(const HugeNumber &other) const;
    bool operator==(const HugeNumber &other) const;
    bool operator!=(const HugeNumber &other) const;
    bool operator<(const HugeNumber &other) const;
    bool operator<=(const HugeNumber &other) const;
    bool operator>(const HugeNumber &other) const;
    bool operator>=(const HugeNumber &other) const;
    HugeNumber& operator++();    // prefix
    HugeNumber operator++(int);  // postfix
    HugeNumber& operator--();    // prefix
    HugeNumber operator--(int);  // postfix
    friend std::ostream& operator<<(std::ostream &os, const HugeNumber &num);
    friend std::istream& operator>>(std::istream &is, HugeNumber &num);
    HugeNumber operator~() const;
    bool isZero() const;
    int numDigits() const;
    HugeNumber abs() const;
    void normalize();
private:
    std::vector<int> digits; // Stores digit in reverse order
    bool negative;
};

#endif
