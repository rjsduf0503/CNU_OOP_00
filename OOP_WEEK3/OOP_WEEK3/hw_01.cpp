#include <iostream>
class SetValue {
	int x, y;

public:
	void setX(int aX) {
		x = aX;
	}
	void setY(int anY) {
		y = anY;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};

int main() {
	SetValue obj;

	obj.setX(33);
	obj.setY(44);
	std::cout << "X= " << obj.getX() << " , Y= " << obj.getY() << std::endl;
	
	system("pause");
	return 0;
}