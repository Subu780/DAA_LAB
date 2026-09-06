#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// (i) Matrix Addition - O(n^2)
void matAdd(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// (ii) Matrix Multiplication - O(n^3)
void matMul(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// (iii) Check if zero matrix - O(n^2)
int isZeroMat(int **A, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != 0)
                return 0;
    return 1;
}

// (iv) Check if symmetric - O(n^2)
int isSymmetric(int **A, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (A[i][j] != A[j][i])
                return 0;
    return 1;
}

// (v) Determinant using recursion - O(n!)
int determinant(int **A, int n) {
    if (n == 1) return A[0][0];
    if (n == 2) return A[0][0]*A[1][1] - A[0][1]*A[1][0];
    
    int det = 0;
    int **temp = (int **)malloc((n-1) * sizeof(int *));
    for (int i = 0; i < n-1; i++)
        temp[i] = (int *)malloc((n-1) * sizeof(int));
    
    for (int col = 0; col < n; col++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == col) continue;
                temp[subi][subj] = A[i][j];
                subj++;
            }
            subi++;
        }
        int sign = (col % 2 == 0) ? 1 : -1;
        det += sign * A[0][col] * determinant(temp, n-1);
    }
    
    for (int i = 0; i < n-1; i++)
        free(temp[i]);
    free(temp);
    return det;
}

// (vi) Transpose in place - O(n^2)
void transposeInPlace(int **A, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
}

// (vii) Find largest eigenvalue - O(n^2 * iterations)
double eigenvalue(int **A, int n, int maxIter) {
    double *v = (double *)malloc(n * sizeof(double));
    double *v_new = (double *)malloc(n * sizeof(double));
    
    // Initial vector
    for (int i = 0; i < n; i++)
        v[i] = 1.0;
    
    double eigval = 0;
    
    for (int iter = 0; iter < maxIter; iter++) {
        // v_new = A * v
        for (int i = 0; i < n; i++) {
            v_new[i] = 0;
            for (int j = 0; j < n; j++)
                v_new[i] += A[i][j] * v[j];
        }
        
        // Normalize
        double norm = 0;
        for (int i = 0; i < n; i++)
            norm += v_new[i] * v_new[i];
        norm = sqrt(norm);
        
        if (norm < 0.0001) break;
        
        for (int i = 0; i < n; i++)
            v[i] = v_new[i] / norm;
        
        // Estimate eigenvalue
        eigval = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                eigval += v[i] * A[i][j] * v[j];
    }
    
    free(v);
    free(v_new);
    return eigval;
}

// Allocate matrix
int** allocMat(int n) {
    int **mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        mat[i] = (int *)malloc(n * sizeof(int));
    return mat;
}

// Free matrix
void freeMat(int **mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

// Print matrix
void printMat(int **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d ", mat[j][i]);
        printf("\n");
    }
}

int main() {
    int choice, n;
    
    printf("Enter 1 for manual input, 2 for random generation: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter matrix size n: ");
        scanf("%d", &n);
        
        int **A = allocMat(n);
        int **B = allocMat(n);
        
        printf("Enter matrix A (%dx%d):\n", n, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &A[i][j]);
        
        printf("Enter matrix B (%dx%d):\n", n, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &B[i][j]);
        
        printf("\nMatrix A:\n");
        printMat(A, n);
        
        printf("\nMatrix B:\n");
        printMat(B, n);
        
        int **C = allocMat(n);
        matAdd(A, B, C, n);
        printf("\n(i) A + B:\n");
        printMat(C, n);
        
        matMul(A, B, C, n);
        printf("\n(ii) A * B:\n");
        printMat(C, n);
        
        printf("\n(iii) Is A zero matrix? %s\n", isZeroMat(A, n) ? "Yes" : "No");
        printf("(iv) Is A symmetric? %s\n", isSymmetric(A, n) ? "Yes" : "No");
        
        if (n <= 4) {
            printf("(v) Determinant of A: %d\n", determinant(A, n));
        } else {
            printf("(v) Determinant: Skipped (n>4, O(n!) too slow)\n");
        }
        
        transposeInPlace(A, n);
        printf("\n(vi) Transpose of A (in place):\n");
        printMat(A, n);
        
        // Need to restore A from transpose for eigenvalue calculation
        transposeInPlace(A, n);
        
        double eigval = eigenvalue(A, n, 50);
        printf("\n(vii) Largest eigenvalue of A: %.2f\n", eigval);
        
        freeMat(A, n);
        freeMat(B, n);
        freeMat(C, n);
        
    } else {
        srand(time(NULL));
        n = rand() % 4 + 3; // 3-6
        
        int **A = allocMat(n);
        int **B = allocMat(n);
        
        printf("Matrix size: %dx%d\n", n, n);
        printf("\nMatrix A:\n");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                A[i][j] = rand() % 10;
        printMat(A, n);
        
        printf("\nMatrix B:\n");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                B[i][j] = rand() % 10;
        printMat(B, n);
        
        int **C = allocMat(n);
        matAdd(A, B, C, n);
        printf("\n(i) A + B:\n");
        printMat(C, n);
        
        matMul(A, B, C, n);
        printf("\n(ii) A * B:\n");
        printMat(C, n);
        
        printf("\n(iii) Is A zero? %s\n", isZeroMat(A, n) ? "Yes" : "No");
        printf("(iv) Is A symmetric? %s\n", isSymmetric(A, n) ? "Yes" : "No");
        printf("(v) Det(A): %d\n", determinant(A, n));
        
        transposeInPlace(A, n);
        printf("\n(vi) A^T:\n");
        printMat(A, n);
        
        transposeInPlace(A, n);
        
        double eigval = eigenvalue(A, n, 50);
        printf("\n(vii) Largest eigenvalue: %.2f\n", eigval);
        
        freeMat(A, n);
        freeMat(B, n);
        freeMat(C, n);
    }
    
    return 0;
}
