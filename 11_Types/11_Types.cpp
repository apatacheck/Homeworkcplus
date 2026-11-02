#include <iostream>
#include <iomanip>
#include <limits>
#include <bitset>
#include <cstdint>

void print_bytes(const void* ptr, size_t size) {
    const unsigned char* b = static_cast<const unsigned char*>(ptr);
    for (size_t i = 0; i < size; ++i) {
        std::cout << (int)b[i] << " ";
    }
    std::cout << std::endl;
}

template <typename x>
void info_type(){
    std::cout << "Тип: " << typeid(x).name() << "\n";
    std::cout << "Размер: " << sizeof(x) << " байт \n";
    std::cout << "Знаковый: " << (std::numeric_limits<x>::is_signed ? "Знаковый" : "Беззнаковый") << "\n";
    std::cout << "Минимум: " << +std::numeric_limits<x>::min() << "\n";
    std::cout << "Максимум: " << +std::numeric_limits<x>::max() << "\n";
    std::cout << "------ \n";
}



int main(){
//целочисленные типы (знаковые и беззнаковые, разного размера)
info_type<short>();
info_type<unsigned short>();
info_type<int>();
info_type<unsigned int>();
//вещественные типы (разной точности)
info_type<long long>();
info_type<float>();
info_type<double>();
//символы и строки (char и unsigned char, для строк достаточно std::string)
info_type<char>();
info_type<unsigned char>();
std::cout << "Тип: std::string";
std::cout << "Размер: " << sizeof(std::string) << " байт\n";

    std::string s_short = "мал";
    std::string s_long  = "очень очень очень очень немаленькая строчка ну прям хватит даже наверное";

    std::cout << "Короткая (size=" << s_short.size() << ", cap=" << s_short.capacity() << "): "
              << "объект=" << (void*)&s_short << ", данные=" << (void*)s_short.data() << "\n";

    std::cout << "Длинная  (size=" << s_long.size()  << ", cap=" << s_long.capacity()  << "): "
              << "объект=" << (void*)&s_long  << ", данные=" << (void*)s_long.data()  << "\n";
    std::cout << "------\n";
//булев тип
info_type<bool>();


std::cout << "-----------------------\n";
    int val_pos = 1;
    int val_neg = -1;
    std::cout << "int (+1) байты: ";
    print_bytes(&val_pos, sizeof(val_pos)); 

    std::cout << "int (-1) байты: ";
    print_bytes(&val_neg, sizeof(val_neg)); 

    float f_val = 1.0f;
    std::cout << "float (1.0f) байты: ";
    print_bytes(&f_val, sizeof(f_val));     


    bool b_f = false;
    bool b_t = true;
    std::cout << "bool (false) байты: ";
    print_bytes(&b_f, sizeof(b_f));         
    std::cout << "bool (true) байты:  ";
    print_bytes(&b_t, sizeof(b_t));         

    char c_val = static_cast<char>(200);
    unsigned char uc_val = 200;
    std::cout << "char (200) как число:   " << static_cast<int>(c_val)  << " (знаковое расширение отрицательного)\n";
    std::cout << "unsigned char (200) как число: " << static_cast<int>(uc_val) << "\n";


    std::cout << "------------------ \n";

    // А. Беззнаковое переполнение (гарантированный wrap-around по модулю 2^N)
    unsigned short u_max = std::numeric_limits<unsigned short>::max(); // 65535
    std::cout << "unsigned short max: " << u_max << "\n";
    u_max = u_max + 1; // Возврат в 0
    std::cout << "unsigned short max + 1: " << u_max;

    // Б. Граница знакового int (перенос в знаковый бит)
    int s_max = std::numeric_limits<int>::max(); // 2147483647
    std::cout << "signed int max:         " << s_max << "\n";
    unsigned char* b_smax = reinterpret_cast<unsigned char*>(&s_max);
    b_smax[0] += 1; // Имитируем перенос единицы в старший знаковый бит без UB сложения
    std::cout << "int max с перенесенным знаковым битом: " << s_max << " (переход в отрицательный диапазон)\n";

    // В. Граничные состояния вещественных чисел (деление на ноль)
    float zero = 0.0f;
    float f_inf = 1.0f / zero;
    float f_nan = zero / zero;
    std::cout << "float 1.0 / 0.0: " << f_inf << " | байты: ";
    print_bytes(&f_inf, sizeof(f_inf)); // Бесконечность (+inf)

    std::cout << "float 0.0 / 0.0: " << f_nan << " | байты: ";
    print_bytes(&f_nan, sizeof(f_nan)); // Не число (NaN)
}