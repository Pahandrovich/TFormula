#pragma once
#pragma warning(disable : 4996)
#ifndef TFORMULA_H
#define TFORMULA_H

#include <iostream>
#include "TStack.h"
#include "cstring"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

const int MAX = 255;

class TFormula
{
	char Formula[MAX];
	char PostfixForm[MAX];
	int CheckOperation(char c);
	int PriorityOp(char c);
	double CalculationOp(char c, double op1, double op2);
public:
	TFormula(char *_Formula);
	~TFormula();
	int CheckOfError(int *mas, int &sizemas);
	char* ConvertForm();
	double CalculationFormula();
};
#endif
