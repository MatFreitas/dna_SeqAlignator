#include<iostream>
#include<algorithm>
#include<vector>
#include <bits/stdc++.h>
#include <bits/stdc++.h>
#include<fstream>
using namespace std;

struct salto {
    int movimento;
};

int main() {
    // Inicializando tamanho n, m 
    // das seq. A e B, respectivamente
    int n, m;
    cin >> n >> m;

    // Inicializando lista de movimentos
    salto path;
    path.movimento = 0;
    vector<vector<salto>> saltos(n, vector<salto>(m, path));

    // Inicializando as seq. A e B
    string a, b;
    cin >> a >> b;

    // Adicionando o gap _
    a = "-" + a;
    // cout << a << endl;
    n++;

    b = "-" + b;
    // cout << b << endl;
    m++;
    
    // Matriz H a ser preenchida
    vector<vector<int>> H(n, vector<int>(m, 0));


    // Inicializar matriz com 0s.
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            H[i][j] = 0;
        }
    }

    // cout << endl;

    int seta = 0;

    int maxValor = 0;
    int maxValor_i = 0;
    int maxValor_j = 0;
    
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

            // Guardando movimento
            // diag = 3
            // cima = 2
            // esqu = 1
            // nenh = 0

            if(H[i][j] == 0) {
            //    movimentos[i-1][j-1] = 0;
               salto jump;
               jump.movimento = 0;
               saltos[i-1][j-1] = jump;
            } else if(H[i][j] == diagonal) {
                // movimentos[i-1][j-1] = 3;
                salto jump;
                jump.movimento = 3;
                saltos[i-1][j-1] = jump;
            } else if(H[i][j] == delecao) {
                // movimentos[i-1][j-1] = 2;
                salto jump;
                jump.movimento = 2;
                saltos[i-1][j-1] = jump;
            } else if(H[i][j] == insercao) {
                // movimentos[i-1][j-1] = 1;
                salto jump;
                jump.movimento = 1;
                saltos[i-1][j-1] = jump;
            }

            // 8. Retornar o máximo de H[_,_]
            if(H[i][j] > maxValor) {
                maxValor = H[i][j];
                maxValor_i = i;
                maxValor_j = j;
            }

            seta++;
        }
    }

    maxValor_i--;
    maxValor_j--;

    string alignmentSeqA, alignmentSeqB, match;

    // cout << "Movimentos:" << endl;

    while(maxValor_i >= 0 && maxValor_j >= 0) {
        if(saltos[maxValor_i][maxValor_j].movimento == 0) {
            break;
        }
        else if(saltos[maxValor_i][maxValor_j].movimento == 3) {
            maxValor_i--;
            maxValor_j--;

            alignmentSeqA += a[maxValor_i+2];
            alignmentSeqB += b[maxValor_j+2];
            match += "*";

            // cout << "diag" << endl;
        }
        else if(saltos[maxValor_i][maxValor_j].movimento == 1) {
            maxValor_j--;

            alignmentSeqA += "_";
            alignmentSeqB += b[maxValor_j+2];
            match += " ";

            // cout << "esqu" << endl;
        }
        else if(saltos[maxValor_i][maxValor_j].movimento == 2) {
            maxValor_i--;

            alignmentSeqA += a[maxValor_i+2];
            alignmentSeqB += "_";
            match += " ";

            // cout << "cima" << endl;
        }
    }

    // reverse(alignmentSeqA.begin(), alignmentSeqA.end());
    // reverse(alignmentSeqB.begin(), alignmentSeqB.end());
    // reverse(match.begin(), match.end());

    cout << "Melhor Resultado: " << maxValor << endl;

    for(int i = alignmentSeqA.size() - 1; i >= 0; i--) {
        cout << alignmentSeqA[i];
    }

    cout << endl;

    // cout << match << endl;
    
    for(int i = alignmentSeqB.size() - 1; i >= 0; i--) {
        cout << alignmentSeqB[i];
    }

    cout << endl;

    // Prints
    // cout << endl;

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) {
    //         cout << H[i][j] << " ";
    //     }
    //     cout<< endl;
    // }

    // cout << endl << "MaxValor   : " << maxValor << endl;
    // cout << endl;


    // int k = 0;
    // for(int i = 0; i < n-1; i++) {
    //     for(int j = 0; j < m-1; j++) {
    //         cout << saltos[i][j].movimento << " ";
    //         k++;
    //     }
    //     cout<< endl;
    // }

    // cout << endl;

    // ofstream output;
    // output.open("output");

    // output << alignmentSeqA << "\n";
    // output << match << "\n";
    // output << alignmentSeqB << "\n";

    // output.close();

    // cout << alignmentSeqA << endl;
    // cout << match << endl;
    // cout << alignmentSeqB;

    return 0;
}