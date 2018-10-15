//#pragma once
#ifndef GRP_QUEUE
#define GRP_QUEUE

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::ostream;

template <typename T>
class GRPQueue;

template <typename T>
class GRPNode
{
	friend class GRPQueue<T>;
protected:
	T data;
	GRPNode *before;
	GRPNode *next;
	GRPNode() = default;
	GRPNode(T data, GRPNode *before) :data(data), before(before), next(nullptr) {}
	~GRPNode() {}
};

template <typename T>
class GRPQueue
{
private:
	GRPNode<T> *FIRST, *current;
	size_t stack_size;
public:
	GRPQueue();
	~GRPQueue();
	void push(T input);
	T pop();
	T front();
	T back();
	size_t size() const;
	void show() const;
	bool empty() const;
	void clear();
};

template <typename T>
GRPQueue<T>::GRPQueue()
{
	FIRST = current = new GRPNode<T>;
	stack_size = 0;
}

template <typename T>
GRPQueue<T>::~GRPQueue()
{
	GRPNode<T> *kill(FIRST);
	for (; FIRST != nullptr;)
	{
		kill = FIRST;
		FIRST = FIRST->next;
		delete kill;
	}
}

template <typename T>
void GRPQueue<T>::push(T input)
{
	GRPNode<T> *add = new GRPNode<T>(input, current);
	current->next = add;
	current = add;
	++stack_size;
	return;
}

template <typename T>
size_t GRPQueue<T>::size() const
{
	return stack_size;
}

template <typename T>
void GRPQueue<T>::show() const
{
	GRPNode<T> *p(FIRST->next);
	for (; p != nullptr; p = p->next)
		cout << p->data << " ";
	cout << endl;
	return;
}

template <typename T>
bool GRPQueue<T>::empty() const
{
	return current == FIRST;
}

template <typename T>
void GRPQueue<T>::clear()
{
	while (!this->empty())
		this->pop();
	stack_size = 0;
	return;
}

template <typename T>
T GRPQueue<T>::pop()
{
	GRPNode<T> *ret = FIRST->next;
	FIRST->next = ret->next;
	T ret_data(ret->data);
	delete ret;
	return ret_data;
}

template <typename T>
T GRPQueue<T>::front()
{
	return FIRST->next->data;
}

template <typename T>
T GRPQueue<T>::back()
{
	return current->data;
}

#endif
