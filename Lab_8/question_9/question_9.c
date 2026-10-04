/* Question 9: Collatz Conjecture - trajectory analysis
   Part A: one starting value    Part B: every value in an interval [a, b] */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX_RANGE 5000000
#define SHOW_TABLE_LIMIT 20

typedef unsigned long long ull;

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

int getModeChoice() {
    int mode;
    while (1) {
        printf("Enter 1 to analyse a single starting value\n");
        printf("Enter 2 to analyse an interval [a, b]\n");
        printf("Your choice: ");
        if (scanf("%d", &mode) != 1) {
            printf("Invalid input, exiting.\n");
            exit(1);
        }
        if (mode == 1 || mode == 2)
            return mode;
        printf("Please enter only 1 or 2.\n\n");
    }
}

/* returns 1 if 3n+1 would not fit in an unsigned long long */
int willOverflow(ull n) {
    if (n > (ULLONG_MAX - 1) / 3)
        return 1;
    return 0;
}

ull nextTerm(ull n) {
    if (n % 2 == 0)
        return n / 2;
    return 3 * n + 1;
}

/* Builds the whole trajectory in a growing heap array.
   Returns the array; *length gets the number of terms (including n and 1).
   *peak is the largest term seen, *overflow is set if we had to stop early. */
ull *getTrajectory(ull n, int *length, ull *peak, int *overflow) {
    int capacity = 64, count = 0;
    ull *path = (ull *) malloc(capacity * sizeof(ull));
    ull current = n;

    *peak = n;
    *overflow = 0;
    if (path == NULL)
        return NULL;

    path[count++] = current;
    while (current != 1) {
        if (current % 2 == 1 && willOverflow(current)) {
            *overflow = 1;
            break;
        }
        current = nextTerm(current);
        if (current > *peak)
            *peak = current;
        if (count == capacity) {
            capacity = capacity * 2;
            path = (ull *) realloc(path, capacity * sizeof(ull));
            if (path == NULL)
                return NULL;
        }
        path[count++] = current;
    }
    *length = count;
    return path;
}

/* Same walk, but only counts steps (no storage), used for big intervals.
   Returns -1 if overflow stopped the walk. */
long long countSteps(ull n, ull *peak) {
    long long steps = 0;
    *peak = n;
    while (n != 1) {
        if (n % 2 == 1 && willOverflow(n))
            return -1;
        n = nextTerm(n);
        if (n > *peak)
            *peak = n;
        steps++;
    }
    return steps;
}

void analyseSingle(ull n) {
    int length, overflow, i;
    ull peak;
    ull *path = getTrajectory(n, &length, &peak, &overflow);

    if (path == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Trajectory of %llu:\n", n);
    for (i = 0; i < length; i++) {
        printf("%llu", path[i]);
        if (i < length - 1)
            printf(" -> ");
        if ((i + 1) % 10 == 0 && i < length - 1)
            printf("\n");
    }
    printf("\n");

    if (overflow) {
        printf("Stopped early: the next 3n+1 would overflow 64 bits.\n");
    } else {
        printf("Steps to reach 1 : %d\n", length - 1);
        printf("Highest value    : %llu\n", peak);
    }
    free(path);
}

void analyseInterval(ull a, ull b) {
    ull size = b - a + 1;
    ull i, peak, bestStepsStart = a, bestPeakStart = a, bestPeak = 0;
    long long steps, bestSteps = -1, totalSteps = 0;
    long long *stepList;
    ull counted = 0, overflowCount = 0;

    stepList = (long long *) malloc(size * sizeof(long long));
    if (stepList == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    if (size <= SHOW_TABLE_LIMIT)
        printf("%12s %8s %20s\n", "Start", "Steps", "Highest value");

    for (i = a; i <= b; i++) {
        steps = countSteps(i, &peak);
        stepList[i - a] = steps;
        if (steps == -1) {
            overflowCount++;
            continue;
        }
        counted++;
        totalSteps += steps;
        if (steps > bestSteps) {
            bestSteps = steps;
            bestStepsStart = i;
        }
        if (peak > bestPeak) {
            bestPeak = peak;
            bestPeakStart = i;
        }
        if (size <= SHOW_TABLE_LIMIT)
            printf("%12llu %8lld %20llu\n", i, steps, peak);
    }

    printf("\nInterval [%llu, %llu] (%llu numbers)\n", a, b, size);
    if (counted > 0) {
        printf("Longest trajectory : start %llu takes %lld steps\n", bestStepsStart, bestSteps);
        printf("Highest peak       : start %llu reaches %llu\n", bestPeakStart, bestPeak);
        printf("Average steps      : %.2f\n", (double) totalSteps / counted);
    }
    if (overflowCount > 0)
        printf("Skipped %llu numbers because of 64-bit overflow\n", overflowCount);

    free(stepList);
}

int main() {
    int mode, choice;
    ull n, a, b;

    srand((unsigned int) time(NULL));
    mode = getModeChoice();
    printf("\n");
    choice = getMenuChoice();

    if (mode == 1) {
        if (choice == 1) {
            printf("Enter starting value n (n >= 1): ");
            if (scanf("%llu", &n) != 1 || n < 1) {
                printf("n must be a positive integer.\n");
                return 1;
            }
        } else {
            n = 1 + rand() % 100000;
            printf("Generated n = %llu\n", n);
        }
        printf("\n");
        analyseSingle(n);
    } else {
        if (choice == 1) {
            printf("Enter a and b (1 <= a <= b, at most %d numbers): ", MAX_RANGE);
            if (scanf("%llu %llu", &a, &b) != 2 || a < 1 || a > b
                || b - a + 1 > MAX_RANGE) {
                printf("Invalid interval.\n");
                return 1;
            }
        } else {
            a = 1 + rand() % 1000;
            b = a + 5000 + rand() % 5000;
            printf("Generated interval [%llu, %llu]\n", a, b);
        }
        printf("\n");
        analyseInterval(a, b);
    }
    return 0;
}
