/* Question 7: Rod Cutting with reconstruction */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 10000

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
    int n, i, j, choice, left;
    int *price, *firstCut;
    long long *best;

    srand((unsigned int) time(NULL));
    choice = getMenuChoice();

    if (choice == 1) {
        printf("Rod length n (1 to %d): ", MAX_N);
        if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N) {
            printf("Invalid length.\n");
            return 1;
        }
        price = (int *) malloc((n + 1) * sizeof(int));
        printf("Enter prices for lengths 1 to %d: ", n);
        for (i = 1; i <= n; i++) {
            if (scanf("%d", &price[i]) != 1 || price[i] < 0) {
                printf("Prices must be non-negative integers.\n");
                return 1;
            }
        }
    } else {
        n = 4 + rand() % 8;
        price = (int *) malloc((n + 1) * sizeof(int));
        for (i = 1; i <= n; i++)
            price[i] = i + rand() % (2 * i + 1);
        printf("Generated rod length n = %d\n", n);
        printf("Generated prices:");
        for (i = 1; i <= n; i++)
            printf(" %d", price[i]);
        printf("\n");
    }

    best = (long long *) malloc((n + 1) * sizeof(long long));
    firstCut = (int *) malloc((n + 1) * sizeof(int));

    /* best[j] = max revenue for a rod of length j,
       firstCut[j] = length of the first piece in an optimal split of j */
    best[0] = 0;
    for (j = 1; j <= n; j++) {
        best[j] = -1;
        for (i = 1; i <= j; i++) {
            if (price[i] + best[j - i] > best[j]) {
                best[j] = price[i] + best[j - i];
                firstCut[j] = i;
            }
        }
    }

    printf("Maximum revenue = %lld\n", best[n]);
    printf("Pieces:");
    left = n;
    while (left > 0) {
        printf(" %d", firstCut[left]);
        left = left - firstCut[left];
    }
    printf("\n");

    free(price);
    free(best);
    free(firstCut);
    return 0;
}
