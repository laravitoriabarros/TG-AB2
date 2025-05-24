#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

struct Aresta {
    int u, v, peso;
    bool operator<(const Aresta& outra) const {
        return peso < outra.peso;
    }
};

vector<int> pai, rank_union;

int find(int u) {
    if (pai[u] != u)
        pai[u] = find(pai[u]);
    return pai[u];
}

void unir(int u, int v) {
    int ru = find(u);
    int rv = find(v);
    if (ru != rv) {
        if (rank_union[ru] < rank_union[rv]) {
            pai[ru] = rv;
        } else if (rank_union[ru] > rank_union[rv]) {
            pai[rv] = ru;
        } else {
            pai[rv] = ru;
            rank_union[ru]++;
        }
    }
}

int main(int argc, char* argv[]) {
    string input_file = "";
    string output_file = "";
    bool mostrar_solucao = false;
    bool mostrar_help = false;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) mostrar_help = true;
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) output_file = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) input_file = argv[++i];
        else if (strcmp(argv[i], "-s") == 0) mostrar_solucao = true;
    }

    ostream* out = &cout;
    ofstream fout;
    if (!output_file.empty()) {
        fout.open(output_file);
        out = &fout;
    }

    if (mostrar_help || input_file.empty()) {
        *out << "Uso: ./kruskal -f <arquivo> [-s] [-o <arquivo>] [-h]\n";
        return 0;
    }

    ifstream fin(input_file);
    if (!fin.is_open()) {
        cerr << "Erro ao abrir arquivo: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    vector<Aresta> arestas;
    for (int i = 0; i < m; ++i) {
        int u, v, p;
        fin >> u >> v >> p;
        arestas.push_back({u - 1, v - 1, p});
    }

    sort(arestas.begin(), arestas.end());

    pai.resize(n);
    rank_union.resize(n, 0);
    for (int i = 0; i < n; ++i)
        pai[i] = i;

    vector<pair<int, int>> resultado;
    int custo_total = 0;

    for (const auto& a : arestas) {
        if (find(a.u) != find(a.v)) {
            unir(a.u, a.v);
            custo_total += a.peso;
            resultado.emplace_back(a.u, a.v);
        }
    }

    if (mostrar_solucao) {
        for (const auto& par : resultado) {
            int u = par.first;
            int v = par.second;
            *out << "(" << u + 1 << "," << v + 1 << ") ";
        }
        *out << endl;
    } else {
        *out << custo_total << endl;
    }


    return 0;
}
