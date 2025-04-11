#include"Matrix.h"
#include<iostream>
using namespace std;
void Matrix::setMatrix(const double* values)//设置矩阵
{
	for (int i = 0;i < size * size;i++)
	{
		elements[i] = values[i];//矩阵成员赋初值
	}
}
Matrix::Matrix(int size) :size(size)//Matrix的构造函数
{
	elements = new double[size * size];//动态内存分配
}
Matrix::~Matrix()//Matrix的析构函数
{
	delete[] elements;
}
void Matrix::printMatrix()const//显示矩阵的元素
{
	cout << "The Matrix is: " << endl;
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
			cout << element(i, j) << " ";
		cout << endl;
	}
}