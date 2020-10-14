#include <iostream>
#include <stdexcept>

class Test {
public:
    Test(char id) : id_(id) {}
    ~Test() {
        std::cout << "Destructor execution: "
            << id_ << std::endl;
    }

private:
    char id_;
};

int funcB() { //B�Լ������� catch�� ����
    Test r('B');
    throw std::runtime_error("Exception from funcB!\n");
    std::cout << "Executed in B" << std::endl;
}
int funcA() { //A�Լ������� catch ����
    Test r('A');
    funcB();
    std::cout << "Executed in A" << std::endl;
    return 0;
}
int main() { //main���� catch�Ͽ� ���������� ����ó���� �Ͼ -> stack unwinding
    try {
        funcA();
    }
    catch (std::exception & e) {
        std::cout << "Exception : " << e.what();
    }
}