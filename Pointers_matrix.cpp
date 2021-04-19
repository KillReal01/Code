#include <iostream>
using namespace std;

const int N = 4, M = 10;

void show_1(int* A) {//Двумерный массив через указатель как одномерный массив
    for (int i = 0; i < N * M; i++)
        cout << A[i] << " ";
}

void show_2(int* A[]) {//Двумерный массив через массив указателей
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
}

int main()
{

    //Создаем двумерный массив
    int A[N][M] = {};
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            A[i][j] = rand() % 10;

    // show_1((int*)A);

     //Создаем массив указателей
    int* ptr[N];
    for (int i = 0; i < N; i++)
        ptr[i] = A[i];

    show_2(ptr);


    return 0;
}