#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
using namespace std;

int** Read_File(string path,int &n) {
    fstream file;
    //int n = 0;
    file.open(path);
    if (!file.is_open())
    {
        cout << "erro!\n";
    }

    file >> n;
    file >> n;

    int** A = new int* [n];
    for (int i = 0; i < n; i++)
    {
        A[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) {
            file >> A[i][j];
        }
    }
    file.close();
    return A;
}
void Printf_matrix(int** A,int n) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //cout << A[i][j] << " ";
            printf("%2d ", A[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}
void Free(int** data,int n) {
    for (int i = 0; i < n; i++)
        delete[] data[i];
    delete[] data;
}
int** creat_memory(int n) {
    int** C = new  int* [n];
    for (int i = 0; i < n; i++)
    {
        C[i] = new int[n];
    }
    return C;
}
void matrix_add(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void matrix_multiply_recursive(int n, int** A, int** B, int** C) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mid = n / 2;
    int** A11 = creat_memory(mid),**A12 = creat_memory(mid), **A21 = creat_memory(mid), **A22 = creat_memory(mid);
    int** B11 = creat_memory(mid), **B12 = creat_memory(mid), **B21 = creat_memory(mid), **B22 = creat_memory(mid);
    int** C11 = creat_memory(mid), **C12 = creat_memory(mid), **C21 = creat_memory(mid), **C22 = creat_memory(mid);
    int** temp = creat_memory(mid);
    // 分割矩阵
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    // 递归计算
    /*matrix_multiply_recursive(mid, A11, B11, C11);
    matrix_multiply_recursive(mid, A12, B21, C11);
    matrix_multiply_recursive(mid, A11, B12, C12);
    matrix_multiply_recursive(mid, A12, B22, C12);
    matrix_multiply_recursive(mid, A21, B11, C21);
    matrix_multiply_recursive(mid, A22, B21, C21);
    matrix_multiply_recursive(mid, A21, B12, C22);
    matrix_multiply_recursive(mid, A22, B22, C22);*/
    matrix_multiply_recursive(mid, A11, B11, C11);
    matrix_multiply_recursive(mid, A12, B21, temp);
    matrix_add(mid, C11, temp, C11);

    matrix_multiply_recursive(mid, A11, B12, C12);
    matrix_multiply_recursive(mid, A12, B22, temp);
    matrix_add(mid, C12, temp, C12);

    matrix_multiply_recursive(mid, A21, B11, C21);
    matrix_multiply_recursive(mid, A22, B21, temp);
    matrix_add(mid, C21, temp, C21);

    matrix_multiply_recursive(mid, A21, B12, C22);
    matrix_multiply_recursive(mid, A22, B22, temp);
    matrix_add(mid, C22, temp, C22);
    // 组合结果
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }
    Free(A11,mid);Free(A12, mid);Free(A21, mid);Free(A22, mid);
    Free(B11, mid);Free(B12, mid);Free(B21, mid);Free(B22, mid); 
    Free(C11, mid);Free(C12, mid);Free(C21, mid);Free(C22, mid);
    Free(temp, mid);
}





int main() {
   
    fstream file;
    string path = "Data/2A.txt";
    string path2 = "Data/2B.txt";
    int n = 0, n2 = 0;
    int** A=NULL, ** B =NULL, ** C=NULL;
    
    A = Read_File(path , n );
    Printf_matrix(A, n);
    B = Read_File(path2, n2);
    Printf_matrix(B, n2);
    C = creat_memory(n);
    matrix_multiply_recursive(n, A, B, C);
    Printf_matrix(C, n);

    Free(A, n);
    Free(B, n2);
    Free(C, n);
    return 0;
}
