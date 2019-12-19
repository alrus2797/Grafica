#ifndef BEZIER_H
#define BEZIER_H

#include <stdio.h>
#include <vector>
#include <math.h>

typedef std::vector<std::vector<int>> BinomialTree;

BinomialTree lut;

int binomial(int n, int k){
    int s;
    while(n >= lut.size()){
        s = lut.size();
        std::vector<int> row(s+1, 0);
        row[0] = 1;
        for (size_t i = 0, prev = s-1; i < s; i++)
        {
            row[i] = lut[prev][i-1] + lut[prev][i];
        }
        row[s] = 1;
        lut.push_back(row);
    }
    return lut[n][k];
}

void print_list(std::vector<int> &a){
    size_t i;
    for (i = 0; i < a.size()-1; i++)
    {
        printf("%i ", a[i]);
    }
    printf("%i\n", a[i]);
    
}

void print_binomial(){
    for (size_t i = 0; i < lut.size(); i++)
    {
        printf("\t\t\t");
        print_list(lut[i]);
    }
}


int bezier(int n, double t, std::vector<int> &w){
    int sum = 0, val = 0;
    for (size_t k = 0; k <= n; k++)
    {
        val = w[k] * binomial(n, k) * pow((1-t), n-k) * pow(t,k);
        // printf("\t %i %i\n", sum, val);
        sum += val;
    }
    return sum;
    
}

// int main(int argc, char const *argv[])
// {
//     printf("Hello World!\n");
//     binomial(4,3);
//     printf("%i\n", bezier(2,));

//     print_binomial();
//     return 0;
// }

#endif