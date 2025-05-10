#include "utils.h"
#include <graphics.h>
#include <string>
// ���� stringToWstring ����
std::wstring stringToWstring(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

void drawButton(int left, int top, int right, int bottom, const std::string& text) {
    setfillcolor(LIGHTGRAY);
    fillrectangle(left, top, right, bottom);
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    RECT r = { left, top, right, bottom };
    std::wstring wtext = stringToWstring(text); // ת��Ϊ���ַ�
    drawtext(wtext.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

bool isInside(int x, int y, int left, int top, int right, int bottom) {
    return x >= left && x <= right && y >= top && y <= bottom;
}

std::string inputBox(const std::string& title, const std::string& prompt) {
    wchar_t input[256] = { 0 }; // ʹ�ÿ��ַ�������
    std::wstring wtitle = stringToWstring(title);   // ת��Ϊ���ַ�
    std::wstring wprompt = stringToWstring(prompt); // ת��Ϊ���ַ�
    InputBox(input, 256, wprompt.c_str(), wtitle.c_str());
    return std::string(input, input + wcslen(input)); // ת���� std::string
}

// ���� encryptDecrypt ����
std::string encryptDecrypt(const std::string& input) {
    std::string output = input;
    char key = 'K'; // �򵥵ļ�����Կ
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] ^= key; // ʹ������������/����
    }
    return output;
}
