#pragma warning(disable:4326)
#include<iostream>
#include "List.h"
#include "List.cpp"
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define minitab " "
#define delimiter "\n-----------------------------------------------------\n"

//#define DEBUG

template<typename T>class List;
template<typename T>class Element;
template<typename T>class Iterator;
template<typename T>class BaseIterator;
template<typename T>class ReverseIterator;


void main()
{
	setlocale(LC_ALL, "Russian");
	//int n;	cout << "Введите размер списка: "; cin >> n;
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

	cout << "Введите индекс удавляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.print_reverse();
#endif // BASE_CHECK

#ifdef SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR
	//List list = n;	//Type conversion from int to List
	List list(n);
	for (size_t i = 0; i < list.getSize(); i++)list[i] = rand() % 100;
	for (size_t i = 0; i < list.getSize(); i++)cout << list[i] << tab;
	cout << endl;
	list.print();
#endif // SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	list.print();
	for (int i : list)
		cout << i << tab;
	cout << endl;
	for (List::Iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
	cout << "\n----------------------------------------------------------\n";
	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

#ifdef COPY_METHODS_CHECK
	List list1 = { 3,5,8,13,21 };
	list1.print();
	//List list2 = list1;	//CopyConstructor
	List list2;
	list2 = list1;	//CopyAssignment
	list2.print();
#endif // DEBUG

#ifdef MOVE_METHODS_CHECK
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	cout << delimiter << endl;
	//List list3 = list1 + list2;	//MoveConstructor
	List<int> list3;
	list3 = list1 + list2;	//MoveAssignment
	cout << delimiter << endl;
	list3.print();
#endif // MOVE_METHODS_CHECK

	List<int> i_list = { 3,5, 8, 13,21 };
	i_list.print();
	List<double> d_list = { 2.5, 3,14, 5.2, 8.3 };
	d_list.print();
	List <string> s_list = { "What", "can", "I", "do", "?" };
	for (string i : s_list) cout << i << minitab; cout << endl;

	for (List <string>::Iterator it = s_list.begin(); it != s_list.end(); it++)
		cout << *it << minitab;
	cout << endl;
	for (List <string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); it++)
		cout << *it << minitab;
	cout << endl;
}