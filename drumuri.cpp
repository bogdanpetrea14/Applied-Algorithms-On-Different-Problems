#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

ifstream fin("drumuri.in");
ofstream fout("drumuri.out");

struct Edge {
    int to;
    long long weight;
};

int N, M;
vector<vector<Edge>> adj_list;

void add_edge(int u, int v, long long w) {
    adj_list[u].push_back({v, w});
}

vector<long long> dijkstra(int source, const vector<vector<Edge>>& graph) {
    vector<long long> dist(N + 1, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                                            greater<pair<long long, int>>> pq;
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto &edge : graph[u]) {
            int v = edge.to;
            long long cost = edge.weight;

            if (dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    fin >> N >> M;
    adj_list.resize(N + 1);

    for (int i = 0; i < M; ++i) {
        int u, v;
        long long w;
        fin >> u >> v >> w;
        add_edge(u, v, w);
    }

    int x, y, z;
    fin >> x >> y >> z;

    vector<long long> dist_x = dijkstra(x, adj_list);
    vector<long long> dist_y = dijkstra(y, adj_list);

    fout << dist_x[z] + dist_y[z] << "\n";

    return 0;
}
