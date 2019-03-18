#include "pch.h"
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<deque>
#include<iomanip>
#include<sstream>
#include<stack>
#include<iostream>
#include<limits>
#include<bitset>
#include<list>
#include<queue>
#include<memory>
#include<functional>
#include<cstdio>
using namespace std;
const int N = 500010;
namespace string_hash
{
	const long long mod1 = 9e8 + 11;
	const long long mod2 = 9e8 + 41;
	const long long mod3 = 9e8 + 53;
	const long long mod4 = 9e8 + 67;
	const long long mod5 = 19260817;
	const long long prime1 = 131;
	const long long prime2 = 233;
	const long long prime3 = 13331;
	class stringHash
	{
	public:
		long long prime_n[N], hash[N];
		long long mod, prime;
		int s1[N], len;
		int lcp2;
		stringHash(long long Mod = mod1, long long Prime = prime1) :mod(Mod), prime(Prime) {}
		void init1()
		{
			prime_n[0] = 0;
			prime_n[1] = prime;
			for (int i = 2; i < N; ++i)
				prime_n[i] = (prime_n[i - 1] * prime) % mod;
		}
		void trans1(string &str)
		{
			hash[0] = 0, len = str.size();
			for (int i = 0; i < str.size(); ++i)
				hash[i + 1] = (hash[i] * prime + str[i]) % mod, s1[i + 1] = str[i];
		}
		void pop_back()
		{
			len--;
		}
		void addchar(char p)
		{
			len++;
			hash[len] = (hash[len - 1] * prime + p) % mod, s1[len] = p;
		}
		long long substring1(int l, int r)
		{
			return ((hash[r] - hash[l - 1] * prime_n[r - l + 1]) % mod + mod) % mod;
		}
		int lcp(int L1, int R1, int L2, int R2)
		{
			lcp2 = 0;
			Lcp(L1, L2, 1, min(R1 - L1 + 1, R2 - L2 + 1));
			return lcp2;
		}
		int lsp(int L1, int R1, int L2, int R2)
		{
			lcp2 = 0;
			Lsp(R1, R2, 1, min(R1 - L1 + 1, R2 - L2 + 1));
			return lcp2;
		}
		void Lsp(int i1, int i2, int L, int R)
		{
			int mid = (L + R) / 2;
			if (L <= R)
			{
				if (substring1(i1 - mid + 1, i1) == substring1(i2 - mid + 1, i2))
				{
					Lsp(i1, i2, mid + 1, R);
					lcp2 = max(lcp2, mid);
				}
				else
					Lsp(i1, i2, L, mid - 1);
			}
		}
		void Lcp(int i1, int i2, int L, int R)
		{
			int mid = (L + R) / 2;
			if (L <= R)
			{
				if (substring1(i1, i1 + mid - 1) == substring1(i2, i2 + mid - 1))
				{
					Lcp(i1, i2, mid + 1, R);
					lcp2 = max(lcp2, mid);
				}
				else
					Lcp(i1, i2, L, mid - 1);
			}
		}
		bool cmp_prefix(int a, int b) //falseÎªbÐ¡£¬trueÎªa
		{
			int k = lsp(1, a, 1, b);
			if (k == b)
				return false;
			if (k == a)
				return true;
			return s1[a - k] < s1[b - k];
		}
	};
}
using namespace string_hash;

