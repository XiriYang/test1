// PasswordRecord.h
#pragma once
#ifndef PARE_H
#define PARE_H

#include "Record.h"
#include <string>

class PasswordRecord : public Record {
private:
    std::string website;
    std::string username;
    std::string encryptedPassword;
public:
    PasswordRecord(const std::string& site, const std::string& user, const std::string& pwd);
    void display(int x, int y) const override;
    void saveToFile(std::ofstream& ofs) const override;
    bool matchWebsite(const std::string& site) const;
    std::string decryptPassword() const;
};
#endif