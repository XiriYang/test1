#include<iostream>
#include<cmath>
#include"Complex.h"
using namespace std;
int main()
{
	int i;
	double a, b;
	complex c1, c2, c3, c, p[5];
	cin >> a >> b;//���븴��c1��ʵ�����鲿
	c1 = complex(a, b);
	cout << "c1=";
	c1.prt();
	cout << endl;
	cin >> a >> b;//���븴��c2��ʵ�����鲿
	c2 = complex(a, b);
	cout << "c1=";
	c2.prt();
	cout << endl;
	cin >> a >> b;//���븴��c3��ʵ�����鲿
	c3 = complex(a, b);
	cout << "c3=";
	c3.prt();
	cout << endl;
	c = c1 + c2;
	cout << "c1+c2= ";c.prt();cout << endl;
	c = c1 - c2;
	cout << "c1-c2= ";c.prt();cout << endl;
	c = c1 * c2;
	cout << "c1*c2= ";c.prt();cout << endl;
	c = c1 / c2;
	cout << "c1/c2= ";c.prt();cout << endl;
	c = c3.cpower(-3);
	cout << "c3��-3�η� =";c.prt();cout << endl;
	cout << "c3��5�η���Ϊ��" << endl;
	c3.croot(5, p);
	for (int i = 0;i < 5;i++)
	{
		p[i].prt();cout << endl;
	}
	c = c3.cexp();
	cout << "c3.cexp()= ";c.prt();cout << endl;
	c = c3.clog();
	cout << "c3.clog()= ";c.prt();cout << endl;
	c = c3.csin();
	cout << "c3.csin()= ";c.prt();cout << endl;
	c = c3.ccos();
	cout << "c3.ccos()= ";c.prt();cout << endl;
	return 0;
}