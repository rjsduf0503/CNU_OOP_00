#include <iostream>

class Animal {
public:
	//...
protected:
	int age;
};

class Cat : public virtual Animal{};//virtual �߰�
class Dog : public virtual Animal{};//virtual �߰�

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

//13��° �ٿ��� Dog,Cat Ŭ������ ��� ���� DogCat��
//Dog,Cat Ŭ������ �������� Animal Ŭ������ ����� �ΰ� �����ȴ�.
//��� Ŭ������ ���� ���� ����� BaseŬ������ ��� �Լ��� ȣ������ �� �� ����.
//���� 25,26��° ��ó�� ����ȯ�� ���� �ʴ´ٸ� ���� ����� �޵��� virtual�� �߰��Ѵ�.