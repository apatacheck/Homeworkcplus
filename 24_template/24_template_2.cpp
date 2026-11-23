#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <memory>
#include <type_traits>
#include <string>
#include <windows.h>

template <typename T>
using EnableIfArithmetic = std::enable_if_t<std::is_arithmetic_v<T>, int>;

template <typename T>
using SmartTable = std::unique_ptr<std::unique_ptr<T[]>[]>;

template <typename T, EnableIfArithmetic<T> = 0>
SmartTable<T> create_table(size_t rows, size_t cols) {
    auto table = std::make_unique<std::unique_ptr<T[]>[]>(rows);
    for (size_t i = 0; i < rows; ++i) {
        table[i] = std::make_unique<T[]>(cols);
    }
    return table;
}

template <typename T, EnableIfArithmetic<T> = 0>
SmartTable<T> create_square_table(size_t size) {
    return create_table<T>(size, size);
}

template <typename T, EnableIfArithmetic<T> = 0>
void fill_zeros(const SmartTable<T>& table, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            table[i][j] = T{0};
        }
    }
}

template <typename T, EnableIfArithmetic<T> = 0>
void fill_random(const SmartTable<T>& table, size_t rows, size_t cols, T min_val = T{-10}, T max_val = T{10}) {
    static std::mt19937 gen(std::random_device{}());

    if constexpr (std::is_integral_v<T>) {
        using DistType = std::conditional_t<sizeof(T) < sizeof(short), int, T>;
        std::uniform_int_distribution<DistType> dist(static_cast<DistType>(min_val), static_cast<DistType>(max_val));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                table[i][j] = static_cast<T>(dist(gen));
            }
        }
    } else {
        std::uniform_real_distribution<T> dist(min_val, max_val);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                table[i][j] = dist(gen);
            }
        }
    }
}

template <typename T, EnableIfArithmetic<T> = 0>
void fill_keyboard(const SmartTable<T>& table, size_t rows, size_t cols) {
    std::cout << "Введите элементы таблицы (" << rows << "x" << cols << "):\n";
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cin >> table[i][j];
        }
    }
}

template <typename T, EnableIfArithmetic<T> = 0>
SmartTable<T> read_from_file(const std::string& filename, size_t& rows, size_t& cols) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        rows = 0;
        cols = 0;
        return nullptr;
    }

    file >> rows >> cols;
    auto table = create_table<T>(rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            file >> table[i][j];
        }
    }
    return table;
}

template <typename T, EnableIfArithmetic<T> = 0>
void print_console(const SmartTable<T>& table, size_t rows, size_t cols) {
    if (!table) {
        std::cout << "[Пустая таблица]\n";
        return;
    }

    for (size_t i = 0; i < rows; ++i) {
        std::cout << "| ";
        for (size_t j = 0; j < cols; ++j) {
            if constexpr (std::is_floating_point_v<T>) {
                std::cout << std::setw(8) << std::fixed << std::setprecision(2) << table[i][j] << " ";
            } else {
                std::cout << std::setw(6) << +table[i][j] << " ";
            }
        }
        std::cout << "|\n";
    }
}

template <typename T, EnableIfArithmetic<T> = 0>
bool write_to_file(const std::string& filename, const SmartTable<T>& table, size_t rows, size_t cols) {
    std::ofstream file(filename);
    if (!file.is_open() || !table) return false;

    file << rows << " " << cols << "\n";
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            file << table[i][j] << (j + 1 < cols ? " " : "");
        }
        file << "\n";
    }
    return true;
}

template <typename T, EnableIfArithmetic<T> = 0>
double avg_negative(const SmartTable<T>& table, size_t rows, size_t cols) {
    double sum = 0.0;
    size_t count = 0;

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (table[i][j] < T{0}) {
                sum += static_cast<double>(table[i][j]);
                ++count;
            }
        }
    }
    return count > 0 ? (sum / count) : 0.0;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "1. Прямоугольная таблица (int, 2x3) + fill_zeros\n";
    size_t r1 = 2, c1 = 3;
    auto t_zeros = create_table<int>(r1, c1);
    fill_zeros(t_zeros, r1, c1);
    print_console(t_zeros, r1, c1);
    std::cout << "Среднее отрицательных: " << avg_negative(t_zeros, r1, c1) << "\n\n";

    std::cout << " 2. Заполнение случайными числами (fill_random)\n";
    fill_random(t_zeros, r1, c1, -10, 10);
    print_console(t_zeros, r1, c1);
    std::cout << "Среднее отрицательных: " << avg_negative(t_zeros, r1, c1) << "\n\n";

    std::cout << "3. Запись в файл (write_to_file) и чтение (read_from_file) \n";
    if (write_to_file("test_table.txt", t_zeros, r1, c1)) {
        std::cout << "Таблица успешно записана в test_table.txt\n";
    }
    t_zeros.reset();
    std::cout << "После reset() указатель равен: " << t_zeros.get() << "\n";
    print_console(t_zeros, r1, c1);

    size_t f_rows = 0, f_cols = 0;
    auto t_loaded = read_from_file<int>("my_matrix.txt", f_rows, f_cols);
    std::cout << "Прочитанная из файла таблица (" << f_rows << "x" << f_cols << "):\n";
    print_console(t_loaded, f_rows, f_cols);
    std::cout << "\n";

    std::cout << "4. Квадратная таблица (double, 2x2) + fill_keyboard \n";
    size_t sq_size = 2;
    auto t_sq = create_square_table<double>(sq_size);
    fill_keyboard(t_sq, sq_size, sq_size);
    std::cout << "Введённая квадратная таблица:\n";
    print_console(t_sq, sq_size, sq_size);
    std::cout << "Среднее отрицательных: " << avg_negative(t_sq, sq_size, sq_size) << "\n";

    return 0;
}