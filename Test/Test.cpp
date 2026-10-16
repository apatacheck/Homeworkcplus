#include <iostream>

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    for (int d = 0; ; ++d) {
        int left = n - d;
        if (left >= 2) {
            bool is_prime = true;
            for (int i = 2; i * i <= left; ++i) {
                if (left % i == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) {
                std::cout << left;
                break;
            }
        }

        if (d > 0) {
            int right = n + d;
            bool is_prime = true;
            for (int i = 2; i * i <= right; ++i) {
                if (right % i == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) {
                std::cout << right;
                break;
            }
        }
    }
}