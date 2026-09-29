#include <iostream>
#include <windows.h>
#include <iostream>
using namespace std;

int main() {
    SetConsoleOutputCP(1251);

    int n;
    cout << "Введите двузначное число:";
    cin >> n;
    int digit1 = n / 10;  
    int digit2 = n % 10;  
    string result = (digit1 == digit2) ? "Цифры одинаковы" : "Цифры разные";
    cout << result << endl;
}