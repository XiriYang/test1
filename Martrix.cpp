#include"Matrix.h"
#include<iostream>
using namespace std;
void Matrix::setMatrix(const double* values)//���þ���
{
	for (int i = 0;i < size * size;i++)
	{
		elements[i] = values[i];//�����Ա����ֵ
	}
}
Matrix::Matrix(int size) :size(size)//Matrix�Ĺ��캯��
{
	elements = new double[size * size];//��̬�ڴ����
}
Matrix::~Matrix()//Matrix����������
{
	delete[] elements;
}
void Matrix::printMatrix()const//��ʾ�����Ԫ��
{
	cout << "The Matrix is: " << endl;
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < size;j++)
			cout << element(i, j) << " ";
		cout << endl;
	}
}