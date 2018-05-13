#include "Complex.h"

char* DelNULLL = "Деление на 0!! ";
char* Error_Ress = "Переполнение при вычислении выражения !!!!!";

bool Complex:: operator > (Complex& com)
{
	if (this->re > com.re)
		return 1;
	else if (this->re == com.re && this->im > com.im)
		return 1;
	else
		return 0;
}

bool Complex::operator>(const double com)
{
	if (this->re > com) return true;
	return false;
}

bool Complex ::operator < (Complex& com)
{
	if (this->re < com.re)
		return 1;
	else if (this->re == com.re && this->im < com.im)
		return 1;
	else
		return 0;

}

bool Complex::operator != (Complex& com)
{
	if (this->re != com.re || this->im != com.im)
		return 1;
	else
		return 0;
}

bool Complex::operator==(Complex& com)
{
	if (this->re == com.re && this->im == com.im)
		return 1;
	else
		return 0;
}

bool Complex::operator==(const int a)
{
	if (re*re + im * im == 0 || re * re + im * im == 0)
		return 1;
	return false;
}


Complex Complex::operator*(Complex &com)
{
	double i, j;
	i = re * com.re - im * com.im;
	j = re * com.im + com.re * im;
	re = i;
	im = j;
	return *this;
}

Complex Complex::operator*(const double a)
{
	long double k1 = re * a, k2 = im * a;
	if (k1 > DBL_MAX || k1<-DBL_MAX || k2>DBL_MAX || k2 < -DBL_MAX)
	{
		re = DBL_MIN;
		im = DBL_MIN;
		return *this;
	}
	re *= a;
	im *= a;
	return *this;
}

Complex Complex::operator/(Complex &com)
{
	long double i = LDBL_MAX, j = LDBL_MAX;
	long double k1 = (com.re*com.re + com.im*com.im);
	if (k1 == 0.) {
		re = DBL_MIN;
		im = DBL_MIN;
		return *this;
	}
	i = ((re*com.re) + (im*com.im)) / k1;
	long double k2 = (com.re*com.re + com.im*com.im);
	if (k2 == 0.) {
		re = DBL_MIN;
		im = DBL_MIN;
		return *this;
	}
	j = (com.re*im - re*com.im) / k2;
	if (i > DBL_MAX || i<-DBL_MAX || j>DBL_MAX || j < -DBL_MAX) {
		re = DBL_MIN;
		im = DBL_MIN;
		return *this;
	}
	re = i;
	im = j;
	return *this;
}

Complex Complex::operator/(const double a)
{
	re /= a;
	im /= a;
	return *this;
}

Complex Complex::randComplex()
{
	double p1 = (double)(rand()) / RAND_MAX * 2000 - 1000;
	double p2 = (double)(rand()) / RAND_MAX * 2000 - 1000;
	Complex a(p1, p2);
	return a;
}

Complex::Complex(double a)
{
	re = a;
	im = (double)(rand()) / RAND_MAX * 2000 - 1000;
}

Complex& Complex::operator =(Complex com)
{
	this->re = com.re;
	this->im = com.im;
	return *this;
}

Complex Complex::operator+(Complex com)
{
	this->re = this->re + com.re;
	this->im = this->im + com.im;
	return *this;
}

Complex Complex::operator-(Complex com)
{
	this->re = this->re - com.re;
	this->im = this->im - com.im;
	return *this;
}


std::ostream& operator << (std::ostream& out, const Complex& com)
{
	if (com.im < 0)
		out << com.re << "+i(" << com.im << ")";
	else
		out << com.re << "+i" << com.im;
	return out;
}

std::istream& operator >> (std::istream& in, Complex& com)
{
	std::cout << "Введите через пробел действительную и мнимую части: ";
	in >> com.re >> com.im;
	return in;
}

Complex& Complex::operator+=(Complex a)
{
	re += a.re;
	im += a.im;
	return *this;
}

Complex Complex::operator+(const double a)
{
	long double k = re + a;
	if (k > DBL_MAX) {
		re = DBL_MIN;
		im = DBL_MIN;
		return *this;
	}
	re += a;
	return *this;
}


Complex& Complex::operator-=(Complex a)
{
	re -= a.re;
	im -= a.im;
	return *this;
}

Complex Complex::operator-(const double a)
{
	long double k = re - a;
	if (k < -DBL_MAX) {
		re = DBL_MIN;
		im = DBL_MIN;
		return *this;
	}
	re -= a;
	return *this;
}

Complex& Complex::operator*=(Complex a)
{
	re *= a.re;
	im *= a.im;
	return *this;
}

Complex& Complex::operator/=(Complex a)
{
	re /= a.re;
	im /= a.im;
	return *this;
}
