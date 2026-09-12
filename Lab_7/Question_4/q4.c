#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 20

 int allZeroBits(int mask, int from, int n) {
    for (int b = from; b < n; b++)
        if ((mask >> b) & 1) return 0;
    return 1;
}

 int canToggle(int mask, int switchIdx, int n) {
    int b = switchIdx - 1;
    if (switchIdx == n) return 1;
    return ((mask >> (b + 1)) & 1) && allZeroBits(mask, b + 2, n);
}

 unsigned long long formula(int n) {
    return ((1ULL << (n + 1)) - 1) / 3ULL;
}

 void solve(int n) {
    int size = 1 << n;
    int *queue = malloc(sizeof(int) * size);
    int *dist = malloc(sizeof(int) * size);
    int *prev = malloc(sizeof(int) * size);
    int *move = malloc(sizeof(int) * size);
    if (!queue || !dist || !prev || !move) {
        printf("Out of memory.\n");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        dist[i] = -1;
        prev[i] = -1;
        move[i] = 0;
    }

    int start = (1 << n) - 1;
    int goal = 0;
    int head = 0, tail = 0;
    queue[tail++] = start;
    dist[start] = 0;

    while (head < tail) {
        int m = queue[head++];
        if (m == goal) break;
        for (int s = 1; s <= n; s++) {
            if (!canToggle(m, s, n)) continue;
            int nm = m ^ (1 << (s - 1));
            if (dist[nm] != -1) continue;
            dist[nm] = dist[m] + 1;
            prev[nm] = m;
            move[nm] = s;
            queue[tail++] = nm;
        }
    }

    int minMoves = dist[goal];
    unsigned long long f = formula(n);

    printf("Switches: %d\n", n);
    printf("Initial state: all ON\n");
    printf("Minimum moves (BFS shortest path): %d\n", minMoves);
    printf("Minimum moves (closed-form formula): %llu\n", f);
    if ((unsigned long long)minMoves == f) {
        printf("Both approaches agree.\n");
    } else {
        printf("Approaches disagree.\n");
    }

    if (n <= 10) {
        int *reversed = malloc(sizeof(int) * size);
        int count = 0;
        int m = goal;
        while (move[m] != 0) {
            reversed[count++] = move[m];
            m = prev[m];
        }
        printf("Optimal toggle sequence (%d moves):\n", count);
        for (int i = count - 1; i >= 0; i--)
            printf("Toggle switch %d\n", reversed[i]);
        free(reversed);
    }

    free(queue);
    free(dist);
    free(prev);
    free(move);
}

int main() {
    srand(time(NULL));
    printf("Security Switches Problem\n");
    printf("1. Random number of switches (1-10)\n");
    printf("2. Enter number of switches (1-%d)\n", MAX_N);
    printf("Choose an option: ");
    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (choice == 1) {
        solve(1 + rand() % 10);
    } else if (choice == 2) {
        printf("Enter number of switches (1-%d): ", MAX_N);
        int n;
        if (scanf("%d", &n) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
        if (n < 1 || n > MAX_N) {
            printf("Number of switches must be between 1 and %d.\n", MAX_N);
            return 1;
        }
        solve(n);
    } else {
        printf("Invalid choice.\n");
    }
    return 0;
}