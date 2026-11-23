#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>
#define NOMINMAX
#include <windows.h>

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

std::vector<std::vector<int>> read_matrix(int n, int m) {
    std::vector<std::vector<int>> mat(n, std::vector<int>(m));
    std::cout << "Введите матрицу:\n";
    
    for (int i = 0; i < n; ++i) {
        std::cout << "Строка " << i + 1 << ": ";
        std::string line;
        std::getline(std::cin, line);
        
        std::istringstream iss(line);
        for (int j = 0; j < m; ++j) {
            if (!(iss >> mat[i][j])) {
                mat[i][j] = 0;
            }
        }
    }
    return mat;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n, m;
    std::cout << "Введите количество строк и столбцов: ";
    std::cin >> n >> m;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
1

    std::vector<std::vector<int>> mat = read_matrix(n, m);

    std::cout << "\nДо сдвига:\n";
    print_matrix(mat);

    shift_middle_columns(mat);

    std::cout << "\nПосле сдвига:\n";
    print_matrix(mat);
    return 0;
}