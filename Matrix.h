#pragma once
#ifndef _MATRIX_H
#define _MATRIX_H
class Matrix //matrix定义
{
public:			//外部接口
	Matrix(int size = 2);//构造函数
	~Matrix();//析构函数
	void setMatrix(const double* values);//矩阵赋初值
	void printMatrix()const;//显示矩阵
	int getSize()const { return size; }//得到矩阵大小
	double& element(int i, int j) { return elements[i * size + j]; }
	double element(int i, int j)const { return elements[i * size + j]; }
private:
	int size;//矩阵的大小
	double* elements;//矩阵存放数组的首地址
};
#endif