#include <iostream>
#define interface struct
using namespace std;

interface Strategy {
public:
	virtual int doOperation(int num1, int num2) = 0;
};

class OperationAdd : public Strategy {
public:
	virtual int doOperation(int num1, int num2) override {
		return num1 + num2;
	}
};

class OperationSubstract : public Strategy {
public:
	virtual int doOperation(int num1, int num2) override {
		return num1 - num2;
	}
};

class OperationMultiply : public Strategy {
public:
	virtual int doOperation(int num1, int num2) override {
		return num1 * num2;
	}
};

class Context {
private:
	Strategy *stg;
public:
	Context(Strategy *stg) {
		this->stg = stg;
	}
	int excuteStrategy(int num1, int num2) {
		return stg->doOperation(num1, num2);
	}
	
};



int main(void) {
	Context *context = new Context(new OperationAdd());
	cout << "10 + 5 = " <<context->excuteStrategy(10,5) << endl;
	context = new Context(new OperationSubstract());
	cout << "10 - 5 = " << context->excuteStrategy(10, 5) << endl;
	context = new Context(new OperationMultiply());
	cout << "10 * 5 = " << context->excuteStrategy(10, 5) << endl;
}