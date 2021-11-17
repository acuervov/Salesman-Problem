#include <vector>
#include <iostream>
#include <random>
#include "tsp.hpp"
#include <chrono>



void min_distancia(Localizacion ciudades, int N, double t_i, double t_f, double R, std::vector <int> &  path){//algoritmo del recocido simulado.
  double T = 0;
  double T_i = t_i;
  double T_f = t_f;
  double r = R;
  double rnd;
  double delta;
  int p = 1;
  T = T_i;

  int seed = 10;
  std::mt19937 gen32(seed);
  std::uniform_real_distribution<double> dis(0, 1);

  
  while(T > T_f){
    rnd = dis(gen32);
    ciudades.gen_path(ciudades.newpath, N);
    delta = ciudades.length(ciudades.newpath, N) - ciudades.length(ciudades.oldpath, N);
    if((delta < 0) || (exp((-1*delta)/T) > rnd)){
      ciudades.oldpath = ciudades.newpath;
      path = ciudades.newpath; 
    }
    T = T * r;
    ciudades.print2(p, N);
    std::cout<<"#Distancia: "<<ciudades.length(ciudades.newpath, N)<<"\n";
  }
}


int main(int argc, char **argv){
  const int N = std::atoi(argv[1]);//Cantidad de ciudades.
  const int s = std::atoi(argv[2]);//Semilla.
  const int in = std::atoi(argv[3]);//Límite inferior.
  const int end = std::atoi(argv[4]);//Límite superior.
  double t_i = std::atof(argv[5]);//Temperatura inicial;
  double t_f = std::atof(argv[6]);//Temperatura final;
  double R = std::atof(argv[7]);//factor de enfriamiento;
  int p = 0;
  std::vector <int> minPath; 

  Localizacion ciudades;
  ciudades.initializer(N);
  ciudades.location(s, in, end, N);
  ciudades.print1(N);
  std::cout<<"\n";
  ciudades.print2(p, N);
  std::cout<<"#Distancia: "<<ciudades.length(ciudades.newpath, N)<<"\n";

  auto start =std::chrono::high_resolution_clock::now();
  
  min_distancia(ciudades, N, t_i, t_f, R, minPath);

  auto stop =std::chrono::high_resolution_clock::now();

  std::cout << "#Mejor path: " << std::endl;
  for (int ii = 0; ii <= N; ii++){
    std::cout << minPath[ii] << " ";
  }
  std::cout << "Distancia mejor path: " << ciudades.length(minPath, N)<< std::endl; 

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    
    std::cout << "tiempo total: " << duration.count() << std::endl;
    
  return 0;
}




