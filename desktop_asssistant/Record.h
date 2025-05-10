// Record.h
#pragma once
#ifndef RECORD_H
#define RECORD_H
#include <string>

class Record {
public:
    virtual void display(int x, int y) const = 0; // 在界面 (x,y) 坐标显示
    virtual void saveToFile(std::ofstream& ofs) const = 0; // 保存到文件
    virtual ~Record() {}
};
#endif