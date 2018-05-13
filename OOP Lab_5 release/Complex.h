#pragma once
#ifndef __MYCOMPLEX_H
#define __MYCOMPLEX_H
#include <iostream>
#include <math.h>
#include <conio.h> 
#include <fstream>
#include <cassert>  
using namespace std;

//char* Error_Res = "Переполнение при вычислении выражения !!!!!";

//char* DelNULL = "Деление на 0!! ";
class Complex
{
private:
	long double re, im;
public:
	Complex randComplex();
	Complex() { re = 0; im = 0; }
	Complex(double a);
	Complex(double r, double i) { re = r; im = i; }
	Complex(const Complex &ob) { re = ob.re; im = ob.im; };
	Complex& operator = (Complex);
	Complex operator + (Complex);
	Complex operator - (Complex);
	Complex operator * (Complex&);
	Complex operator *(const double a);
	Complex operator / (Complex&);
	Complex operator / (const double a);
	Complex & operator+=(Complex a);
	//	Complex& operator += (Complex);
	Complex operator + (const double a);
	Complex& operator -= (Complex);
	Complex operator - (const double a);
	Complex& operator *= (Complex);
	Complex& operator /=(Complex);
	friend std::istream& operator >>(std::istream&, Complex&);
	friend std::ostream& operator << (std::ostream&, const Complex&);
	bool operator == (Complex& com);
	bool operator == (const int a);
	bool operator != (Complex& com);
	bool operator > (Complex& com);
	bool operator > (const double com);
	bool operator < (Complex& com);
};
#endif