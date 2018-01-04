#pragma warning(disable : 4996)
#include <iostream>
#include "TStack.h"
#include "TFormula.h"
#include "cstring"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

TFormula::TFormula(char *_Formula)
{
	strcpy(Formula, _Formula);
	strcpy(PostfixForm, "");
}
TFormula::~TFormula()
{
	delete[] Formula;
	delete[] PostfixForm;
}

int TFormula::CheckOfError(int *mas, int &sizemas)
{
	TStack stack(MAX);
	int index = 1, countEr = 0, len;
	sizemas = 0;
	len = strlen(Formula);
	for (int i = 0; i < len; i++)
	{
		if (Formula[i] == '(')
		{
			stack.InsertElem(index++);
		}
		else
		{
			if (Formula[i] == ')')
			{
				if (!(stack.CheckOfEmpty()))
				{
					mas[sizemas++] = stack.DeleteElem();
				}
				else
				{
					mas[sizemas++] = 0;
					countEr++;
				}
				mas[sizemas++] = index++;
			}
		}
	}
	while (!(stack.CheckOfEmpty()))
	{
		countEr++;
		mas[sizemas++] = stack.DeleteElem();
		mas[sizemas++] = 0;
	}
	return countEr;
}

int TFormula::CheckOperation(char c)
{
	int res = 0;
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')': res = 1;
		break;
	}
	return res;
}

int TFormula::PriorityOp(char c)
{
	int res;
	switch (c)
	{
	case '(': { res = 0; break; }
	case ')': { res = 1; break; }
	case '+': { res = 2; break; }
	case '-': { res = 2; break; }
	case '*': { res = 3; break; }
	case '/': { res = 3; break; }
			  break;
	}
	return res;
}

char* TFormula::ConvertForm()
{
	TStack stack(MAX);
	int i, plen = 0, prior, lenStrOfNum = 0;;
	int len = strlen(Formula);
	char tmp;
	char StrOfNum[MAX] = "";
	for (i = 0; i < len; i++)
	{
		if (!(CheckOperation(Formula[i])))
		{
			PostfixForm[plen++] = Formula[i];
		}
		else
		{
			if (((Formula[i] == '-') || (Formula[i] == '+')) && ((i == 0) || (Formula[i - 1] == '(')))
			{
				PostfixForm[plen++] = ' ';
				PostfixForm[plen++] = '0';
				PostfixForm[plen++] = ' ';
			}
			PostfixForm[plen++] = ' ';
			if (stack.CheckOfEmpty())
				stack.InsertElem(Formula[i]);
			else
			{
				prior = PriorityOp(Formula[i]);
				if (!prior)
					stack.InsertElem(Formula[i]);
				else
				{
					tmp = stack.DeleteElem();
					if (prior > PriorityOp(tmp))
					{
						stack.InsertElem(tmp);
						stack.InsertElem(Formula[i]);
					}
					else
					{
						if (Formula[i] != ')')
						{
							PostfixForm[plen++] = tmp;
							PostfixForm[plen++] = ' ';
							do
							{
								if (!(stack.CheckOfEmpty()))
								{
									tmp = stack.DeleteElem();
									if (prior <= PriorityOp(tmp))
									{
										PostfixForm[plen++] = tmp;
										PostfixForm[plen++] = ' ';
									}
									else
									{
										stack.InsertElem(tmp);
										break;
									}
								}
								else break;
							} while (true);
							stack.InsertElem(Formula[i]);
						}
						else
						{
							if (tmp != '(')
							{
								PostfixForm[plen++] = tmp;
								PostfixForm[plen++] = ' ';
								while (true)
								{
									tmp = stack.DeleteElem();
									if (tmp == '(')
										break;
									else
									{
										PostfixForm[plen++] = tmp;
										PostfixForm[plen++] = ' ';
									}
								}
							}
						}
					}
				}
			}
		}
	}
	PostfixForm[plen++] = ' ';
	while (!stack.CheckOfEmpty())
	{
		PostfixForm[plen++] = stack.DeleteElem();
		PostfixForm[plen++] = ' ';
	}
	PostfixForm[plen] = '\0';
	return PostfixForm;
}

double TFormula::CalculationOp(char c, double op1, double op2)
{
	double res;
	switch (c)
	{
	case '+': { res = op1 + op2; break; }
	case '-': { res = op1 - op2; break; }
	case '*': { res = op1 * op2; break; }
	case '/': { res = op1 / op2; break; }
			  break;
	}
	return res;
}

double TFormula::CalculationFormula()
{
	TStack stack(MAX);
	double op1, op2, res;
	int i, len, CheckOfErrorFLAG = 0;
	char StrOfNum[MAX] = "";
	int lenStrOfNum = 0;
	len = strlen(PostfixForm);
	for (i = 0; (i < len) && (CheckOfErrorFLAG == 0); i++)
	{
		while (PostfixForm[i] == ' ' && i < len) i++;
		if (i >= len) break;
		if (PostfixForm[i] != '(' && PostfixForm[i] != ')')
		{
			if (!(CheckOperation(PostfixForm[i])))
			{
				while (PostfixForm[i] >= '0' && PostfixForm[i] <= '9')
				{
					StrOfNum[lenStrOfNum++] = PostfixForm[i];
					i++;
				}
				StrOfNum[lenStrOfNum] = '\0';
				stack.InsertElem(atof(StrOfNum));
				strcpy(StrOfNum, "");
				lenStrOfNum = 0;
			}
			else
			{
				if (!stack.CheckOfEmpty())
				{
					op2 = stack.DeleteElem();
					if (!stack.CheckOfEmpty())
					{
						op1 = stack.DeleteElem();
						if (PostfixForm[i] == '/' && op2 == 0)
							CheckOfErrorFLAG = 1;
						else
							stack.InsertElem(CalculationOp(PostfixForm[i], op1, op2));
					}
					else
					{
						CheckOfErrorFLAG = 1;
					}
				}
				else
				{
					CheckOfErrorFLAG = 1;
				}
			}
		}
		else
		{
			CheckOfErrorFLAG = 1;
			break;
		}
	}
	if ((!stack.CheckOfEmpty()) && !CheckOfErrorFLAG)
		res = stack.DeleteElem();
	else
	{
		cout << "Fatal Error :(" << endl;
		res = 0;
	}
	return res;
}