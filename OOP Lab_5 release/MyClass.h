#pragma once
#ifndef __MYCLASS_H
#define __MYCLASS_H
#include <iostream>
#include <math.h>
#include <conio.h> 
#include <fstream>
#include <complex>
#include <cassert>  
using namespace std;

char* Error_Res = "Переполнение при вычислении выражения !!!!!";

char* DelNULL = "Деление на 0!! ";
char* Next_Num = "Данное число пропущенно :";
// Класс для вычисления арифметического выражения
template <class T>
class Array
{
	friend ostream &operator<<(ostream &output, const Array &a) {
		int i;
		for (i = 0; i < a.size; i++) {
			output << a.ptr[i] << "\t";
		}
		if ((i + 1) % 10 == 0) output << endl;
		return output;
	}
	friend istream &operator>>(istream &is, Array &a) {
		cout << "Введите " << a.getSize() << " элемент(ов) массива типа " << typeid(a.ptr[0]).name() << ":" << endl;

		for (int i = 0; i < a.size; i++)
			a.inputElem(a.ptr[i], is);
		return is;
	}



private:
	T *ptr;
	int size;
public:
	//T * ptr;
	//int size;
	T & operator[] (int i) {
		//assert(0 <= i && i < size);
		return ptr[i];
	}

	Array(int arraySize) {
		size = arraySize;
		ptr = new T[size];
		assert(ptr != 0);
		for (int i = 0; i < size; i++) ptr[i] = 0;
	}
	Array(const Array &init) {
		size = init.size;
		ptr = new T[size];
		assert(ptr != 0);
		for (int i = 0; i < size; i++) ptr[i] = init.ptr[i];
	}
	~Array() {
		if (size == 1) delete ptr;
		else delete[] ptr;
	}

	const Array &operator = (const Array &a) {
		Array x(*this);
		if (&a != this) {
			delete[] ptr;
			size = a.size;
			ptr = new T[size];
			assert(ptr != 0);
			for (int i = 0; i < size; i++) {
				ptr[i] = a.ptr[i];
			}
			return *this;
		}
	}
	Array operator=(const int a) {
		for (int i = 0; i < size; i++) {
			ptr[i] = a;
		}
		return *this;
	}

	Array operator+(const double b) {
#ifdef _DEBUG
		cout << "b/a + " << b << ": ";
#endif
		Array x(*this);
		int count = 0;
		for (int i = 0, k = 0; i < size; i++, k++) {
			if (typeid(int) == typeid(T) || typeid(double) == typeid(T) || typeid(float) == typeid(T))
				if (x[i] + b > numeric_limits<T>::max()) {
					k--;
					cout << "\nПревышен диапазон" << endl;
					continue;
				}
			x[k] = x[i] + b;
			if (typeid(T) == typeid(Complex) && x[k] == (DBL_MIN, DBL_MIN)) {
				k--;
				cout << "\nПревышен диапазон" << endl;
				continue;
			}
			count++;
		}
		if (count == 0)
			throw Error_Res;
		if (count < x.getSize()) {
			Array newArr(count);
			for (int i = 0; i < count; i++) {
				newArr[i] = x[i];
			}
#ifdef _DEBUG
			cout << newArr << endl;
#endif
			return newArr;
		}
		else {
#ifdef _DEBUG
			cout << x << endl;
#endif
			return x;
		}
	}

	Array operator-(const double b) {
#ifdef _DEBUG
		cout << "a*2 - 5: ";
#endif
		Array x(*this);
		int count = 0;
		for (int i = 0, k = 0; i < size; i++, k++) {
			if (typeid(int) == typeid(T) || typeid(double) == typeid(T) || typeid(float) == typeid(T))
				if (x[i] - b < numeric_limits<T>::min()) {
					k--;
					cout << "\nПревышен диапазон" << endl;
					continue;
				}
			x[k] = x[i] - b;
			if (typeid(T) == typeid(Complex) && x[k] == (DBL_MIN, DBL_MIN)) {
				k--;
				cout << "\nПревышен диапазон" << endl;
				continue;
			}
			count++;
		}
		if (count == 0)
			throw Error_Res;
		if (count < x.getSize()) {
			Array newArr(count);
			for (int i = 0; i < count; i++) {
				newArr[i] = x[i];
			}
#ifdef _DEBUG
			cout << newArr << endl;
#endif
			return newArr;
		}
		else {
#ifdef _DEBUG
			cout << x << endl;
#endif
			return x;
		}
	}
	int operator==(const Array &a) const {
		if (size == 1 && a.size == 1) return *ptr == *a.ptr;
		if (size != a.size) return 0;
		for (int i = 0; i < size; i++) {
			if (ptr[i] != a.ptr[i]) return 0;
		}
		return 1;
	}
	Array<T> operator/(const Array &a) {
		int count = 0;
		if (typeid(T) != typeid(Complex))
			for (int i = 0; i<a.size; i++) {
				if (a.ptr[i] == 0) {
					count++;
				}
			}
		if (a.getSize() == count)
			throw DelNULL;
		int size_x = (size + (a.size - count)) / 2;
		Array<T> x(size_x);
		for (int i = 0, j = 0, k = 0; k < size_x && j<size_x; i++, j++, k++) {
			if (i == size) i = 0;
			if (j == a.size) j = 0;
			if (typeid(T) != typeid(Complex) && a.ptr[j] == 0) {
				i--;
				k--;
				cout << "\nДеление на 0!" << endl;
				continue;
			}
			x[k] = ptr[i] / a.ptr[j];
			if (typeid(T) == typeid(Complex) && x[k] == (DBL_MAX, DBL_MAX)) {
				i--;
				k--;
				cout << "\nДеление на 0!" << endl;
				continue;
			}
		}
#ifdef _DEBUG
		cout << x << endl;
#endif
		return x;
	}
	Array operator*(const double b) {
#ifdef _DEBUG
		cout << "a * 2: ";
#endif
		Array x(*this);
		int count = 0;
		for (int i = 0, k = 0; i < size; i++, k++) {
			if (typeid(T) == typeid(int) || typeid(T) == typeid(double) || typeid(T) == typeid(float)) {
				if (x[i] * b > numeric_limits<T>::max() || x[i] * b < numeric_limits<T>::min()) {
					k--;
					cout << "\nПревышен диапазон" << endl;
					continue;
				}
			}
			x[k] = x[i] * b;
			if (typeid(T) == typeid(Complex) && x[k] == (DBL_MIN, DBL_MIN)) {
				k--;
				cout << "\nПревышен диапазон" << endl;
				continue;
			}
			count++;
		}
		if (count == 0)
			throw Error_Res;
		if (count < x.getSize()) {
			Array newArr(count);
			for (int i = 0; i < count; i++) {
				newArr[i] = x[i];
			}
#ifdef _DEBUG
			cout << newArr << endl;
#endif
			return newArr;
		}
		else {
#ifdef _DEBUG
			cout << x << endl;
#endif
			return x;
		}
	}
	int operator>(const Array &a) const {
		if (size == 1 && a.size == 1) return *ptr > *a.ptr;
		T sum1 = 0, sum2 = 0;
		if (size > a.size) return 1;
		else if (size == a.size) {
			for (int i = 0; i < size; i++) { sum1 += ptr[i] * (i + 1) / 10; sum1 /= 10; }
			for (int i = 0; i < a.size; i++) { sum2 += a.ptr[i] * (i + 1) / 10; sum2 /= 10; }
			return sum1 > sum2;
		}
		return 0;
	}

	int operator<(const Array &a) const {
		if (size == 1 && a.size == 1) return *ptr < *a.ptr;

		T sum1 = 0, sum2 = 0;
		if (size < a.size) return 1;
		else if (size == a.size) {
			for (int i = 0; i < size; i++) { sum1 += (ptr[i] * (i + 1) / 10); }
			for (int i = 0; i < a.size; i++) { sum2 += (a.ptr[i] * (i + 1) / 10); }
			return sum1 < sum2;
		}
		return 0;
	}

	void arrRand(Array &a) {
		for (int i = 0; i < a.size; i++) {
			if (typeid(T) == typeid(int))
				a[i] = (rand() % 2000 - 1000);
			else if (typeid(T) == typeid(float))
				a[i] = (float)(rand()) / RAND_MAX * 2000 - 1000;
			else {
				a[i] = (double)(rand()) / RAND_MAX * 2000 - 1000;
			}

		}
	}
	int getSize() const {
		return size;
	}
	void inputElem(T &k, istream &is) {
		while (true) {
			is >> k;
			if (!is || is.peek() != '\n') {
				cout << "Переменная не может содержать эти символы. Или произошло переполнение." << endl;
				is.clear();
				while (is.get() != '\n');
			}
			else break;
		}
	}


};
#endif /* __MYCLASS_H */
