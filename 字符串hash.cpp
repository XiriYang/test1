#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
typedef unsigned long long ULL;
const int X = 13331;
vector<ULL>h, x;
void bkdr_hash(string s)//计算hash值
{
	h[0] = s[0];
	x[0] = 1;
	for (int i = 1;i < s.size();i++)
	{
		h[i] = h[i - 1] * X + s[i];
		x[i] = x[i - 1] * X;
	}
}
ULL get_hash(int left, int right)//子串的hash值
{
	if (!left)return h[right];
	else
	{
		return h[right] - h[left - 1] * x[right - left + 1];
	}
}
int main()
{
	string s;
	cin >> s;
	h.resize(s.size());
	x.resize(s.size());
	bkdr_hash(s);
	string ss;
	cin >> ss;
	ULL hash2 = 0;
	for (int i = 0;i < ss.size();i++)
	{
		hash2 = hash2 * X + ss[i];
	}
	for (int i = 0;i < s.size();i++)
		cout << get_hash(i, min(s.size() - 1, i + ss.size() - 1)) << " ";
	cout << endl;
	cout << hash2;
	return 0;
}
