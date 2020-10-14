#include <iostream>

class Animal {
public:
	//...
protected:
	int age;
};

class Cat : public virtual Animal{};//virtual 추가
class Dog : public virtual Animal{};//virtual 추가

class DogCat : public Cat, public Dog { 
public:
	void setAge() {
		age = 10;
		Cat::age = 10;
	}
};

int main() {
	DogCat* dat = new DogCat();
	Animal* animal;
	animal = dat;
	animal = static_cast <Cat*>(dat);
	animal = (Cat*)dat;
}

//13번째 줄에서 Dog,Cat 클래스를 상속 받은 DogCat은
//Dog,Cat 클래스의 영향으로 Animal 클래스의 멤버가 두개 생성된다.
//어느 클래스를 통해 간접 상속한 Base클래스의 멤버 함수를 호출할지 알 수 없다.
//따라서 25,26번째 줄처럼 형변환을 하지 않는다면 가상 상속을 받도록 virtual을 추가한다.