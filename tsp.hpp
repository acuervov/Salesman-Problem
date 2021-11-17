
#pragma once 



class Localizacion{
public:
  std::vector<double> X;
  std::vector<double> Y;
  std::vector<int> oldpath;
  std::vector<int> newpath;
  void initializer(const int size);//Inicializa cada uno de los vectores.
  void location(int seed, int a, int b, int size);//Establece las posiciones de manera aleatoria de cada ciudad;
  void gen_path(std::vector<int> &path, int size);//establece un camino de manera aleatoria.
  double length(std::vector<int> path,int size);//Calcula la distancia total del camino que toma como parámetro.
  void print1(const int size);//imprime las ciudades y usu coordenadas.
  void print2(int p, int N);//imprime cada uno de los caminos.

};
