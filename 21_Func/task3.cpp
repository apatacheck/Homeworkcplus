#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>

int dividers(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b) {
        int t = a % b; a = b; b = t;
    }
    return a;
}

std::vector<int> common_divisors(int a, int b) {
    int g = dividers(a, b);
    std::vector<int> res;
    for (int d = 1; d <= g; ++d)
        if (g % d == 0) res.push_back(d);
    return res;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int a, b;
    std::cout << "Введите два числа: ";
    std::cin >> a >> b;

    std::cout << "НОД чисел " << a << " и " << b << ": " << dividers(a, b) << "\n";

    std::vector<int> divs = common_divisors(a, b);
    std::cout << "Общие делители:" << divs.size();
    for (int d : divs) 
        std::cout << d << " ";
    std::cout << "\n";
}