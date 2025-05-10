#include <graphics.h>
#include <iostream> // 替换 <conio.h>，使用标准输入
#include "FinanceManager.h"
#include "ReminderManager.h"
#include "PasswordManager.h"
#include "utils.h"

FinanceManager financeManager;
ReminderManager reminderManager;
PasswordManager passwordManager;

// 检测鼠标点击的按钮
int detectButtonClick(RECT buttons[], int buttonCount) {
    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) { // 检测鼠标左键点击
                for (int i = 0; i < buttonCount; ++i) {
                    if (msg.x >= buttons[i].left && msg.x <= buttons[i].right &&
                        msg.y >= buttons[i].top && msg.y <= buttons[i].bottom) {
                        return i; // 返回点击的按钮索引
                    }
                }
            }
        }
    }
}

// 主菜单
int showMainMenu() {
    cleardevice();
    settextstyle(30, 0, _T("微软雅黑"));
    outtextxy(180, 50, _T("个人桌面助手系统"));

    settextstyle(20, 0, _T("微软雅黑"));
    outtextxy(220, 150, _T("1. 记账本"));
    outtextxy(220, 200, _T("2. 课程提醒"));
    outtextxy(220, 250, _T("3. 密码管理"));
    outtextxy(220, 300, _T("0. 退出系统"));

    // 定义按钮区域
    RECT buttons[] = {
        {220, 150, 420, 180}, // 记账本
        {220, 200, 420, 230}, // 课程提醒
        {220, 250, 420, 280}, // 密码管理
        {220, 300, 420, 330}  // 退出系统
    };

    return detectButtonClick(buttons, 4); // 返回点击的按钮索引
}

// 记账本菜单
void financeMenu() {
    while (true) {
        cleardevice();
        settextstyle(25, 0, _T("微软雅黑"));
        outtextxy(180, 50, _T("记账本模块"));

        settextstyle(20, 0, _T("微软雅黑"));
        outtextxy(220, 150, _T("1. 添加消费记录"));
        outtextxy(220, 200, _T("2. 查看所有消费记录"));
        outtextxy(220, 250, _T("3. 查询某月消费记录"));
        outtextxy(220, 300, _T("4. 删除消费记录"));
        outtextxy(220, 350, _T("0. 返回主菜单"));

        // 定义按钮区域
        RECT buttons[] = {
            {220, 150, 420, 180}, // 添加消费记录
            {220, 200, 420, 230}, // 查看所有消费记录
            {220, 250, 420, 280}, // 查询某月消费记录
            {220, 300, 420, 330}, // 删除消费记录
            {220, 350, 420, 380}  // 返回主菜单
        };

        int choice = detectButtonClick(buttons, 5);
        if (choice == 0) financeManager.addRecord();
        else if (choice == 1) financeManager.displayAll();
        else if (choice == 2) financeManager.query();
        else if (choice == 3) financeManager.deleteRecord(); // 调用删除记录功能
        else if (choice == 4) break; // 返回主菜单
    }
}


// 课程提醒菜单
void reminderMenu() {
    while (true) {
        cleardevice();
        settextstyle(25, 0, _T("微软雅黑"));
        outtextxy(180, 50, _T("课程提醒模块"));

        settextstyle(20, 0, _T("微软雅黑"));
        outtextxy(220, 150, _T("1. 添加提醒事项"));
        outtextxy(220, 200, _T("2. 查看所有提醒事项"));
        outtextxy(220, 250, _T("3. 查询某天提醒事项"));
        outtextxy(220, 300, _T("0. 返回主菜单"));

        // 定义按钮区域
        RECT buttons[] = {
            {220, 150, 420, 180}, // 添加提醒事项
            {220, 200, 420, 230}, // 查看所有提醒事项
            {220, 250, 420, 280}, // 查询某天提醒事项
            {220, 300, 420, 330}  // 返回主菜单
        };

        int choice = detectButtonClick(buttons, 4);
        if (choice == 0) reminderManager.addRecord();
        else if (choice == 1) reminderManager.displayAll();
        else if (choice == 2) reminderManager.query();
        else if (choice == 3) break; // 返回主菜单
    }
}

// 密码管理菜单
void passwordMenu() {
    while (true) {
        cleardevice();
        settextstyle(25, 0, _T("微软雅黑"));
        outtextxy(180, 50, _T("密码管理模块"));

        settextstyle(20, 0, _T("微软雅黑"));
        outtextxy(220, 150, _T("1. 添加密码记录"));
        outtextxy(220, 200, _T("2. 查看所有网站"));
        outtextxy(220, 250, _T("3. 查询网站密码"));
        outtextxy(220, 300, _T("4. 删除密码记录"));
        outtextxy(220, 350, _T("0. 返回主菜单"));

        // 定义按钮区域
        RECT buttons[] = {
            {220, 150, 420, 180}, // 添加密码记录
            {220, 200, 420, 230}, // 查看所有网站
            {220, 250, 420, 280}, // 查询网站密码
            {220, 300, 420, 330}, // 删除密码记录
            {220, 350, 420, 380}  // 返回主菜单
        };

        int choice = detectButtonClick(buttons, 5);
        if (choice == 0) passwordManager.addRecord();
        else if (choice == 1) passwordManager.displayAll();
        else if (choice == 2) passwordManager.query();
        else if (choice == 3) passwordManager.deleteRecord(); // 调用删除记录功能
        else if (choice == 4) break; // 返回主菜单
    }
}


int main() {
    initgraph(640, 480);
    setbkcolor(RED);
    cleardevice();

    financeManager.loadFromFile();
    reminderManager.loadFromFile();
    passwordManager.loadFromFile();

    while (true) {
        int choice = showMainMenu(); // 使用鼠标选择
        if (choice == 0) financeMenu();
        else if (choice == 1) reminderMenu();
        else if (choice == 2) passwordMenu();
        else if (choice == 3) break; // 退出系统
    }

    closegraph();
    return 0;
}
