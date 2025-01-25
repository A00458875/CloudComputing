// SumaArreglos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>        //Se improta la librer�a de OpenMP.
#include <cstdlib>      //Se importa para poder utilizar rand() y srand().
#include <ctime>        //Se importa para poder utilizar time() como semilla del random.

//Se definen las constantes que se utilizar�n como tama�os.
const int ARRAY_SIZE = 1000;
const int PARTITION_SIZE = 100;
const int PRINT_SIZE = 10; 

//Funci�n que permite llenar un arreglo con n�meros aleatorios.
void fillArray(int arrInt[], int iSize)
{
    for (int i = 0; i < iSize; i++)
    {
        arrInt[i] = rand() % 100; //Se generan valores aleatorios entre 0 y 99.
    }
}

//Funci�n que permite imprimir una parte del arreglo.
void printArray(const int arrInt[], int iPrintSize, char chrArrayName)
{
    std::cout << "Imprimiendo los primeros " << iPrintSize << " valores del arreglo " << chrArrayName << ":" << std::endl;
    for (int i = 0; i < iPrintSize; i++)
    {
        std::cout << arrInt[i] << " ";
    }
    std::cout << "...\n" << std::endl;
}

int main()
{
    std::cout << "Sumando arreglos en paralelo!\n";

    //Se declaran los tres arreglos a utilizar con el mismo tama�o.
    int arrIntA[ARRAY_SIZE], arrIntB[ARRAY_SIZE], arrIntC[ARRAY_SIZE];

    //Se define el �ndice para poder usarlo dentro del for paralelo.
    int i;

    //Se genera la semilla para los n�meros aleatorios. 
    //Se utiliza time(0) para obtener la hora actual en segundos y as� garantizar 
    //que en cada ejecuci�n los n�meros aleatoriso ser�n diferentes.
    srand(static_cast<unsigned int>(time(0)));

    //Se llenan los arreglos con n�meros aleatorios.
    fillArray(arrIntA, ARRAY_SIZE);
    fillArray(arrIntB, ARRAY_SIZE);

    int iChunck = PARTITION_SIZE;

    //Se paraleliza la suma utilizando OpenPM.
    #pragma omp parallel for \
            shared(arrIntA, arrIntB, arrIntC, iChunck) private(i) \
            schedule(static, iChunck)

    for (i = 0; i < ARRAY_SIZE; i++)
    {
        arrIntC[i] = arrIntA[i] + arrIntB[i]; //Se hace la suma del arreglo A y B; el resultado se almacena en C.
    }

    //Se imprimen los arreglos.
    printArray(arrIntA, PRINT_SIZE, 'A');
    printArray(arrIntB, PRINT_SIZE, 'B');
    printArray(arrIntC, PRINT_SIZE, 'C');
}
