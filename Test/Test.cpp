#include <iostream>
#include <iomanip> 

int main() {
    int n;
    std::cin >> n;
    int flag = 0;
    float summ = 0;
    for (int i = 0; i < n; ++i) {
        float x;
        std::cin >> x;

        if (x < 0) {
            flag++;
            if (flag == 2) {
                break;
            }
            continue;
        }

        if (flag == 1) {
            summ += x;
        }
    }
    if (flag < 2) {
        summ = 0;
    }
    std::cout << std::fixed << std::setprecision(3) << summ;
}