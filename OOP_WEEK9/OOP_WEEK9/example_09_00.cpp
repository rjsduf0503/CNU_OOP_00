
class Base {
public:
	void func_1() {};
protected:
	void func_2() {};
private:
	int x_;
};

class Derived : protected Base { //이 부분을 public으로 바꾸어주면 해결가능.
public:
	void func_3() {
		func_1();
		func_2();
	}
};

int main() {
	Derived d;
	d.func_3();
	//d.func_1(); <= error, protected이므로 상속받은 클래스에서만 사용가능


	//d.func_2(); <= public이어도 Base에서 protected이므로 사용 불가능
}