#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Convolution - O(m*n)
void convolution(int A[], int m, int B[], int n, int C[]) {
    int resLen = m + n - 1;
    for (int k = 0; k < resLen; k++) {
        C[k] = 0;
        for (int j = 0; j < m; j++) {
            int idx = k - j;
            if (idx >= 0 && idx < n) {
                C[k] += A[j] * B[idx];
            }
        }
    }
}

// Merge for merge sort
void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    
    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];
    
    for (i = left; i <= right; i++)
        arr[i] = temp[i];
}

// Divide and conquer approach
void conv2(int A[], int m, int B[], int n, int C[]) {
    // For true O(n log n), use FFT
    
    if (m <= 16 || n <= 16) {
        convolution(A, m, B, n, C);
        return;
    }
    
    // Full FFT algorithm needed for O(n log n)
    convolution(A, m, B, n, C);
}

void printArr(int arr[], int len, int max) {
    int show = (len < max) ? len : max;
    for (int i = 0; i < show; i++)
        printf("%d ", arr[i]);
    if (len > max) printf("...");
    printf("\n");
}

int main() {
    int choice, m, n;
    
    printf("Enter 1 for manual input, 2 for random generation: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("Enter size m (for array A): ");
        scanf("%d", &m);
        printf("Enter size n (for array B, n >= m): ");
        scanf("%d", &n);
        
        if (n < m) {
            printf("Error: n must be >= m\n");
            return 1;
        }
        
        int *A = (int *)malloc(m * sizeof(int));
        int *B = (int *)malloc(n * sizeof(int));
        int *C = (int *)malloc((m + n - 1) * sizeof(int));
        
        printf("Enter array A (%d elements): ", m);
        for (int i = 0; i < m; i++)
            scanf("%d", &A[i]);
        
        printf("Enter array B (%d elements): ", n);
        for (int i = 0; i < n; i++)
            scanf("%d", &B[i]);
        
        printf("\nArray A: ");
        printArr(A, m, 20);
        printf("Array B: ");
        printArr(B, n, 20);
        
        convolution(A, m, B, n, C);
        printf("\nConvolution C (length %d): ", m + n - 1);
        printArr(C, m + n - 1, 20);
        
        printf("\nFormula: C[k] = sum(A[j]*B[k-j]) for valid j\n");
        
        free(A);
        free(B);
        free(C);
        
    } else {
        srand(time(NULL));
        m = rand() % 8 + 3; // 3-10
        n = rand() % 8 + m; // >= m
        
        int *A = (int *)malloc(m * sizeof(int));
        int *B = (int *)malloc(n * sizeof(int));
        int *C = (int *)malloc((m + n - 1) * sizeof(int));
        
        printf("m = %d, n = %d\n", m, n);
        
        printf("Array A: ");
        for (int i = 0; i < m; i++) {
            A[i] = rand() % 10;
            printf("%d ", A[i]);
        }
        printf("\n");
        
        printf("Array B: ");
        for (int i = 0; i < n; i++) {
            B[i] = rand() % 10;
            printf("%d ", B[i]);
        }
        printf("\n");
        
        convolution(A, m, B, n, C);
        printf("\nConvolution C (length %d): ", m + n - 1);
        printArr(C, m + n - 1, 30);
        
        printf("\nNaive: O(m*n)\n");
        printf("Optimal: O(n log n)\n");
        
        free(A);
        free(B);
        free(C);
    }
    
    return 0;
}
