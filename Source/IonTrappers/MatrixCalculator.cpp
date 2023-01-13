/** @file */
#include "MatrixCalculator.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <random>
#include <ctime>
#include <vector>
MatrixCalculator::MatrixCalculator()
{
	m = 0;
	x = y = c_x = c_y = 0;

}

MatrixCalculator::MatrixCalculator(int a, int b)
{
	y = a;
	x = b;
	c_x = x;
	c_y = y;
	m = new std::complex<double>*[y];
	for (int i = 0; i < y; i++)
		m[i] = new std::complex<double>[x];
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			m[i][j] = 0;
}

MatrixCalculator::MatrixCalculator(int a, int b, std::complex<double>** tab)
{
	y = a;
	x = b;
	c_x = x;
	c_y = y;
	m = new std::complex<double>*[y];
	for (int i = 0; i < y; i++)
		m[i] = new std::complex<double>[x];
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			m[i][j] = tab[i][j];
}

MatrixCalculator::MatrixCalculator(int a, int b, std::vector<std::vector<std::complex<double>>> tab)
{
	y = a;
	x = b;
	c_x = x;
	c_y = y;
	m = new std::complex<double>*[y];
	for (int i = 0; i < y; i++)
		m[i] = new std::complex<double>[x];
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			m[i][j] = tab[i][j];
}

MatrixCalculator::MatrixCalculator(MatrixCalculator& A)
{
	if (this != &A)
	{
		int y_ = A.size_y();
		int x_ = A.size_x();
		std::complex<double>** tmp = new std::complex<double>*[y_];
		for (int i = 0; i < y_; i++)
			tmp[i] = new std::complex<double>[x_];

		for (int i = 0; i < y_; i++)
			for (int j = 0; j < x_; j++)
			{
				(tmp[i][j]) = std::complex<double>(A.m[i][j]);
			}


		this->m = tmp;
		this->x = x_;
		this->y = y_;

	}
	else
	{
		m = 0;
		x = 0;
		y = 0;
	}
	c_x = x;
	c_y = y;
}


MatrixCalculator::~MatrixCalculator()
{
	this;
	for (int i = 0; i < c_y; i++)
		delete[] m[i];
	delete m;
	m = 0;

}
std::complex<double>* MatrixCalculator:: operator[] (int a)const
{
	return m[a];
}

MatrixCalculator& MatrixCalculator::operator=(const MatrixCalculator& A)
{

	if (this != &A)
	{
		int y1 = A.size_y();
		int x1 = A.size_x();
		std::complex<double>** tmp = new std::complex<double>*[y1];
		for (int i = 0; i < y1; i++)
			tmp[i] = new std::complex<double>[x1];

		for (int i = 0; i < y1; i++)
			for (int j = 0; j < x1; j++)
			{
				(tmp[i][j]) = (A.m[i][j]);
			}

		for (int i = 0; i < y1; i++)
			delete[] m[i];
		delete[] m;
		m = tmp;
		x1 = x1;
		y1 = y1;
		c_x = x1;
		c_y = y1;

	}
	return *this;
}
MatrixCalculator& MatrixCalculator::operator=(std::complex<double>** a)
{


	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
		{
			(m[i][j]) = (a[i][j]);
		}


	x = x;
	y = y;

	return *this;
}

MatrixCalculator& MatrixCalculator::operator+=(MatrixCalculator& A)
{
	if (x == A.x && y == A.y)
	{
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				m[i][j] += A.m[i][j];
			}
		}
	}
	return *this;
}

MatrixCalculator MatrixCalculator::operator+(const MatrixCalculator& A) const
{
	MatrixCalculator tmp{ y,x };
	if (x == A.x && y == A.y)
	{

		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				tmp.m[i][j] = m[i][j] + A.m[i][j];
			}
		}
	}
	return tmp;
}

MatrixCalculator MatrixCalculator::operator*(const MatrixCalculator& A) const
{
	MatrixCalculator l{ this->y,A.x };
	if (this->x == A.y)
	{


		for (int i = 0; i < l.y; i++)
		{
			for (int j = 0; j < l.x; j++)
			{
				std::complex<double> suma = 0;
				for (int k = 0; k < this->x; k++)
				{
					suma += m[i][k] * A[k][j];
				}
				l[i][j] = suma;
			}
		}


	}

	return l;
}

MatrixCalculator MatrixCalculator::operator*(const std::complex<double> a) const
{

	MatrixCalculator R{ y,x };
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			R.m[i][j] = m[i][j] * a;
		}
	}
	return R;

}

MatrixCalculator MatrixCalculator::tensorProduct(MatrixCalculator& A)
{
	MatrixCalculator l{ this->y * A.y, this->x * A.x };
	for (int i = 0; i < l.y; i++)
	{
		for (int j = 0; j < l.x; j++)
		{
			l[i][j] = this->m[i % A.y][j % A.x] * A[i % A.y][j % A.x];
		}

	}
	return l;
}

MatrixCalculator MatrixCalculator::operator*=(std::complex<double> a)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			m[i][j] = m[i][j] * a;
		}
	}
	return *this;
}

void MatrixCalculator::swap_x(int x1, int x2)
{

	for (int i = 0; i < y; i++)
	{
		std::swap(m[i][x1], m[i][x2]);

	}

}
void MatrixCalculator::swap_y(int y1, int y2)
{

	for (int i = 0; i < x; i++)
	{
		std::swap(m[y1][i], m[y1][i]);

	}

}
void MatrixCalculator::add_d_y(int d)
{
	if (y + d < c_y)
	{
		y += d;
	}
	else if (this->y + d > 0)
	{
		2 * c_y < y + d ? c_y += 2 * d : c_y *= 2;
		std::complex<double>** tmp = new std::complex<double>*[c_y];
		for (int i = 0; i < c_y; i++)
			tmp[i] = new std::complex<double>[x];

		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
			{
				tmp[i][j] = this->m[i][j];
			}

		for (int i = 0; i < y; i++)
			delete[] m[i];
		delete[] m;
		m = tmp;
		y = y + d;
	}
	else
	{

		for (int i = 0; i < y; i++)
			delete[] m[i];
		delete[] m;
		m = 0;
		x = y = 0;
	}
}

void MatrixCalculator::set_d(int dy, int dx)
{
	if (dy < c_y && dx < c_x)
	{
		y = dy;
		x = dx;
	}
	else
	{
		std::complex<double>** tmp = new std::complex<double>*[dy];
		for (int i = 0; i < dy; i++)
			tmp[i] = new std::complex<double>[dx];



		for (int i = 0; i < y; i++)
			delete[] m[i];
		delete[] m;
		m = tmp;
		c_y = y = dy;
		c_x = x = dx;

	}
}

void MatrixCalculator::add_d_x(int d)
{

	if (x + d < c_x)
	{
		x += d;
	}
	if (this->x + d > 0)
	{
		2 * c_x < x + d ? c_x += 2 * d : c_x *= 2;
		std::complex<double>** tmp = new std::complex<double>*[y];
		for (int i = 0; i < y; i++)
			tmp[i] = new std::complex<double>[c_x];

		for (int i = 0; i < y; i++)
			for (int j = 0; j < x && j < c_x; j++)
			{
				tmp[i][j] = std::complex<double>(this->m[i][j]);
			}

		for (int i = 0; i < y; i++)
			delete[] m[i];
		delete[] m;
		m = tmp;
		x = x + d;
	}
	else
	{

		for (int i = 0; i < y; i++)
			delete[] m[i];
		delete[] m;
		m = 0;
		x = y = 0;
	}
}



const void MatrixCalculator::print()
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			std::cout << std::fixed << std::setw(7) << std::setprecision(5) << m[i][j] << " ";

		}
		std::cout << std::endl;
	}
}
const void MatrixCalculator::print(int precision, int width)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			std::cout << std::fixed << std::setw(width) << std::setprecision(precision) << m[i][j] << " ";

		}
		std::cout << std::endl;
	}
}
const void MatrixCalculator::print(int precision)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			std::cout << std::fixed << std::setprecision(precision) << m[i][j] << " ";

		}
		std::cout << std::endl;
	}
}
const void MatrixCalculator::print_t(int precision)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			std::cout << std::fixed << std::setprecision(precision) << m[j][i] << ", ";

		}
		std::cout << std::endl;
	}
}
const int MatrixCalculator::size_y()const
{
	return y;
}

const int MatrixCalculator::size_x()const
{
	return x;
}

const int MatrixCalculator::capacity_x()const
{
	return c_x;
}

const int MatrixCalculator::capacity_y()const
{
	return c_y;
}

MatrixCalculator operator*(std::complex<double> a, MatrixCalculator A)
{
	MatrixCalculator R{ A.y,A.x };
	for (int i = 0; i < A.y; i++)
	{
		for (int j = 0; j < A.x; j++)
		{
			R.m[i][j] = A.m[i][j] * a;
		}
	}
	return R;
}



std::ostream& operator<<(std::ostream& os, MatrixCalculator& A)
{
	os << "\n";
	for (int i = 0; i < A.size_y(); i++)
	{
		for (int j = 0; j < A.size_x(); j++)
		{
			os << A[i][j] << " ";

		}
		os << "\n";
	}
	return os;
}

