
class Base {
public:
	void func_1() {};
protected:
	void func_2() {};
private:
	int x_;
};

class Derived : protected Base { //�� �κ��� public���� �ٲپ��ָ� �ذᰡ��.
public:
	void func_3() {
		func_1();
		func_2();
	}
};

int main() {
	Derived d;
	d.func_3();
	//d.func_1(); <= error, protected�̹Ƿ� ��ӹ��� Ŭ���������� ��밡��


	//d.func_2(); <= public�̾ Base���� protected�̹Ƿ� ��� �Ұ���
}