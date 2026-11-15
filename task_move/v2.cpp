#include <iostream>
#include <utility> // Для std::move()

class MyClass
{
public:
	MyClass(int value) : data(new int(value)) {}
	~MyClass() { delete data; }

	// Конструктор копирования
	MyClass(const MyClass& copyFrom);

	// Конструктор перемещения
	MyClass(MyClass&& moveFrom) noexcept;

	// Оператор копирования 
	MyClass& operator = (const MyClass& copyFrom);

	// Оператор перемещения
	MyClass& operator = (MyClass&& moveFrom) noexcept;

	void print() const 
	{ 
		if (this->data == nullptr)
		{
			std::cout << "Pointer == nullptr!" << std::endl;
		}
		else
		{
			std::cout << *data << std::endl;
		}
		
	}

private:

	int* data;
};



int main(void)
{

	MyClass a(10);
	a.print();

	MyClass b = std::move(a);
	b.print();
	a.print();          // (moved-from)

	MyClass c = b;      // конструктор копирования
	c.print();

	MyClass d(20);
	d = c;              // оператор присваивания копированием
	d.print();

	MyClass e(30);
	e = std::move(d);   // оператор присваивания перемещением
	e.print();
	d.print();          // (moved-from)


	return 0;
}



MyClass::MyClass(const MyClass& copyFrom)
{
	if (copyFrom.data == nullptr)
		this->data = nullptr;
	else
		this->data = new int (*(copyFrom.data));
}



MyClass::MyClass(MyClass&& moveFrom) noexcept
{
	this->data = moveFrom.data;
	moveFrom.data = nullptr;
}




MyClass& MyClass::operator=(const MyClass& copyFrom)
{
	if (this == &copyFrom)
		return *this;


	int* NewData = copyFrom.data ? new int(*copyFrom.data) : nullptr;

	delete data;

	this->data = NewData;

	return *this;
}



MyClass& MyClass::operator=(MyClass&& moveFrom) noexcept
{
	if (this == &moveFrom)
		return *this;

	delete this->data;

	this->data = moveFrom.data;

	moveFrom.data = nullptr;

	return *this;
}
