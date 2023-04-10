#include <iostream>

class A {
  public:
    int getNum(void) {
      return this->num;
    }
    void setNum(int num) {
      this->num = num;
    }

  private:
    int num;
};

class B : public A {

  public:
    int getBNum(void) {
      return this->b_num;
    }
    void setBNum(int num) {
      this->b_num = num;
    }

  private:
    int b_num;
};


int main() {
  B b;
  b.setNum(10);
  std::cout << b.getNum() << std::endl;
}
