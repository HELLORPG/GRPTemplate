//#pragma once
#ifndef GRP_STACK
#define GRP_STACK

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::ostream;

template <typename T>
class GRPStack;

//template <typename T>
//class GRPNode
//{
//	friend class GRPStack<T>;
//protected:
//	T data;
//	GRPNode *before;
//	GRPNode *next;
//	GRPNode() = default;
//	GRPNode(T data, GRPNode *before) :data(data), before(before), next(nullptr) {}
//	~GRPNode() {}
//};

template <typename T>
class GRPSinNode
{
	friend class GRPStack<T>;
protected:
	T data;
	GRPSinNode *next;
	GRPSinNode() :data(*(new T)), next(nullptr) {}
	GRPSinNode(T data) :data(data), next(nullptr) {}
	GRPSinNode(T data, GRPSinNode *next) :data(data), next(next) {}
	~GRPSinNode() {}
};

template <typename T>
class GRPStack
{
private:
	GRPSinNode<T> *FIRST/*, *current*/;
	size_t stack_size;
public:
	GRPStack();
	~GRPStack();
	void push(T input);
	T pop();
	T top();
	size_t size() const;
	void show() const;
	bool empty() const;
	void clear();
};

//template <typename T>
//GRPStack<T>::GRPStack()
//{
//	FIRST = current = new GRPNode<T>;
//	stack_size = 0;
//}
//
//template <typename T>
//GRPStack<T>::~GRPStack()
//{
//	GRPNode<T> *kill(FIRST);
//	for (; FIRST != nullptr;)
//	{
//		kill = FIRST;
//		FIRST = FIRST->next;
//		delete kill;
//	}
//}
//
//template <typename T>
//void GRPStack<T>::push(T input)
//{
//	GRPNode<T> *add = new GRPNode<T>(input, current);
//	current->next = add;
//	current = add;
//	++stack_size;
//	return;
//}
//
//template <typename T>
//T GRPStack<T>::pop()
//{
//	GRPNode<T> *p = current;
//	current = current->before;
//	current->next = nullptr;
//	--stack_size;
//	T pop_ret(p->data);
//	delete p;//换成delete[]就会不行，待解
//	return pop_ret;
//}
//
//template <typename T>
//T GRPStack<T>::top()
//{
//	return current->data;
//}
//
//template <typename T>
//size_t GRPStack<T>::size() const
//{
//	return stack_size;
//}
//
//template <typename T>
//void GRPStack<T>::show() const
//{
//	GRPNode<T> *p(FIRST->next);
//	for (; p != nullptr; p = p->next)
//		cout << p->data << " ";
//	cout << endl;
//	return;
//}
//
//template <typename T>
//bool GRPStack<T>::empty() const
//{
//	return current == FIRST;
//}
//
//template <typename T>
//void GRPStack<T>::clear()
//{
//	while (!this->empty())
//		this->pop();
//	stack_size = 0;
//	return;
//}

template <typename T>
GRPStack<T>::GRPStack()
{
	FIRST = new GRPSinNode<T>;
	stack_size = 0;
}

template <typename T>
void GRPStack<T>::push(T input)
{
	FIRST->next = new GRPSinNode<T>(input, FIRST->next);
	++stack_size;
	return;
}

template <typename T>
T GRPStack<T>::pop()
{
	GRPSinNode<T> *p(FIRST->next);
	T ret_data(p->data);
	FIRST->next = p->next;
	delete p;
	--stack_size;
	return ret_data;
}

template <typename T>
size_t GRPStack<T>::size() const
{
	return stack_size;
}

template <typename T>
bool GRPStack<T>::empty() const
{
	return !(FIRST->next);
}

template <typename T>
void GRPStack<T>::clear()
{
	while (!this->empty())
		this->pop();
	stack_size = 0;
	return;
}

template <typename T>
T GRPStack<T>::top()
{
	return FIRST->next->data;
}

template <typename T>
GRPStack<T>::~GRPStack()
{
	for (GRPSinNode<T> *p(FIRST); p != nullptr;)
	{
		GRPSinNode<T> *kill = p;
		p = p->next;
		delete kill;
	}
}

template <typename T>
void GRPStack<T>::show() const
{
	cout << "==========" << endl << "<TOP>" << endl;
	for (GRPSinNode<T> *p(FIRST->next); p != nullptr; p = p->next)
		cout << p->data << endl;
	return;
}



#endif