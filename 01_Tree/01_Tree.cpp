#include <iostream>
#include <windows.h>

int main()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int n;
    std::cin >> n;
    SetConsoleTextAttribute(h, 4);
    for (int i = 0; i < n; i++)
        std::cout << " ";
    std::cout << "*" << '\n';
    SetConsoleTextAttribute(h, 10);
    for (int k = 1; k <= n; k++)
    {
        std::string line;
        for (int i = 0; i < n - k; i++)
            std::cout << " ";
        for (int j = 1; j <= k; j++)
            line += "/";
        for (int m = 1; m <= k; m++)
            line += "\\";
        std::cout << line << '\n';
    }
    SetConsoleTextAttribute(h, 14);
    for (int k = 1; k <= 2; k++)
    {
        std::string stem;
        for (int i = 0; i < n - 2; i++)
            stem += " ";
        stem += "|";
        for (int i = 1; i <= n / 3; i++)
            stem += " ";
        stem += "|";
            std::cout << stem << '\n';
    }

}