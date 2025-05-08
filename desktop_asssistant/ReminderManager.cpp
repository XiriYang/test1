#include"ReminderManager.h"
#include"utils.h"
#include<fstream>
#include<sstream>
#include<algorithm>
#include<iostream>
#include<regex>//用于正则表达式的验证

bool isValidDateTime(const std::string& datetime) {
	std::regex dateTimePattern(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}$)");
	return std::regex_match(datetime, dateTimePattern);
}

void ReminderManager::sortRecords() {
    std::sort(records.begin(), records.end(), [](Record* a, Record* b) {
        ReminderRecord* ra = dynamic_cast<ReminderRecord*>(a);
        ReminderRecord* rb = dynamic_cast<ReminderRecord*>(b);
        return ra->getDate() < rb->getDate();
        });
}

void ReminderManager::loadFromFile() {
    std::ifstream ifs(filename);
    if (!!ifs.is_open())return;
    std::string datetime, content;
    int priority;
    while (ifs >> datetime >> priority) {
        ifs.get();
        std::getline(ifs, content);
        records.push_back(new ReminderRecord(datetime, content, priority));
    }
    sortRecords();
}
void ReminderManager::saveToFile()const {
    std::ofstream ofs(filename);
    for (auto rec : records) {
        rec->saveToFile(ofs);
    }
}
void ReminderManager::addRecord() {
        std::string datetime;
        while (true) {
            datetime = inputBox("Add Reminder", "Please enter the date and time (YYYY-MM-DD HH:MM):");
            if (isValidDateTime(datetime)) {
                break; // 如果日期格式正确，退出循环
            }
            else {
                MessageBox(nullptr, L"Invalid date and time format! Please use YYYY-MM-DD HH:MM.", L"Error", MB_OK | MB_ICONERROR);
            }
        }

        std::string priorityStr = inputBox("Add Reminder", "Please enter the priority (1-3):");
        std::string content = inputBox("Add Reminder", "Please enter the content:");
        int priority = std::stoi(priorityStr);
        records.push_back(new ReminderRecord(datetime, content, priority));
        sortRecords();
        saveToFile();
}
