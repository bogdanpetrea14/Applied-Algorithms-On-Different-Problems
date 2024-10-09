#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

ifstream fin("trenuri.in");
ofstream fout("trenuri.out");

unordered_map<string, vector<string>> graph;
unordered_map<string, int> memo;
unordered_map<string, bool> visited;

int dfs(const string &current, const string &destination) {
    if (current == destination) {
        return 1;
    }

    // Daca deja avem un drum pana la nodul curent, il returnam direct
    if (memo.find(current) != memo.end()) {
        return memo[current];
    }

    visited[current] = true;
    int max_length = 0;

    for (const auto &neighbor : graph[current]) {
        if (!visited[neighbor]) {
            max_length = max(max_length, dfs(neighbor, destination));
        }
    }

    visited[current] = false;
    memo[current] = 1 + max_length;
    return memo[current];
}

int main() {
    string start_city, end_city;
    fin >> start_city >> end_city;

    int M;
    fin >> M;

    for (int i = 0; i < M; ++i) {
        string u, v;
        fin >> u >> v;
        graph[u].push_back(v);
    }

    int result = dfs(start_city, end_city);

    fout << result << "\n";

    fin.close();
    fout.close();
    return 0;
}
