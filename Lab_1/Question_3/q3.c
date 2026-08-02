#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main() {
    int max_sz = 5000;
    int step = 100;
    
    FILE *d_file = fopen("bubble_data.txt", "w");
    if (d_file == NULL) {
        printf("Error: Could not create data file.\n");
        return 1;
    }

    srand(time(NULL));
    printf("--- Bubble Sort Efficiency Simulator ---\n");
    printf("Simulating arrays (Half Random, Half Sorted) from %d to %d...\n", step, max_sz);

    // Loop through different array sizes
    for (int n = step; n <= max_sz; n += step) {
        int *a_opt = (int *)malloc(n * sizeof(int));
        int *a_std = (int *)malloc(n * sizeof(int));

        // --- ARRAY GENERATION LOGIC ---
        int half = n / 2;
        int max_v = -1;

        // 1. First half: Randomized
        for (int i = 0; i < half; i++) {
            a_opt[i] = rand() % 10000;
            if (a_opt[i] > max_v) {
                max_v = a_opt[i]; // Keep track of the maximum value
            }
        }

        // 2. Second half: Sorted and strictly greater than the maximum of the first half
        int cur_v = max_v;
        for (int i = half; i < n; i++) {
            // Add a random increment (1 to 10) to ensure strictly increasing order
            cur_v += (rand() % 10) + 1; 
            a_opt[i] = cur_v;
        }

        // --- INLINE ARRAY COPY ---
        // Make an exact copy for the standard sort directly in main
        for (int i = 0; i < n; i++) {
            a_std[i] = a_opt[i];
        }

        long long cmp_o = 0;
        long long cmp_s = 0;

        // ---------------------------------------------------------
        // (i) OPTIMIZED BUBBLE SORT (Terminates if sorted early)
        // ---------------------------------------------------------
        bool swap;
        for (int i = 0; i < n - 1; i++) {
            swap = false;
            for (int j = 0; j < n - i - 1; j++) {
                cmp_o++; // Count comparison
                if (a_opt[j] > a_opt[j + 1]) {
                    int tmp = a_opt[j];
                    a_opt[j] = a_opt[j + 1];
                    a_opt[j + 1] = tmp;
                    swap = true;
                }
            }
            if (!swap) break; // Early exit if no swaps occurred
        }

        // ---------------------------------------------------------
        // (ii) STANDARD BUBBLE SORT (Always completes n-1 passes)
        // ---------------------------------------------------------
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                cmp_s++; // Count comparison
                if (a_std[j] > a_std[j + 1]) {
                    int tmp = a_std[j];
                    a_std[j] = a_std[j + 1];
                    a_std[j + 1] = tmp;
                }
            }
        }

        // Write the N size and both comparison counts to the file
        fprintf(d_file, "%d %lld %lld\n", n, cmp_o, cmp_s);

        free(a_opt);
        free(a_std);
    }

    fclose(d_file);
    printf("Simulation complete! Generating PNG image...\n");

    // Launch Gnuplot to create the graph
    FILE *gp = _popen("gnuplot", "w"); 
    if (gp == NULL) {
        printf("Error: Could not open gnuplot.\n");
        return 1;
    }

    fprintf(gp, "set terminal png size 1000,600\n");
    fprintf(gp, "set output 'bubble_sort_comparison.png'\n");
    
    fprintf(gp, "set title 'Bubble Sort Comparisons: Optimized vs Standard (Half Random / Half Sorted)'\n"); 
    fprintf(gp, "set xlabel 'Array Size (N)'\n");                       
    fprintf(gp, "set ylabel 'Number of Comparisons'\n");
    
    fprintf(gp, "set grid\n");
    fprintf(gp, "set key left top box spacing 1.5 width 2\n");

    // Plot both sets of data
    fprintf(gp, "plot 'bubble_data.txt' using 1:2 title 'Optimized (Early Exit)' with lines lw 2 lc rgb '#8A2BE2', \\\n");
    fprintf(gp, "     '' using 1:3 title 'Standard (Always n-1 passes)' with lines lw 2 lc rgb '#FF8C00'\n");
    
    fflush(gp);
    _pclose(gp);
    
    printf("Success! Graph saved as 'bubble_sort_comparison.png'.\n");
    
    // Cleanup temporary data
    remove("bubble_data.txt");
    
    return 0;
}