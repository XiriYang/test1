// FinanceManager.h
#pragma once
#ifndef FIM_H
#define FIM_H

#include "Manager.h"
#include "FinanceRecord.h"

class FinanceManager : public Manager {
private:
    std::string filename = "finance.txt";
public:
    void loadFromFile() override;
    void saveToFile() const override;
    void addRecord() override;
    void displayAll() const override;
    void query() const override;
    void deleteRecord();
};
#endif
