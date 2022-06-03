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

struct calculoScore
{
    thrust::device_ptr<char> subA;
    char letradeB;
    thrust::device_ptr<int> calc0;

    calculoScore(thrust::device_ptr<char> subA_, char letradeB_, thrust::device_ptr<int> calc0_) :
    subA(subA_),
    letradeB(letradeB_),
    calc0(calc0_) {};
    
    __host__ __device__
    int operator()(const int& x) {

        int score = (letradeB == subA[x-1] ? 2 : -1);

        int diagonal = calc0[x-1] + score;
        int cima = calc0[x] - 1;

        int result;
        if(diagonal >= cima && diagonal > 0) {
            result = diagonal;
        } else if (cima > 0) {
            result = cima;
        } else {
            result = 0;
        }

        return result;
    }
};

struct calculoHorizontal
{
    
    __host__ __device__
    int operator()(const int& i, const int& j) {
        int max, actual, left;

        actual = j;
        left = i - 1;

        if(left >= actual && left > 0) {
            max = left;
        } else if(actual > 0) {
            max = actual;
        } else {
            max = 0;
        }

        return max;
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
    thrust::counting_iterator<int> c0(1);

    thrust::device_vector<int> maxScores;

    #pragma omp for collapse(2)
    for(uint i = 0; i < a_combinations.size(); i++) {
        for(uint j = 0; j < b_combinations.size(); j++) {

            thrust::device_vector<char> subA(a_combinations[i].begin(), a_combinations[i].end());
            thrust::device_vector<char> subB(b_combinations[j].begin(), b_combinations[j].end()); 

            thrust::device_vector<int> calc[2];
            calc[0].resize(subA.size()+1);
            calc[1].resize(subA.size()+1);
            thrust::fill(calc[0].begin(), calc[0].end(), 0);

            thrust::counting_iterator<int> c1(int(subA.size()) + 1);

            for(int k = 0; k < subB.size(); k++) {
                char letradeB = subB[k];
                thrust::transform(c0, c1, calc[1].begin() + 1, calculoScore(subA.data(), letradeB, calc[0].data()));
                thrust::inclusive_scan(calc[1].begin() + 1, calc[1].end(), calc[0].begin() + 1, calculoHorizontal());
            }


            maxScores.push_back(calc[0].back());
        }    
    }

    cout << thrust::reduce(maxScores.begin(), maxScores.end(), 0, thrust::maximum<int>()) << endl;
    return 0;
}
