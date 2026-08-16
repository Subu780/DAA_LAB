#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Helper to allocate an n x n matrix
int** create_matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));
    }
    return matrix;
}

// Helper to free an n x n matrix
void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Matrix Addition
void add_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// Matrix Subtraction
void sub_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

// O(n^2) Recursive Multiplication for Structured Matrices
void multiply_structured(int** A, int** B, int** C, int n) {
    // Base Case
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = n / 2;
    
    // Allocate Memory for submatrices
    int** A1 = create_matrix(half); int** A2 = create_matrix(half);
    int** B1 = create_matrix(half); int** B2 = create_matrix(half);

    // Extract A1, A2, B1, B2 (from top-left and top-right quadrants)
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + half];
            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + half];
        }
    }

    // Temporary matrices for operations
    int** T1 = create_matrix(half); int** T2 = create_matrix(half);
    int** T3 = create_matrix(half); int** T4 = create_matrix(half);
    int** P1 = create_matrix(half); int** P2 = create_matrix(half);

    // T1 = (A1 + A2), T2 = (B1 + B2)
    add_matrix(A1, A2, T1, half);
    add_matrix(B1, B2, T2, half);
    
    // T3 = (A1 - A2), T4 = (B1 - B2)
    sub_matrix(A1, A2, T3, half);
    sub_matrix(B1, B2, T4, half);

    // Only 2 Recursive Multiplications
    multiply_structured(T1, T2, P1, half); // P1 = (A1 + A2)(B1 + B2)
    multiply_structured(T3, T4, P2, half); // P2 = (A1 - A2)(B1 - B2)

    int** C1 = create_matrix(half);
    int** C2 = create_matrix(half);

    // C1 = (P1 + P2) / 2
    // C2 = (P1 - P2) / 2
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C1[i][j] = (P1[i][j] + P2[i][j]) / 2;
            C2[i][j] = (P1[i][j] - P2[i][j]) / 2;
        }
    }

    // Reconstruct the final matrix C using C1 and C2
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C1[i][j];                 // Top-Left (M1)
            C[i][j + half] = C2[i][j];          // Top-Right (M2)
            C[i + half][j] = C2[i][j];          // Bottom-Left (M2)
            C[i + half][j + half] = C1[i][j];   // Bottom-Right (M1)
        }
    }

    // Free memory
    free_matrix(A1, half); free_matrix(A2, half);
    free_matrix(B1, half); free_matrix(B2, half);
    free_matrix(T1, half); free_matrix(T2, half);
    free_matrix(T3, half); free_matrix(T4, half);
    free_matrix(P1, half); free_matrix(P2, half);
    free_matrix(C1, half); free_matrix(C2, half);
}

// Function to recursively generate a matrix with the required structure
void generate_structured_matrix(int** M, int r, int c, int size) {
    if (size == 1) {
        M[r][c] = rand() % 10;
        return;
    }
    int half = size / 2;
    
    // Generate M1 (top-left) and M2 (top-right)
    generate_structured_matrix(M, r, c, half);
    generate_structured_matrix(M, r, c + half, half);
    
    // Copy M2 to Bottom-Left
    for(int i = 0; i < half; i++) {
        for(int j = 0; j < half; j++) {
            M[r + half + i][c + j] = M[r + i][c + half + j];
        }
    }
    // Copy M1 to Bottom-Right
    for(int i = 0; i < half; i++) {
        for(int j = 0; j < half; j++) {
            M[r + half + i][c + half + j] = M[r + i][c + j];
        }
    }
}

// Check if a number is a power of 2
int is_power_of_two(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

int main() {
    int choice, n;

    printf("Enter 1 to input matrices manually, or 2 to generate randomly: ");
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        printf("Invalid choice.\n");
        return 1;
    }

    printf("Enter the dimension of the square matrices (n must be power of 2): ");
    if (scanf("%d", &n) != 1 || !is_power_of_two(n)) {
        printf("Invalid dimension. n must be a power of 2 (e.g., 2, 4, 8, 16).\n");
        return 1;
    }

    int** A = create_matrix(n);
    int** B = create_matrix(n);
    int** C = create_matrix(n);

    if (choice == 1) {
        printf("\nNOTE: For the algorithm to output correctly, the matrices MUST follow the M=[M1 M2; M2 M1] structure.\n");
        printf("Enter elements of Matrix A:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &A[i][j]);
            }
        }

        printf("Enter elements of Matrix B:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &B[i][j]);
            }
        }
    } else {
        srand(time(NULL));
        printf("\nGenerating random structured matrices...\n");
        generate_structured_matrix(A, 0, 0, n);
        generate_structured_matrix(B, 0, 0, n);

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
    }

    // Perform O(n^2) structured multiplication
    multiply_structured(A, B, C, n);

    printf("\nResultant Matrix C (A * B):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Cleanup
    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C, n);

    return 0;
}