#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "\n1. Одномерный статический массив\n";


    int static_uninit[5];
    std::cout << "Без инициализации: ";
    for (int i = 0; i < 5; ++i) 
      std::cout << static_uninit[i] << " ";
    std::cout << "\n";


    int static_init[5] = { 1, 2, 3, 4, 5 };
    std::cout << "С инициализацией: ";
    for (int i = 0; i < 5; ++i)
      std::cout << static_init[i] << " ";
    std::cout << "\n";


    std::ifstream file_static_1d("array_1d.txt");
    int size_static_1d = 0;
    const int MAX_SIZE_1D = 10;
    int static_arr[MAX_SIZE_1D];
    file_static_1d >> size_static_1d;
    for (int i = 0; i < size_static_1d; ++i) file_static_1d >> static_arr[i];
    file_static_1d.close();


    std::cout << "Элементы и адреса:\n";
    for (int i = 0; i < size_static_1d; ++i) {
        std::cout << "static_arr[" << i << "] = " << static_arr[i] << " - адрес: " << &static_arr[i] << "\n";
    }


    std::cout << "Элемент по индексу [2]: " << static_arr[2] << "\n";

    int min_abs_idx_1d = 0;
    for (int i = 1; i < size_static_1d; ++i) {
        if (std::abs(static_arr[i]) < std::abs(static_arr[min_abs_idx_1d])) min_abs_idx_1d = i;
    }
    std::cout << "Индекс мин. по модулю: " << min_abs_idx_1d << " (значение " << static_arr[min_abs_idx_1d] << ")\n";

    std::swap(static_arr[0], static_arr[size_static_1d - 1]);
    std::cout << "После swap:" << static_arr[0] << " ... " << static_arr[size_static_1d - 1] << "\n";

//Массив на стеке удалится и сам

    std::cout << "\n2. Одномерный динамический массив\n";

     
    int* dyn_uninit = new int[5];
    std::cout << "Без инициализации: ";
    for (int i = 0; i < 5; ++i) 
      std::cout << dyn_uninit[i] << " ";
    std::cout << "\n";
    delete[] dyn_uninit;


    int* dyn_init = new int[5]{ 1, 2, 3, 4, 5 };
    std::cout << "С инициализацией: ";
    for (int i = 0; i < 5; ++i)
      std::cout << dyn_init[i] << " ";
    std::cout << "\n";
    delete[] dyn_init;


    std::ifstream file_dyn_1d("array_1d.txt");
    int size_dyn_1d = 0;
    int* dyn_arr = nullptr;

    file_dyn_1d >> size_dyn_1d;
    dyn_arr = new int[size_dyn_1d];
    for (int i = 0; i < size_dyn_1d; ++i) file_dyn_1d >> dyn_arr[i];
    file_dyn_1d.close();


    std::cout << "Элементы и адреса в куче:\n";
    for (int i = 0; i < size_dyn_1d; ++i) {
        std::cout << "dyn_arr[" << i << "] = " << dyn_arr[i] << " | адрес: " << (dyn_arr + i) << "\n";
    }

   
    std::cout << "Элемент по индексу [1]: " << dyn_arr[1] << "\n";

    int min_abs_idx_dyn = 0;
    for (int i = 1; i < size_dyn_1d; ++i) {
        if (std::abs(dyn_arr[i]) < std::abs(dyn_arr[min_abs_idx_dyn])) min_abs_idx_dyn = i;
    }
    std::cout << "Индекс мин. по модулю: " << min_abs_idx_dyn << " (значение " << dyn_arr[min_abs_idx_dyn] << ")\n";

    std::swap(dyn_arr[0], dyn_arr[size_dyn_1d - 1]);
    std::cout << "После swap: " << dyn_arr[0] << ".." << dyn_arr[size_dyn_1d - 1] << "\n";

 
    delete[] dyn_arr;
    dyn_arr = nullptr;
// а вот тут уже можно и очистить 


    std::cout << "\n3. Двумерный статический массив\n";

  
    int static_2d_uninit[2][2];
    std::cout << "Без инициализации [2][2]: " << static_2d_uninit[0][0] << " " << static_2d_uninit[0][1] << "\n";


    int s2d[2][2] = { {1, 2}, {3, 4} };
    std::cout << "С инициализацией [2][2]: " << s2d[0][0] << " " << s2d[0][1] << "\n";


    std::ifstream file_static_2d("matrix_2d.txt");
    int rows_static = 0, cols_static = 0;
    int static_matrix[5][5];
    file_static_2d >> rows_static >> cols_static;
    for (int i = 0; i < rows_static; ++i) {
        for (int j = 0; j < cols_static; ++j) file_static_2d >> static_matrix[i][j];
    }
    file_static_2d.close();



    std::cout << "Элементы и адреса\n"; //память идет строка за строкой 
    for (int i = 0; i < rows_static; ++i) {
        for (int j = 0; j < cols_static; ++j) {
            std::cout << static_matrix[i][j] << " (" << &static_matrix[i][j] << ") ";
        }
        std::cout << "\n";
    }

   
    std::cout << "Элемент [1][2]: " << static_matrix[1][2] << "\n";

    int min_row_static = 0, min_col_static = 0;
    for (int i = 0; i < rows_static; ++i) {
        for (int j = 0; j < cols_static; ++j) {
            if (std::abs(static_matrix[i][j]) < std::abs(static_matrix[min_row_static][min_col_static])) {
                min_row_static = i;
                min_col_static = j;
            }
        }
    }
    std::cout << "Мин. по модулю: [" << min_row_static << "][" << min_col_static << "] = " << static_matrix[min_row_static][min_col_static] << "\n";

    // Обмен первой и последней строк
    for (int j = 0; j < cols_static; ++j) 
      std::swap(static_matrix[0][j], static_matrix[rows_static - 1][j]);
    std::cout << "Первая и последняя строки обменены\n";

    // Обмен первого и последнего столбцов
    for (int i = 0; i < rows_static; ++i) 
      std::swap(static_matrix[i][0], static_matrix[i][cols_static - 1]);
    std::cout << "Первый и последний столбцы обменены\n";


//это стек, сам удалится



    std::cout << "\n4. Двумерный массив как единый блок памяти\n";


    int* flat_uninit = new int[2 * 2];
    std::cout << "Без инициализации new int[4]: " << flat_uninit[0] << " " << flat_uninit[1] << "\n";
    delete[] flat_uninit;

    int* flat_init = new int[2 * 2]{ 10, 20, 30, 40 }; 
    std::cout << "С инициализацией: " << flat_init[0] << " " << flat_init[1] << "\n";
    delete[] flat_init;


    std::ifstream file_flat_2d("matrix_2d.txt");
    int rows_flat = 0, cols_flat = 0;
    int* flat_matrix = nullptr;

    file_flat_2d >> rows_flat >> cols_flat;
    flat_matrix = new int[rows_flat * cols_flat]; 

    for (int i = 0; i < rows_flat; ++i) {
        for (int j = 0; j < cols_flat; ++j) {
            file_flat_2d >> flat_matrix[i * cols_flat + j];
        }
    }
    file_flat_2d.close();


    std::cout << "Элементы и адреса:\n"; //единый кусок в куче
    for (int i = 0; i < rows_flat; ++i) {
        for (int j = 0; j < cols_flat; ++j) {
            int linear_idx = i * cols_flat + j;
            std::cout << flat_matrix[linear_idx] << " (" << &flat_matrix[linear_idx] << ") ";
        }
        std::cout << "\n";
    }

  
    std::cout << "Элемент [1][2]: " << flat_matrix[1 * cols_flat + 2] << "\n";

    int min_linear_idx = 0;
    for (int i = 1; i < rows_flat * cols_flat; ++i) {
        if (std::abs(flat_matrix[i]) < std::abs(flat_matrix[min_linear_idx])) min_linear_idx = i;
    }
    std::cout << "Мин. по модулю: [" << (min_linear_idx / cols_flat) << "][" << (min_linear_idx % cols_flat) 
              << "] = " << flat_matrix[min_linear_idx] << "\n";

    // Обмен строк
    for (int j = 0; j < cols_flat; ++j) std::swap(flat_matrix[0 * cols_flat + j], flat_matrix[(rows_flat - 1) * cols_flat + j]);
    std::cout << "Первая и последняя строки обменены\n";

    // Обмен столбцов
    for (int i = 0; i < rows_flat; ++i) std::swap(flat_matrix[i * cols_flat + 0], flat_matrix[i * cols_flat + (cols_flat - 1)]);
    std::cout << "Первый и последний столбцы обменены\n";

    delete[] flat_matrix;
    flat_matrix = nullptr;

    std::cout << "\n5. Двумерный динамический массив\n";


    int** ptrs_uninit = new int*[2];
    std::cout << "Неинициализированный массив указателей: ptrs[0] = " << (void*)ptrs_uninit[0] << "\n";
    delete[] ptrs_uninit;

    int** ptrs_init = new int*[2]{
        new int[2]{ 1, 2 },
        new int[2]{ 3, 4 }
    };
    std::cout << "С инициализацией: ptrs_init[0][0] = " << ptrs_init[0][0] << ", ptrs_init[1][1] = " << ptrs_init[1][1] << "\n";
    delete[] ptrs_init[0];
    delete[] ptrs_init[1];
    delete[] ptrs_init;


    std::ifstream file_dyn_2d("matrix_2d.txt");
    int rows_dyn = 0, cols_dyn = 0;
    int** dyn_matrix = nullptr;

    file_dyn_2d >> rows_dyn >> cols_dyn;
    dyn_matrix = new int*[rows_dyn];  //сначала массив указателей, потом каждая строка
    for (int i = 0; i < rows_dyn; ++i) {
        dyn_matrix[i] = new int[cols_dyn];
        for (int j = 0; j < cols_dyn; ++j) file_dyn_2d >> dyn_matrix[i][j];
    }
    file_dyn_2d.close();


    std::cout << "Адрес массива указателей dyn_matrix: " << dyn_matrix << "\n";
    for (int i = 0; i < rows_dyn; ++i) {
        std::cout << "Строка " << i << " (начинается по адресу " << (void*)dyn_matrix[i] << "):\n  ";
        for (int j = 0; j < cols_dyn; ++j) {
            std::cout << dyn_matrix[i][j] << " (" << &dyn_matrix[i][j] << ") ";
        }
        std::cout << "\n";
    }
//строки в разных несвязных местах кучи

  
    std::cout << "Элемент [1][2]: " << dyn_matrix[1][2] << "\n";

    int min_row_dyn = 0, min_col_dyn = 0;
    for (int i = 0; i < rows_dyn; ++i) {
        for (int j = 0; j < cols_dyn; ++j) {
            if (std::abs(dyn_matrix[i][j]) < std::abs(dyn_matrix[min_row_dyn][min_col_dyn])) {
                min_row_dyn = i;
                min_col_dyn = j;
            }
        }
    }
    std::cout << "Мин. по модулю: [" << min_row_dyn << "][" << min_col_dyn << "] = " << dyn_matrix[min_row_dyn][min_col_dyn] << "\n";

    // Обмен строк: меняем сами указатели 
    std::swap(dyn_matrix[0], dyn_matrix[rows_dyn - 1]);
    std::cout << "Первая и последняя строки обменены \n";

    // Обмен столбцов: только поэлементно
    for (int i = 0; i < rows_dyn; ++i) std::swap(dyn_matrix[i][0], dyn_matrix[i][cols_dyn - 1]);
    std::cout << "Первый и последний столбцы обменены\n";


    for (int i = 0; i < rows_dyn; ++i) {
        delete[] dyn_matrix[i]; // Сначала удаляем каждую строку
    }
    delete[] dyn_matrix;        // Затем удаляем массив указателей
    dyn_matrix = nullptr;

    return 0;
}