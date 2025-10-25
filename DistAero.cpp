#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void llenarMatriz(double** mat, int tam){
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            if(i==j){
                mat[i][j]=0;
            }
            //Al ser una matriz simétrica:
            else if(j>i){
                mat[i][j]=rand() % 1401 + 100;
                mat[j][i]=mat[i][j];
            }
        }
    }
}

void imprimir(double** mat, int tam){
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            cout<<"\t"<<mat[i][j];
        }
        cout<<endl;
    }
}
/*Inicializamos un nuevo arreglo para almacenar las
distancias promedio */
double* promedioDistancias(double** mat, int tam){
    double* ptr = new double[tam];
    for(int i=0; i<tam; i++){
        double sum=0.0;
        for(int j=0; j<tam; j++){
            sum+=mat[i][j];
        }
        ptr[i]=sum/(tam-1);
    }
    return ptr;
}

/*Retornamos el indice respectivo al aeropuerto:*/
int minPromDistancias(double* p, int n){
    double MAX=*p;
    int indice=0;
    for(int i=1; i<n; i++){
        if(p[i]<MAX){
            MAX=p[i];
            indice=i;
        }
    }
    return indice;
}

/* Trabajamos por referencia el puntero, para que al momento
de darle valor nullptr al puntero, este sea modificado. */
void liberarMatriz(double**& mat, int n){
    for(int i=0; i<n; i++){
        delete[] mat[i];
        mat[i]=nullptr;
    }

    delete[] mat;
    mat=nullptr;
}

int main(){
    int n;
    //Leemos el número de aeropuertos:
    cout<<"Inserte el numero de aeropuertos: ";
    cin>>n;
    srand(time(NULL));

    //Inicializamos la matriz dinámica:
    double** distancias = new double*[n];
    for (int i=0; i<n; i++){
        distancias[i] = new double[n];
    }

    //Llenar matriz de variables aleatorias:
    llenarMatriz(distancias, n);

    //Imprimir matriz desarrollada:
    imprimir(distancias, n);

    //Calculamos el promedio de las distancias para cada aeropuerto:
    cout<<"Promedio de las distancias para cada aeropuerto:\n";
    double* ptr=promedioDistancias(distancias, n);
    cout<<fixed<<setprecision(2);
    for(int i=0; i<n; i++){
        cout<<"Aeropuerto "<<i+1<<" = "<<ptr[i]<<endl;
    }

    //Mostramos el aeropuerto con la menor distancia promedio:
    cout<<"El aeropuerto con la menor distancia promedio:\n";
    int ind=minPromDistancias(ptr, n);
    cout<<"Aeropuerto "<<ind+1<<" = "<<ptr[ind]<<endl;

    //Implementamos la funcion liberarMatriz, trabajando por referencia:
    liberarMatriz(distancias, n);

    //liberamos también el arreglo ptr que almacena los promedios:
    delete[] ptr;
    ptr=nullptr;

return 0;
}