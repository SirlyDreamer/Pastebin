#include <iostream>
#include <unordered_map>
using namespace std;

namespace std
{
	template <>
	struct hash<string>
	{
		size_t operator()(const string& str) const
		{
			long long o;
			for (auto& c : str)
			{
				o = c;
				o += 0x9e3779b97f4a7c15;
				o = (o ^ (o >> 30)) * 0xbf58476d1ce4e5b9;
				o = (o ^ (o >> 27)) * 0x94d049bb133111eb;
			}
			return o ^ (o >> 31);
		}
	};
}

unordered_map<string, int> mp;

void tolow(string& str)
{
	for (auto& c : str)
		if ('A' <= c && c <= 'Z')
			c = c - 'A' + 'a';
}


int main()
{
	iostream::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string str;
	while (cin >> str)
	{
		tolow(str);
		mp[str]++;
	}
	int n(0);
	string ans;
	for (auto& a : mp)
	{
		if (a.second > n)
		{
			n = a.second;
			ans = a.first;
		}
		if (a.second == n && a.first < ans)
		{
			ans = a.first;
		}
	}
	cout << ans << ' ' << n;
	return 0;
}
