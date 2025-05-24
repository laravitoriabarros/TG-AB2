#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <iomanip>
#include <cstring>

using namespace std;

const int INF = 1e9;

void help() {
    cout << "Uso: ./floyd-warshall -f <arquivo> [-o <arquivo>] [-h]" << endl;
    exit(0);
}

int main(int argc, char *argv[]) {
    string input_file, output_file;
    bool has_output = false;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h")) {
            help();
        } else if (!strcmp(argv[i], "-f")) {
            input_file = argv[++i];
        } else if (!strcmp(argv[i], "-o")) {
            output_file = argv[++i];
            has_output = true;
        }
    }

    ifstream infile(input_file);
    if (!infile) {
        cerr << "Erro ao abrir arquivo de entrada." << endl;
        return 1;
    }

    int V, E;
    infile >> V >> E;

    vector<vector<int>> dist(V + 1, vector<int>(V + 1, INF));

    for (int i = 1; i <= V; i++)
        dist[i][i] = 0;

    for (int i = 0; i < E; i++) {
        int u, v, w;
        infile >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
    }

    for (int k = 1; k <= V; k++)
        for (int i = 1; i <= V; i++)
            for (int j = 1; j <= V; j++)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    ostream *out;
    ofstream fout;
    if (has_output) {
        fout.open(output_file);
        out = &fout;
    } else {
        out = &cout;
    }

    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            if (j != 1) *out << " ";
            if (dist[i][j] == INF)
                *out << -1;
            else
                *out << dist[i][j];
        }
        *out << endl;
    }

    return 0;
}
