#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
#include<cmath>
#include<omp.h>
#include "tsp.hpp"


void Localizacion::initializer(const int size){
    for(int i = 0; i < size; i++){
        X.push_back(i);
        Y.push_back(i);
    }

    for(int j = 0; j <= size; j++){
        oldpath.push_back(j);
        newpath.push_back(j);
    }

    for(int i = 0; i <= size; i++){
        if(i < size){
            continue;
        }
        else if(i == size){
            newpath[i] = newpath[0];
            oldpath[i] = oldpath[0];
        }
    }
}

void Localizacion::location(int seed, int a, int b, int size){
    std::mt19937 gen32(seed);
    std::uniform_real_distribution<double> dis(a, b);
#pragma parallel for
    {
    for(int i = 0; i < size; i++){
        X[i] = dis(gen32);
        Y[i] = dis(gen32);
    }
     }
}

void Localizacion::gen_path(std::vector<int> &path, int size){
    std::random_shuffle(path.begin() + 1, path.end() - 1);//Esta función reorganiza cada una de las componentes del vector de manera aleatoria.
}

double Localizacion::length(std::vector<int> path, int size){
    double dx, dy;
    double subdis = 0;
    double distance = 0;

#pragma parallel for reduction(+:distance) 
    for(int i = 0; i < size; i++){
        dx = X[path[i + 1]] - X[path[i]];
        dy = Y[path[i + 1]] - Y[path[i]];
        subdis = sqrt(pow(dx, 2) + pow(dy, 2));
        distance += subdis;
    }
    return distance;
}

void Localizacion::print1(const int size){
    for(int i = 0; i < size; i++){
        std::cout<<"Coordenadas ciudad"<<i + 1<<": ("<<X[i]<<", "<<Y[i]<<").\n";
    }
}

void Localizacion::print2(int p, int N){
    if(p == 0){
        std::cout<<"Camino inicial: ";
        for(int i = 0; i <= N; i++){
            if(i < N){
                std::cout<<newpath[i]<<"-->";
            }
            else if(i == N){
                std::cout<<newpath[i]<<"\n";
            }    
        }
    }
    else{
        std::cout<<"Camino: ";
        for(int i = 0; i <= N; i++){
            if(i < N){
                std::cout<<newpath[i]<<"-->";
            }
            else if(i == N){
                std::cout<<newpath[i]<<"\n";
            }    
        }
    }
}


