#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
#include<cmath>
#include <chrono>

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

}ciudades;

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
    for(int i = 0; i < size; i++){
        X[i] = dis(gen32);
        Y[i] = dis(gen32);
    }
}

void Localizacion::gen_path(std::vector<int> &path, int size){
    std::random_shuffle(path.begin() + 1, path.end() - 1);//Esta función reorganiza cada una de las componentes del vector de manera aleatoria.
}

double Localizacion::length(std::vector<int> path, int size){
    double dx, dy;
    double subdis = 0;
    double distance = 0;
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

void min_distancia(Localizacion ciudades, int N, double t_i, double t_f, double R, std::vector <int> & path){//algoritmo del recocido simulado.
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

    std::vector <int> minPath(N + 1); 

    ciudades.initializer(N);
    ciudades.location(s, in, end, N);
    ciudades.print1(N);
    std::cout<<"\n";
    ciudades.print2(p, N);
    std::cout<<"#Distancia: "<<ciudades.length(ciudades.newpath, N)<<"\n";

    auto start =std::chrono::high_resolution_clock::now();
    
    min_distancia(ciudades, N, t_i, t_f, R, minPath);

    auto stop =std::chrono::high_resolution_clock::now();
    
    std::cout << "min path: "<< std::endl; 
    for (int ii = 0; ii <= N; ii ++){
        std::cout << minPath[ii] << " "; 
    }
    std::cout <<"Distancia minima: " << ciudades.length(minPath, N) << std::endl; 

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    
    std::cout << "tiempo total: " << duration.count() << std::endl;
    
    return 0;
}

