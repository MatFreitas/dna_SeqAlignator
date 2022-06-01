#include<iostream>
#include<algorithm>
#include <bits/stdc++.h>
#include<fstream>
#include<random>
#include<cstring>
#include <string.h>
#include<omp.h>
#include <thrust/transform.h>
#include <thrust/transform_reduce.h>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/iterator/counting_iterator.h>
using namespace std;

struct calculo
{
    thrust::device_ptr<int> comb_A_index;
    thrust::device_ptr<int> comb_B_index;
    string * a_combinations;
    string * b_combinations;

    calculo(thrust::device_ptr<int> comb_A_index_, thrust::device_ptr<int> comb_B_index_, string * a_combinations_, string * b_combinations_) :
    comb_A_index(comb_A_index_),
    comb_B_index(comb_B_index_),
    a_combinations(a_combinations_),
    b_combinations(b_combinations_) {};
    

    __host__
    int operator()(const int& x) {
        // thrust::device_vector<char> a(int(a_combinations[comb_A_index[x]].size()));

        // for(int i = 0; i < int(a_combinations[comb_A_index[x]].size()); i++) {
        //     a[i] = a_combinations[comb_A_index[x]][i];
        // }

        // string a = a_combinations[comb_A_index[x]];
        return 0;
    }
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

int algorithmLocalAlignment(int n, int m, string sa, string sb) {
    return 0;
}

int main() {
    // Inicializando as seq. A e B e 
    // seus respectivos tamanhos
    int n, m;
    string a, b;

    cin >> n >> m;
    cin >> a >> b;

    vector<string> a_combinations = subString(a, n);
    vector<string> b_combinations = subString(b, m);

    thrust::device_vector<int> comb_A_index; 
    thrust::device_vector<int> comb_B_index; 

    for(uint i = 0; i < a_combinations.size(); i++) {
        for(uint j = 0; j < b_combinations.size(); j++) {
            comb_A_index.push_back(i);
        }
    }

    thrust::sequence(comb_B_index.begin(), comb_B_index.end(), 1);

    thrust::counting_iterator<int> c0(0);
    thrust::counting_iterator<int> c1(int(comb_A_index.size()));

    thrust::device_vector<int> calc[2];
    calc[0].resize(n+1);
    calc[1].resize(n+1);
    thrust::fill(calc[0].begin(), calc[0].end(), 0);

    thrust::transform(c0, c1, calc[1].begin() + 1, calculo(comb_A_index.data(), comb_B_index.data(), a_combinations.data(), b_combinations.data()));


    

    // thrust::device_vector<int> calc[2];
    // calc[0].resize(n+1);
    // calc[1].resize(n+1);
    // thrust::fill(calc[0].begin(), calc[0].end(), 0);
    // thrust::device_vector<char> d_S(a_combinations[i].begin(), a_combinations[i].end());
    // thrust::device_vector<char> d_T(b_combinations[j].begin(), a_combinations[j].end());

    // thrust::counting_iterator<int> c0(0);
    // thrust::counting_iterator<int> c1(0);

    // for(int j = 0; j < m; j++) {

    // }
    





    // for(uint i = 0; i < a_combinations.size(); i++) {
    //     for(uint j = 0; j < b_combinations.size(); j++) {
    //         n = a_combinations[i].size();
    //         m = b_combinations[j].size();

    //         thrust::device_vector<int> calc[2];
    //         calc[0].resize(n+1);
    //         calc[1].resize(n+1);
    //         thrust::fill(calc[0].begin(), calc[0].end(), 0);
    //         thrust::device_vector<char> d_S(a_combinations[i].begin(), a_combinations[i].end());
    //         thrust::device_vector<char> d_T(b_combinations[j].begin(), a_combinations[j].end());

    //         for(int index = 0; index < m; index++) {
    //             char letradeT = b_combinations[j][index];

    //         }

            
    //         int scoreAlignment = algorithmLocalAlignment(n, m, a_combinations[i], b_combinations[j]);
    //     }
    // }
    
    // thrust::device_vector<const char *> seq_A(a_combinations.size());
    // thrust::device_vector<const char *> seq_B(b_combinations.size());

    // thrust::copy(a_combinations.begin(), a_combinations.end(), seq_A.begin());
    // thrust::copy(b_combinations.begin(), b_combinations.end(), seq_B.begin());

    // thrust::device_vector<scores> resultados(a_combinations.size()*b_combinations.size());
    // thrust::transform(a_combinations.begin(), a_combinations.begin(), )
    return 0;
}