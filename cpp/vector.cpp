#include <iostream>
#include <vector>

class A {
	private:
		int num;
		std::string name;
	public:
		A(int i, std::string s) : num(i), name(s) {}
};

int	main(void)
{
	{
		std::vector<int> v;
		for (int i = 1; i <= 5; i++)
			v.push_back(i);
		for (std::vector<int>::iterator iter = v.begin(); iter != v.end(); iter++)
			std::cout << *iter << std::endl;
		std::vector<int>::iterator it = std::find(v.begin(), v.end(), 3);
		std::cout << *it << std::endl;
	}

	{
		std::vector<A> v;
		A a(1, "hwan");

//		v.push_back(1, "hi");   //error -> v.push_back(a); push_back()은 내부적으로 템플릿<T>에 대한 생성자 호출을 지원하지 않기에 에러다. 
//		그래서 v.push_back(a)를 통하면 삽입은 되긴 하지만 복사 생성자가 호출되기에 오버헤드가 커진다.
		v.emplace_back(1, "hi"); //ok!! emplace_back()은 템플릿<T>에 대한 생성자 호출을 지원하기에 편하고, 복사 생성자 호출을 하지 않아도 되기에 오버헤드가 적다.
	}
	return 0;
}
