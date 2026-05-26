# Arbitrary Precision Integer Library in C++

A custom big integer class implemented from scratch in C++, capable of handling integers of arbitrary length — far beyond the limits of `long long` or any built-in numeric type.

---

## Overview

Most programming languages limit integers to 64-bit values (up to ~9.2 × 10¹⁸). This library removes that constraint entirely by storing numbers as sequences of decimal digits, enabling arithmetic on numbers of any size.

---

## Features

- Arbitrary length integer support
- Full arithmetic: addition, subtraction, multiplication
- Complete comparison operators
- Increment and decrement (prefix and postfix)
- Digit reversal operator (`~`)
- Stream input and output (`<<` and `>>`)
- Input validation with exception handling
- Handles positive numbers, negative numbers, and zero correctly

---

## Internal Design

### Digit Storage
Digits are stored in a `vector<int>` in **reverse order** — the ones place is at index 0, tens place at index 1, and so on. This makes arithmetic operations more natural since we process from least significant to most significant digit.

**Example:** The number `12345` is stored as `{5, 4, 3, 2, 1}`

### Sign Storage
The sign is stored as a separate `bool negative` field. It is never encoded inside the digit vector. Zero is always stored as non-negative.

### Normalization
After every operation, `normalize()` is called to:
- Remove any leading zeros from the digit vector
- Ensure zero is never marked as negative

---

## How Arithmetic Works

### Addition
- If both numbers have the **same sign**: add digit by digit with carry, keep the sign
- If signs **differ**: delegate to subtraction on the absolute values

### Subtraction
- If signs **differ**: add the absolute values, keep the sign of the left operand
- If signs **same**: subtract the smaller absolute value from the larger, adjust sign accordingly
- Uses borrow-based digit-by-digit subtraction

### Multiplication
- Uses the standard long multiplication algorithm
- Iterates over each digit of the first number, multiplies against every digit of the second
- Accumulates results with carry into a result vector
- Sign is positive if both operands have the same sign, negative otherwise

---

## File Structure

```
arbitrary-precision-integer-cpp/
├── hugeNumber.h      # Class declaration
├── hugeNumber.cc     # Class implementation
├── main.cc           # Test cases demonstrating all features
└── README.md
```

---

## How to Compile and Run

```bash
g++ main.cc hugeNumber.cc -o huge
./huge
```

---

## Example Output

```
=== CONSTRUCTION TESTS ===
From string:           12345678901234567890
From char array:       -45009
From vector (pos):     12345
From vector (neg):     -12345
Default (zero):        0

=== ARITHMETIC TESTS ===
999999999999 + 1 = 1000000000000
1000000000000 - 1 = 999999999999
-2500 + 300 = -2200
-25 * -4 = 100
-25 * 4 = -100

=== TILDE (DIGIT REVERSAL) TESTS ===
~12345 = 54321
~123400 = 4321
~-9080 = -809
```

---

## Error Handling

Constructors throw `std::invalid_argument` for:
- Empty input
- Non-digit characters (other than a leading `-`)
- Input consisting of only `-`
- Vector elements outside the range 0–9

Exceptions were chosen over `abort()` to allow callers to recover gracefully.

---

## Supported Constructors

```cpp
HugeNumber()                                      // Default: value 0
HugeNumber("12345678901234567890")                // From string
HugeNumber(charArray, size)                       // From char array
HugeNumber({1,2,3,4,5}, false)                   // From vector, false = positive
HugeNumber({1,2,3,4,5}, true)                    // From vector, true = negative
```

---

## Skills Demonstrated

- Object-oriented design in C++
- Operator overloading
- STL vector manipulation
- Algorithm implementation without standard library shortcuts
- Exception handling
- Memory-efficient digit-by-digit arithmetic
