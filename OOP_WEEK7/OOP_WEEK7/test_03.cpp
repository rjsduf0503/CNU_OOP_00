#include <iostream>
int main() {
	int a, b;
	std::cout << "�� ���� ������ �Է� : ";
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