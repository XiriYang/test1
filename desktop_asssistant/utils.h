#pragma once
#include<string>
#include<graphics.h>
#ifndef UTILS_H
#define UTILS_H

//绘制按钮
void drawButton(int left, int top, int right, int bottom, const std::string& text);
//判断是否点中了按钮
bool isInside(int x, int y, int left, int top, int right, int bottom);
//弹出输入框，获取用户输入
std::string inputBox(const std::string& title, const std::string& prompt);
//声明encryptDecrypt函数
std::string encryptDecrypt(const std::string& input);
//声明stringToWstring函数
std::wstring stringToWstring(const std::string& str);

#endif