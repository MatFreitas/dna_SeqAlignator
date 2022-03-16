#include<iostream>
#include<algorithm>
#include <bits/stdc++.h>
using namespace std;

int main() {
    // Inicializando tamanho n, m 
    // das seq. A e B, respectivamente
    int n, m;
    cin >> n >> m;

    // Inicializando lista de movimentos
    string movimentos[n][m];

    // Inicializando as seq. A e B
    string a, b;
    cin >> a >> b;

    // Adicionando o gap _
    a = "-" + a;
    cout << a << endl;
    n++;

    b = "-" + b;
    cout << b << endl;
    m++;
    
    // Matriz H a ser preenchida
    int H[n][m];


    // Inicializar matriz com 0s.
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            H[i][j] = 0;
        }
    }

    cout << endl;

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
            if(H[i][j] == 0) {
               movimentos[i-1][j-1] = "nenh";
            } else if(H[i][j] == diagonal) {
                movimentos[i-1][j-1] = "diag";
            } else if(H[i][j] == delecao) {
                movimentos[i-1][j-1] = "cima";
            } else if(H[i][j] == insercao) {
                movimentos[i-1][j-1] = "esqu";
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

    cout << "Movimentos:" << endl;
    while(maxValor_i >= 0 && maxValor_j >= 0) {
        if(movimentos[maxValor_i][maxValor_j] == "nenh") {
            break;
        }
        else if(movimentos[maxValor_i][maxValor_j] == "diag") {
            maxValor_i--;
            maxValor_j--;

            alignmentSeqA += a[maxValor_i+2];
            alignmentSeqB += b[maxValor_j+2];
            match += "*";

            cout << "diag" << endl;
        }
        else if(movimentos[maxValor_i][maxValor_j] == "esqu") {
            maxValor_j--;

            alignmentSeqA += "_";
            alignmentSeqB += b[maxValor_j+2];
            match += " ";

            cout << "esqu" << endl;
        }
        else if(movimentos[maxValor_i][maxValor_j] == "cima") {
            maxValor_i--;

            alignmentSeqA += a[maxValor_i+2];
            alignmentSeqB += "_";
            match += " ";

            cout << "cima" << endl;
        }
    }

    reverse(alignmentSeqA.begin(), alignmentSeqA.end());
    reverse(alignmentSeqB.begin(), alignmentSeqB.end());
    reverse(match.begin(), match.end());

    // Prints
    cout << endl;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << H[i][j] << " ";
        }
        cout<< endl;
    }

    cout << endl << "MaxValor   : " << maxValor << endl;
    cout << endl;


    int k = 0;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < m-1; j++) {
            cout << movimentos[i][j] << " ";
            k++;
        }
        cout<< endl;
    }

    cout << endl;
    cout << alignmentSeqA << endl;
    cout << match << endl;
    cout << alignmentSeqB << endl;

    return 0;
}