#include <iostream>
int main() {
	int a, b;
	std::cout << "두 개의 정수를 입력 : ";
	std::cin >> a >> b;
	try {
		if (b == 0) throw b;
		std::cout << a << "/ " << b << " = " << a / b << std::endl;
	}
	catch (int exception) {
		std::cout << "exceipt" << std::endl;
	}
	return 0;
}