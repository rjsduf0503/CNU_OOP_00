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

int funcB() { //B함수에서는 catch를 못함
    Test r('B');
    throw std::runtime_error("Exception from funcB!\n");
    std::cout << "Executed in B" << std::endl;
}
int funcA() { //A함수에서도 catch 못함
    Test r('A');
    funcB();
    std::cout << "Executed in A" << std::endl;
    return 0;
}
int main() { //main에서 catch하여 정상적으로 예외처리가 일어남 -> stack unwinding
    try {
        funcA();
    }
    catch (std::exception & e) {
        std::cout << "Exception : " << e.what();
    }
}