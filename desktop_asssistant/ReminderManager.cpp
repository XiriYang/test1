#include "ReminderManager.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream> // Replace <conio.h> with standard input
#include <regex>    // 用于正则表达式验证

// 验证日期格式是否为 YYYY-MM-DD HH:MM
bool isValidDateTime(const std::string& datetime) {
    std::regex dateTimePattern(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}$)");
    return std::regex_match(datetime, dateTimePattern);
}

// 自动排序提醒事项
void ReminderManager::sortRecords() {
    std::sort(records.begin(), records.end(), [](Record* a, Record* b) {
        ReminderRecord* ra = dynamic_cast<ReminderRecord*>(a);
        ReminderRecord* rb = dynamic_cast<ReminderRecord*>(b);
        return ra->getDate() < rb->getDate();
        });
}

void ReminderManager::loadFromFile() {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return;
    std::string datetime, content;
    int priority;
    while (ifs >> datetime >> priority) {
        ifs.get();
        std::getline(ifs, content);
        records.push_back(new ReminderRecord(datetime, content, priority));
    }
    // 自动排序
    sortRecords();
}

void ReminderManager::saveToFile() const {
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
    // 自动排序
    sortRecords();
    saveToFile();
}

void ReminderManager::displayAll() const {
    cleardevice();
    outtextxy(10, 10, stringToWstring("Date and Time        Content (Priority)").c_str());
    int y = 40;

    for (auto rec : records) {
        ReminderRecord* r = dynamic_cast<ReminderRecord*>(rec);
        if (r) {
            r->display(10, y);
            y += 30;
        }
    }

    // Draw the "Back" button
    RECT backButton = { 10, y + 50, 150, y + 90 };
    drawButton(backButton.left, backButton.top, backButton.right, backButton.bottom, "Back");

    // Wait for the user to click the "Back" button
    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                if (msg.x >= backButton.left && msg.x <= backButton.right &&
                    msg.y >= backButton.top && msg.y <= backButton.bottom) {
                    break; // Exit the function when the "Back" button is clicked
                }
            }
        }
    }
}

void ReminderManager::query() const {
    std::string date = inputBox("Query Reminder", "Please enter the date (YYYY-MM-DD):");
    cleardevice();
    outtextxy(10, 10, stringToWstring("Querying reminders for " + date).c_str());
    int y = 40;
    for (auto rec : records) {
        ReminderRecord* r = dynamic_cast<ReminderRecord*>(rec);
        if (r && r->getDate().substr(0, 10) == date) {
            r->display(10, y);
            y += 30;
        }
    }

    // Draw the "Back" button
    RECT backButton = { 10, y + 50, 150, y + 90 };
    drawButton(backButton.left, backButton.top, backButton.right, backButton.bottom, "Back");

    // Wait for the user to click the "Back" button
    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                if (msg.x >= backButton.left && msg.x <= backButton.right &&
                    msg.y >= backButton.top && msg.y <= backButton.bottom) {
                    break; // Exit the function when the "Back" button is clicked
                }
            }
        }
    }
}
