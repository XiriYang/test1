// FinanceRecord.h
#pragma once
#ifndef FIRE_H
#define FIRE_H

#include "Record.h"
#include <string>

class FinanceRecord : public Record {
private:
    std::string date;   // ∏Ò Ω£∫YYYY-MM-DD
    double amount;
    std::string category;
public:
    FinanceRecord(const std::string& d, double a, const std::string& c);
    void display(int x, int y) const override;
    void saveToFile(std::ofstream& ofs) const override;
    const std::string& getDate() const { return date; }
    double getAmount() const { return amount; }
    const std::string& getCategory()const { return category; }
};
#endif