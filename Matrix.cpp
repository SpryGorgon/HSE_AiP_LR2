#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <type_traits>
#include <time.h>
#include <stdio.h>
#include <fstream>

using namespace std;
typedef long long ll;
typedef long double ld;
const int SEED = 1e9 + 7 + 7e7;

template<typename T>
class Matrix
{
private:
	T** data;
public:
	int shape[2];
	Matrix()
	{
		data = nullptr;
		shape = { 0,0 };
	}
	Matrix(int s1)
	{
		init_data(s1, 1);
		shape[0] = s1; shape[1] = 1;
	}
	Matrix(int s1, int s2)
	{
		init_data(s1, s2);
		shape[0] = s1; shape[1] = s2;
	}
	/*Matrix(std::initializer_list<T> list)
	{
		if (list.size() == 0) throw runtime_error("array is empty");
		init_data(list.size(), 1);
		shape[0] = list.size(); shape[1] = 1;
		int i = 0;
		for (T e : list)
		{
			data[i][0] = e;
			i++;
		}
	}

	Matrix(std::initializer_list<std::initializer_list<T>> in)
	{
		if (in.size() == 0) throw runtime_error("array is empty");
		init_data(in.size(), (*in.begin()).size());
		shape[0] = in.size(); shape[1] = (*in.begin()).size();
		int i = 0;
		for (auto list : in) {
			int j = 0;
			for (auto e : list) {
				data[i][j] = e;
				j++;
			}
			i++;
		}
	}*/

	Matrix(const Matrix& other)
	{
		shape[0] = other.shape[0]; shape[1] = other.shape[1];
		init_data(shape[0], shape[1]);
		for (int i = 0; i < shape[0]; i++) for (int j = 0; j < shape[1]; j++) data[i][j] = other.data[i][j];
	}

	void init_data(int s1, int s2)
	{
		T** data = new T * [s1];
		for (int i = 0; i < s1; i++)
		{
			data[i] = new T[s2];
			for (int j = 0; j < s2; j++) data[i][j] = T();
		}
		this->data = data;
	}

	Matrix& operator = (const std::initializer_list<T> list)
	{
		delete[] data;
		init_data(list.size(), 1);
		shape = { list.size(),1 };
		int i = 0;
		for (T e : list)
		{
			data[i][0] = e;
			i++;
		}
		return *this;
	}

	Matrix& operator = (const Matrix& other)
	{
		delete[] data;
		init_data(other.shape[0], other.shape[1]);
		shape[0] = other.shape[0]; shape[1] = other.shape[1];
		for (int i = 0; i < shape[0]; i++) for (int j = 0; j < shape[1]; j++) data[i][j] = other.data[i][j];
		return *this;
	}

	Matrix& operator=(Matrix&& other) {
		if (this != &other) {
			delete[]  data;
			delete[] shape;
			swap(data, other.data);
			swap(shape, other.shape);
		}
		return *this;
	}

	friend ostream& operator << (ostream& os, const Matrix& o)
	{
		os << "[";
		for (int i = 0; i < o.shape[0]; i++)
		{
			os << "[";
			for (int j = 0; j < o.shape[1]; j++)
			{
				os << o(i,j) << (j == (o.shape[1] - 1) ? "]" : ", ");
			}
			os << (i == (o.shape[0] - 1) ? "]" : ",\n");
		}
		return os;
	}
	T& operator () (const int i, const int j)
	{
		if (i<0 || j<0 || i>shape[0] || j>shape[1]) std::cerr << "Out of Range error \n";
		return data[i][j];
	}

	const T& operator () (const int i, const int j) const {
		if (i<0 || j<0 || i>shape[0] || j>shape[1]) std::cerr << "Out of Range error \n";
		return data[i][j];
	}
	Matrix& operator + (const Matrix& other) const
	{
		if (shape[0] != other.shape[0] || shape[1] != other.shape[1]) throw runtime_error("invalid shapes");
		Matrix res(shape[0], shape[1]);
		for (int i = 0; i < shape[0]; i++) for (int j = 0; j < shape[1]; j++) res(i, j) = data[i][j] + other.data[i][j];
		return res;
	}
	Matrix& operator - (const Matrix& other) const
	{
		if (shape[0] != other.shape[0] || shape[1] != other.shape[1]) throw runtime_error("invalid shapes");
		Matrix res(shape[0], shape[1]);
		for (int i = 0; i < shape[0]; i++) for (int j = 0; j < shape[1]; j++) res(i, j) = data[i][j] - other.data[i][j];
		return res;
	}
	Matrix& operator * (const Matrix& other) const
	{
		if (shape[1] != other.shape[0]) throw runtime_error("invalid shapes");
		Matrix res(shape[0], other.shape[1]);
		for (int i = 0; i < shape[0]; i++) for (int j = 0; j < other.shape[1]; j++) for (int k = 0; k < shape[1]; k++) res(i, j) = res(i, j) + data[i][k] * other.data[k][j];
		return res;
	}
	Matrix& operator * (const double other) const
	{
		Matrix res(*this);
		for (int i = 0; i < shape[0]; i++) for (int j = 0; j < shape[1]; j++) res(i, j) = data[i][j] * other;
		return res;
	}
	friend Matrix& operator * (const double a, const Matrix& b)
	{
		return b * a;
	}
	void operator += (const Matrix& other)
	{
		if (shape[0] != other.shape[0] || shape[1] != other.shape[1]) throw runtime_error("invalid shapes");
		for (int i = 0; i < shape[0]; i++) for (int j = 0; j < shape[1]; j++) data[i][j] += other.data[i][j];
	}
	void operator -= (const Matrix& other)
	{
		if (shape[0] != other.shape[0] || shape[1] != other.shape[1]) throw runtime_error("invalid shapes");
		for (int i = 0; i < shape[0]; i++) for (int j = 0; j < shape[1]; j++) data[i][j] -= other.data[i][j];
	}
	void operator *= (const double other)
	{
		for (int i = 0; i < shape[0]; i++) for (int j = 0; j < shape[1]; j++) data[i][j] *= other;
	}
	template < typename NewT >
	operator Matrix< NewT >()
	{
		Matrix< NewT > res(shape[0], shape[1]);
		for (int i = 0; i < shape[0]; i++) for (int j = 0; j < shape[1]; j++) res(i, j) = NewT(data[i][j]);
		return res;
	}

	template< typename NewT >
	Matrix(const Matrix< NewT >& other)
	{
		Matrix res(other.shape[0], other.shape[1]);
		for (int i = 0; i < shape[0]; i++) for (int j = 0; j < shape[1]; j++) res(i, j) = T(other.data[i][j]);
	}

	template < typename NewT >
	Matrix& operator=(const Matrix< NewT >& other)
	{
		for (int i = 0; i < shape[0]; i++) delete[] data[i];
		delete[] data;
		//delete[] shape;
		init_data(other.shape[0], other.shape[1]);
		shape[0] = other.shape[0]; shape[1] = other.shape[1];
		for (int i = 0; i < shape[0]; i++) for (int j = 0; j < shape[1]; j++) data[i][j] = T(other(i,j));
		return *this;
	}
	/*template < typename NewT >
	Matrix(std::initializer_list<NewT> list)
	{
		if (list.size() == 0) throw runtime_error("array is empty");
		init_data(list.size(), 1);
		shape[0] = list.size(); shape[1] = 1;
		int i = 0;
		for (NewT e : list)
		{
			data[i][0] = T(e);
			i++;
		}
	}*/

	template < typename NewT >
	Matrix(std::initializer_list<std::initializer_list<NewT>> in)
	{
		if (in.size() == 0) throw runtime_error("array is empty");
		init_data(in.size(), (*in.begin()).size());
		shape[0] = in.size(); shape[1] = (*in.begin()).size();
		int i = 0;
		for (auto list : in) {
			int j = 0;
			for (auto e : list) {
				data[i][j] = T(e);
				j++;
			}
			i++;
		}
	}
};

//Matrix::operator int() { return Matrix<int>(*this); }


//template <typename other>
//operator Matrix<other>()
//{
//	Matrix<other> res(shape[0], shape[1]);
//	for (int i = 0; i < shape[0]; i++) for (int j = 0; j < shape[1]; j++) res(i, j) = (other)data[i][j];
//	return res;
//}

using MyType = int;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	Matrix<MyType> m1(4); // матрица вида: 4 строки и 1 столбец
	Matrix<MyType> m2(4, 6); // матрица вида: 4 строки и 6 столбцов
	Matrix<int> m5 = { { {1, 2, 3}, {4, 5, 6} } };
	Matrix<int> m6 = { { {1, 2, 3, 4, 5, 6} } };
	Matrix<int> m7 = { { 1,2,3,4,5,6 } };
	Matrix<int> m8 = { { {1},{2},{3},{4},{5},{6} } };

	// Конструктор копирования:
	Matrix<MyType> m3(m1);

	// Оператор приваивания:
	m1 = m2;

	// Перемещающий конструктор
	Matrix<MyType> m4(std::move(m2));

	Matrix<int> m = { { {1, 2, 3}, {4, 5, 6} } };
	int val = m(0, 2); // =&gt; 3 т.к. это 1-ая строка, 3-ий элемент
	m(0, 2) = 7; // теперь 1-ая строка, 3-ий элемент стал равен 7

	// int список инициализации в double матрицу
	Matrix<double> m_d = { {1, 2}, {3, 4}, {5, 6} };
	// double список инициализации в int матрицу
	Matrix<int> m_i = { {1.1, 2.2, 3.3}, {4.4, 5.5, 6.6} };
	// инициализация short матрицы с помощью double матрицы
	Matrix<short> m_s = m_d;
	// присваивание int матрицы в short матрицу
	m_s = m_i;
	// Арифметические операции между матрицами с разными типами:
	m_s += m_i;
	m_s -= m_i;
	m_s *= 3.14;
	m_s + m_i - m_s;
	m_d* m_i;
	m_d * 0;
	3.14 * m_i;
}