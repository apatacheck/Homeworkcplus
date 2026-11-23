#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define NOMINMAX
#include <windows.h>

int damerau_levenshtein(const std::string& a, const std::string& b) {
    const int n = (int)a.size();
    const int m = (int)b.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));

    for (int i = 0; i <= n; ++i) 
        dp[i][0] = i;
    for (int j = 0; j <= m; ++j) 
        dp[0][j] = j;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
            dp[i][j] = std::min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
            if (i > 1 && j > 1 && a[i - 1] == b[j - 2] && a[i - 2] == b[j - 1]) {
                dp[i][j] = std::min(dp[i][j], dp[i - 2][j - 2] + 1);
            }
        }
    }
    return dp[n][m];
}

int dam_leven(const std::string& s1, const std::string& s2, const std::string& s3) {
    int d12 = damerau_levenshtein(s1, s2);
    int d13 = damerau_levenshtein(s1, s3);
    int d23 = damerau_levenshtein(s2, s3);
    return std::max({d12, d13, d23});
}

std::string read_line(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::string s1 = read_line("Введите первую строку: ");
    std::string s2 = read_line("Введите вторую строку: ");
    std::string s3 = read_line("Введите третью строку: ");
    std::cout << "Максимальное расстояние между парами: " << dam_leven(s1, s2, s3) << "\n";
    return 0;
}