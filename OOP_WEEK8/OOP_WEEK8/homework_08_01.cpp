#include <iostream>

class GlobalClass {
private:
	int m_value;
	static GlobalClass* s_instance;//이 객체에 접근할 수 있도록 static

	GlobalClass(int v = 0) { //생성자를 private으로 선언하여 다른 객체에서 생성할 수 없도록 함
		m_value = v;
	}
public:
	int get_value() {
		return m_value;
	}
	void set_value(int v) {
		m_value = v;
	}
	static GlobalClass* instance() {
		if (!s_instance) {
			s_instance = new GlobalClass;
		}
		return s_instance;
	}
};

// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object itself.
GlobalClass* GlobalClass::s_instance = 0; 
//GlobalClass 정적 데이터 멤버 할당 및 초기화
//포인터가 할당되고 있기 때문에 객체 자체는 아님.

void foo(void) {
	GlobalClass::instance()->set_value(1);
	std::cout << "foo: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

void bar(void) {
	GlobalClass::instance()->set_value(2);
	std::cout << "bar: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

int main() {
	std::cout << "main: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
	foo();
	bar();
}