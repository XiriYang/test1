// ReminderRecord.h
#pragma once
#include "Record.h"
#include <string>

class ReminderRecord : public Record {
private:
    std::string datetime; // ∏Ò Ω: YYYY-MM-DD HH:MM
    std::string content;
    int priority;         // 1-3
public:
    ReminderRecord(const std::string& dt, const std::string& cont, int pri);
    void display(int x, int y) const override;
    void saveToFile(std::ofstream& ofs) const override;
    const std::string& getDate() const;
};
