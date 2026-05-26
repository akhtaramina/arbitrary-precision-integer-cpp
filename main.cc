#include <iostream>
#include <sstream>
#include <vector>
#include "hugeNumber.h"

int main() {

    // ─────────────────────────────────────────
    // SECTION 1: Construction Tests
    // ─────────────────────────────────────────
    std::cout << "=== CONSTRUCTION TESTS ===" << std::endl;

    // From string
    HugeNumber a("12345678901234567890");
    std::cout << "From string:           " << a << std::endl;

    HugeNumber neg("-45009");
    std::cout << "From string (neg):     " << neg << std::endl;

    // From char array
    char arr[] = "-45009";
    HugeNumber b(arr, 6);
    std::cout << "From char array:       " << b << std::endl;

    // From vector (positive)
    std::vector<int> d = {1, 2, 3, 4, 5};
    HugeNumber c(d, false);
    std::cout << "From vector (pos):     " << c << std::endl;

    // From vector (negative)
    HugeNumber cn(d, true);
    std::cout << "From vector (neg):     " << cn << std::endl;

    // Default constructor
    HugeNumber def;
    std::cout << "Default (zero):        " << def << std::endl;

    // ─────────────────────────────────────────
    // SECTION 2: Arithmetic Tests
    // ─────────────────────────────────────────
    std::cout << "\n=== ARITHMETIC TESTS ===" << std::endl;

    // Two positives
    HugeNumber p1("999999999999");
    HugeNumber p2("1");
    std::cout << p1 << " + " << p2 << " = " << (p1 + p2) << std::endl;

    HugeNumber p3("1000000000000");
    std::cout << p3 << " - " << p2 << " = " << (p3 - p2) << std::endl;

    // Two negatives
    HugeNumber n1("-500");
    HugeNumber n2("-300");
    std::cout << n1 << " + " << n2 << " = " << (n1 + n2) << std::endl;
    std::cout << n1 << " - " << n2 << " = " << (n1 - n2) << std::endl;
    std::cout << n1 << " * " << n2 << " = " << (n1 * n2) << std::endl;

    // Mixed signs
    HugeNumber m1("-2500");
    HugeNumber m2("300");
    std::cout << m1 << " + " << m2 << " = " << (m1 + m2) << std::endl;

    HugeNumber m3("-25");
    HugeNumber m4("-4");
    std::cout << m3 << " * " << m4 << " = " << (m3 * m4) << std::endl;

    HugeNumber m5("-25");
    HugeNumber m6("4");
    std::cout << m5 << " * " << m6 << " = " << (m5 * m6) << std::endl;

    // Edge cases
    HugeNumber zero("0");
    HugeNumber one("1");
    HugeNumber negOne("-1");
    std::cout << "0 + 1          = " << (zero + one)     << std::endl;
    std::cout << "0 - 1          = " << (zero - one)     << std::endl;
    std::cout << "-1 + 1         = " << (negOne + one)   << std::endl;
    std::cout << "1 - 1          = " << (one - one)      << std::endl;
    std::cout << "0 * 999        = " << (zero * HugeNumber("999")) << std::endl;

    // ─────────────────────────────────────────
    // SECTION 3: Comparison Tests
    // ─────────────────────────────────────────
    std::cout << "\n=== COMPARISON TESTS ===" << std::endl;

    HugeNumber x("12345");
    HugeNumber y("12344");
    std::cout << x << " > "  << y << ": " << (x > y  ? "true" : "false") << std::endl;
    std::cout << x << " < "  << y << ": " << (x < y  ? "true" : "false") << std::endl;
    std::cout << x << " >= " << x << ": " << (x >= x ? "true" : "false") << std::endl;
    std::cout << x << " <= " << y << ": " << (x <= y ? "true" : "false") << std::endl;
    std::cout << x << " == " << y << ": " << (x == y ? "true" : "false") << std::endl;
    std::cout << x << " != " << y << ": " << (x != y ? "true" : "false") << std::endl;

    HugeNumber neg999("-999");
    HugeNumber pos5("5");
    std::cout << neg999 << " < " << pos5 << ": " << (neg999 < pos5 ? "true" : "false") << std::endl;

    HugeNumber nHun1("-100");
    HugeNumber nHun2("-100");
    std::cout << nHun1 << " == " << nHun2 << ": " << (nHun1 == nHun2 ? "true" : "false") << std::endl;

    // ─────────────────────────────────────────
    // SECTION 4: Increment / Decrement Tests
    // ─────────────────────────────────────────
    std::cout << "\n=== INCREMENT / DECREMENT TESTS ===" << std::endl;

    HugeNumber counter("10");
    std::cout << "Start:          " << counter   << std::endl;
    std::cout << "++counter:      " << ++counter << std::endl;
    std::cout << "counter++:      " << counter++ << std::endl;
    std::cout << "After post++:   " << counter   << std::endl;
    std::cout << "--counter:      " << --counter << std::endl;
    std::cout << "counter--:      " << counter-- << std::endl;
    std::cout << "After post--:   " << counter   << std::endl;

    // Cross zero boundary
    HugeNumber crosser("1");
    std::cout << "Start at 1, --: " << --crosser << std::endl;
    std::cout << "At 0, --:       " << --crosser << std::endl;
    std::cout << "At -1, ++:      " << ++crosser << std::endl;

    // ─────────────────────────────────────────
    // SECTION 5: Tilde Operator Tests
    // ─────────────────────────────────────────
    std::cout << "\n=== TILDE (DIGIT REVERSAL) TESTS ===" << std::endl;

    HugeNumber t1("12345");
    std::cout << "~" << t1 << " = " << ~t1 << std::endl;

    HugeNumber t2("123400");
    std::cout << "~" << t2 << " = " << ~t2 << std::endl;

    HugeNumber t3("-9080");
    std::cout << "~" << t3 << " = " << ~t3 << std::endl;

    // ─────────────────────────────────────────
    // SECTION 6: Stream Operator Tests
    // ─────────────────────────────────────────
    std::cout << "\n=== STREAM OPERATOR TESTS ===" << std::endl;

    // operator<<
    HugeNumber streamOut("987654321");
    std::cout << "Stream out: " << streamOut << std::endl;

    // operator>>
    HugeNumber streamIn;
    std::istringstream iss("-99999999999999999");
    iss >> streamIn;
    std::cout << "Stream in:  " << streamIn << std::endl;

    // ─────────────────────────────────────────
    // SECTION 7: Exception Handling Tests
    // ─────────────────────────────────────────
    std::cout << "\n=== EXCEPTION HANDLING TESTS ===" << std::endl;

    try {
        HugeNumber bad("");
    } catch (const std::exception &e) {
        std::cout << "Empty string:     " << e.what() << std::endl;
    }

    try {
        HugeNumber bad("12a4");
    } catch (const std::exception &e) {
        std::cout << "Invalid char:     " << e.what() << std::endl;
    }

    try {
        HugeNumber bad("-");
    } catch (const std::exception &e) {
        std::cout << "Only minus sign:  " << e.what() << std::endl;
    }

    try {
        std::vector<int> badVec = {1, 2, 15, 4};
        HugeNumber bad(badVec, false);
    } catch (const std::exception &e) {
        std::cout << "Bad vector digit: " << e.what() << std::endl;
    }

    return 0;
}
