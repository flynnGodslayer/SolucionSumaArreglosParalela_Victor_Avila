// SolucionSumaArreglosParalela.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

// Mandamos a llamar las library que usaremos
#include <cstdlib>
#include <iostream>
#include<conio.h>
#include <time.h>
# ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif

// Se define el numero de elementos a manejar en los arreglos
#define N 1000
// Se define el tamaño que tendrán los pedazos de los arreglos para que cada hilo se encargue de esta cantidad de elementos
#define chunk 500
// Se define el # de valores que mostraremos
#define mostrar 10
using namespace std;

int main()
{
    // Semilla para generar numeros random, puede mandar una alerta si se ejecuta en un timestamp de 64 bits y la funcion requiere 34. 
    // Se pierde info pero no importa, ya que solo es una seed
    srand(time(NULL));

    // Inicializamos 3 arreglos a rellenar 
    int arreglo_1[1000];
    int arreglo_2[1000];
    int arreglo_3[1000];

    // Rellenamos los arreglos con numeros aleatorios
    for (int i = 0; i <= 999; i++) {
        arreglo_1[i] = ((int)rand() / 1000) * (1000 - 1) + 1;
        arreglo_2[i] = ((int)rand() / 1000) * (1000 - 1) + 1;
    }

    // Imprimimos los primero 5 valores de cada arreglo para verificar sus contenidos
    
    std::cout << "Los primeros 10 valores del arreglo 1 son: \n";

    for (int i = 0; i <= mostrar; i++) {
        std::cout << arreglo_1[i] << " | ";
    }
    
    std::cout << "\n\n Los primeros 10 valores del arreglo 2 son: \n";

    for (int i = 0; i <= mostrar; i++) {
        std::cout << arreglo_2[i] << " | ";
    }

    cout << "\n\n\n Una vez definidos los arreglos, podemos hacer la suma de los 3 arreglos en paralelo con Open MP. ";
    cout << "\n Rellenaremos el arreglo_3 con la suma de arreglo_1 y arreglo_2. ";

    // Pasamos a la variable pedazos el valor de la vazriable global chunk
    int pedazos = chunk;
    // inicializamos la variable del contador
    int j;

    // Iniciamos la función de OpenMP para ejecutar en paralelo el código que se encuentra dentro de ella
    // Definimos los arreglos que seran compartidos entre los hilos, y definimos el contador j como una 
    // variable privada de cada hilo para que no sea mezclada con los ciclos de otros hilos
    // Se define al scheduler como variable estatica, definiendo cuantos pedazos debe de tomar. En este caso 500 para que sean 2 hilos. 
#pragma omp parallel for \
    shared(arreglo_1, arreglo_2, arreglo_3) private(j) \
    schedule (static, pedazos)

    // Se hace el bucle de suma de cada objeto en el arreglo
    for (j = 0; j < N; j++)
        arreglo_3[j] = arreglo_1[j] + arreglo_2[j];
    
    // Se imprimen los valores de la suma de los primeros 10 valores
    cout << "La suma de los primeros " << mostrar << " valores esta en marcha " << endl;
    for (int x = 0; x <= mostrar; x++)
        cout << arreglo_2[x] << " | ";

    cout << "\n\n\n ";
    

}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
