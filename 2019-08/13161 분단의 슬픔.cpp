#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

#define INF INT_MAX

class Dinic
{
private:
	struct Edge
	{
		int to, rev, cap, flow;
		Edge(int _to, int _cap) : to(_to), cap(_cap), flow(0)
		{
		}
	};

	vector<vector<Edge>> adj;
	vector<int> depth, work;

	void bfs()
	{
		fill(depth.begin(), depth.end(), -1);

		queue<int> q;
		q.push(source);
		depth[source] = 0;

		while ( !q.empty() )
		{
			int s = q.front();
			q.pop();

			for ( auto &e : adj[s] )
			{
				if ( e.cap - e.flow > 0 && depth[e.to] == -1 )
				{
					depth[e.to] = depth[s] + 1;
					q.push(e.to);
				}
			}
		}
	}

	int dfs(int s, int flow)
	{
		if ( s == sink )
			return flow;

		for ( int i = work[s]; i < adj[s].size(); i++, work[s]++ )
		{
			auto &e = adj[s][i];

			if ( depth[e.to] > depth[s] && e.cap - e.flow > 0 )
			{
				int f = dfs(e.to, min(flow, e.cap - e.flow));

				if ( f < 0 )
					continue;

				e.flow += f;
				adj[e.to][e.rev].flow -= f;

				return f;
			}
		}

		return -1;
	}

public:
	int source, sink;

	Dinic(int n)
	{
		source = 0;
		sink = n + 1;

		adj.resize(sink + 1);
		depth.resize(sink + 1);
		work.resize(sink + 1);
	}

	void add_edge(int u, int v, int cap)
	{
		adj[u].push_back(Edge(v, cap));
		adj[v].push_back(Edge(u, 0));
		adj[u].back().rev = adj[v].size() - 1;
		adj[v].back().rev = adj[u].size() - 1;
	}

	int max_flow(int a, int n)
	{
		int flow = 0;
		while ( 1 )
		{
			bfs();
			if ( depth[sink] == -1 )
				break;

			fill(work.begin(), work.end(), 0);
			while ( 1 )
			{
				int f = dfs(source, INF);
				if ( f < 0 )
					break;
				flow += f;
			}
		}

		cout << a + flow << '\n';

		for ( int i = 1; i <= n; i++ )
			if ( depth[i] != -1 )
				cout << i << " ";

		cout << '\n';

		for ( int i = 1; i <= n; i++ )
			if ( depth[i] == -1 )
				cout << i << " ";

		cout << '\n';

		return flow;
	}
};

int N;
vector<int> team[3];
int capacity[502][502];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	//////////////////////////////////

	cin >> N;
	Dinic mf(N);

	for ( int n = 1; n <= N; n++ )
	{
		int jinyung;
		cin >> jinyung;
		if ( jinyung == 1 )
			mf.add_edge(mf.source, n, INT_MAX);
		else if ( jinyung == 2 )
			mf.add_edge(n, mf.sink, INT_MAX);
	}

	for ( int i = 1; i <= N; i++ )
	{
		for ( int j = 1; j <= N; j++ )
		{
			cin >> capacity[i][j];
			if ( i == j )
				continue;

			mf.add_edge(i, j, capacity[i][j]);
		}
	}


	mf.max_flow(0, N);

	return 0;
}