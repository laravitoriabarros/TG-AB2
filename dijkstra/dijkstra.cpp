#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <cstring>

using namespace std;

const int INF = 1e9;

void help() {
    cout << "Uso: ./dijkstra -f <arquivo> [-i <vértice>] [-o <arquivo>] [-h]" << endl;
    exit(0);
}

int main(int argc, char *argv[]) {
    string input_file, output_file;
    bool has_output = false;
    int start_vertex = 1;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h")) {
            help();
        } else if (!strcmp(argv[i], "-f")) {
            input_file = argv[++i];
        } else if (!strcmp(argv[i], "-o")) {
            output_file = argv[++i];
            has_output = true;
        } else if (!strcmp(argv[i], "-i")) {
            start_vertex = atoi(argv[++i]);
        }
    }

    if (input_file.empty()) {
        cerr << "Arquivo de entrada não fornecido.\n";
        help();
    }

    ifstream infile(input_file);
    if (!infile) {
        cerr << "Erro ao abrir o arquivo de entrada.\n";
        return 1;
    }

    int V, E;
    infile >> V >> E;

    vector<vector<pair<int, int>>> adj(V + 1);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        infile >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    vector<int> dist(V + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start_vertex] = 0;
    pq.push(make_pair(0, start_vertex));

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        if (d > dist[u]) continue;

        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            int w = adj[u][i].second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    ostream *out;
    ofstream fout;
    if (has_output) {
        fout.open(output_file, ios::out | ios::binary);
        out = &fout;
    } else {
        out = &cout;
    }

    for (int i = 1; i <= V; i++) {
        if (i > 1) *out << " ";
        *out << i << ":";
        if (dist[i] == INF)
            *out << -1;
        else
            *out << dist[i];
    }

    *out << '\n';

    return 0;
}
