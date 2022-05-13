#include<iostream>
#include<algorithm>
#include <bits/stdc++.h>
#include<fstream>
#include<random>
#include <string.h>
#include<omp.h>
using namespace std;

struct result {
    string sa;
    string sb;
    int score;
};

// Function to print all sub strings
vector<string> subString(string str, int n) {
    vector<string> str_combinations; 

    // Pick starting point
    for (int len = 1; len <= n; len++) {
        string substring;

        // Pick ending point
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;           
            for (int k = i; k <= j; k++) {
                substring += str[k];
            }

            str_combinations.push_back(substring);
            substring.clear();
        }
    }

    return str_combinations;
}

int algorithmLocalAlignment(int n, int m, string a, string b, vector<vector<int>> H) {
    // Adicionando o gap _
    a = "-" + a;
    // cout << a << endl;
    n++;

    b = "-" + b;
    // cout << b << endl;
    m++;

    H.resize(n+1);
    for(int e=0; e<=n; e++){
        H[e].resize(m+1);
    }
    
    // Matriz H a ser preenchida
    // vector<vector<int>> H(n, vector<int>(m, 0));


    // Inicializar matriz com 0s.
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            H[i][j] = 0;
        }
    }
    
    int maxValor = 0;

    // 3. Para cada 1≤i≤n e 1≤j≤m:
    for(int i = 1; i < n; i++) {
        for(int j = 1; j < m; j++) {
            // Calculando score w
            int w;

            if(a[i] == b[j]) {
                // match
                w = 2;
            } else {
                // mismatch ou gap
                w = -1;
            }

            int diagonal, delecao, insercao;

            // 4. Calcular diagonal
            diagonal = H[i-1][j-1] + w;

            // 5. Calcular deleção
            delecao = H[i-1][j] - 1;

            // 6. Calcular inserção
            insercao = H[i][j-1] - 1;

            // cout << diagonal << " " << delecao << " " << insercao << endl;
            // 7. Calcular H[i,j]=máximo (0, diagonal, deleção, inserção)
            H[i][j] = max({0, diagonal, delecao, insercao});

            // 8. Retornar o máximo de H[_,_]
            if(H[i][j] > maxValor) {
                maxValor = H[i][j];
            }
        }
    }

    result resultado;

    resultado.score = maxValor;

    return resultado.score;
}

int main() {
    // Inicializando as seq. A e B e 
    // seus respectivos tamanhos
    int n, m;
    string a, b;

    cin >> n >> m;
    cin >> a >> b;


    vector<string> a_combinations = subString(a, a.size());
    vector<string> b_combinations = subString(b, b.size());

    vector<result> results;

    for(uint i = 0; i < a_combinations.size(); i++) {
        for(uint j = 0; j < b_combinations.size(); j++) {
            n = a_combinations[i].size();
            m = b_combinations[j].size();

            result resultado;
            resultado.sa = a_combinations[i];
            resultado.sb = b_combinations[j];
            results.push_back(resultado); 
        }
    }

    vector<vector<int>> H;
    H.resize(n+1);
    for(int e=0; e<=n; e++){
        H[e].resize(m+1);
    }
    
    for(uint i = 0; i < results.size(); i++) {
        n = results[i].sa.size();
        m = results[i].sb.size();

        int scoreAlignment = algorithmLocalAlignment(n, m, results[i].sa, results[i].sb, H);

        results[i].score = scoreAlignment;
    }

    result maxResult;
    maxResult.score = 0;
    for(auto& el: results) {
        if(el.score > maxResult.score) {
            maxResult = el;
        }
    }

    cout << "Melhor Resultado: " << maxResult.score << endl;

    for(uint i = 0; i < maxResult.sa.size(); i++) {
        cout << maxResult.sa[i];
    }

    cout << endl;
    
    for(uint i = 0; i < maxResult.sb.size(); i++) {
        cout << maxResult.sb[i];
    }

    cout << endl;

    return 0;
}