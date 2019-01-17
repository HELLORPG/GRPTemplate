//#pragma once
#ifndef GRP_VECTOR
#define GRP_VECTOR

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;



#define GRP_VECTOR_DEFAULTSIZE 1 //��Ĭ�ϳ��ȸ���Ϊ1��ģ��

template <typename T>
class GRPVector
{
protected:
	T *data;
	size_t max_size;
	size_t real_size;
public:
	GRPVector();
	GRPVector(const GRPVector &x);
	~GRPVector();

	void push_back(const T &input);
	void pop_back();
	size_t size() const;
	bool empty() const;
	void clear();

	const T front();
	T& back();
	T& operator[](int i);
	const T& operator[](int i) const;

	void insert(int i, const T &add);
	void erase(int i);

	int find(T which) const;//Ѱ��ĳԪ�أ�������������

	GRPVector& operator=(const GRPVector& copy);
};

template <typename T>
GRPVector<T>::GRPVector() : data(new T[GRP_VECTOR_DEFAULTSIZE]), max_size(GRP_VECTOR_DEFAULTSIZE), real_size(0) {}

template <typename T>
GRPVector<T>::~GRPVector()
{
	delete[] data;//����̬����黹
	//��������̬������Զ��黹
}


template <typename T>
size_t GRPVector<T>::size() const
{
	return real_size;
}

template <typename T>
bool GRPVector<T>::empty() const
{
	return real_size == 0;
}

template <typename T>
void GRPVector<T>::clear()
{
	real_size = 0;
	return;
}



template <typename T>
void GRPVector<T>::push_back(const T &input)
{
	if (real_size == max_size)
	{
		T *old = data;
		data = new T[2 * max_size];//��һ������һ��������
		for (size_t i(0); i < max_size; ++i)
		{
			data[i] = old[i];
		}
		max_size *= 2;//�����ݷ���
		//cout << old[0] << endl;
		delete[] old; //�����ӣ����ɿռ�黹		
	}
	//�����費��Ҫ���ݣ������Ĺ�����һ����
	data[real_size] = input;
	++real_size;
	return;
}

template <typename T>
void GRPVector<T>::pop_back()
{
	//�����û�д�����ɿ����Զ����ٳ��ȵĹ���
	--real_size;//ֱ�ӽ����ı�ʶ��ǰ���ɣ������ӾͿ��Ա������
	return;
}

template <typename T>
T& GRPVector<T>::operator[](int i)
{
	//cout << -static_cast<int>(real_size) << endl;
	//cout << (i >= -static_cast<int>(real_size)) << endl;
	if ((i < static_cast<int>(real_size)) && (i >= -static_cast<int>(real_size)))
	{
		if (i >= 0)
			return data[i];
		else
			return data[this->size() + i];
	}

	else
	{
		cout << "This GRPVector's size is " << real_size << endl;
		cout << "You should not read the place [" << i << "]" << endl;
		exit(-1);
	}
}

template <typename T>
const T& GRPVector<T>::operator[](int i) const
{
	if ((i < static_cast<int>(real_size)) && (i >= -static_cast<int>(real_size)))
	{
		if (i >= 0)
			return data[i];
		else
			return data[this->size() + i];
	}

	else
	{
		cout << "This GRPVector's size is " << real_size << endl;
		cout << "You should not read the place [" << i << "]" << endl;
		exit(-1);
	}
}


template <typename T>
const T GRPVector<T>::front()
{
	T x = data[0];
	//return (*this)[0];
	return x;
}

template <typename T>
T& GRPVector<T>::back()
{
	return (*this)[this->size() - 1];
}

template <typename T>
void GRPVector<T>::insert(int i, const T& add)
{
	if (i < real_size)
	{
		this->push_back(this->back());//�����һλ�����������һ�Σ�����չ
		//++real_size;
		for (int j(i); j < real_size - 1; ++j)
		{
			(*this)[j + 1] = (*this)[j];
		}
		(*this)[i] = add;
	}
	else
	{
		cout << "GRPVector���ܳ���Ϊ" << real_size << "��������[" << i << "]������Ԫ��" << endl;
	}
	return;
}

template <typename T>
void GRPVector<T>::erase(int i)
{
	if (i < real_size)
	{
		for (int j(i); j < real_size - 1; ++j)
		{
			//(*this)[j] = (*this)[j + 1];
			data[j] = data[j + 1]; //2019.1.16 UPDATE ���ٺ����ĵ��ÿ��Լӿ�һ���������ٶȣ����Ǹ��ӻ��˴���
		}
		this->pop_back();
		//--real_size; //2019.1.16 DEBUG �˴�Ӧ�ø��Ĵ�С��ͬ��
	}
	else
	{
		cout << "GRPVector���ܳ���Ϊ" << real_size << "��������ɾ��[" << i << "]Ԫ��" << endl;
	}
	return;
}


template <typename T>
int GRPVector<T>::find(T which) const
{
	for (int i(0); i < real_size; ++i)
	{
		if (data[i] == which)
			return i;
	}
	return -1;//��Ϊ�޴�Ԫ�صı�־
}



template <typename T>
GRPVector<T>& GRPVector<T>::operator=(const GRPVector& copy)
{
	this->clear();
	this->data = new T[copy.max_size];
	for (int i(0); i < copy.size(); ++i)
	{
		//this->push_back(copy[i]);
		this->data[i] = copy.data[i];
	}
	this->real_size = copy.real_size;
	this->max_size = copy.max_size;
	return *this;
}

template <typename T>
GRPVector<T>::GRPVector(const GRPVector& x)
{
	/*this->clear();
	for (int i(0); i < x.size(); ++i)
	{
		this->push_back(x[i]);
	}*/
	this->data = new T[x.max_size];
	for (int i(0); i < x.size(); ++i)
	{
		//this->push_back(copy[i]);
		this->data[i] = x.data[i];
	}
	this->real_size = x.real_size;
	this->max_size = x.max_size;
	//return *this;
	//return *this;
}

#endif
