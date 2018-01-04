#pragma warning(disable : 4996)
#include <iostream>
#include "TStack.h"
#include "cstring"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

TStack::TStack(int _MemSize)
{
	Top = -1;
	if (_MemSize <= 0) _MemSize = 10;
	MemSize = _MemSize;
	pMem = new double[MemSize];
}

TStack::~TStack()
{
	delete[]pMem;
	pMem = NULL;
}

void TStack::InsertElem(double n)
{
	Top++;
	pMem[Top] = n;
}

double TStack::DeleteElem()
{
	return (pMem[Top--]);
}

int TStack::CheckOfEmpty() const
{
	return (Top == -1);
}

int TStack::CheckOfFully() const
{
	return (Top == (MemSize - 1));
}