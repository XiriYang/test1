#include"ReminderManager.h"
#include<graphics.h>
#include<sstream>
#include<fstream>
#include"utils.h"

ReminderRecord::ReminderRecord(const std::string& dt, const std::string& cont, int pri)
	:datetime(dt),content(cont),priority(pri){ }
void ReminderRecord::display(int x, int y)const {
	std::ostringstream oss;
	oss << datetime << " [Priority: " << priority << "]" << content;
	std::wstring wtext = stringToWstring(oss.str());
	outtextxy(x, y, wtext.c_str());
}

void ReminderRecord::saveToFile(std::ofstream& ofs)const {
	ofs << datetime << " " << priority << " " << content << std::endl;
	if (!ofs) {
		throw std::ios_base::failure("Failed to write to file");
	}
}

const std::string& ReminderRecord::getDate()const {
	return datetime;
}