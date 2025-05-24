#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>
#include <cstring>
#include <string>

using namespace std;

const int INF = 1e9;

struct Aresta {
    int u, v, peso;
    bool operator<(const Aresta& outra) const {
        return peso > outra.peso;
    }
};

int main(int argc, char* argv[]) {
    string input_file = "";
    string output_file = "";
    bool mostrar_solucao = false;
    bool mostrar_help = false;
    int inicio = -1;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) mostrar_help = true;
        else if (strcmp(argv[i], "-o") == 0 && i+1 < argc) output_file = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i+1 < argc) input_file = argv[++i];
        else if (strcmp(argv[i], "-i") == 0 && i+1 < argc) inicio = stoi(argv[++i]) - 1;
        else if (strcmp(argv[i], "-s") == 0) mostrar_solucao = true;
    }

    if (inicio == -1) inicio = 0;

    ostream* out = &cout;
    ofstream fout;
    if (!output_file.empty()) {
        fout.open(output_file);
        out = &fout;
    }

    if (mostrar_help || input_file.empty()) {
        *out << "Uso: ./prim -f <arquivo> -i <vertice_inicial> [-s] [-o <arquivo>] [-h]\n";
        return 0;
    }

    ifstream fin(input_file);
    if (!fin.is_open()) {
        *out << "-1\n";
        return 0;
    }

    int n, m;
    if (!(fin >> n >> m)) {
        *out << "-1\n";
        return 0;
    }

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, p;
        if (!(fin >> u >> v >> p)) {
            *out << "-1\n";
            return 0;
        }
        adj[u-1].emplace_back(v-1, p);
        adj[v-1].emplace_back(u-1, p);
    }

    vector<bool> visitado(n, false);
    priority_queue<Aresta> fila;
    vector<pair<int, int>> resultado;
    int custo_total = 0;

    visitado[inicio] = true;
    for (size_t j = 0; j < adj[inicio].size(); ++j) {
        int v = adj[inicio][j].first;
        int p = adj[inicio][j].second;
        fila.push({inicio, v, p});
    }

    while (!fila.empty()) {
        Aresta atual = fila.top(); fila.pop();
        if (visitado[atual.v]) continue;
        visitado[atual.v] = true;
        resultado.emplace_back(atual.u, atual.v);
        custo_total += atual.peso;
        for (size_t j = 0; j < adj[atual.v].size(); ++j) {
            int viz = adj[atual.v][j].first;
            int peso = adj[atual.v][j].second;
            if (!visitado[viz]) fila.push({atual.v, viz, peso});
        }
    }

    if (mostrar_solucao) {
        for (size_t j = 0; j < resultado.size(); ++j) {
            int u = resultado[j].first;
            int v = resultado[j].second;
            *out << "(" << u+1 << "," << v+1 << ") ";
        }
        *out << '\n';
    } else {
        if (resultado.empty()) {
            *out << "-1\n";
        } else {
            *out << to_string(custo_total) << "\n";
        }
    }

    return 0;
}
