#include "PasswordRecord.h"
#include <graphics.h>
#include <sstream>
#include <fstream>
#include "utils.h"

// Simple encryption and decryption (XOR encryption)
static std::string encryptDecrypt(const std::string& input) {
    std::string output = input;
    for (char& c : output) {
        c ^= 0xAA; // Fixed XOR value
    }
    return output;
}

PasswordRecord::PasswordRecord(const std::string& site, const std::string& user, const std::string& pwd)
    : website(site), username(user), encryptedPassword(encryptDecrypt(pwd)) {
}

void PasswordRecord::display(int x, int y) const {
    std::ostringstream oss;
    oss << "Website: " << website << " Username: " << username;
    std::wstring wtext = stringToWstring(oss.str()); // Convert to wide characters
    outtextxy(x, y, wtext.c_str());
}

void PasswordRecord::saveToFile(std::ofstream& ofs) const {
    if (!ofs.is_open()) {
        throw std::ios_base::failure("Output file stream is not open");
    }
    ofs << website << " " << username << " " << encryptedPassword << std::endl;
    if (!ofs) {
        throw std::ios_base::failure("Failed to write to file");
    }
}

bool PasswordRecord::matchWebsite(const std::string& site) const {
    std::string siteLower = site, websiteLower = website;
    for (char& c : siteLower) c = tolower(c);
    for (char& c : websiteLower) c = tolower(c);
    return siteLower == websiteLower;
}

std::string PasswordRecord::decryptPassword() const {
    return encryptDecrypt(encryptedPassword);
}
