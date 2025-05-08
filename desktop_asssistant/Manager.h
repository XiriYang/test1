// Manager.h
#pragma once
#ifndef MANAGER_H
#define MANAGER_H


#include <vector>
#include "Record.h"
#include <fstream>
#include <string>

class Manager {
protected:
    std::vector<Record*> records;
public:
    virtual void loadFromFile() = 0;
    virtual void saveToFile() const = 0;
    virtual void addRecord() = 0;
    virtual void displayAll() const = 0;
    virtual void query() const = 0;
    virtual ~Manager();
};
#endif