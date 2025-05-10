// PasswordManager.h
#pragma once
#ifndef PAM_H
#define PAM_H
#include "Manager.h"
#include "PasswordRecord.h"

class PasswordManager : public Manager {
private:
    std::string filename = "password.txt";
public:
    void loadFromFile() override;
    void saveToFile() const override;
    void addRecord() override;
    void displayAll() const override;
    void query() const override;
    void deleteRecord();
};
#endif
