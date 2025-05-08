#pragma once
#include<string>
#include<graphics.h>
#ifndef UTILS_H
#define UTILS_H

//���ư�ť
void drawButton(int left, int top, int right, int bottom, const std::string& text);
//�ж��Ƿ�����˰�ť
bool isInside(int x, int y, int left, int top, int right, int bottom);
//��������򣬻�ȡ�û�����
std::string inputBox(const std::string& title, const std::string& prompt);
//����encryptDecrypt����
std::string encryptDecrypt(const std::string& input);
//����stringToWstring����
std::wstring stringToWstring(const std::string& str);

#endif