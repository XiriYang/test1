#include "FinanceRecord.h"
#include <graphics.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include"utils.h"
FinanceRecord::FinanceRecord(const std::string& d, double a, const std::string& c)
    : date(d), amount(a), category(c) {
}

void FinanceRecord::display(int x, int y) const {
    std::ostringstream oss;
    oss << date << "  "
        << std::fixed << std::setprecision(2) << amount << "  "
        << category;
    std::wstring wtext = stringToWstring(oss.str()); // ×ª»»Îª¿í×Ö·û
    outtextxy(x, y, wtext.c_str());
}

void FinanceRecord::saveToFile(std::ofstream& ofs) const {
    if (!ofs.is_open()) {
        throw std::ios_base::failure("Output file stream is not open");
    }
    ofs << date << " " << amount << " " << category << std::endl;
    if (!ofs) {
        throw std::ios_base::failure("Failed to write to file");
    }
}

