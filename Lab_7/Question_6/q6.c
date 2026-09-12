#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define MAX_SCI 50
#define NAME_LEN 50
#define MAX_YEARS 20000

typedef struct {
    char name[NAME_LEN];
    int birth;
    int death;
} Scientist;

typedef struct {
    int year;
    int delta;
} Event;

int cmpEvents(const void *a, const void *b) {
    Event *ea = (Event *)a;
    Event *eb = (Event *)b;
    if (ea->year != eb->year) return ea->year - eb->year;
    return eb->delta - ea->delta;
}

void printList(int *years, int yCount) {
    for (int i = 0; i < yCount; i++) {
        printf(" %d", years[i]);
        if (i < yCount - 1) printf(",");
    }
    printf("\n");
}

void sweepLine(Scientist *s, int n) {
    int minYear = INT_MAX, maxYear = INT_MIN;
    Event events[MAX_SCI * 2];
    int eCount = 0;

    for (int i = 0; i < n; i++) {
        if (s[i].birth < minYear) minYear = s[i].birth;
        if (s[i].death > maxYear) maxYear = s[i].death;
        events[eCount].year = s[i].birth;
        events[eCount].delta = 1;
        eCount++;
        events[eCount].year = s[i].death;
        events[eCount].delta = -1;
        eCount++;
    }

    qsort(events, eCount, sizeof(Event), cmpEvents);

    int maxAlive = 0, yCount = 0;
    int years[MAX_YEARS];
    int current = 0;

    int i = 0;
    while (i < eCount) {
        int curYear = events[i].year;
        while (i < eCount && events[i].year == curYear) {
            current += events[i].delta;
            i++;
        }
        if (current > maxAlive) {
            maxAlive = current;
            yCount = 0;
        }
        if (current == maxAlive) {
            int endYear = (i < eCount) ? events[i].year - 1 : maxYear;
            if (endYear > maxYear) endYear = maxYear;
            for (int y = curYear; y <= endYear; y++)
                years[yCount++] = y;
        }
    }

    if (yCount == 0) {
        maxAlive = 0;
        yCount = 1;
        years[0] = minYear;
    }

    printf("Sweep-line result: max %d alive, years", maxAlive);
    printList(years, yCount);
}

int main() {
    srand(time(NULL));

    int m, choice;
    Scientist s[MAX_SCI];

    printf("Choose input method:\n1. Random scientists\n2. Manual input\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter number of scientists (3-10): ");
        scanf("%d", &m);
        if (m < 3 || m > 10) m = 3 + rand() % 8;
        for (int i = 0; i < m; i++) {
            sprintf(s[i].name, "Scientist_%d", i + 1);
            s[i].birth = 1900 + rand() % 91;
            s[i].death = s[i].birth + 1 + rand() % 90;
            if (s[i].death > 2000) s[i].death = 2000;
        }
    } else {
        printf("Enter number of scientists (1-50): ");
        scanf("%d", &m);
        if (m < 1) m = 1;
        if (m > 50) m = 50;
        for (int i = 0; i < m; i++) {
            printf("Scientist %d - Name Birth Death: ", i + 1);
            scanf("%s %d %d", s[i].name, &s[i].birth, &s[i].death);
            while (s[i].birth >= s[i].death) {
                printf("Invalid! Birth must be < Death. Re-enter Birth Death: ");
                scanf("%d %d", &s[i].birth, &s[i].death);
            }
        }
    }

    printf("\nNumber of scientists: %d\n", m);
    printf("Name Birth Death\n");
    for (int i = 0; i < m; i++)
        printf("%s %d %d\n", s[i].name, s[i].birth, s[i].death);

    printf("\n");
    sweepLine(s, m);

    return 0;
}