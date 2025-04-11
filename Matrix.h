#pragma once
#ifndef _MATRIX_H
#define _MATRIX_H
class Matrix //matrix����
{
public:			//�ⲿ�ӿ�
	Matrix(int size = 2);//���캯��
	~Matrix();//��������
	void setMatrix(const double* values);//���󸳳�ֵ
	void printMatrix()const;//��ʾ����
	int getSize()const { return size; }//�õ������С
	double& element(int i, int j) { return elements[i * size + j]; }
	double element(int i, int j)const { return elements[i * size + j]; }
private:
	int size;//����Ĵ�С
	double* elements;//������������׵�ַ
};
#endif