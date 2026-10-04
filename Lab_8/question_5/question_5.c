/* Question 5: Maximum Sum Increasing Subsequence */
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

int main() {
    int n, i, j, choice, bestEnd = 0, count = 0;
    int *a, *prev, *chain;
    long long *sum;

    srand((unsigned int) time(NULL));
    choice = getMenuChoice();

    if (choice == 1) {
        printf("Number of elements (1 to %d): ", MAX_N);
        if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N) {
            printf("Invalid size.\n");
            return 1;
        }
        a = (int *) malloc(n * sizeof(int));
        printf("Enter the %d positive elements: ", n);
        for (i = 0; i < n; i++) {
            if (scanf("%d", &a[i]) != 1 || a[i] <= 0) {
                printf("Elements must be positive integers.\n");
                return 1;
            }
        }
    } else {
        n = 6 + rand() % 8;
        a = (int *) malloc(n * sizeof(int));
        for (i = 0; i < n; i++)
            a[i] = 1 + rand() % 100;
        printf("Generated array:");
        for (i = 0; i < n; i++)
            printf(" %d", a[i]);
        printf("\n");
    }

    sum = (long long *) malloc(n * sizeof(long long));
    prev = (int *) malloc(n * sizeof(int));
    chain = (int *) malloc(n * sizeof(int));

    /* sum[i] = best sum of an increasing subsequence that ends at a[i] */
    for (i = 0; i < n; i++) {
        sum[i] = a[i];
        prev[i] = -1;
        for (j = 0; j < i; j++) {
            if (a[j] < a[i] && sum[j] + a[i] > sum[i]) {
                sum[i] = sum[j] + a[i];
                prev[i] = j;
            }
        }
        if (sum[i] > sum[bestEnd])
            bestEnd = i;
    }

    printf("Maximum sum of an increasing subsequence = %lld\n", sum[bestEnd]);

    for (i = bestEnd; i != -1; i = prev[i])
        chain[count++] = a[i];
    printf("Subsequence:");
    for (i = count - 1; i >= 0; i--)
        printf(" %d", chain[i]);
    printf("\n");

    free(a);
    free(sum);
    free(prev);
    free(chain);
    return 0;
}
