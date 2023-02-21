#include <iostream>

class Airplane {
  public:
    virtual void fly() = 0;
};

void Airplane::fly() {          // 사실 순수 가상 함수도 구현 할 수 있다!!
  std::cout << "Airplane fly" << std::endl;
}

class A : public Airplane {
  public:
    void fly() {
      Airplane::fly();         // 구현한 순수 가상 함수 호출!!
      std::cout << "A fly" << std::endl;
    }
};

int main() {
  A a;
  a.fly();
}
