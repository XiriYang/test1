#include "FinanceManager.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <graphics.h>
#include <string>
#include <iostream>
#include <regex> // 用于正则表达式验证

// 验证日期格式是否为YYYY-MM-DD
bool isValidDate(const std::string& date) {
    std::regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
    return std::regex_match(date, datePattern);
}

void FinanceManager::loadFromFile() {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return;
    std::string date, category;
    double amount;
    while (ifs >> date >> amount) {
        ifs.get(); // Read the space
        std::getline(ifs, category);
        records.push_back(new FinanceRecord(date, amount, category));
    }
}

void FinanceManager::saveToFile() const {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        throw std::ios_base::failure("Failed to open file for writing");
    }
    for (auto rec : records) {
        rec->saveToFile(ofs);
    }
}

void FinanceManager::addRecord() {
    std::string date;
    while (true) {
        date = inputBox("Expense", "Please enter the date (YYYY-MM-DD):");
        if (isValidDate(date)) {
            break; // 如果日期格式正确，退出循环
        }
        else {
            MessageBox(nullptr, L"Invalid date format! Please use YYYY-MM-DD.", L"Error", MB_OK | MB_ICONERROR);
        }
    }

    std::string amountStr = inputBox("Add Expense Record", "Please enter the amount:");
    std::string category = inputBox("Add Expense Record", "Please enter the category:");
    double amount = std::stod(amountStr);
    records.push_back(new FinanceRecord(date, amount, category));
    saveToFile();
}

void FinanceManager::deleteRecord() {
    std::string date;
    while (true) {
        date = inputBox("Delete Expense Record", "Please enter the date (YYYY-MM-DD):");
        if (isValidDate(date)) {
            break; // 如果日期格式正确，退出循环
        }
        else {
            MessageBox(nullptr, L"Invalid date format! Please use YYYY-MM-DD.", L"Error", MB_OK | MB_ICONERROR);
        }
    }

    std::string category = inputBox("Delete Expense Record", "Please enter the category:");
    auto it = std::remove_if(records.begin(), records.end(), [&](Record* rec) {
        FinanceRecord* f = dynamic_cast<FinanceRecord*>(rec);
        return f && f->getDate() == date && f->getCategory() == category;
        });

    if (it != records.end()) {
        // 删除匹配的记录
        for (auto i = it; i != records.end(); ++i) {
            delete* i; // 释放内存
        }
        records.erase(it, records.end());
        saveToFile(); // 保存更新后的记录到文件
        MessageBox(nullptr, L"Record deleted successfully.", L"Success", MB_OK | MB_ICONINFORMATION);
    }
    else {
        MessageBox(nullptr, L"No matching record found.", L"Error", MB_OK | MB_ICONERROR);
    }
}

void FinanceManager::displayAll() const {
    cleardevice();
    outtextxy(10, 10, stringToWstring("Date       Amount      Category").c_str());
    int y = 40;
    for (auto rec : records) {
        rec->display(10, y);
        y += 30;
    }

    // 绘制返回按钮
    RECT backButton = { 10, y + 50, 150, y + 90 };
    drawButton(backButton.left, backButton.top, backButton.right, backButton.bottom, "Back");

    // 等待用户点击返回按钮
    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                if (msg.x >= backButton.left && msg.x <= backButton.right &&
                    msg.y >= backButton.top && msg.y <= backButton.bottom) {
                    break; // 点击返回按钮，退出函数
                }
            }
        }
    }
}

void FinanceManager::query() const {
    std::string month = inputBox("Query Expense Records", "Please enter the month (YYYY-MM):");
    cleardevice();
    outtextxy(10, 10, stringToWstring("Querying expense records for " + month).c_str());
    int y = 40;
    double total = 0;
    for (auto rec : records) {
        FinanceRecord* f = dynamic_cast<FinanceRecord*>(rec);
        if (f && f->getDate().substr(0, 7) == month) {
            f->display(10, y);
            total += f->getAmount();
            y += 30;
        }
    }
    std::ostringstream oss;
    oss << "Total Expense: " << total;
    outtextxy(10, y + 20, stringToWstring(oss.str()).c_str());

    // 绘制返回按钮
    RECT backButton = { 10, y + 50, 150, y + 90 };
    drawButton(backButton.left, backButton.top, backButton.right, backButton.bottom, "Back");

    // 等待用户点击返回按钮
    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) {
                if (msg.x >= backButton.left && msg.x <= backButton.right &&
                    msg.y >= backButton.top && msg.y <= backButton.bottom) {
                    break; // 点击返回按钮，退出函数
                }
            }
        }
    }
}
