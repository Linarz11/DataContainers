#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n----------------\n"


//#define DEBUG
class Element
{
	int Data;		// Значение элемента
	Element* pNext; // Указатель на следующий элемент
	static int count;

public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)//DefoultConstructor создает пустой список.
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;

#endif // DEBUG
	}
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;			// Инициализация статической переменной

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr)
	{
		this->Temp = Temp;

#ifdef DEBUG
		cout << "ICOnstructor: \t" << this << endl;

#endif // DEBUG
	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "IDestructor:\t" << this << endl;

#endif // DEBUG
	}

	//Operators
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	Element*& operator->()
	{
		return Temp;
	}
	Element* get_current_address()
	{
		return Temp;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}

};


class ForwardList
{
	Element* Head;
	int size;

public:
	Iterator getHead()
	{
		return Head;
	}

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	ForwardList()
	{
		//DefoultConstructor
		Head = nullptr;
		size = 0;
#ifdef DEBUG
		cout << "LConstructor:\t" << this << endl;

#endif // DEBUG

	}

	ForwardList(initializer_list<int> il) :ForwardList()//Делегирование конструктора по умолчанию
	{
			//il - это контейнер, такой же, как наш ForwardList
			//У любого метода есть методы begin() и end(),
			//которые возвращают указатели на начало и конец контейнера
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			//it - это итератор, который проходит по il.
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other)
	{
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
#ifdef DEBUG
		cout << "LCopyConstructor: " << this << endl;

#endif // DEBUG

	}
	~ForwardList()
	{
		while (Head)pop_front();
#ifdef DEBUG
		cout << "LDestructor:\t" << this << endl;

#endif // DEBUG
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
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
		Head = new Element(Data, Head);
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
		//Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext != nullptr)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int index)
	{
		if (index == 0)
		{
			push_front(Data);
			return;
		}
		//Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++, Temp = Temp->pNext)
			if (Temp->pNext == nullptr)break;
		//Temp = Temp->pNext;
	//New->pNext = Temp->pNext;
	//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
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
		for (int i = 0; i < index-1; i++)
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
		/*	Element* Temp = Head;
			while (Temp != nullptr)
			{
				cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
				Temp = Temp->pNext;
			}*/
		for (Iterator Temp = Head; Temp != nullptr; Temp++)
			//cout  <<Temp.get_current_address()<<tab<< Temp->Data << tab << Temp->pNext << endl;
			//cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			cout << *Temp << tab;
		cout << endl;
		cout << "Количество элементов в списке: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}


};

//#define BASE_CHECK
//#define ITERATOR_CHECK
//#define RANGE_BASED_ARRAY

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << " Введите размер списка: "; cin >> n;

	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
#endif // BASE_CHECK
#ifdef ITERATOR_CHECK
	for (Iterator it = list.getHead(); it != nullptr; it++)
	{
		*it = rand() % 100;
	}

	list = list;
	list.print();
#endif // ITERATOR_CHECK

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

#ifdef RANGE_BASED_ARRAY
	int arr[] = { 3,5,8,13,21 };
	cout << size(arr) << endl;
	for (int i = 0; i < size(arr); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	for (int i : arr)		//Range-based for(цикл for для диапазона, для контейнера)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_ARRAY

	ForwardList list = { 3,5,8,13,21 };
	list.print();
	for ( int i : list)
		{
			cout << i << tab;
		}
	cout << endl;
}