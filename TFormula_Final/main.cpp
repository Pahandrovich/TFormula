#pragma warning(disable : 4996)
#include <iostream>
#include "TStack.h"
#include "TFormula.h"
#include "cstring"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

int main()
{
	char str[MAX], str2[MAX], c;
	cout << "Enter expression: ";
	fgets(str, MAX, stdin);
	str[strlen(str) - 1] = '\0';
	TFormula F1(str);
	int sizemas = 0, Errors;
	int mas[MAX];
	int i;
	for (i = 0; i < MAX; i++)
		mas[i] = -1;
	Errors = F1.CheckOfError(mas, sizemas);
	cout << "Check for brackets: " << Errors << " errors" << endl;
	i = 0;
	while (mas[i] != -1)
	{
		cout << "parenthesis " << mas[i] << " corresponds to parenthesis " << mas[i + 1] << endl;
		i += 2;
	}
	if (!Errors) cout << "postfix: " << F1.ConvertForm() << endl;
	else F1.ConvertForm();
	cout << "Result of calculation : " << F1.CalculationFormula() << endl;

	system("pause");
	return 0;
}