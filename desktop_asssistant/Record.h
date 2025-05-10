// Record.h
#pragma once
#ifndef RECORD_H
#define RECORD_H
#include <string>

class Record {
public:
    virtual void display(int x, int y) const = 0; // �ڽ��� (x,y) ������ʾ
    virtual void saveToFile(std::ofstream& ofs) const = 0; // ���浽�ļ�
    virtual ~Record() {}
};
#endif