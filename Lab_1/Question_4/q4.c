#include <stdio.h>
#include <stdlib.h>

// Recursive function to simulate Tower of Hanoi and count moves
void toh(int n, char s, char d, char a, long long *m) {
    if (n == 0) return;
    
    // Move n-1 disks from Source to Aux
    toh(n - 1, s, a, d, m);
    
    // Move the nth disk from Source to Dest (we just count it here)
    (*m)++;
    
    // Move n-1 disks from Aux to Dest
    toh(n - 1, a, d, s, m);
}

int main() {
    int max_n = 20; 
    
    FILE *d_file = fopen("toh_data.txt", "w");
    if (d_file == NULL) {
        printf("Error: Could not create data file.\n");
        return 1;
    }

    printf("--- Tower of Hanoi Simulator ---\n");
    printf("Simulating moves for 1 up to %d disks...\n", max_n);
    
    // Looping through different numbers of disks
    for (int n = 1; n <= max_n; n++) {
        long long m = 0;
        toh(n, 'A', 'C', 'B', &m);
        fprintf(d_file, "%d %lld\n", n, m);
        printf("Disks: %d -> Moves: %lld\n", n, m);
    }

    fclose(d_file);
    printf("Simulation complete! Generating PNG image...\n");

    // Implementing GNUPLOT to visualize the Tower of Hanoi moves
    FILE *gp = _popen("gnuplot", "w"); 
    if (gp == NULL) {
        printf("Error: Could not open gnuplot.\n");
        return 1;
    }

    fprintf(gp, "set terminal png size 1000,600\n");
    fprintf(gp, "set output 'toh_plot.png'\n");
    
    fprintf(gp, "set title 'Tower of Hanoi: Number of Disks vs Total Moves'\n"); 
    fprintf(gp, "set xlabel 'Number of Disks (N)'\n");                       
    fprintf(gp, "set ylabel 'Total Moves Required'\n");
    
    fprintf(gp, "set xrange [1:22]\n");
    
    fprintf(gp, "set grid\n");
    fprintf(gp, "set key left top box spacing 2 width 2\n");

    // Plotting the data with lines and points
    fprintf(gp, "plot 'toh_data.txt' using 1:2 with lines dt 3 lw 2 lc rgb '#BBBBBB' notitle, \\\n");
    fprintf(gp, "    '' using 1:2 title 'Measured Moves' with points pt 7 ps 1.5 lc rgb '#FF0000'\n");
    
    fflush(gp);
    _pclose(gp);
    
    printf("Success! Graph saved as 'toh_plot.png'.\n");

    return 0;
}