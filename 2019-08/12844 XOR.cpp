#include <iostream>
using namespace std;

using ll = long long;

// Class SegTree start
#include <vector>
#define mid ((left + right) / 2)
#define gaesu (right - left + 1)
#define child1 (pos * 2)
#define child2 (pos * 2 + 1)
#define par (pos / 2)
class SegmentTree
{
public:
	vector<int> tree;
	vector<int> lazy;
	int size;

	SegmentTree(int N)
	{
		for ( size = 1; size <= N; size *= 2 );
		tree.resize(2 * size, 0);
		lazy.resize(2 * size, -1);
	}

	void lazy_update(int pos, int left, int right)
	{
		if ( lazy[pos] != -1)
		{
			if ( left != right )
			{
				if ( lazy[child1] == -1 )
				{
					lazy[child1] = lazy[pos];
				}
				else
				{
					lazy[child1] ^= lazy[pos];
				}
				if ( lazy[child2] == -1 )
				{
					lazy[child2] = lazy[pos];
				}
				else
				{
					lazy[child2] ^= lazy[pos];
				}
			}
			else
			{
				tree[pos] ^= lazy[pos];
			}

			lazy[pos] = -1;
		}
	}

	void update(int start, int end, int plusValue)
	{
		update(1, 1, size, start, end, plusValue);
	}
	void update(int pos, int left, int right, int start, int end, int plusValue)
	{
		lazy_update(pos, left, right);

		if ( end < left || right < start )
			return;
		if ( start <= left && right <= end )
		{
			if ( left != right )
			{
				if ( lazy[child1] == -1 )
				{
					lazy[child1] = plusValue;
				}
				else
				{
					lazy[child1] ^= plusValue;
				}
				if ( lazy[child2] == -1 )
				{
					lazy[child2] = plusValue;
				}
				else
				{
					lazy[child2] ^= plusValue;
				}
			}
			else
			{
				tree[pos] ^= plusValue;
			}

			lazy[pos] = 0;
			return;
		}

		update(child1, left, mid, start, end, plusValue);
		update(child2, mid + 1, right, start, end, plusValue);

		tree[pos] = tree[child1] ^ tree[child2];
	}

	ll getSum(int start, int end)
	{
		return getSum(1, 1, size, start, end);
	}
	ll getSum(int pos, int left, int right, int start, int end)
	{
		lazy_update(pos, left, right);

		if ( end < left || right < start )
			return 0ll;
		if ( start <= left && right <= end )
			return tree[pos];

		return getSum(child1, left, mid, start, end) ^
			getSum(child2, mid + 1, right, start, end);
	}
};
// Class SegMent Tree end

int N, M;
int t, a, b, c;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//////////////////////////////////

	cin >> N;
	SegmentTree ST(N);
	for ( int n = 1; n <= N; n++ )
	{
		int num;
		cin >> num;
		ST.update(n, n, num);
	}
	
	cin >> M;
	while ( M-- )
	{
		cin >> t;
		if ( t == 1 )
		{
			cin >> a >> b >> c;
			if ( a > b )
				swap(a, b);
			ST.update(a + 1, b + 1, c);

		}
		else if ( t == 2 )
		{
			cin >> a >> b;
			if ( a > b )
				swap(a, b);
			cout << ST.getSum(a + 1, b + 1) << '\n';
		}
	}

	return 0;
}