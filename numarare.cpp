#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

ifstream fin("numarare.in");
ofstream fout("numarare.out");

const int MOD = 1000000007;

vector<int> topologicalSort(const vector<vector<int>>& graph, int N) {
    vector<int> inDegree(N + 1, 0);
    vector<int> topoOrder;
    queue<int> q;

    for (int u = 1; u <= N; ++u) {
        for (int v : graph[u]) {
            ++inDegree[v];
        }
    }

    for (int i = 1; i <= N; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        for (int v : graph[u]) {
            if (--inDegree[v] == 0) {
                q.push(v);
            }
        }
    }

    bool isDAG = true;
    for (int i = 1; i <= N; ++i) {
        if (inDegree[i] != 0) {
            isDAG = false;
            break;
        }
    }

    if (!isDAG) {
        return vector<int>();
    }
    return topoOrder;
}

vector<long long> countPaths(const vector<vector<int>>& graph,
                             const vector<int>& topoOrder, int N) {
    vector<long long> dp(N + 1, 0);
    dp[1] = 1;

    for (int u : topoOrder) {
        for (int v : graph[u]) {
            dp[v] = (dp[v] + dp[u]) % MOD;
        }
    }

    return dp;
}

int main() {
    int N, M;
    fin >> N >> M;

    vector<vector<int>> graph1(N + 1);
    vector<vector<int>> graph2(N + 1);

    for (int i = 0; i < M; ++i) {
        int x, y;
        fin >> x >> y;
        graph1[x].push_back(y);
    }

    for (int i = 0; i < M; ++i) {
        int x, y;
        fin >> x >> y;
        // daca graph1 contine muchia (x, y), atunci o adaugam in graph2
        if (find(graph1[x].begin(), graph1[x].end(), y) != graph1[x].end()) {
            graph2[x].push_back(y);
        }
    }

    vector<int> topoOrder2 = topologicalSort(graph2, N);

    vector<long long> paths2 = countPaths(graph2, topoOrder2, N);

    fout << paths2[N] % MOD << endl;

    return 0;
}
