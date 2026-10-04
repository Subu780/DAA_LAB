/* Question 4: Longest Increasing Subsequence
   Method 1: O(n^2) DP    Method 2: O(n log n) with binary search */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 100000

int getMenuChoice() {
    int choice;
    while (1) {
        printf("Enter 1 to give input manually\n");
        printf("Enter 2 to generate random input\n");
        printf("Your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input, exiting.\n");
            exit(1);
        }
        if (choice == 1 || choice == 2)
            return choice;
        printf("Please enter only 1 or 2.\n\n");
    }
}

/* O(n^2): len[i] = LIS length ending at index i, prev[i] = index before i */
int lisQuadratic(int a[], int n, int seq[]) {
    int *len = (int *) malloc(n * sizeof(int));
    int *prev = (int *) malloc(n * sizeof(int));
    int i, j, best = 0, bestEnd = 0, k;

    for (i = 0; i < n; i++) {
        len[i] = 1;
        prev[i] = -1;
        for (j = 0; j < i; j++) {
            if (a[j] < a[i] && len[j] + 1 > len[i]) {
                len[i] = len[j] + 1;
                prev[i] = j;
            }
        }
        if (len[i] > best) {
            best = len[i];
            bestEnd = i;
        }
    }

    k = best;
    for (i = bestEnd; i != -1; i = prev[i])
        seq[--k] = a[i];

    free(len);
    free(prev);
    return best;
}

/* O(n log n): tails[k] = smallest last element of an increasing
   subsequence of length k+1. Each element replaces the first tail >= it. */
int lisFast(int a[], int n) {
    int *tails = (int *) malloc(n * sizeof(int));
    int size = 0, i, lo, hi, mid;

    for (i = 0; i < n; i++) {
        lo = 0;
        hi = size;
        while (lo < hi) {
            mid = (lo + hi) / 2;
            if (tails[mid] < a[i])
                lo = mid + 1;
            else
                hi = mid;
        }
        tails[lo] = a[i];
        if (lo == size)
            size++;
    }
    free(tails);
    return size;
}

int main() {
    int n, i, choice, len1, len2;
    int *a, *seq;

    srand((unsigned int) time(NULL));
    choice = getMenuChoice();

    if (choice == 1) {
        printf("Number of elements (1 to %d): ", MAX_N);
        if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N) {
            printf("Invalid size.\n");
            return 1;
        }
        a = (int *) malloc(n * sizeof(int));
        printf("Enter the %d elements: ", n);
        for (i = 0; i < n; i++) {
            if (scanf("%d", &a[i]) != 1) {
                printf("Invalid element.\n");
                return 1;
            }
        }
    } else {
        n = 8 + rand() % 8;
        a = (int *) malloc(n * sizeof(int));
        for (i = 0; i < n; i++)
            a[i] = 1 + rand() % 50;
        printf("Generated array:");
        for (i = 0; i < n; i++)
            printf(" %d", a[i]);
        printf("\n");
    }

    seq = (int *) malloc(n * sizeof(int));
    len1 = lisQuadratic(a, n, seq);
    len2 = lisFast(a, n);

    printf("O(n^2) method     : LIS length = %d\n", len1);
    printf("O(n log n) method : LIS length = %d\n", len2);
    printf("One such subsequence:");
    for (i = 0; i < len1; i++)
        printf(" %d", seq[i]);
    printf("\n");
    if (len1 != len2)
        printf("Mismatch between the two methods!\n");

    free(a);
    free(seq);
    return 0;
}
