#include <iostream>

const int MAX_DIGITS = 128; // A large enough number to hold L500
const int MAX_LUCAS = 500; // Maximum Lucas number to compute
char memo[MAX_LUCAS + 1][MAX_DIGITS]; // Array to hold Lucas numbers as strings

void addLargeNumbers(const char *a, const char *b, char *result) {
    int len_a = strlen(a), len_b = strlen(b);
    int carry = 0;
    int sum_col;  // Sum of two digits in the same column

    // Start from the end of both strings
    int i = len_a - 1, j = len_b - 1, k = MAX_DIGITS - 1;
    result[k--] = '\0'; // Null-terminate the result string

    while (i >= 0 || j >= 0 || carry > 0) {
        sum_col = carry + (i >= 0 ? a[i--] - '0' : 0) + (j >= 0 ? b[j--] - '0' : 0);
        result[k--] = (sum_col % 10) + '0'; // Current digit
        carry = sum_col / 10; // Carry for the next digit
    }

    // Shift the result to the beginning of the string if necessary
    if (k != MAX_DIGITS - 2) {
        memmove(result, result + k + 1, MAX_DIGITS - k - 1);
    }
}

void lucas_number_string(int n) {
    if (memo[n][0] != '\0') {
        return; // Already computed
    }

    if (n == 0) {
        strcpy(memo[n], "2");
    } else if (n == 1) {
        strcpy(memo[n], "1");
    } else {
        lucas_number_string(n - 1);
        lucas_number_string(n - 2);
        addLargeNumbers(memo[n - 1], memo[n - 2], memo[n]);
    }
}

int main() {

    // Initialize memo array with null-terminated strings
    for (auto & i : memo) {
        i[0] = '\0';
    }

    // Compute and print Lucas numbers for 0 <= i <= 25, multiplied by 20
    for (int i = 0; i <= 25; ++i) {
        lucas_number_string(i * 20);
        std::cout << "Lucas Number L_" << i * 20 << " is " << memo[i * 20] << std::endl;
    }

    return 0;
}


