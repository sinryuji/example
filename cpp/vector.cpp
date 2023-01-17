#include <iostream>
#include <vector>

int	main(void)
{
	std::vector<int> v;
	for (int i = 1; i <= 5; i++)
		v.push_back(i);
	for (std::vector<int>::iterator iter = v.begin(); iter != v.end(); iter++)
		std::cout << *iter << std::endl;
	std::vector<int>::iterator it = std::find(v.begin(), v.end(), 3);
	std::cout << *it << std::endl;
}
