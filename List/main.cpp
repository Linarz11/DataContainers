#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
//#define BASE_CHECK
//#define SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR
//#define DEBUG
#define delimeter "\n---------------------------------------------------------------------------------------------\n"
class List
{
	class Element
	{
		int Data;		// значение элемента
		Element* pNext; // указатель на следующий элемент
		Element* pPrev; // указатель на предыдущий элемент
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) //:Data(Data), pNext(pNext), pPrev(pPrev);
		{
			this->Data = Data;
			this->pNext = pNext;
			this->pPrev = pPrev;
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;

#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;

#endif // DEBUG
		}
		friend class List;

	};
	Element* Head;		//указатель на начальный элемент списка
	Element* Tail;		//указатель на конечный элемент списка
	unsigned int size;	// размер списка


				//Base iterator
	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr) : Temp(Temp)
		{
#ifdef DEBUG
			cout << "BIConstructor:\t" << this << endl;

#endif // DEBUG
		}
		~BaseIterator()
		{
#ifdef DEBUG
			cout << "BIDestructor:\t" << this << endl;

#endif // DEBUG
		}
		
		bool operator==(const BaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		int& operator*()
		{
			return Temp->Data;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
	};

public:
	class Iterator:public BaseIterator
	{
		//Element* Temp;
	public: 
		Iterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ITDestructor:\t" << this << endl;

#endif // DEBUG
		}

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		/*Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}*/

	/*	bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}*/

		
	};
	class ReverseIterator:public BaseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RICOnstructor:\t" << this << endl;

#endif // DEBUG
		}
		~ReverseIterator()
		{
#ifdef DEBUG
			cout << "RIDenstructor:\t" << this << endl;

#endif // DEBUG
		}
		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		/*bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const
		{
			return this->Temp != other.Temp;
		}*/

	};
	size_t getSize()const
	{
		return size;
	}

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;

	}
	explicit List(int size) :List()
	{
		while (size--)push_back(0);
	}
	List(const initializer_list<int>& il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;

	}

		//OPerators
	int& operator[](size_t index)
	{
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (size_t i = 0; i < index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i < size - index - 1; i++) Temp = Temp->pPrev;
		}
		return Temp->Data;
	}



	// Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		/*Element* New = new Element(Data);
		New->pNext = Head;
		New->pNext->pPrev = New;
		Head = New;*/
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(unsigned int Index, int Data)
	{
		if (Index > size)return;
		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		if (Index == size)
		{
			push_back(Data);
			return;
		}
		Element* Temp;
		if (Index < size / 2)
		{
		 Temp = Head;
			for (size_t i = 0; i < Index; i++)Temp = Temp->pNext;
		}

		else
		{
			Temp = Tail;
			for (size_t i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
		}
		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp -> pPrev->pNext = New;
		Temp->pPrev = New;*/
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}

			//Erasing elements
	void pop_front()
	{
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(size_t Index)
		/*{
			if (Index > size)return;
			if (Index == size)
			{
				pop_back();
				return;
			}
			if (Index == 0)
			{
				pop_front();
				return;
			}

			Element* Temp;
			if (Index < size / 2)
			{
				Temp = Head;
				for (int i = 0; i < Index; i++)
				{
					Temp = Temp->pNext;
				}
			}
			else
			{
				Temp = Tail;
				for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
			}
			Temp->pPrev->pNext = Temp->pNext;
			Temp->pNext->pPrev = Temp->pPrev;
			delete Temp;
			size--;
		}*/	  //Homework
	{
		if (Index == 0)
		{
			pop_front();
			return;
		}
		if (Index == size-1)
		{
			pop_back();
			return;
		}
		if (Index >= size)return;
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (size_t i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i<size - Index - 1; i++)Temp = Temp->pPrev;
		}
		//1) Исключаем удаляемый элемент из списка:
		Temp->pPrev->pNext = Temp->pNext;	//В указатель pNext элемента Temp->pPrev записываем адрес элемента Temp->pNext
		Temp->pNext->pPrev = Temp->pPrev;	//В указатель pPrev элемента Temp->pNext записываем адрес жлемента Temp->pPrev
		//2) Удаляем элемент из памяти:
		delete Temp;
		//Mission complete
	}

			//Methods
	void print()
	{
		for (Element* Temp = Head; Temp; Temp = Temp-> pNext)
		{
			cout << Temp<<tab ;
			cout <<Temp<<tab<< Temp->pPrev << tab << Temp->Data << tab << Temp ->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}

		void print_reverse()
		{
			for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp << tab<<Temp->pPrev<< tab << Temp->Data << tab << Temp ->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		}

	};


void main()
{
	setlocale(LC_ALL, "");
	//int n; cout << "Введите размер списка: "; cin >> n;
#ifdef BASE_CHECK
	List list;
	for (int i = 0; i < n; i++)
		list.push_back(rand() % 100);
	/*list.print();
	list.pop_front();*/
	list.print();
	list.print_reverse();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.print_reverse();

	cout << "Введите индекс удаляемого элемента: "; cin >> value;
	list.erase(index);
	list.print();
	list.print_reverse();
#endif // BASE_CHECK


#ifdef SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR
	List list(n);
	for (size_t i = 0; i < list.getSize(); i++)list[i] = rand() % 100;
	for (size_t i = 0; i < list.getSize(); i++) cout << list[i] << tab;
	cout << endl;

	list.print();
#endif // SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR

	List list = { 3, 5, 8, 13, 21 };
	list.print();
	for (int i : list)
		cout << i << tab;
	cout << endl;
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	cout << delimeter << endl;
	

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}