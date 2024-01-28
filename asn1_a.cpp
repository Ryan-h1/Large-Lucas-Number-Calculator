#include <iostream>

int I_MAX = 10;
int MULTIPLIER = 5;

long long lucas_number(long long n) {
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }

    return lucas_number(n - 1) + lucas_number(n - 2);
}

int main() {
    for (int i = 0; i <= I_MAX; ++i) {
        std::cout << "Lucas Number L_" << i * MULTIPLIER << " is " << lucas_number(i * MULTIPLIER) << std::endl;
    }

    return 0;
}


