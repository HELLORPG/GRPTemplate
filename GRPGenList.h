//#pragma once
#ifndef GRP_GENLIST
#define GRP_GENLIST

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::istream;
using std::ostream;


template <typename T>
class GRPGenListItem;//作为返回值类型

template <typename T>
class GRPGenListNode;//作为广义表的节点类型

template <typename T>
class GRPGenList;//作为广义表的主体

template <typename T>
class GRPGenListItem
{
	friend class GRPGenList<T>;
private:
	int type;
	union
	{
		int ref;
		T data;
		GRPGenListNode<T> *link;
	}info;

public:
	GRPGenListItem() : type(0) { info.ref = 0; }
	GRPGenListItem(GRPGenListItem<T> &copy) { type = copy.type; info = copy.info; }
};

template <typename T>
class GRPGenListNode
{
	friend class GRPGenList<T>;
private:
	int type;//取值只可能是0/1/2，决定了当前节点的类型，0为头节点，1位数据，2为指针域
	GRPGenListNode<T> *next_link;//指向同一个层级的下一个节点
	union
	{
		int ref;//如果是头结点，则存储的是引用计数
		T data;//如果是数据
		GRPGenListNode<T> *link;
	}info;

public:
	GRPGenListNode() :type(0), next_link(nullptr) { info.ref = 0; }//作为头结点的时候的建立
	GRPGenListNode(GRPGenListNode<T> &copy) { type = copy.type; next_link = copy.next_link; info = copy.info; }//拷贝赋值
	~GRPGenListNode() {}
};

template <typename T>
class GRPGenList
{
private:
	GRPGenListNode<T> *HEAD;
	GRPGenListNode<T> *copy(GRPGenListNode<T> *x);//复制一个x指示的无共享非递归表
	int length(GRPGenListNode<T> *x);
	int depth(GRPGenListNode<T> *x);

public:
	GRPGenList();
	//~GRPGenList();
	bool head(GRPGenListItem<T> &x);//返回头元素
	bool tail(GRPGenList<T> &it);
	void copy(const GRPGenList<T> &x);//广义表的复制
	GRPGenListNode<T>* first();//返回广义表的第一个元素，如果为空，则返回一个空指针nullptr
	GRPGenListNode<T>* next(GRPGenListNode<T> *x);//返回所给元素的直接后续元素
	int length();
	int depth();
	//另外需要一个建立广义表的算法
	void createlist(istream &input, GRPGenListNode<T> *&x);//这里是仿照书上所做的构建函数，可能会不符合自己的预期
	void remove(GRPGenListNode<T> *it);
};

template <typename T>
GRPGenList<T>::GRPGenList()
{
	HEAD = new GRPGenListNode<T>;
	if (HEAD != nullptr)
	{
		cout << "The HEAD is not nullptr!" << endl;
		exit(-1);
	}
}

template <typename T>
bool GRPGenList<T>::head(GRPGenListItem<T>& x)
{
	if (HEAD->next_link == nullptr)
		return false;//此时是没有头的
	else
	{
		x.type = HEAD->next_link->type;
		x.info = HEAD->next_link->info;
		return true;//需要返回的通过引用进行返回
	}
}

template <typename T>
bool GRPGenList<T>::tail(GRPGenList<T>& it)
{
	if (HEAD->next_link == nullptr)
		return false;//空表，没有tail可以返回
	else
	{
		it.HEAD->type = 0;//作为一个头结点
		it.HEAD->info.ref = 0;
		it.HEAD->next_link = copy(HEAD->next_link->next_link);//将tail的头放入头结点之后
		return true;
	}
}

template <typename T>
void GRPGenList<T>::copy(const GRPGenList<T> &x)
{
	HEAD = copy(x.HEAD);//调用了私有函数，定义如下
}

template <typename T>
GRPGenListNode<T>* GRPGenList<T>::copy(GRPGenListNode<T>* x)
{
	GRPGenListNode<T> *p = nullptr;
	if (x != nullptr)
	{
		p = new GRPGenListNode<T>;
		p->type = x->type;//将这个节点的类型设置成为拷贝进来的类型
		switch (x->type)
		{
		case 0:p->info.ref = x->info.ref; break;
		case 1:p->info.data = x->info.data; break;
		case 2:p->info.link = x->info.link; break;
		default:cout << x->type << " is not expected as a type!" << endl; exit(-1); break;
		}
		p->next_link = copy(x->next_link);//处理同一层的下一个节点
	}
	return p;
}

template <typename T>
GRPGenListNode<T>* GRPGenList<T>::first()
{
	if (HEAD->next_link == nullptr)
		return nullptr;
	else
		return HEAD->next_link;
}

template <typename T>
GRPGenListNode<T>* GRPGenList<T>::next(GRPGenListNode<T>* x)
{
	if (x->next_link == nullptr)
		return nullptr;
	else
		return x->next_link;
}

template <typename T>
int GRPGenList<T>::length()
{
	return length(HEAD);
}

template <typename T>
int GRPGenList<T>::length(GRPGenListNode<T>* x)
{
	//相当于一个递归调用，不断寻找该链条
	if (x != nullptr)
		return 1 + length(x->next_link);
	else
		return 0;
}

template <typename T>
int GRPGenList<T>::depth()
{
	return depth(HEAD);
}

template <typename T>
int GRPGenList<T>::depth(GRPGenListNode<T>* x)
{
	//一样的是一个递归调用
	/*
	 * depth有三种可能的情形
	 * 如果x为空表：1
	 * 如果x为原子：0
	 * default：1+max{depth} 其中，depth为表中所有对应的子表的深度
	 */
	if (x->next_link == nullptr)
		return 1;
	GRPGenListNode<T> *p = x->next_link;
	int m(0), n(0);//两个临时变量
	while (p != nullptr)//空则不考虑
	{
		if (p->type == 2)//如果是广义表的节点，而非元素（不可能是表头）
		{
			n = depth(p->info.link);//计算以该节点为头的广义表的深度
			if (m < n)//此时m已然不是最大深度
				m = n;
		}
		p = p->next_link;
	}
	return m + 1;//因为还要算上自己的深度
}


template <typename T>
void GRPGenList<T>::createlist(istream& input, GRPGenListNode<T> *&x)
{
	T input_data;//作为读取出来的数据
	//在这里，希望能够直接达到DSOJ的输入要求，而非书上的
	//DSOJ输入样例：((a,(b,c)),(),(d))
	//如上
	//此时的建立均没有考虑共享表
	input >> input_data;//读入一个单位的数据

	if (input_data == '(')//如果是左括号，则为表
	{
		x = new GRPGenListNode<T>;
		x->type = 2;//建立了一个子表节点

		x->info.link = new GRPGenListNode<T>;//新加节点
		x->info.link->type = 0;//是个表头
		x->info.link->ref = 1;//被引用了一次

		createlist(input, x->info.link->next_link);//递归建立子表，同层向后
		createlist(input, x);
	}

	else if (input_data == ',')
	{
		//此时应该是建立后续节点
		createlist(input, x->next_link);
	}

	else if (input_data == '#')
	{
		//此时代表为空表
		x = nullptr;
		input >> input_data;//这是在DSOJ测试后的问题===================================================
	}

	else if (input_data == ')')
	{
		//说明该层已经结束了
		x->next_link = nullptr;
	}

	else
	{
		//此时是元素的节点
		x = new GRPGenListNode<T>;
		x->type = 1;//data节点
		x->info.data = input_data;
		createlist(input, x);
	}
	return;
}



template <typename T>
void GRPGenList<T>::remove(GRPGenListNode<T>* it)
{
	--(it->info.ref);//将引用减1，因为只有当引用为0的时候，才可以放心的删除这个头结点
	if (it->info.ref == 0)//此时就可以删除了
	{
		GRPGenListNode<T> *p(nullptr);
		while (it->next_link != nullptr)//当同层的下一个节点存在
		{
			p = it->next_link;
			if (p->type == 2)//如果是link域
			{
				remove(p->info.link);//递归求，向下进行删除
				if (p->info.link->info.ref <= 0)//所指向的头结点的引用已经安全
					delete p->info.link;//所以删除
			}
			it->next_link = p->next_link;
			delete p;
		}
	}
}



#endif