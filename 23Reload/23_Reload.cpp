#include <iostream>
#include <cmath>
#include <windows.h>

float func(float x){
    float y;
    if(std::abs(x)<3){
        y = std::sin(x);
    }
    if(std::abs(x)>=3 && std::abs(x)<9){
        y = std::sqrt(x*x+1)/std::sqrt(x*x+5);
    }
    if(std::abs(x)>=9){
        y = std::sqrt(x*x+1)-std::sqrt(x*x+5);
    }
    
    return y;
}

void func(float x, float &y){
    y = func(x);
}

int main(){
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    float x;
    std::cout << "Введите x: ";
    std::cin >> x;
    std::cout << func(x) << '\n';
    std::cout << "Работа функции с передачей значения переменной y:" << '\n';
    float y = 0;
    std::cout << "y до: " << y << '\n';
    func(x,y);
    std::cout <<"y после: " << y << '\n';
}