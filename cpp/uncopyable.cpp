class Uncopyable {
	protected:
		Uncopyable() {}                                // 생성자와 소멸자는 허용한다.
		~Uncopyable() {}

	private:
		Uncopyable(const Uncopyable&);                 // 하지만 복사는 방지한다.
		Uncopyable& operator=(const Uncopyable&);      // protected에 있으면 에러 발생 안함!!
};

class HomeForSale: private Uncopyable {          // 복사 생성자도, 대입 연산자도 선언 불가
	public:
		HomeForSale() {}
		HomeForSale(const Uncopyable&);
};

int main()
{
	HomeForSale a;
	HomeForSale b(a);
}
