//Создайте неинициализированные указатели разных типов и инициализированные nullptr и "посмотрите" на них и по ним (попробуйте разыменовать).
#include <iostream>
#include <string>

int main()
{
	int* p;
	std::cout << "Адрес " << p << std::endl;
	std::cout << "Содержимое " << *p << std::endl;
	float* f;
	std::cout <<"Адрес " << f << std::endl;
	std::cout << "Содержимое " << *f << std::endl;
	char* c;
	std::cout << "Адрес " << c << std::endl;
	std::cout << "Содержимое " << *c << std::endl;

}
