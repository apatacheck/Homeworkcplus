#include <iostream>
#include <iomanip>
#include <cmath>  
#include <windows.h>


using namespace std;

int main() {
    SetConsoleOutputCP(1251);
    double a, b, result;

    cout << "Введите a: ";
    cin >> a;
    cout << "Введите b: ";
    cin >> b;
    double denominator = 1.0 - (pow(a, 3) - b) / 3.0;

    if (denominator == 0) {
        cout << "Деление на ноль" << endl;
    }
    else {
        double numerator = pow(a, 2) + pow(b, 2);
        result = numerator / denominator;
        cout << "Ответ: " << fixed << setprecision(6) << result << endl;
    }

    return 0;
}