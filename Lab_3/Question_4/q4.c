#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));
    }
    return matrix;
}

void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void add_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int new_size = n / 2;
    
    int** A11 = create_matrix(new_size); int** A12 = create_matrix(new_size);
    int** A21 = create_matrix(new_size); int** A22 = create_matrix(new_size);
    int** B11 = create_matrix(new_size); int** B12 = create_matrix(new_size);
    int** B21 = create_matrix(new_size); int** B22 = create_matrix(new_size);
    
    int** M1 = create_matrix(new_size); int** M2 = create_matrix(new_size);
    int** M3 = create_matrix(new_size); int** M4 = create_matrix(new_size);
    int** M5 = create_matrix(new_size); int** M6 = create_matrix(new_size);
    int** M7 = create_matrix(new_size);
    
    int** tempA = create_matrix(new_size); int** tempB = create_matrix(new_size);

    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            A11[i][j] = A[i][j]; A12[i][j] = A[i][j + new_size];
            A21[i][j] = A[i + new_size][j]; A22[i][j] = A[i + new_size][j + new_size];
            B11[i][j] = B[i][j]; B12[i][j] = B[i][j + new_size];
            B21[i][j] = B[i + new_size][j]; B22[i][j] = B[i + new_size][j + new_size];
        }
    }

    add_matrix(A11, A22, tempA, new_size); add_matrix(B11, B22, tempB, new_size);
    strassen(tempA, tempB, M1, new_size);

    add_matrix(A21, A22, tempA, new_size);
    strassen(tempA, B11, M2, new_size);

    sub_matrix(B12, B22, tempB, new_size);
    strassen(A11, tempB, M3, new_size);

    sub_matrix(B21, B11, tempB, new_size);
    strassen(A22, tempB, M4, new_size);

    add_matrix(A11, A12, tempA, new_size);
    strassen(tempA, B22, M5, new_size);

    sub_matrix(A21, A11, tempA, new_size); add_matrix(B11, B12, tempB, new_size);
    strassen(tempA, tempB, M6, new_size);

    sub_matrix(A12, A22, tempA, new_size); add_matrix(B21, B22, tempB, new_size);
    strassen(tempA, tempB, M7, new_size);

    add_matrix(M1, M4, tempA, new_size); sub_matrix(tempA, M5, tempB, new_size); add_matrix(tempB, M7, A11, new_size);
    add_matrix(M3, M5, A12, new_size);
    add_matrix(M2, M4, A21, new_size);
    sub_matrix(M1, M2, tempA, new_size); add_matrix(tempA, M3, tempB, new_size); add_matrix(tempB, M6, A22, new_size);

    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            C[i][j] = A11[i][j]; C[i][j + new_size] = A12[i][j];
            C[i + new_size][j] = A21[i][j]; C[i + new_size][j + new_size] = A22[i][j];
        }
    }

    free_matrix(A11, new_size); free_matrix(A12, new_size); free_matrix(A21, new_size); free_matrix(A22, new_size);
    free_matrix(B11, new_size); free_matrix(B12, new_size); free_matrix(B21, new_size); free_matrix(B22, new_size);
    free_matrix(M1, new_size); free_matrix(M2, new_size); free_matrix(M3, new_size); free_matrix(M4, new_size);
    free_matrix(M5, new_size); free_matrix(M6, new_size); free_matrix(M7, new_size);
    free_matrix(tempA, new_size); free_matrix(tempB, new_size);
}

int next_power_of_two(int n) {
    int p = 1;
    while (p < n) {
        p *= 2;
    }
    return p;
}

int main() {
    int n, choice;
    
    printf("Enter 1 to input matrices manually, or 2 to generate randomly: ");
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Invalid choice.\n");
        return 1;
    }

    printf("Enter the dimension of the square matrices (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int m = next_power_of_two(n);

    int** A = create_matrix(m);
    int** B = create_matrix(m);
    int** C = create_matrix(m);

    if (choice == 1) {
        printf("\nEnter elements of Matrix A:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &A[i][j]);
            }
        }

        printf("\nEnter elements of Matrix B:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &B[i][j]);
            }
        }
    } else {
        srand(time(NULL));
        printf("\nGenerating random matrices...\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10; // Keeping numbers small to prevent overflow
                B[i][j] = rand() % 10;
            }
        }
        
        // Only print the generated matrices if they are small enough
        if (n <= 16) {
            printf("\nMatrix A:\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%d ", A[i][j]);
                }
                printf("\n");
            }
            
            printf("\nMatrix B:\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%d ", B[i][j]);
                }
                printf("\n");
            }
        } else {
            printf("(Matrices are too large to print, skipping input display.)\n");
        }
    }

    strassen(A, B, C, m);

    if (n <= 16 || choice == 1) {
        printf("\nResultant Matrix C (A * B):\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("\nMultiplication complete. (Result matrix too large to print)\n");
    }

    free_matrix(A, m);
    free_matrix(B, m);
    free_matrix(C, m);

    return 0;
}