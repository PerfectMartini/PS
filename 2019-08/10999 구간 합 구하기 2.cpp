#include <cstdio>
#include <climits>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
using namespace std;

#define MAX_N ((int)(1e6) + 10)

#define mid ((start + end) / 2)
#define gaesu (end - start + 1)
#define child1 (node * 2)
#define child2 (node * 2 + 1)

long long habTree[4 * MAX_N]; // 2N개만큼 필요
long long lazyTree[4 * MAX_N];
long long arr[MAX_N];

//함수
long long initTree(int node, int start, int end);
long long sumTree(int hab_left, int hab_right);
long long _sumTree(int node, int start, int end, int hab_left, int hab_right);
void plusValue(int plus_left, int plus_right, long long Value);
void _plusValue(int node, int start, int end, int plus_left, int plus_right, long long Value);

//백준변수
int N, M, K;
int a, b, c;
long long d;

int main(void)
{
	int i, j, k;

	scanf("%d %d %d", &N, &M, &K);

	//입력
	for ( i = 1; i <= N; i++ )
	{
		scanf("%lld", &arr[i]);
	}
	//트리에 넣기
	initTree(1, 1, N);

	while ( M + K )
	{
		scanf("%d", &a);

		switch ( a )
		{
		case 1:
			scanf("%d %d %lld", &b, &c, &d);
			plusValue(b, c, d);
			M--;
			break;

		case 2:
			scanf("%d %d", &b, &c);
			printf("%lld\n", sumTree(b, c));
			K--;
			break;
		}
	}


	return 0;
}

// (start,end) : node가 담당하고 있는 구간
long long initTree(int node, int start, int end)
{
	if ( start == end )
	{
		return habTree[node] = arr[start];
	}
	else
	{
		return habTree[node] = initTree(child1, start, mid) + initTree(child2, mid + 1, end);
	}
}
long long sumTree(int hab_left, int hab_right)
{
	return _sumTree(1, 1, N, hab_left, hab_right);
}
// (start,end) : node가 담당하고 있는 구간
long long _sumTree(int node, int start, int end, int hab_left, int hab_right)
{
	if ( lazyTree[node] != 0 )
	{
		habTree[node] += lazyTree[node] * gaesu;

		if ( start != end )
		{
			lazyTree[child1] += lazyTree[node];
			lazyTree[child2] += lazyTree[node];
		}

		lazyTree[node] = 0;
	}

	if ( end < hab_left || hab_right < start )
	{
		return 0;
	}
	if (  hab_left <= start && end <= hab_right )
	{
		return habTree[node];
	}
	return _sumTree(child1, start, mid, hab_left, hab_right) + _sumTree(child2, mid + 1, end, hab_left, hab_right);
}
void plusValue(int plus_left, int plus_right, long long Value)
{
	_plusValue(1, 1, N, plus_left, plus_right, Value);
}
// (start,end) : node가 담당하고 있는 구간
void _plusValue(int node, int start, int end, int plus_left, int plus_right, long long Value)
{
	if ( lazyTree[node] != 0 )
	{
		habTree[node] += lazyTree[node] * gaesu;

		if ( start != end )
		{
			lazyTree[child1] += lazyTree[node];
			lazyTree[child2] += lazyTree[node];
		}

		lazyTree[node] = 0;
	}

	if ( plus_right < start || end < plus_left ) return;

	if ( plus_left <= start && end <= plus_right )
	{
		habTree[node] += Value * gaesu;

		if ( start != end )
		{
			lazyTree[child1] += Value;
			lazyTree[child2] += Value;
		}

		lazyTree[node] = 0;
		return;
	}

	_plusValue(child1, start, mid, plus_left, plus_right, Value);
	_plusValue(child2, mid+1, end, plus_left, plus_right, Value);
	habTree[node] = habTree[child1] + habTree[child2];
}