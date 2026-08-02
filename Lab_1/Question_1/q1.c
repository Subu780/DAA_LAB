#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int start_n = 1;
    int end_n = 200;
    
    FILE *d_file = fopen("growth_data.txt", "w");
    if (d_file == NULL) {
        printf("Error: Could not create data file.\n");
        return 1;
    }

    printf("Generating data for n = %d to %d...\n", start_n, end_n);

    // Data points for all 12 functions
    for (int n = start_n; n <= end_n; n++) {
        double dn = (double)n;
        
        double f1  = 1.0 / dn;
        double f2  = log2(dn);
        double f3  = 12.0 * sqrt(dn);
        double f4  = 50.0 * sqrt(dn);
        double f5  = pow(dn, 0.51);
        double f6  = pow(2.0, 32.0) * dn; 
        double f7  = dn * log2(dn);
        double f8  = pow(dn, 2.0) - 324.0;
        double f9  = 100.0 * pow(dn, 2.0) + 6.0 * dn;
        double f10 = 2.0 * pow(dn, 3.0);
        double f11 = pow(dn, log2(dn));
        double f12 = pow(3.0, dn);

        fprintf(d_file, "%d %e %e %e %e %e %e %e %e %e %e %e %e\n", 
                n, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12);
    }

    fclose(d_file);
    printf("Data generation complete.\n");

    // GNUPLOT integration to visualize the data
    FILE *gp = _popen("gnuplot", "w"); 
    if (gp == NULL) {
        printf("Error: Could not open gnuplot.\n");
        return 1;
    }

    fprintf(gp, "set terminal pngcairo size 1200,800 font 'Segoe UI,10'\n");
    fprintf(gp, "set output 'growth_graph.png'\n");
    
    fprintf(gp, "set title 'Order of Growth: Function Comparison (Log-Log Scale)' font ',14'\n"); 
    fprintf(gp, "set xlabel 'n (Input Size)'\n");                       
    fprintf(gp, "set ylabel 'f(n) (Operations)'\n");
    
    // Logarithmic Scale for both X and Y axes
    fprintf(gp, "set logscale xy\n");
    
    // Clamp the X-axis to exactly match our data range to prevent blank space
    fprintf(gp, "set xrange [20:200]\n");
    
    // Y-axis range to accommodate the largest function value
    fprintf(gp, "set yrange [1e-10:1e10]\n");
    fprintf(gp, "set grid mxtics mytics lc rgb '#E0E0E0' dt 2\n");
    fprintf(gp, "set key outside right top box spacing 1.5 width 2\n");

    // All 12 functions. 
    // They are listed in their mathematically proven order of growth.
    fprintf(gp, "plot 'growth_data.txt' \\\n");
    fprintf(gp, "using 1:2 title '1/n' with lines lw 2 lc rgb '#000000', \\\n");
    fprintf(gp, "'' using 1:3 title 'log2(n)' with lines lw 2 lc rgb '#1f77b4', \\\n");
    fprintf(gp, "'' using 1:4 title '12*sqrt(n)' with lines lw 2 lc rgb '#ff7f0e', \\\n");
    fprintf(gp, "'' using 1:5 title '50*sqrt(n)' with lines lw 2 lc rgb '#ff7f0e', \\\n");
    fprintf(gp, "'' using 1:6 title 'n^{0.51}' with lines lw 2 lc rgb '#2ca02c', \\\n");
    fprintf(gp, "'' using 1:7 title '2^{32}n' with lines lw 2 lc rgb '#d62728', \\\n");
    fprintf(gp, "'' using 1:8 title 'n log2(n)' with lines lw 2 lc rgb '#9467bd', \\\n");
    fprintf(gp, "'' using 1:9 title 'n^2 - 324' with lines lw 2 lc rgb '#8c564b', \\\n");
    fprintf(gp, "'' using 1:10 title '100n^2 + 6n' with lines lw 2 lc rgb '#8c564b', \\\n");
    fprintf(gp, "'' using 1:11 title '2n^3' with lines lw 2 lc rgb '#e377c2', \\\n");
    fprintf(gp, "'' using 1:12 title 'n^{log2(n)}' with lines lw 2 lc rgb '#7f7f7f', \\\n");
    fprintf(gp, "'' using 1:13 title '3^n' with lines lw 2 lc rgb '#bcbd22'\n");
    
    fflush(gp);
    _pclose(gp);
    
    printf("Success! Graph saved as 'growth_graph.png'.\n");
    
    return 0;
}