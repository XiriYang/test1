// ReminderManager.h
#pragma once
#ifndef REM_H
#define REM_H
#include"Manager.h"
#include"ReminderRecord.h"

class ReminderManager :public Manager {
private:
	std::string filename = "reminder.txt";
public:
	void loadFromFile()override;
	void saveToFile()const override;
	void addRecord()override;
	void displayAll()const override;
	void query()const override;
	void sortRecords();
};