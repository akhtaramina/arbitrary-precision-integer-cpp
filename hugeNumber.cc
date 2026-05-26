/* * DESIGN CHOICE: Error Handling
 * I chose to use 'throw std::invalid_argument' instead of 'abort()'.
 * Exceptions are preferred because they allow the program to catch and
 * recover from errors (as demonstrated in main) rather than
 * crashing the entire application immediately.
 */

#include "hugeNumber.h"
#include <algorithm>
#include <stdexcept>
HugeNumber::HugeNumber(){
	negative = false;
	digits.push_back(0);
}
HugeNumber::HugeNumber(const std::string &strDigit) {
	if (strDigit.empty()){
		throw std::invalid_argument("Empty input");
	}
	negative = false;
	int startIndex = 0;
    	if (strDigit[0] == '-') {
        	negative = true;
        	startIndex = 1;
    	}
	for (int i = (int)strDigit.length() - 1; i >= startIndex; --i) {
		if (!isdigit(strDigit[i])){
			throw std::invalid_argument("Invalid char");
		}
        		digits.push_back(strDigit[i] - '0');
    	}
    	normalize();
}
HugeNumber::HugeNumber(char arrDigit[], int n) {
	if (n <= 0){
		throw std::invalid_argument("Invalid size");
	}
	negative = false;
	int startIndex = 0;
	if(arrDigit[0] == '-'){
		if (n == 1){
			throw std::invalid_argument("Input is only a minus sign");
		}
		negative = true;
		startIndex = 1;
	}
	for (int i = n - 1; i >= startIndex; --i) {
        	if (!isdigit(arrDigit[i])) throw std::invalid_argument("Invalid char");
        	digits.push_back(arrDigit[i] - '0');
    	}
    	normalize();
}
HugeNumber::HugeNumber(const std::vector<int> &vectDigit, bool isNegative){
    	negative = isNegative;
    	if (vectDigit.empty()) {
        	throw std::invalid_argument("Empty vector");
    	}
    	for (int i = (int)vectDigit.size() - 1; i >= 0; --i) {
	        if (vectDigit[i] < 0 || vectDigit[i] > 9) {
			throw std::invalid_argument("Vector contains non-digit value");
        	}
        	digits.push_back(vectDigit[i]);
    	}
    	normalize();
}
void HugeNumber::normalize(){
	while ((int)digits.size() > 1 && digits.back() == 0) {
        	digits.pop_back(); // removing leading zero, unless the result is 0
    	}
    	if (digits.empty()) {
        	digits.push_back(0);
    	}
    	if ((int)digits.size() == 1 && digits[0] == 0) {
        	negative = false;
    	}
}
bool HugeNumber::isZero() const{
	return (int)digits.size() == 1 && digits[0] == 0;
}
int HugeNumber::numDigits() const{
	return (int)digits.size();
}
HugeNumber HugeNumber::abs() const{
	HugeNumber absoluteVal = *this;
	absoluteVal.negative = false;
 	return absoluteVal;
}
bool HugeNumber::operator==(const HugeNumber &other) const{
	return negative == other.negative && digits == other.digits;
}

bool HugeNumber::operator!=(const HugeNumber &other) const {
	return !(*this == other);
}
bool HugeNumber::operator<(const HugeNumber &other) const {
    	if (this->negative == true && other.negative == false) {
        	return true;
    	}
    	if (this->negative == false && other.negative == true) {
        	return false;
    	}
    	if ((int)this->digits.size() != (int)other.digits.size()) { //sign same, size different
        	if (this->negative == false) {
            		return (int)this->digits.size() < (int)other.digits.size();
        	} else {
            		return (int)this->digits.size() > (int)other.digits.size();
        	}
    	}
    	for (int i = (int)this->digits.size() - 1; i >= 0; i--) { // sign and size same
        	if (this->digits[i] != other.digits[i]) {
            		if (this->negative == false) {
                		return this->digits[i] < other.digits[i];
            		} else {
                	return this->digits[i] > other.digits[i];
            		}
        	}
    	}
    	return false;
}
bool HugeNumber::operator<=(const HugeNumber &other)const{
	return *this < other || *this == other;
}
bool HugeNumber::operator>(const HugeNumber &other) const {
	return !(*this <= other);
}
bool HugeNumber::operator>=(const HugeNumber &other) const {
	return !(*this < other);
}
HugeNumber HugeNumber::operator+(const HugeNumber &other) const {
    	HugeNumber result;
    	result.digits.clear();
    	if (this->negative == other.negative) {
        	int carry = 0;
        	int maxLen = std::max((int)this->digits.size(), (int)other.digits.size());
        	for (int i = 0; i < maxLen; i++) {
            		int digitA = (i < (int)this->digits.size()) ? (int)this->digits[i] : 0;
            		int digitB = (i < (int)other.digits.size()) ? (int)other.digits[i] : 0;
	            	int sum = digitA + digitB + carry;
            		result.digits.push_back(sum % 10);
            		carry = sum / 10;
        	}
        	if (carry > 0) {
            		result.digits.push_back(carry);
        	}
		result.negative = this->negative;
		result.normalize();
		return result;
    	}
    	if (!this->negative && other.negative) {
        	return *this - other.abs();
    	}
    	//if (this->negative && !other.negative) {
        else{
		return other - this->abs();
    	}
	//return result;
}
HugeNumber HugeNumber::operator-(const HugeNumber &other) const{
    	if (this->negative != other.negative) {
        	HugeNumber result = this->abs() + other.abs();
        	result.negative = this->negative;
        	result.normalize();
        	return result;
    	}
    	if (this->abs() < other.abs()) {
        	HugeNumber result = other.abs() - this->abs();
        	result.negative = !this->negative;
        	result.normalize();
        	return result;
    	}
    	HugeNumber result = *this;
    	int borrow = 0;
    	for (int i = 0; i < (int)other.digits.size() || borrow; i++) {
        	int digitA = result.digits[i];
        	int digitB = (i < (int)other.digits.size()) ? other.digits[i] : 0;
        	int sub = digitA - borrow - digitB;
        	if (sub < 0) {
            		sub = sub + 10;
            		borrow = 1;
        	} else {
            		borrow = 0;
        	}
        	result.digits[i] = sub;
    	}
    	result.normalize();
    	return result;
}
HugeNumber HugeNumber::operator*(const HugeNumber &other) const {
    	HugeNumber res;
    	res.digits.assign((int)this->digits.size() + (int)other.digits.size(), 0);

    	for (int i = 0; i < (int)this->digits.size(); i++) {
        	int carry = 0;
        	for (int j = 0; j < (int)other.digits.size() || carry > 0; j++) {
            		int otherDigit = (j < (int)other.digits.size()) ? other.digits[j] : 0;
            		long long product = (long long)this->digits[i] * otherDigit;
            		if (i + j >= (int)res.digits.size()) {
                		res.digits.push_back(0);
            		}
            		long long currentTotal = res.digits[i + j] + product + carry;
            		res.digits[i + j] = currentTotal % 10;
            		carry = (int)(currentTotal / 10);
        	}
    	}
    	res.negative = (this->negative != other.negative);
    	res.normalize();
    	return res;
}
HugeNumber& HugeNumber::operator++(){
	*this = *this + HugeNumber("1");
	return *this;
}
HugeNumber HugeNumber::operator++(int) {
	HugeNumber tmp = *this;
	++(*this);
	return tmp;
}
HugeNumber& HugeNumber::operator--() {
    	*this = *this - HugeNumber("1");
    	return *this;
}
HugeNumber HugeNumber::operator--(int) {
	HugeNumber tmp = *this;
	--(*this);
	return tmp;
}
HugeNumber HugeNumber::operator~() const {
    	HugeNumber res = *this;
	// Since digits are stored in reverse order (ones place at index 0),
    	// reversing the vector itself effectively reverses the actual number.
    	// Example: 123 is stored as {3, 2, 1}. Reversing it makes it {1, 2, 3},
	// which represents the number 321.
    	std::reverse(res.digits.begin(), res.digits.end());
    	res.normalize();
    	return res;
}

std::ostream& operator<<(std::ostream &os, const HugeNumber &num) {
    	if (num.negative) os << '-';
   	for (int i = (int)num.digits.size() - 1; i >= 0; --i){
		os << num.digits[i];
	}
    	return os;
}

std::istream& operator>>(std::istream &is, HugeNumber &num) {
    	std::string s;
    	if (is >> s){
		num = HugeNumber(s);
	}
    	return is;
}
