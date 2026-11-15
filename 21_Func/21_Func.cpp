#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#define NOMINMAX   
#include <windows.h> 

// 2. Функция принимает три строки и возвращает максимальное значение расстояния Дамерау-Левенштейна между парами строк.
int damerau_levenshtein(std::string a, std::string b) {
    const int n = (int)a.size();
    const int m = (int)b.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));

    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int j = 0; j <= m; ++j) dp[0][j] = j;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
            dp[i][j] = std::min({dp[i - 1][j] + 1,dp[i][j - 1] + 1,  dp[i - 1][j - 1] + cost  });
            if (i > 1 && j > 1 && a[i - 1] == b[j - 2] &&a[i - 2] == b[j - 1]) {
                dp[i][j] = std::min(dp[i][j], dp[i - 2][j - 2] + 1);
            }
        }
    }
    return dp[n][m];
}

int dam_leven(std::string s1, std::string s2, std::string s3) {
    int d12 = damerau_levenshtein(s1, s2);
    int d13 = damerau_levenshtein(s1, s3);
    int d23 = damerau_levenshtein(s2, s3);
    return std::max({d12, d13, d23});
}

// 6. Функция принимает массив n x m и циклически сдвигает средний столбец (или 2 средних, если m чётное) на один элемент назад, т.е. элементы из последней строки передвинутся на предпоследнюю, со второй строки на первую и с первой на последнюю.
void print_matrix(const std::vector<std::vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int val : row) {
            std::cout << std::setw(3) << val << " ";
        }
        std::cout << "\n";
    }
}

void shift_middle_columns(std::vector<std::vector<int>>& a) {
    int n = (int)a.size();
    if (n == 0) return;
    int m = (int)a[0].size();
    if (m == 0) return;

    std::vector<int> cols;
    if (m % 2 == 1) {
        cols.push_back(m / 2);
    } else {
        cols.push_back(m / 2 - 1);
        cols.push_back(m / 2);
    }

    for (int c : cols) {
        int saved = a[0][c];
        for (int i = 0; i < n - 1; ++i) {
            a[i][c] = a[i + 1][c];
        }
        a[n - 1][c] = saved;
    }
}
// 2. Написать функцию получения общих делителей двух чисел. Функция должна принимать два числа, а результатом работы будет массив искомых чисел и его размер.
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


int main(){
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::string s1 = "cat";
    std::string s2 = "act";
    std::string s3 = "action";
    std::cout <<"Расстояние: " << dam_leven(s1,s2,s3) << "\n";
    std::cout <<"-------------------------\n";

    std::vector<std::vector<int>> mat_odd = {{1, 2, 3},{4, 5, 6},{7, 8, 9}};
    std::cout << "Нечетная до:\n";
    print_matrix(mat_odd);

    shift_middle_columns(mat_odd);
    std::cout << "Нечетная после:\n";
    print_matrix(mat_odd);

    std::vector<std::vector<int>> mat_even = {
        {10, 20, 30, 40},
        {50, 60, 70, 80},
        {11, 22, 33, 44}
    };
    std::cout << "\nЧетная до\n";
    print_matrix(mat_even);

    shift_middle_columns(mat_even);
    std::cout << "Четная после:\n";
    print_matrix(mat_even);
    std::cout << "\n";
    std::cout <<"-------------------------\n";

    int a = 6, b = 36;
    std::cout << "НОД чисел " << a << " и " << b << ": " << dividers(a, b) << "\n";
    std::vector<int> divs = common_divisors(a, b);
    std::cout << "Общие делители (всего " << divs.size() << " шт.): ";
    for (int d : divs) {
        std::cout << d << " ";
    }
    std::cout << "\n";
}