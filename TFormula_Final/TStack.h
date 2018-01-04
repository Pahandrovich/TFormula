
#pragma once
#pragma warning(disable : 4996)
#ifndef TSTACK_H
#define TSTACK_H

#include <iostream>
#include "cstring"

using namespace std;

class TStack
{
private:
	double *pMem;
	int MemSize;
	int Top;
public:
	TStack(int _MemSize = 10);
	~TStack();
	void InsertElem(double n);
	double DeleteElem();
	int CheckOfEmpty() const;
	int CheckOfFully() const;
};

#endif
