#include "utils.h"
#include <graphics.h>
#include <string>
// 定义 stringToWstring 函数
std::wstring stringToWstring(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

void drawButton(int left, int top, int right, int bottom, const std::string& text) {
    setfillcolor(LIGHTGRAY);
    fillrectangle(left, top, right, bottom);
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    RECT r = { left, top, right, bottom };
    std::wstring wtext = stringToWstring(text); // 转换为宽字符
    drawtext(wtext.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

bool isInside(int x, int y, int left, int top, int right, int bottom) {
    return x >= left && x <= right && y >= top && y <= bottom;
}

std::string inputBox(const std::string& title, const std::string& prompt) {
    wchar_t input[256] = { 0 }; // 使用宽字符缓冲区
    std::wstring wtitle = stringToWstring(title);   // 转换为宽字符
    std::wstring wprompt = stringToWstring(prompt); // 转换为宽字符
    InputBox(input, 256, wprompt.c_str(), wtitle.c_str());
    return std::string(input, input + wcslen(input)); // 转换回 std::string
}

// 定义 encryptDecrypt 函数
std::string encryptDecrypt(const std::string& input) {
    std::string output = input;
    char key = 'K'; // 简单的加密密钥
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] ^= key; // 使用异或操作加密/解密
    }
    return output;
}
