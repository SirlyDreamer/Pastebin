#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int maxn = 1e6 + 5;

vector<int> a, dp1, dp2;

int main()
{
	int tmp;
	while (cin >> tmp)
		a.emplace_back(tmp);
	for (auto& n:a)
	{
		if (!dp1.empty() && dp1.back() < n)
		{
			auto iter = upper_bound(dp1.begin(), dp1.end(), n, greater<int>());
			*iter = n;
			continue;
		}
		dp1.emplace_back(n);
	}

	for (auto& n:a)
	{
		if (!dp2.empty() && dp2.back() >= n)
		{
			auto iter = lower_bound(dp2.begin(), dp2.end(), n, less<int>());
			*iter = n;
			continue;
		}
		dp2.emplace_back(n);
	}
	cout << dp1.size() << "\n" << dp2.size();
}
