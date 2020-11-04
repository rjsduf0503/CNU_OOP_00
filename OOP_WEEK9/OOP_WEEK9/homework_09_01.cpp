#include <iostream>

class MyData {
    int number;
    std::string strNumber;
public:
    MyData(int data, std::string str) : number(data), strNumber(str) {}
    //Operator conversion(변환 연산자) : 객체에서 일반 type 값을 받을 수 있도록 도와줌
    operator int() { return number; }
    operator std::string() { return strNumber; }

    //Unary operator(단항 연산자)
    int operator++(int) { //postfix operation (indicated by dummy 'int') dummy int형
        MyData temp = *this;
        number++;
        return temp;
    }
    int operator++() { //prefix operation
        return ++number;
    }

    friend std::ostream& operator<<(std::ostream&, MyData&);
};

// non-member operator<< function
std::ostream& operator<<(std::ostream& os, MyData& md) {
    return os << "This number is: " << md.strNumber << "\n";
}

int main() {
    MyData mydata(1, "one");

    std::string strNum = mydata; //one
    int intNum = mydata; //1

    std::cout << strNum << std::endl; // one
    std::cout << intNum << std::endl; // 1
    std::cout << mydata++ << std::endl; // 1
    std::cout << ++mydata << std::endl; // 3
    std::cout << mydata;

}