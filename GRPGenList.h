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
class GRPGenListItem;//��Ϊ����ֵ����

template <typename T>
class GRPGenListNode;//��Ϊ�����Ľڵ�����

template <typename T>
class GRPGenList;//��Ϊ����������

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
	int type;//ȡֵֻ������0/1/2�������˵�ǰ�ڵ�����ͣ�0Ϊͷ�ڵ㣬1λ���ݣ�2Ϊָ����
	GRPGenListNode<T> *next_link;//ָ��ͬһ���㼶����һ���ڵ�
	union
	{
		int ref;//�����ͷ��㣬��洢�������ü���
		T data;//���������
		GRPGenListNode<T> *link;
	}info;

public:
	GRPGenListNode() :type(0), next_link(nullptr) { info.ref = 0; }//��Ϊͷ����ʱ��Ľ���
	GRPGenListNode(GRPGenListNode<T> &copy) { type = copy.type; next_link = copy.next_link; info = copy.info; }//������ֵ
	~GRPGenListNode() {}
};

template <typename T>
class GRPGenList
{
private:
	GRPGenListNode<T> *HEAD;
	GRPGenListNode<T> *copy(GRPGenListNode<T> *x);//����һ��xָʾ���޹���ǵݹ��
	int length(GRPGenListNode<T> *x);
	int depth(GRPGenListNode<T> *x);

public:
	GRPGenList();
	//~GRPGenList();
	bool head(GRPGenListItem<T> &x);//����ͷԪ��
	bool tail(GRPGenList<T> &it);
	void copy(const GRPGenList<T> &x);//�����ĸ���
	GRPGenListNode<T>* first();//���ع����ĵ�һ��Ԫ�أ����Ϊ�գ��򷵻�һ����ָ��nullptr
	GRPGenListNode<T>* next(GRPGenListNode<T> *x);//��������Ԫ�ص�ֱ�Ӻ���Ԫ��
	int length();
	int depth();
	//������Ҫһ�������������㷨
	void createlist(istream &input, GRPGenListNode<T> *&x);//�����Ƿ������������Ĺ������������ܻ᲻�����Լ���Ԥ��
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
		return false;//��ʱ��û��ͷ��
	else
	{
		x.type = HEAD->next_link->type;
		x.info = HEAD->next_link->info;
		return true;//��Ҫ���ص�ͨ�����ý��з���
	}
}

template <typename T>
bool GRPGenList<T>::tail(GRPGenList<T>& it)
{
	if (HEAD->next_link == nullptr)
		return false;//�ձ�û��tail���Է���
	else
	{
		it.HEAD->type = 0;//��Ϊһ��ͷ���
		it.HEAD->info.ref = 0;
		it.HEAD->next_link = copy(HEAD->next_link->next_link);//��tail��ͷ����ͷ���֮��
		return true;
	}
}

template <typename T>
void GRPGenList<T>::copy(const GRPGenList<T> &x)
{
	HEAD = copy(x.HEAD);//������˽�к�������������
}

template <typename T>
GRPGenListNode<T>* GRPGenList<T>::copy(GRPGenListNode<T>* x)
{
	GRPGenListNode<T> *p = nullptr;
	if (x != nullptr)
	{
		p = new GRPGenListNode<T>;
		p->type = x->type;//������ڵ���������ó�Ϊ��������������
		switch (x->type)
		{
		case 0:p->info.ref = x->info.ref; break;
		case 1:p->info.data = x->info.data; break;
		case 2:p->info.link = x->info.link; break;
		default:cout << x->type << " is not expected as a type!" << endl; exit(-1); break;
		}
		p->next_link = copy(x->next_link);//����ͬһ�����һ���ڵ�
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
	//�൱��һ���ݹ���ã�����Ѱ�Ҹ�����
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
	//һ������һ���ݹ����
	/*
	 * depth�����ֿ��ܵ�����
	 * ���xΪ�ձ�1
	 * ���xΪԭ�ӣ�0
	 * default��1+max{depth} ���У�depthΪ�������ж�Ӧ���ӱ�����
	 */
	if (x->next_link == nullptr)
		return 1;
	GRPGenListNode<T> *p = x->next_link;
	int m(0), n(0);//������ʱ����
	while (p != nullptr)//���򲻿���
	{
		if (p->type == 2)//����ǹ����Ľڵ㣬����Ԫ�أ��������Ǳ�ͷ��
		{
			n = depth(p->info.link);//�����Ըýڵ�Ϊͷ�Ĺ��������
			if (m < n)//��ʱm��Ȼ����������
				m = n;
		}
		p = p->next_link;
	}
	return m + 1;//��Ϊ��Ҫ�����Լ������
}


template <typename T>
void GRPGenList<T>::createlist(istream& input, GRPGenListNode<T> *&x)
{
	T input_data;//��Ϊ��ȡ����������
	//�����ϣ���ܹ�ֱ�ӴﵽDSOJ������Ҫ�󣬶������ϵ�
	//DSOJ����������((a,(b,c)),(),(d))
	//����
	//��ʱ�Ľ�����û�п��ǹ����
	input >> input_data;//����һ����λ������

	if (input_data == '(')//����������ţ���Ϊ��
	{
		x = new GRPGenListNode<T>;
		x->type = 2;//������һ���ӱ�ڵ�

		x->info.link = new GRPGenListNode<T>;//�¼ӽڵ�
		x->info.link->type = 0;//�Ǹ���ͷ
		x->info.link->ref = 1;//��������һ��

		createlist(input, x->info.link->next_link);//�ݹ齨���ӱ�ͬ�����
		createlist(input, x);
	}

	else if (input_data == ',')
	{
		//��ʱӦ���ǽ��������ڵ�
		createlist(input, x->next_link);
	}

	else if (input_data == '#')
	{
		//��ʱ����Ϊ�ձ�
		x = nullptr;
		input >> input_data;//������DSOJ���Ժ������===================================================
	}

	else if (input_data == ')')
	{
		//˵���ò��Ѿ�������
		x->next_link = nullptr;
	}

	else
	{
		//��ʱ��Ԫ�صĽڵ�
		x = new GRPGenListNode<T>;
		x->type = 1;//data�ڵ�
		x->info.data = input_data;
		createlist(input, x);
	}
	return;
}



template <typename T>
void GRPGenList<T>::remove(GRPGenListNode<T>* it)
{
	--(it->info.ref);//�����ü�1����Ϊֻ�е�����Ϊ0��ʱ�򣬲ſ��Է��ĵ�ɾ�����ͷ���
	if (it->info.ref == 0)//��ʱ�Ϳ���ɾ����
	{
		GRPGenListNode<T> *p(nullptr);
		while (it->next_link != nullptr)//��ͬ�����һ���ڵ����
		{
			p = it->next_link;
			if (p->type == 2)//�����link��
			{
				remove(p->info.link);//�ݹ������½���ɾ��
				if (p->info.link->info.ref <= 0)//��ָ���ͷ���������Ѿ���ȫ
					delete p->info.link;//����ɾ��
			}
			it->next_link = p->next_link;
			delete p;
		}
	}
}



#endif