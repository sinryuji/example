#include <algorithm>
#include <iostream>
#include <vector>

int	main(void)
{
	{
		std::vector<int> v;
		v.push_back(1);
		v.push_back(3);
		v.push_back(5);
		v.push_back(7);
		v.push_back(9);
		std::vector<int>::iterator it = std::adjacent_find(v.begin(), v.end());
		if (it != v.end())
			std::cout << "dup!" << std::endl;
		else
			std::cout << "not dup!" << std::endl;
	}

	{
		std::vector<int> v;
		v.push_back(1);
		v.push_back(3);
		v.push_back(3);
		v.push_back(7);
		v.push_back(9);
		std::vector<int>::iterator it = std::adjacent_find(v.begin(), v.end());
		if (it != v.end())
			std::cout << "dup!" << std::endl;
		else
			std::cout << "not dup!" << std::endl;
	}

	return 0;
}
