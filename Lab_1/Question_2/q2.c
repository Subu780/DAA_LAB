#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int total_tosses;
    double biased_prob;

    // DYNAMIC INPUT: Let the user define the simulation parameters
    printf("--- Coin Toss Simulator ---\n");
    printf("Enter total number of tosses : ");
    scanf("%d", &total_tosses);
    
    printf("Enter expected probability for the biased coin (0.0 to 1.0): ");
    scanf("%lf", &biased_prob);

    if(biased_prob < 0.0 || biased_prob > 1.0) {
        printf("Error: Biased probability must be between 0.0 and 1.0.\n");
        return 0;
    }

    int fair_heads = 0;
    int biased_heads = 0;
    
    FILE *data_file = fopen("line_graph_data.txt", "w");
    if (data_file == NULL) {
        printf("Error: Could not create data file.\n");
        return 1;
    }

    srand(time(NULL));
    printf("Simulating tosses...\n");

    for (int i = 1; i <= total_tosses; i++) {
        double r_fair = (double)rand() / RAND_MAX;
        double r_biased = (double)rand() / RAND_MAX;

        if (r_fair < 0.5) fair_heads++;
        if (r_biased < biased_prob) biased_heads++;

        double current_fair_prob = (double)fair_heads / i;
        double current_biased_prob = (double)biased_heads / i;
        
        fprintf(data_file, "%d %f %f\n", i, current_fair_prob, current_biased_prob);
    }

    fclose(data_file);
    FILE *gnuplot = _popen("gnuplot", "w"); 
    if (gnuplot == NULL) {
        printf("Error: Could not open gnuplot.\n");
        return 1;
    }

    // --- Set terminal to PNG and define the output file name ---
    fprintf(gnuplot, "set terminal png size 1000,600\n");
    fprintf(gnuplot, "set output 'coin_simulation.png'\n");
    
    fprintf(gnuplot, "set title 'Law of Large Numbers: Fair vs Biased Coin'\n"); 
    fprintf(gnuplot, "set xlabel 'Number of Tosses'\n");                       
    fprintf(gnuplot, "set ylabel 'Probability of Heads'\n");
    
    // Set y-axis to go up to 1.1 
    fprintf(gnuplot, "set yrange [0:1.1]\n");
    
    fprintf(gnuplot, "set grid\n");
    
    // Use the dynamic biased_prob for the second reference line
    fprintf(gnuplot, "set arrow 1 from graph 0,first 0.5 to graph 1,first 0.5 nohead lc rgb 'black' dt 2 lw 2\n");
    fprintf(gnuplot, "set arrow 2 from graph 0,first %f to graph 1,first %f nohead lc rgb 'gray50' dt 2 lw 2\n", biased_prob, biased_prob);
    
    fprintf(gnuplot, "set key outside right top box spacing 2.0 width 2\n");

    fprintf(gnuplot, "plot 'line_graph_data.txt' using 1:2 with lines title 'Fair Heads (Expected 0.5)' lc rgb '#8A2BE2', \\\n");
    fprintf(gnuplot, "     '' using 1:3 with lines title 'Biased Heads (Expected %.2f)' lc rgb '#FF8C00'\n", biased_prob);
    
    fflush(gnuplot);
    _pclose(gnuplot);
    
    printf("Graph saved as 'coin_simulation.png' in your current folder.\n");
    
    return 0;
}