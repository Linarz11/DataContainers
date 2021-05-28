﻿#include <iostream>
using namespace std;

#define tab "\t"
#define delimeter "\n----------------\n"
class Element
{
	int Data;		// Значение элемента
	Element* pNext; // Указатель на следующий элемент
	static int count;

public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)//DefoultConstructor создает пустой список.
	{
		count++;
		cout << "EConstructor:\t" <<this<< endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this<<endl;
	}
	friend class ForwardList;
};

int Element::count = 0;			// Инициализация статической переменной


class ForwardList
{
	Element* Head;
	int size;
public:
	ForwardList() 
	{
		//DefoultConstructor
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;

	}
	ForwardList(const ForwardList& other)
	{
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "LCopyConstructor: " << this << endl;

	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}



			//Operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "LCopyAssignment: " << this << endl;
		return *this;
	}


		//				Adding elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}

	void push_back(int Data)
	{
		//Этот метод НЕ умеет работать с пустым списком. 
		if (Head == nullptr) //Если список пуст, тогда вызываем Push front
		{
			push_front(Data);
			return;
		}
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
			Temp = Temp->pNext;
		Temp->pNext = New;
		size++;
	}
	void insert(int Data, int index)
	{
		if (index == 0)
		{
			push_front(Data);
			return;
		}
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++, Temp = Temp->pNext)
			if (Temp->pNext == nullptr)break;
			//Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}


			//Erasing elements
	void pop_front()
	{
		//1)Прежде чем исключить элемент из списка, нужно запомнить его адрес, для того чтобы можно было удалить его из памяти
		Element* Temp = Head;
		//2)Исключаем элемент из списка
		Head = Head->pNext;
		//3)Удаляем элемент из памяти
		delete Temp;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)
			Temp = Temp->pNext;		//Переход на следующий элемент
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;

	}

	void erase(int index)
	{

		if (index > size)return;
		if (index == 0)
		{
			pop_front();
			return;
		}
			//1. Доходим до первого элемента
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}
			//2. Запоминаем адрес удаляемого элемента
		Element* to_del = Temp->pNext;
			//3. Исключаем удаляемы элемент из списка
		Temp->pNext = Temp->pNext->pNext;
			//4. Удаляем элемент из памяти
		delete to_del;
		size--;

	}


			//Metods:
	void print()
	{
		Element* Temp = Head;
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов в списке: " <<size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << " Введите размер списка: "; cin >> n;

	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand()% 100);
	}


	list = list;
	list.print();

#ifdef BASE_CHECK
	/*cout << delimeter << endl;
list.pop_front();
list.pop_back();
list.print();*/
	int value;
	int index;
	cout << "Введите добавляемое значение: "; cin >> value;
	cout << "Введите индекс добавляемого значения: "; cin >> index;
	list.insert(value, index);
	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();

	/*cout << "Еще один список: \n";
	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.print();*/
#endif // BASE_CHECK

	//ForwardList list2 = list;
	//list2.print();

	//ForwardList list3;
	//list3 = list2;	//CopyAssignment
	//list3.print();

}