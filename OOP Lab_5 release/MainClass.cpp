#include <iostream>
#include <cstdio>
#include <conio.h>
#include <stdlib.h>
#include <complex>
#include "MyClass.h"
#include "Complex.h"
#include <fstream>
#include <iomanip>
#include <time.h>


using namespace std;

char* Ch_mas_msg = "�������� ��� �������:\n1.Int\n2.double\n3.MyComplex";
char* Ch_sz_msg = "������� ������ ������� �";
char* Ch_el_msg = "������� �������� ������� �";
char* Continue = "��� �� ��������� ������� ����� ������. ��� ������ ������� ESC";
int inputVal() {
	int k;
	while (true) {
		cin >> k;
		if ((!cin || cin.peek() != '\n') || k<1) {
			cout << "���������� �� ����� ��������� ��� �������. ��� ��������� ������������." << endl;
			cin.clear();
			while (cin.get() != '\n');
		}
		else break;
	}
	return k;
}

template<class T>
void inputArray(int n, T& arr) {
	if (n <= 10) {
		cin >> arr;
	}
	else {
		arr.arrRand(arr);
	}

}

template<class A>
void task(A arr1, A arr2, A res) {
	try {
		cout << Ch_el_msg << 1 << endl;
		inputArray(arr1.getSize(), arr1);
		cout << Ch_el_msg << 2 << endl;
		inputArray(arr2.getSize(), arr2);
		cout << "������ ������ (a): " << arr1 << endl;
		cout << "������ ������ (b): " << arr2 << endl;
		if (arr1 > arr2) {
#ifdef _DEBUG
			cout << "\n						array1 > array2\n " << endl;

#endif
			res = (arr2 + 2) / arr1;
			cout << "���������: " << "y=(2+b)/a :" << res << endl;
		}
		else if (arr1 < arr2) {
#ifdef _DEBUG
			cout << "\n						array1 < array2\n " << endl;
#endif
			res = (arr1 - 125) / arr2;
			cout << "���������: " << "y=(a-125)/b :" << res << endl;
		}
		else if (arr1 == arr2) {

#ifdef _DEBUG
			cout << "\n						array1 == array2\n" << endl;
#endif
			res = -4;
			cout << "���������: " << "y = -4 " << res << endl;
		}
	}
	catch (char* v) // ���������� ���� char* �� ��������� v
	{
		cout << "\n!!! ��������� �������������� ��������. !!!" << endl;
		cout << "������: " << v;
	}
	catch (...) // ���������� ���������� - �������� ���� ����������
	{
		cout << "\n!!! ��������� ����������������� �������������� ��������. !!!" << endl;
		throw;
	}
	cout << Continue << endl;
}

void start() {
	cout << Ch_mas_msg << endl;
	int c = inputVal();
	cout << Ch_sz_msg << 1 << endl;
	int n1 = inputVal();
	cout << Ch_sz_msg << 2 << endl;
	int n2 = inputVal();
	int n3 = (n1 + n2) / 2;

	switch (c)
	{
	case 1: {
		Array<int> arr1(n1);
		Array<int> arr2(n2);
		Array<int> res(n3);
		task(arr1, arr2, res);
		break;
	}
	case 2: {
		Array<double> arr1(n1);
		Array<double> arr2(n2);
		Array<double> res(n3);
		task(arr1, arr2, res);
		break;
	}
	case 3: {
		Array<Complex> arr1(n1);
		Array<Complex> arr2(n2);
		Array<Complex> res(n3);
		task(arr1, arr2, res);
		break;
	}

	default:
		cout << "\n������ �������� ���! �������� ���� �� ���������!" << endl;
		start();
		break;
	}
}

int main()
{
	int ESC = 27;
	setlocale(LC_ALL, "Russian");
	cout << setprecision(3);
	fixed;
	srand((unsigned)time(NULL));
	do {
		cout << " ��������� ������� 8:" << endl;
		cout << "      | (2+b)/a,    ���� a>b" << endl;
		cout << " X =  { -4,         ���� a=b" << endl;
		cout << "      | (a-125)/b,  ���� a<b" << endl;
		start();
	} while (_getch() != ESC);
	return 0;
}