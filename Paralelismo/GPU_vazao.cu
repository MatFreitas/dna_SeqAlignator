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

struct index_ctrl {
    int start_sub;
    int size_sub;
};

struct temp {
    thrust::device_ptr<char> subseqB_GPU;
    thrust::device_ptr<index_ctrl> indexB;
    thrust::device_ptr<char> subseq_A;

    temp(thrust::device_ptr<char> subseqB_GPU_, thrust::device_ptr<index_ctrl> indexB_, thrust::device_ptr<char> subseq_A_) :
    subseqB_GPU(subseqB_GPU_),
    indexB(indexB_),
    subseq_A(subseq_A_) {};

     __host__ __device__
    int operator()(const int& i) {
        return 0;
    }    
};

struct calculoScore
{
    int size_allsubB;
    thrust::device_ptr<index_ctrl> indexA;
    thrust::device_ptr<index_ctrl> indexB;
    thrust::device_ptr<char> subseqA_GPU;
    thrust::device_ptr<char> subseqB_GPU;

    

    calculoScore(int size_allsubB_, thrust::device_ptr<index_ctrl> indexA_, thrust::device_ptr<index_ctrl> indexB_, thrust::device_ptr<char> subseqA_GPU_, thrust::device_ptr<char> subseqB_GPU_) :
    size_allsubB(size_allsubB_),
    indexA(indexA_),
    indexB(indexB_),
    subseqA_GPU(subseqA_GPU_),
    subseqB_GPU(subseqB_GPU_) {};
    
    __host__ __device__
    int operator()(const int& i) {
        index_ctrl current_indexA;
        current_indexA = indexA[i];
        thrust::device_ptr<char> subseq_A;
        
        int contador = 0;
        for(uint ite = current_indexA.start_sub; ite < current_indexA.size_sub; ite++) {
            subseq_A[contador] = subseqA_GPU[ite]; 
            contador++;
        }
        
        // thrust::counting_iterator<int> c0(0);
        // thrust::counting_iterator<int> c1(size_allsubB);
        // thrust::device_ptr<int> scores;

        // thrust::transform(c0, c1, scores, temp(subseqB_GPU, indexB, subseq_A));        

        for(uint i = 0; i < size_allsubB; i++) {
            index_ctrl current_indexB;
            current_indexB = indexB[i];
            thrust::device_ptr<char> subseq_B;

            int contador = 0;
            for(uint ite = current_indexB.start_sub; ite < current_indexB.size_sub; ite++) {
                subseq_B[contador] = subseqB_GPU[ite]; 
                contador++;
            }

            
            // int score = (letradeB == subA[x-1] ? 2 : -1);

            // int diagonal = calc0[x-1] + score;
            // int cima = calc0[x] - 1;

            // int result;
            // if(diagonal >= cima && diagonal > 0) {
            //     result = diagonal;
            // } else if (cima > 0) {
            //     result = cima;
            // } else {
            //     result = 0;
            // }

            return result;
        }

        return 0;
    }
};

int main() {
     // Inicializando as seq. A e B e 
    // seus respectivos tamanhos
    int n, m;
    string a, b;

    cin >> n >> m;
    cin >> a >> b;

    vector<string> a_combinations = subString(a, n);
    vector<string> b_combinations = subString(b, m);

    thrust::device_vector<char> subseqA_GPU;
    thrust::device_vector<index_ctrl> indexA;

    int start_subA = 0;
    for(uint i = 0; i < a_combinations.size(); i++) {
        
        for(uint j = 0; j < a_combinations[i].size(); j++) {
            subseqA_GPU.push_back(a_combinations[i][j]);
        }

        index_ctrl current_substring;
        int size_subA = int(a_combinations[i].size());
        current_substring.start_sub = start_subA;
        current_substring.size_sub = size_subA;
        indexA.push_back(current_substring);
        start_subA += size_subA;
    }

    thrust::device_vector<char> subseqB_GPU;
    thrust::device_vector<index_ctrl> indexB;

    int start_subB = 0;
    for(uint i = 0; i < b_combinations.size(); i++) {
        
        for(uint j = 0; j < b_combinations[i].size(); j++) {
            subseqB_GPU.push_back(b_combinations[i][j]);
        }

        index_ctrl current_substring;
        int size_subB = int(b_combinations[i].size());
        current_substring.start_sub = start_subB;
        current_substring.size_sub = size_subB;
        indexB.push_back(current_substring);
        start_subB += size_subB;
    }

    thrust::counting_iterator<int> c0(1);
    thrust::counting_iterator<int> c1(int(indexA.size()) + 1);
    thrust::device_vector<int> scores(int(indexA.size()));

    thrust::transform(c0, c1, scores.begin(), calculoScore(int(indexB.size()), indexA.data(), indexB.data(), subseqA_GPU.data(), subseqB_GPU.data()));

    // cout << thrust::reduce(scores.begin(), scores.end(), 0, thrust::maximum<int>()) << endl;


    // for(uint i = 0; i < subseqA_GPU.size(); i++) {
    //     cout << subseqA_GPU[i] << endl;
    // }

    // for(uint i = 0; i < a_combinations.size(); i++) {
    //     cout << a_combinations[i] << endl;
    // }

    // for(uint i = 0; i < indexA.size(); i++) {
    //     index_ctrl current_index;
    //     current_index = indexA[i];
    //     cout << current_index.start_sub << endl;
    // }

    // for(int i = 0; i < n; i++){
    //     string s="";
    //     for(int j = i; j < n; j++){
    //         s+=a[j];
    //         subseqA_GPU.push_back(a[j]);
    //     }
    // }
    
    return 0;
}
