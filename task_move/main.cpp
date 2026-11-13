#include <iostream>

class MyClass
{
public:
	MyClass(int value) : data(new int(value)) {}
	~MyClass() { delete data; }

	void print() const { std::cout << *data << std::endl; }

private:

	int* data;
};



int main(void)
{

	MyClass a(10);
	MyClass b = std::move(a);

	a.print();
	b.print();

	return 0;
}