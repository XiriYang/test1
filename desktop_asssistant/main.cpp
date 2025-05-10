#include <graphics.h>
#include <iostream> // �滻 <conio.h>��ʹ�ñ�׼����
#include "FinanceManager.h"
#include "ReminderManager.h"
#include "PasswordManager.h"
#include "utils.h"

FinanceManager financeManager;
ReminderManager reminderManager;
PasswordManager passwordManager;

// ���������İ�ť
int detectButtonClick(RECT buttons[], int buttonCount) {
    while (true) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN) { // ������������
                for (int i = 0; i < buttonCount; ++i) {
                    if (msg.x >= buttons[i].left && msg.x <= buttons[i].right &&
                        msg.y >= buttons[i].top && msg.y <= buttons[i].bottom) {
                        return i; // ���ص���İ�ť����
                    }
                }
            }
        }
    }
}

// ���˵�
int showMainMenu() {
    cleardevice();
    settextstyle(30, 0, _T("΢���ź�"));
    outtextxy(180, 50, _T("������������ϵͳ"));

    settextstyle(20, 0, _T("΢���ź�"));
    outtextxy(220, 150, _T("1. ���˱�"));
    outtextxy(220, 200, _T("2. �γ�����"));
    outtextxy(220, 250, _T("3. �������"));
    outtextxy(220, 300, _T("0. �˳�ϵͳ"));

    // ���尴ť����
    RECT buttons[] = {
        {220, 150, 420, 180}, // ���˱�
        {220, 200, 420, 230}, // �γ�����
        {220, 250, 420, 280}, // �������
        {220, 300, 420, 330}  // �˳�ϵͳ
    };

    return detectButtonClick(buttons, 4); // ���ص���İ�ť����
}

// ���˱��˵�
void financeMenu() {
    while (true) {
        cleardevice();
        settextstyle(25, 0, _T("΢���ź�"));
        outtextxy(180, 50, _T("���˱�ģ��"));

        settextstyle(20, 0, _T("΢���ź�"));
        outtextxy(220, 150, _T("1. ������Ѽ�¼"));
        outtextxy(220, 200, _T("2. �鿴�������Ѽ�¼"));
        outtextxy(220, 250, _T("3. ��ѯĳ�����Ѽ�¼"));
        outtextxy(220, 300, _T("4. ɾ�����Ѽ�¼"));
        outtextxy(220, 350, _T("0. �������˵�"));

        // ���尴ť����
        RECT buttons[] = {
            {220, 150, 420, 180}, // ������Ѽ�¼
            {220, 200, 420, 230}, // �鿴�������Ѽ�¼
            {220, 250, 420, 280}, // ��ѯĳ�����Ѽ�¼
            {220, 300, 420, 330}, // ɾ�����Ѽ�¼
            {220, 350, 420, 380}  // �������˵�
        };

        int choice = detectButtonClick(buttons, 5);
        if (choice == 0) financeManager.addRecord();
        else if (choice == 1) financeManager.displayAll();
        else if (choice == 2) financeManager.query();
        else if (choice == 3) financeManager.deleteRecord(); // ����ɾ����¼����
        else if (choice == 4) break; // �������˵�
    }
}


// �γ����Ѳ˵�
void reminderMenu() {
    while (true) {
        cleardevice();
        settextstyle(25, 0, _T("΢���ź�"));
        outtextxy(180, 50, _T("�γ�����ģ��"));

        settextstyle(20, 0, _T("΢���ź�"));
        outtextxy(220, 150, _T("1. �����������"));
        outtextxy(220, 200, _T("2. �鿴������������"));
        outtextxy(220, 250, _T("3. ��ѯĳ����������"));
        outtextxy(220, 300, _T("0. �������˵�"));

        // ���尴ť����
        RECT buttons[] = {
            {220, 150, 420, 180}, // �����������
            {220, 200, 420, 230}, // �鿴������������
            {220, 250, 420, 280}, // ��ѯĳ����������
            {220, 300, 420, 330}  // �������˵�
        };

        int choice = detectButtonClick(buttons, 4);
        if (choice == 0) reminderManager.addRecord();
        else if (choice == 1) reminderManager.displayAll();
        else if (choice == 2) reminderManager.query();
        else if (choice == 3) break; // �������˵�
    }
}

// �������˵�
void passwordMenu() {
    while (true) {
        cleardevice();
        settextstyle(25, 0, _T("΢���ź�"));
        outtextxy(180, 50, _T("�������ģ��"));

        settextstyle(20, 0, _T("΢���ź�"));
        outtextxy(220, 150, _T("1. ��������¼"));
        outtextxy(220, 200, _T("2. �鿴������վ"));
        outtextxy(220, 250, _T("3. ��ѯ��վ����"));
        outtextxy(220, 300, _T("4. ɾ�������¼"));
        outtextxy(220, 350, _T("0. �������˵�"));

        // ���尴ť����
        RECT buttons[] = {
            {220, 150, 420, 180}, // ��������¼
            {220, 200, 420, 230}, // �鿴������վ
            {220, 250, 420, 280}, // ��ѯ��վ����
            {220, 300, 420, 330}, // ɾ�������¼
            {220, 350, 420, 380}  // �������˵�
        };

        int choice = detectButtonClick(buttons, 5);
        if (choice == 0) passwordManager.addRecord();
        else if (choice == 1) passwordManager.displayAll();
        else if (choice == 2) passwordManager.query();
        else if (choice == 3) passwordManager.deleteRecord(); // ����ɾ����¼����
        else if (choice == 4) break; // �������˵�
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
        int choice = showMainMenu(); // ʹ�����ѡ��
        if (choice == 0) financeMenu();
        else if (choice == 1) reminderMenu();
        else if (choice == 2) passwordMenu();
        else if (choice == 3) break; // �˳�ϵͳ
    }

    closegraph();
    return 0;
}
