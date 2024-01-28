#include <iostream>


int I_MAX = 25;
int MULTIPLIER = 20;


/**
 * A class to represent a Lucas number as a string.
 * This class is used to avoid overflow when computing large Lucas numbers.
 */
class LucasNumber {
private:
    char *number;

    static char *addStrings(const char *a, const char *b) {
        int lenA = strlen(a);
        int lenB = strlen(b);
        int maxLength = std::max(lenA, lenB) + 2; // +2 for possible carry and null-terminator

        char *result = new char[maxLength];
        std::fill(result, result + maxLength, '0'); // Initialize with '0's
        result[maxLength - 1] = '\0'; // Null-terminator

        int carry = 0;
        int k = maxLength - 2;
        for (int i = lenA - 1, j = lenB - 1; i >= 0 || j >= 0 || carry; --i, --j, --k) {
            int sum = carry;
            if (i >= 0) sum += a[i] - '0';
            if (j >= 0) sum += b[j] - '0';
            result[k] = (sum % 10) + '0';
            carry = sum / 10;
        }

        // Adjust result for leading zeros
        char *startPos = result;
        while (*startPos == '0' && *(startPos + 1)) {
            ++startPos;
        }
        char *adjustedResult = new char[strlen(startPos) + 1];
        strcpy(adjustedResult, startPos);
        delete[] result;
        return adjustedResult;
    }

public:
    LucasNumber() {
        number = new char[2];
        strcpy(number, "0");
    }

    explicit LucasNumber(const char *num) {
        number = new char[strlen(num) + 1];
        strcpy(number, num);
    }

    LucasNumber(const LucasNumber &other) { // Copy constructor
        number = new char[strlen(other.number) + 1];
        strcpy(number, other.number);
    }

    LucasNumber &operator=(const LucasNumber &other) { // Copy assignment
        if (this != &other) {
            delete[] number;
            number = new char[strlen(other.number) + 1];
            strcpy(number, other.number);
        }
        return *this;
    }

    ~LucasNumber() {
        delete[] number;
    }

    static LucasNumber add(const LucasNumber &a, const LucasNumber &b) {
        char *sum = addStrings(a.number, b.number);
        LucasNumber result(sum);
        delete[] sum;
        return result;
    }

    const char *get() const {
        return number;
    }
};


/**
 * A struct to represent a tuple of two Lucas numbers.
 */
struct LucasNumberTuple {
    LucasNumber first;
    LucasNumber second;

    LucasNumberTuple() = default;

    LucasNumberTuple(const LucasNumber &a, const LucasNumber &b) : first(a), second(b) {}
};


/**
 * Computes the nth Lucas number (defined L(n) = L(n-1) + L(n-2) for n > 1; L(0) = 2, L(1) = 1).
 *
 * It takes advantage of the following fact:
 *
 *
 * Let K_n be a column vector defined as follows:
 *
 * K_n = | L_n   |
 *       | L_n-1 |
 *
 * The recurrence relation for K_n is given by:
 *
 * K_n = | 1 1 | * K_n-1, for n >= 1;
 *       | 1 0 |
 *
 * with the initial column vector K_0 defined as:
 *
 * K_0 = |  2 |
 *       | -1 |
 *
 * This gives us a neat little trick to compute the nth Lucas number in O(n) time without using memoization.
 *
 * @param n The n in the "nth" Lucas number to compute.
 * @return A tuple of two Lucas numbers, where the first element is L(n) and the second element is L(n-1).
 */
LucasNumberTuple lucas_number(int n) {
    // Base cases
    if (n == 0) {
        return LucasNumberTuple(LucasNumber("2"), LucasNumber("-1")); // L0 = 2, L(-1) = -1 (placeholder)
    }
    if (n == 1) {
        return LucasNumberTuple(LucasNumber("1"), LucasNumber("2")); // L1 = 1, L0 = 2
    }

    // Recursive case
    LucasNumberTuple prev = lucas_number(n - 1); // Compute [An-1, Bn-1]
    return LucasNumberTuple(LucasNumber::add(prev.first, prev.second), prev.first); // An = An-1 + Bn-1, Bn = An-1
}

int main() {
    for (int i = 0; i <= I_MAX; ++i) {
        std::cout << "Lucas Number of L_" << i * MULTIPLIER << " is " << lucas_number(i * MULTIPLIER).first.get()
                  << std::endl;
    }

    return 0;
}
