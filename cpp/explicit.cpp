#include <iostream>

class Point{
	private:
		int y;
	public:
		explicit Point(int yy = 0)
		{
			y = yy;
		}
		void Print() const{
			std::cout << y << std::endl;
		}
};

int main()
{
	Point pt;
//	pt = 10; -> compile time error!
	pt = Point(10);
	pt.Print();
}
