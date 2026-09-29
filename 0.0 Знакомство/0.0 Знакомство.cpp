#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>

int main()
{

    SetConsoleOutputCP(1251);
    srand(time(0));
    int ballColors[] = { 12, 9, 13, 14, 11 };
    int numColors = 5;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int n;
    std::cin >> n;


    SetConsoleTextAttribute(h, 14);
    for (int i = 0; i < 2 * n + 10; i++) std::cout << "_";
    std::cout << "\n";

    SetConsoleTextAttribute(h, 11);
    std::cout << "  С НОВЫМ ГОДОМ!  \n";

    SetConsoleTextAttribute(h, 14);
    for (int i = 0; i < 2 * n + 10; i++) std::cout << "-";
    std::cout << "\n\n";

    SetConsoleTextAttribute(h, 4);
    for (int i = 0; i < n; i++)
        std::cout << " ";
    std::cout << "*" << '\n';

 
    SetConsoleTextAttribute(h, 10);
    for (int k = 1; k <= n; k++)
    {
        std::string line;
        for (int i = 0; i < n - k; i++)
            line += " ";
        for (int j = 1; j <= k; j++)
            line += "/";
        for (int m = 1; m <= k; m++)
            line += "\\";


        for (size_t i = 0; i < line.length(); i++)
        {
            if (line[i] == '/' || line[i] == '\\')
            {
                
                if (i % 3 == 0)
                {
                    int randomColor = ballColors[rand() % numColors];
                    SetConsoleTextAttribute(h, randomColor);  
                    std::cout << "o";
                    SetConsoleTextAttribute(h, 10);  
                }
                else
                {
                    std::cout << line[i];             
                }
            }
            else
            {
                std::cout << line[i];             
            }
        }
        std::cout << '\n';
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

    std::cout << "\n";
    SetConsoleTextAttribute(h, 11);
    std::cout << "Удачи в новом году!!\n\n";


    SetConsoleTextAttribute(h, 14);
    for (int i = 0; i < 2 * n + 10; i++) std::cout << "_";
    std::cout << "\n";

    SetConsoleTextAttribute(h, 7);

    return 0;
}