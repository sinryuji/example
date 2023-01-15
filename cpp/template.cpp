#include <iostream>

/*
 * function template
 */
template <typename T>
T sum(T a, T b)
{
	return a + b;
}

/*
 * class template
 */
template <class T>
class Person
{
	private:
		std::string name;
		T height;
		
	public:
		Person(std::string name, T height) : name(name), height(height) {}
		void	print(void)
		{
			std::cout << "name : " << this->name << std::endl;
			std::cout << "hegiht : " << this->height << std::endl;
		}
		void	setName(std::string name);
		void	setHeight(T hegiht);
};

template <typename T>
void	Person<T>::setName(std::string name)
{
	this->name = name;
}

template <typename T>
void	Person<T>::setHeight(T hegiht)
{
	this->height = hegiht;
}

/*
 * class template specialization
 */
template <typename T>
class X {};

template <>
class X<double> {};

template <typename T1, typename T2>
class Y {};

template <typename T1>
class Y<T1, double> {};

template <typename T1, typename T2>
class Z {};

template <>
class Z<double, double> {};

int	main(void)
{
	int a = 1, b = 2;	
	double c = 1.3, d = 2.6;
	std::string str1 = "hello", str2 = " world";

	std::cout << sum(a, b) << std::endl;
	std::cout << sum(c, d) << std::endl;
	std::cout << sum(str1, str2) << std::endl;
	Person<int> p1("kim", 180);
	Person<std::string> p2("kim", "180cm");
	p1.print();
	p2.print();
	p1.setName("park");
	p1.setHeight(190);
	p2.setName("park");
	p2.setHeight("190cm");
	p1.print();
	p2.print();
}
