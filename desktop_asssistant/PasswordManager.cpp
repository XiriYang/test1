#include "PasswordManager.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex> // 用于正则表达式验证
#include <algorithm> // 用于 std::transform

// 验证密码强度
bool isStrongPassword(const std::string& password) {
    if (password.length() < 8) return false; // 至少 8 个字符
    std::regex strongPattern(R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&])[A-Za-z\d@$!%*?&]{8,})");
    return std::regex_match(password, strongPattern);
}

// 转换字符串为小写
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void PasswordManager::loadFromFile() {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) return;
    std::string website, username, encryptedPassword;
    while (ifs >> website >> username >> encryptedPassword) {
        // Decrypt the password and create a PasswordRecord object
        std::string decryptedPassword = encryptDecrypt(encryptedPassword);
        records.push_back(new PasswordRecord(website, username, decryptedPassword));
    }
}

void PasswordManager::saveToFile() const {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        throw std::ios_base::failure("Failed to open file for writing");
    }
    for (auto rec : records) {
        rec->saveToFile(ofs);
    }
}

void PasswordManager::addRecord() {
    std::string site = inputBox("Add Password", "Please enter the website name:");
    std::string user = inputBox("Add Password", "Please enter the username:");
    std::string pwd;

    // 验证密码强度
    while (true) {
        pwd = inputBox("Add Password", "Please enter the password:");
        if (isStrongPassword(pwd)) {
            break; // 密码符合强度要求
        }
        else {
            MessageBox(nullptr, L"Password must be at least 8 characters long and include uppercase, lowercase, numbers, and special characters.", L"Weak Password", MB_OK | MB_ICONERROR);
        }
    }

    records.push_back(new PasswordRecord(site, user, pwd));
    saveToFile();
}

void PasswordManager::deleteRecord() {
    std::string site = inputBox("Delete Password", "Please enter the website name to delete:");
    auto it = std::remove_if(records.begin(), records.end(), [&](Record* rec) {
        PasswordRecord* p = dynamic_cast<PasswordRecord*>(rec);
        return p && p->matchWebsite(site);
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

void PasswordManager::displayAll() const {
    cleardevice();
    outtextxy(10, 10, stringToWstring("Saved websites and usernames:").c_str());
    int y = 40;
    for (auto rec : records) {
        rec->display(10, y);
        y += 30;
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

void PasswordManager::query() const {
    std::string site = inputBox("Query Password", "Please enter the website name to query:");
    cleardevice();
    outtextxy(10, 10, stringToWstring("Querying website " + site).c_str());
    int y = 40;
    bool found = false;
    for (auto rec : records) {
        PasswordRecord* p = dynamic_cast<PasswordRecord*>(rec);
        if (p && p->matchWebsite(site)) {
            std::ostringstream oss;
            oss << "Username: " << p->decryptPassword();
            outtextxy(10, y, stringToWstring(oss.str()).c_str());
            y += 30;
            found = true;
        }
    }
    if (!found) {
        outtextxy(10, y, stringToWstring("No matching website found!").c_str());
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
