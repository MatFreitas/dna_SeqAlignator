#include<iostream>
#include<algorithm>
#include <bits/stdc++.h>
#include<fstream>
#include<random>
#include <string.h>
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

result algorithmLocalAlignment(int n, int m, string a, string b, uint seed) {
    if(n > m) {
        a.resize(m);
    } else {
        b.resize(n);
    }

    int score = 0;

    for(uint i = 0; i < a.size(); i++) {
        score += (a[i] == b[i] ? 2 : -1);
    }

    // cout << "Score: " << score << endl;
    // cout << "a: " << a << endl;
    // cout << "b: " << b << endl;

    result resultado;
    resultado.score = score;
    resultado.sa = a;
    resultado.sb = b;

    return resultado;
}

int main() {
    // Inicializando as seq. A e B e 
    // seus respectivos tamanhos
    int n, m;
    string a, b;

    cin >> n >> m;
    cin >> a >> b;

    // cout << "a: " << a << endl;
    // cout << "b: " << b << endl;

    vector<string> a_combinations = subString(a, a.size());
    vector<string> b_combinations = subString(b, b.size());

    result bestResult;
    bestResult.score = 0;

    int seed = 13607;
    for(int i = 0; i < 10; i++) {
        for(uint i = 0; i < a_combinations.size(); i++) {
            for(uint j = 0; j < b_combinations.size(); j++) {
                n = a_combinations[i].size();
                m = b_combinations[j].size();

                result alignment;

                alignment = algorithmLocalAlignment(n, m, a_combinations[i], b_combinations[j], seed);

                if(alignment.score > bestResult.score) {
                    bestResult = alignment;
                }
                seed++;
            }
        }
    }

    cout << "Melhor resultado: " << bestResult.score << endl;
    cout << bestResult.sa << endl;
    cout << bestResult.sb << endl;
    
    return 0;
}