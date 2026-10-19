#include <iostream>
#include <windows.h>

void print_bytes(const void* ptr, size_t size) {
    const unsigned char* b = static_cast<const unsigned char*>(ptr);
    for (size_t i = 0; i < size; ++i) {
        std::cout << (int)b[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // 1. Создайте неинициализированные указатели разных типов и инициализированные nullptr и "посмотрите" на них и по ним (попробуйте разыменовать).
    std::cout << "\n№1\n" << std::endl; 
    int* p_uninit;
    double* d_uninit;
    float* f_uninit;

    int* p_null = nullptr;
    double* d_null = nullptr;
    float* f_null = nullptr;

    std::cout << "int*    : " << p_uninit << std::endl;
    std::cout << "double* : " << d_uninit << std::endl;
    std::cout << "float*  : " << f_uninit << std::endl;

    std::cout << "int*    : " << p_null << std::endl;
    std::cout << "double* : " << d_null << std::endl;
    std::cout << "float*  : " << f_null << std::endl;

    // std::cout << *p_null << std::endl;

    // std::cout << *p_uninit << std::endl;
    // std::cout << *d_uninit << std::endl;
    // std::cout << *f_uninit << std::endl;

    // 2. Выделите память с подходящими значениями, посмотрите ещё раз.
    std::cout << "\n№2\n" << std::endl; 
    int* p_int = new int(8);    
    double* p_double = new double(3.14);
    float* p_float = new float(128.5f);

    std::cout << "int*:    address = " << p_int    << " value = " << *p_int    << std::endl;
    std::cout << "double*: address = " << p_double << " value = " << *p_double << std::endl;
    std::cout << "float*:  address = " << p_float  << " value = " << *p_float  << std::endl;

    // 3. Используя арифметику указателей, попробуйте "заглянуть" внутрь значений и за их пределы.
    std::cout << "\n№3\n" << std::endl; 
    std::cout << "Bytes of int (8): ";
    print_bytes(p_int, sizeof(int));

    std::cout << "Bytes of float (128.5f): ";
    print_bytes(p_float, sizeof(float));

    std::cout << "Bytes of double (3.14): ";
    print_bytes(p_double, sizeof(double));

    std::cout << "p_int + 0 " << *(p_int + 0) << std::endl;
    std::cout << "p_int + 1 " << *(p_int + 1) << std::endl;
    std::cout << "p_int + 2 " << *(p_int + 2) << std::endl;

    // 4. Измените значение, используя доступ к отдельным байтам.
    std::cout << "\n№4\n" << std::endl; 
    std::cout << "Before: " << *p_int << std::endl;

    unsigned char* b_int = reinterpret_cast<unsigned char*>(p_int);

    *(b_int + 0) = 100; 
    std::cout << "After: " << *p_int << std::endl;
    b_int[1] = 1;
    std::cout << "After: " << *p_int << std::endl;

    std::cout << "Bytes of modified int: ";
    print_bytes(p_int, sizeof(int));

    std::cout << "\n№5\n" << std::endl; 
    // "Потеряйте" прямой указатель на область памяти и посмотрите на содержимое с помощью арифметики указателей.
    std::cout << "true address: " << p_int << std::endl;
    p_int = p_int + 3; 

    std::cout << "address after: " << p_int << std::endl;
    std::cout << "value after (garbage): " << *p_int << std::endl;
    std::cout << "true value via (p_int - 3): " << *(p_int - 3) << std::endl;

    unsigned char* b_lost = reinterpret_cast<unsigned char*>(p_int);

    std::cout << "Byte 0 of original: " << (int)*(b_lost - 12) << std::endl;
    
    p_int = p_int - 3;

    std::cout << "\n№6\n" << std::endl; 
    // 6. Освободите память и посмотрите на её содержимое. Попробуйте добиться, чтобы память по этому адресу была перезаписана.
    std::cout << "Address before deletion: " << p_int << std::endl;
    std::cout << "Value before deletion: " << *p_int << std::endl;

    delete p_int; 

    std::cout << "Address after deletion: " << p_int << std::endl;
    std::cout << "Value after deletion: " << *p_int << std::endl;
    std::cout << "Bytes after deletion: ";
    print_bytes(p_int, sizeof(int));

    int* temp[50];
    for (int i = 0; i < 50; ++i) {
        temp[i] = new int(777);
    }

    std::cout << "\nAfter:" << std::endl;
    std::cout << "Value: " << *p_int << std::endl;
    std::cout << "Bytes: ";
    print_bytes(p_int, sizeof(int));

    for (int i = 0; i < 50; ++i) {
        delete temp[i];
    }

    delete p_double;
    delete p_float;


     std::cout << "\n№7\n" << std::endl; 
    int* p_sign = new int(1); 
    std::cout << "Before: " << *p_sign << std::endl;
    std::cout << "Bytes before: ";
    print_bytes(p_sign, sizeof(int));
    unsigned char* b_sign = reinterpret_cast<unsigned char*>(p_sign);
    b_sign[3] = 128;
    std::cout << "After: " << *p_sign << std::endl;
    std::cout << "Bytes after: ";
    print_bytes(p_sign, sizeof(int));

    delete p_sign;

    return 0;
}