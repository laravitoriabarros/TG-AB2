#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>

using namespace std;

void dfs1(int u, vector<bool>& visitado, const vector<vector<int>>& grafo, stack<int>& ordem) {
    visitado[u] = true;
    for (int v : grafo[u]) {
        if (!visitado[v])
            dfs1(v, visitado, grafo, ordem);
    }
    ordem.push(u);
}

void dfs2(int u, vector<bool>& visitado, const vector<vector<int>>& transposto, vector<int>& componente) {
    visitado[u] = true;
    componente.push_back(u + 1);
    for (int v : transposto[u]) {
        if (!visitado[v])
            dfs2(v, visitado, transposto, componente);
    }
}

int main(int argc, char* argv[]) {
    string input_file = "";
    string output_file = "";
    bool mostrar_help = false;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) mostrar_help = true;
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) output_file = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) input_file = argv[++i];
    }

    ostream* out = &cout;
    ofstream fout;
    if (!output_file.empty()) {
        fout.open(output_file);
        out = &fout;
    }

    if (mostrar_help || input_file.empty()) {
        *out << "Uso: ./kosaraju -f <arquivo> [-o <arquivo>] [-h]\n";
        return 0;
    }

    ifstream fin(input_file);
    if (!fin.is_open()) {
        cerr << "Erro ao abrir arquivo: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    vector<vector<int>> grafo(n), transposto(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        grafo[u - 1].push_back(v - 1);
        transposto[v - 1].push_back(u - 1);
    }

    stack<int> ordem;
    vector<bool> visitado(n, false);

    for (int i = 0; i < n; ++i) {
        if (!visitado[i])
            dfs1(i, visitado, grafo, ordem);
    }

    fill(visitado.begin(), visitado.end(), false);

    while (!ordem.empty()) {
        int u = ordem.top(); ordem.pop();
        if (!visitado[u]) {
            vector<int> componente;
            dfs2(u, visitado, transposto, componente);
            sort(componente.begin(), componente.end());
            for (int v : componente)
                *out << v << " ";
            *out << "\n";
        }
    }

    return 0;
}
