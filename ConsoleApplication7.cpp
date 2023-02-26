#include <string>
#include <iostream>
using namespace std;
class AbstractContainer {
public:
	virtual int Size() = 0;
	virtual bool IsEmpty() = 0;
};

class AbstractStack : public AbstractContainer {
public:
	virtual void Push(int value) = 0;
	virtual void Pop() = 0;
	virtual int Top() = 0;
};

class ListedStack : public AbstractStack {
	int size = 0;
	struct element {
		element* befor;
		int val;
	};
	element* top = nullptr;
public:
	bool IsEmpty() {
		if (size == 0)
			return 1;
		return 0;
	}
	int Size() {
		return size;
	}
	void Push(int val) {
		++size;
		element* a = new element;
		a->val = val;
		a->befor = top;
		top = a;
	}
	void Pop() {
		if (size == 0 || top == nullptr)
			return;
		size--;
		element* f;
		f = top;
		top = top->befor;
		delete[] f;
	}
	int Top() {
		if (size == 0)
			return 0;
		return top->val;
	}
	~ListedStack() {
		for (; top != nullptr;) {
			element* d;
			d = top;
			top = top->befor;
			delete[] d;
		}
	}
};

class LimitedStack : public AbstractStack {
	int limit = 0;
	int size = 0;
	int* stack = nullptr;
public:
	LimitedStack(int a) {
		limit = a;
	}
	bool IsEmpty() {
		if (size == 0)
			return 1;
		return 0;
	}
	int Size() {
		return size;
	}
	void Push(int a) {
		if (size == limit)
			return;
		size+=1;	
		int* _new = new int[size];
		for (int i = 1; i < size; i++) {
			_new[i] = stack[i - 1];
		}
		_new[0] = a;
		delete[] stack;
		stack = _new;
		return;
	}
	void Pop() {
		if (size == 0)
			return;
		size -= 1;
		int* _new = new int[size];
		for (int i = 0; i < size; i++) {
			_new[i] = stack[i + 1];
		}
		delete[] stack;
		stack = _new;
		return;
	}
	int Top() {
		if (size == 0)
			return 0;
		return stack[0];
	}
};
class UnlimitedStack : public AbstractStack {
	int size = 0;
	int* stack = nullptr;
public:
	bool IsEmpty() {
		if (size == 0)
			return 1;
		return 0;
	}
	int Size() {
		return size;
	}
	void Push(int a) { 
		size += 1;
		int* _new = new int[size];
		for (int i = 1; i < size; i++) {
			_new[i] = stack[i - 1];
		}
		_new[0] = a;
		delete[] stack;
		stack = _new;
		return;
	}
	void Pop() {
		if (size == 0)
			return;
		size -= 1;
		int* _new = new int[size];
		for (int i = 0; i < size; i++) {
			_new[i] = stack[i + 1];
		}
		delete[] stack;
		stack = _new;
		return;
	}
	int Top() {
		if (size == 0)
			return 0;
		return stack[0];
	}
};
int main()
{
	
	LimitedStack st(5);
	for (int i = 1; i <= 7; i++) {
		st.Push(i);
	}
	for (int i = 1; i <= 7; i++) {
		cout << st.Top() << endl;
		st.Pop();
	}
	cout << st.IsEmpty() << "||||||" << st.Size();
	cout << endl;
	
	UnlimitedStack unst;
	for (int i = 0; i < 10; i++) {
		unst.Push(i);
		cout << unst.Top() << endl;
	}
	for (int i = 0; i < 12; i++) {
		unst.Pop();
	}
	cout << unst.IsEmpty() << "||||||||" << unst.Size();
	cout << endl;

	ListedStack lst;
	for (int i = 0; i < 10; i++) {
		lst.Push(i);
		cout << lst.Top() << endl;
	}
	for (int i = 0; i < 12; i++) {
		lst.Pop();
	}
	cout << lst.IsEmpty() << "||||||||" << lst.Size();
	cout << endl;
}
