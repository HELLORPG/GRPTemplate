//#pragma once
#ifndef GRP_DOUNODE
#define GRP_DOUNODE

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::ostream;

template <typename T>
class GRPDouNode
{
protected:
	T data;
	GRPDouNode *previous;
	GRPDouNode *next;
	/*
	GRPDouNode() :data(*(new T)), previous(nullptr), next(nullptr) {}
	GRPDouNode(T data, GRPDouNode *previous) :data(data), previous(previous), next(nullptr) {}
	*/
	GRPDouNode(T data = *(new T), GRPDouNode *previous = nullptr, GRPDouNode *next = nullptr) :data(data), previous(previous), next(next) {}
	~GRPDouNode() {}
};

#endif
