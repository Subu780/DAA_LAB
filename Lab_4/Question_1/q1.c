#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef struct {
    int number;
    char col;
} pair;

// Function to sort the array by color in O(n) time and print it
void sort_by_color(pair *pairs, int n) {
    pair *red_pairs = (pair *)malloc(n * sizeof(pair));
    pair *blue_pairs = (pair *)malloc(n * sizeof(pair));
    pair *yellow_pairs = (pair *)malloc(n * sizeof(pair));
    
    int red_count = 0, blue_count = 0, yellow_count = 0;

    // Distribute by color
    for (int i = 0; i < n; i++) {
        if (pairs[i].col == 'r') {
            red_pairs[red_count++] = pairs[i];
        } else if (pairs[i].col == 'b') {
            blue_pairs[blue_count++] = pairs[i];
        } else if (pairs[i].col == 'y') {
            yellow_pairs[yellow_count++] = pairs[i];
        }
    }

    // Copy back to the original array to actually sort it in place
    int index = 0;
    for (int i = 0; i < red_count; i++) pairs[index++] = red_pairs[i];
    for (int i = 0; i < blue_count; i++) pairs[index++] = blue_pairs[i];
    for (int i = 0; i < yellow_count; i++) pairs[index++] = yellow_pairs[i];

    // Print the sorted result in the new format
    printf("\nSorted items by color:\n");
    for (int i = 0; i < n; i++) {
        printf("%d(%c) ", pairs[i].number, toupper(pairs[i].col));
    }
    printf("\n\n");

    // Free the temporary arrays
    free(red_pairs);
    free(blue_pairs);
    free(yellow_pairs);
}

int main() {
    // Seed the random number generator
    srand(time(NULL)); 
    
    int choice = 0;
    
    printf("1. Manually input pairs (must be sorted by number)\n");
    printf("2. Generate random sorted numbers with random colors\n");
    printf("Enter your choice: ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    if (choice == 1) {
        int n;
        printf("Enter the number of pairs: ");
        scanf("%d", &n);
        
        pair *pairs = (pair *)malloc(n * sizeof(pair));
        printf("Enter the pairs (number color):\n");
        for (int i = 0; i < n; i++) {
            scanf("%d %c", &pairs[i].number, &pairs[i].col);
        }
        
        sort_by_color(pairs, n);
        free(pairs); 
        
    } else if (choice == 2) {
        int n;
        printf("Enter the number of random pairs to generate: ");
        scanf("%d", &n);
        
        pair *pairs = (pair *)malloc(n * sizeof(pair));
        char possible_colors[] = {'r', 'b', 'y'};
        
        int current_num = rand() % 10 + 1; // Start with a random number 1-10
        
        printf("\nGenerated Random Pairs:\n");
        for (int i = 0; i < n; i++) {
            pairs[i].number = current_num;
            pairs[i].col = possible_colors[rand() % 3]; // Pick random color
            
            // Print generated pairs in the new format
            printf("%d(%c) ", pairs[i].number, toupper(pairs[i].col));
            
            // Add a random amount (1 to 10) to ensure the next number is larger
            current_num += rand() % 10 + 1; 
        }
        printf("\n");
        
        sort_by_color(pairs, n);
        free(pairs); 
        
    } else {
        printf("Invalid choice. Exiting.\n");
    }

    return 0;
}