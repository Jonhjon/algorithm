#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include<time.h>
using namespace std;

int** Read_File(string path, int& n) {
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
void Printf_matrix(int** A, int n) {
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
void Free(int** data, int n) {
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
void matrix_add(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void matrix_subtract(int n, int** A, int** B, int** C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j]; // 元素逐一相減
        }
    }
}

void strassen_matrix_multiply(int n, int** A, int** B, int** C) {
    
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
    }
    else {
        int mid = n / 2;  

        // 分配子矩陣
        int** A11 = creat_memory(mid), ** A12 = creat_memory(mid), ** A21 = creat_memory(mid), ** A22 = creat_memory(mid);
        int** B11 = creat_memory(mid), ** B12 = creat_memory(mid), ** B21 = creat_memory(mid), ** B22 = creat_memory(mid);
        int** C11 = creat_memory(mid), ** C12 = creat_memory(mid), ** C21 = creat_memory(mid), ** C22 = creat_memory(mid);
        int** M1 = creat_memory(mid), ** M2 = creat_memory(mid), ** M3 = creat_memory(mid), ** M4 = creat_memory(mid), ** M5 = creat_memory(mid), ** M6 = creat_memory(mid), ** M7 = creat_memory(mid);
        int** temp1 = creat_memory(mid), ** temp2 = creat_memory(mid);  // 用於中間結果的矩陣

        // 初始化結果矩陣 C 的子矩陣為 0
        for (int i = 0; i < mid; i++) {
            for (int j = 0; j < mid; j++) {
                C11[i][j] = 0;
                C12[i][j] = 0;
                C21[i][j] = 0;
                C22[i][j] = 0;
            }
        }

        // 將矩陣 A 和 B 分解為四個子矩陣
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

        // 計算 Strassen 算法的 7 個乘積 M
        matrix_add(mid, A11, A22, temp1); // temp1 = A11 + A22
        matrix_add(mid, B11, B22, temp2); // temp2 = B11 + B22
        strassen_matrix_multiply(mid, temp1, temp2, M1); // M1 = (A11 + A22) * (B11 + B22)

        matrix_add(mid, A21, A22, temp1); // temp1 = A21 + A22
        strassen_matrix_multiply(mid, temp1, B11, M2); // M2 = (A21 + A22) * B11

        matrix_subtract(mid, B12, B22, temp1); // temp1 = B12 - B22
        strassen_matrix_multiply(mid, A11, temp1, M3); // M3 = A11 * (B12 - B22)

        matrix_subtract(mid, B21, B11, temp1); // temp1 = B21 - B11
        strassen_matrix_multiply(mid, A22, temp1, M4); // M4 = A22 * (B21 - B11)

        matrix_add(mid, A11, A12, temp1); // temp1 = A11 + A12
        strassen_matrix_multiply(mid, temp1, B22, M5); // M5 = (A11 + A12) * B22

        matrix_subtract(mid, A21, A11, temp1); // temp1 = A21 - A11
        matrix_add(mid, B11, B12, temp2); // temp2 = B11 + B12
        strassen_matrix_multiply(mid, temp1, temp2, M6); // M6 = (A21 - A11) * (B11 + B12)

        matrix_subtract(mid, A12, A22, temp1); // temp1 = A12 - A22
        matrix_add(mid, B21, B22, temp2); // temp2 = B21 + B22
        strassen_matrix_multiply(mid, temp1, temp2, M7); // M7 = (A12 - A22) * (B21 + B22)

        // 計算子矩陣 C
        matrix_add(mid, M1, M4, temp1);
        matrix_subtract(mid, temp1, M5, temp2);
        matrix_add(mid, temp2, M7, C11); // C11 = M1 + M4 - M5 + M7

        matrix_add(mid, M3, M5, C12); // C12 = M3 + M5
        matrix_add(mid, M2, M4, C21); // C21 = M2 + M4

        matrix_add(mid, M1, M3, temp1);
        matrix_subtract(mid, temp1, M2, temp2);
        matrix_add(mid, temp2, M6, C22); // C22 = M1 + M3 - M2 + M6

        // 將子矩陣合併到結果矩陣 C 中
        for (int i = 0; i < mid; i++) {
            for (int j = 0; j < mid; j++) {
                C[i][j] = C11[i][j];
                C[i][j + mid] = C12[i][j];
                C[i + mid][j] = C21[i][j];
                C[i + mid][j + mid] = C22[i][j];
            }
        }
        Free(A11, mid); Free(A12, mid); Free(A21, mid); Free(A22, mid);
        Free(B11, mid); Free(B12, mid); Free(B21, mid); Free(B22, mid);
        Free(C11, mid); Free(C12, mid); Free(C21, mid); Free(C22, mid);
        Free(temp1, mid); Free(temp2, mid);
    }
}

int main() {

    fstream file;
    string path = "Data/1A.txt";
    string path2 = "Data/1B.txt";
    int n = 0, n2 = 0;
    clock_t start_t= 0, finish_t = 0;

    int** A = NULL, ** B = NULL, ** C = NULL;

    A = Read_File(path, n);
    Printf_matrix(A, n);
    B = Read_File(path2, n2);
    Printf_matrix(B, n2);
    C = creat_memory(n);
    start_t = clock();
    for (int i = 0; i < 10000; i++)
    {
        strassen_matrix_multiply(n, A, B, C);
        finish_t = clock();
    }
    Printf_matrix(C, n);
    double Time = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
    cout << "時間為 : " << Time;
    //cout << start_t<<"  "<<finish_t;
    Free(A, n);
    Free(B, n2);
    Free(C, n);
    return 0;
}
