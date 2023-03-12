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

template<class T> class ListedStack : public AbstractStack {
	int size;
	struct element {
		element* befor;
		T val;
	};
	element* top;
public:
	ListedStack() {
		size = 1;
		top = new element;
	}
	ListedStack(ListedStack& other) {
		ListedStack y;
		for (int i = 0; i < other.size; i++) {
			y.Push(other.Top());
			other.Pop();
		}
		for (int i = 0; i < other.size; i++) {
			Push(y.Top());
			y.Pop();
		}
	}
	ListedStack& operator=(ListedStack& other) {
		if (this == &other)
			return *this;
		element* d;
		while (!(top == nullptr)) {
			d = top;
			top = top->befor;
			delete[] d;
		}
		ListedStack y;
		for (int i = 0; i < other.size; i++) {
			y.Push(other.Top());
			other.Pop();
		}
		for (int i = 0; i < other.size; i++) {
			Push(y.Top());
			y.Pop();
		}
	}
	ListedStack& operator=(ListedStack&& poop) {
		if (this == &poop) return *this;
		element* d;
		while (!(top == nullptr)) {
			d = top;
			top = top->befor;
			delete[] d;
		}
		top = poop.top;
		poop.top = nullptr;
		size = poop.size;
		poop.size = 0;
	}
	ListedStack(ListedStack&& poop) {
		top = poop.top;
		size = poop.size;
		poop.top = nullptr;
		poop.size = 0;
	}
	bool IsEmpty() {
		if (size == 0)
			return 1;
		return 0;
	}
	int Size() {
		return size;
	}
	void Push(T val) {
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
	T Top() {
		if (size == 0)
			return 0;
		return top->val;
	}
	~ListedStack() {
		element* d;
		while (size != 0 && top !=nullptr) {
			d = top;
			top = top->befor;
			delete[] d;
		}
	}
};

template<class T> class LimitedStack : public AbstractStack {
	int limit = 0;
	int size = 0;
	T* stack = nullptr;
public:
	LimitedStack() : AbstractStack() {
		limit = 5;
		size = 0;
		stack = nullptr;
	}
	LimitedStack(LimitedStack& poop) {
		stack = new T[poop.size];
		for (int i = 0; i < poop.size; i++) {
			stack[i] = poop.stack[i];
			size = poop.size;
		}
	}
	LimitedStack& operator=(LimitedStack& maybepoop) {
		if (this == &maybepoop) {
			return *this;
		}
		delete[] stack;
		stack = new T[maybepoop.size];
		for (int i = 0; i < maybepoop.size; i++) {
			stack[i] = maybepoop.stack[i];
		}
		size = maybepoop.size;
	}
	~LimitedStack() {
		delete[] stack;
		size = 0;
	}
	LimitedStack& operator=(LimitedStack&& surlypoop) {
		if (this == &surlypoop) {
			return *this;
		}
		delete[] stack;
		stack = surlypoop.stack;
		size = surlypoop.size;
		surlypoop.size = 0;
		surlypoop.stack = nullptr;
	}
	LimitedStack(LimitedStack&& poop) {
		size = poop.size;
		stack = poop.stack;
		poop.size = 0;
		poop.stack = nullptr;
	}
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
	void Push(T a) {
		if (size == limit)
			return;
		size+=1;	
		T* _new = new T[size];
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
		T* _new = new T[size];
		for (int i = 0; i < size; i++) {
			_new[i] = stack[i + 1];
		}
		delete[] stack;
		stack = _new;
		return;
	}
	T Top() {
		if (size == 0)
			return 0;
		return stack[0];
	}
};
template<class T> class UnlimitedStack : public AbstractStack {
	int size;
	T* stack;
public:
	UnlimitedStack() : AbstractStack() {
		size = 0;
		stack = nullptr;
	}
	UnlimitedStack(UnlimitedStack& poop) {
		stack = new T[poop.size];
		for (int i = 0; i < poop.size; i++) {
			stack[i] = poop.stack[i];
			size = poop.size;
		}
	}
	UnlimitedStack& operator=(UnlimitedStack& maybepoop) {
		if (this == &maybepoop) {
			return *this;
		}
		delete[] stack;
		stack = new T[maybepoop.size];
		for (int i = 0; i < maybepoop.size; i++) {
			stack[i] = maybepoop.stack[i];
		}
		size = maybepoop.size;
	}
	~UnlimitedStack() {
		delete[] stack;
		size = 0;
	}
	UnlimitedStack& operator=(UnlimitedStack&& surlypoop) {
		if (this == &surlypoop) {
			return *this;
		}
		delete[] stack;
		stack = surlypoop.stack;
		size = surlypoop.size;
		surlypoop.stack = nullptr;
	}
	UnlimitedStack(UnlimitedStack&& poop) {
		size = poop.size;
		stack = poop.stack;
		poop.size = 0;
		poop.stack = nullptr;
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
		size += 1;
		T* _new = new T[size];
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
		T* _new = new T[size];
		for (int i = 0; i < size; i++) {
			_new[i] = stack[i + 1];
		}
		delete[] stack;
		stack = _new;
		return;
	}
	T Top() {
		if (size == 0)
			return 0;
		return stack[0];
	}
};
int main()
{
	
	LimitedStack<int> st(5);
	for (int i = 1; i <= 7; i++) {
		st.Push(i);
	}
	for (int i = 1; i <= 7; i++) {
		cout << st.Top() << endl;
		st.Pop();
	}
	cout << st.IsEmpty() << "||||||" << st.Size();
	cout << endl;
	
	UnlimitedStack<int> unst;
	for (int i = 0; i < 10; i++) {
		unst.Push(i);
		cout << unst.Top() << endl;
	}
	for (int i = 0; i < 12; i++) {
		unst.Pop();
	}
	cout << unst.IsEmpty() << "||||||||" << unst.Size();
	cout << endl;

	ListedStack<int> lst;
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
