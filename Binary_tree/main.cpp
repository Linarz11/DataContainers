#include <iostream>

using namespace std;

#define tab "\t"
#define delimeter "\n------------------------------\n"
//#define DEBUG

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "ECOnstructor(ELement):\t" << this << endl;

#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor(ELement):\t" << this << endl;

#endif // DEBUG
		}
		friend class Tree;
		friend class UniqueTree;

	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TCOnstructor(Tree):\t" << this << endl;
	}
	~Tree()
	{
		cout << "TDestructor(Tree):\t" << this << endl;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else// (Data>Root->Data)
		{
			/*if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);*/
			if (Root->pRight)insert(Data, Root->pRight);
			else Root->pRight = new Element(Data);
		}
	}
	int minValue(Element* Root)
	{
		if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);
	}
	int maxValue(Element* Root)
	{
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
		//return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
	}
	int count(Element* Root)
	{
		/*static int Count=0;
		if (Root == nullptr)return 0;
		return count(Root->pLeft) + count(Root->pRight) + 1;*/
		
		/* Count++;
		if (Root->pLeft) count(Root->pLeft);
		if (Root->pRight)count(Root->pRight);
		return Count;*/

		return Root ? count(Root->pLeft) + count(Root->pRight) + 1 : 0;
	}
	int sum(int Data, Element* Root)
	{
		return Root ? sum(Data, Root->pLeft) + sum(Data, Root->pRight) : 0;
	}
	void print(Element* Root)
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
public:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		if (Data > Root->Data)
		{
			/*if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);*/
			if (Root->pRight)insert(Data, Root->pRight);
			else Root->pRight = new Element(Data);
		}
	}
};


void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер дерева: "; cin >> n;

	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand()%100, tree.getRoot());
	}
	//tree.insert(-2, tree.getRoot());
	tree.print(tree.getRoot());
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue(tree.getRoot()) << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue(tree.getRoot())<< endl;
	cout << "Количество элементов в дереве: " << tree.count(tree.getRoot())<< endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100, u_tree.getRoot());
	}
	u_tree.print(u_tree.getRoot());
	cout << endl;
	cout << "Количество элементов в дереве: " << u_tree.count(u_tree.getRoot())<< endl;
	cout << delimeter;
	cout << "Сумма элементов в дереве: " << tree.sum(data, tree.getRoot())<< endl;
}