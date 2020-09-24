#include<iostream>

void swap(int &first, int &second) { //참조 연산자인 reference 사용
    int temp = first;
    first = second;
    second = temp;
}
int main() {
    int a = 2, b = 3;
    swap(a, b);
    std::cout << a << " " << b << std::endl;
    return 0;
}
