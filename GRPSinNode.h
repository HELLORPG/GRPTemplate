//#pragma once
#ifndef GRP_SinNode
#define GRP_SinNode

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::ostream;

template <typename T>
class GRPSinNode
{
protected:
	T data;
	GRPSinNode *next;
	GRPSinNode() :data(*(new T)), next(nullptr) {}
	GRPSinNode(T data) :data(data), next(nullptr) {}
	GRPSinNode(T data, GRPSinNode *next) :data(data), next(next) {}
	~GRPSinNode() {}
};

#endif
