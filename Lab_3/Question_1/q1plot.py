import csv
import matplotlib.pyplot as plt

# Initialize lists to store our data
array_sizes = []
bsc_values = []
tsc_values = []

with open('results.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)  # Skip the header row
    
    for row in reader:
        if not row:
            continue
        array_sizes.append(int(row[0]))
        bsc_values.append(int(row[1]))
        tsc_values.append(int(row[2]))

# Set up the plot
plt.figure(figsize=(10, 6))

# Plot both lines with distinct markers
plt.plot(array_sizes, bsc_values, label='Binary Search (bsc)', color='blue', marker='o', linewidth=2)
plt.plot(array_sizes, tsc_values, label='Ternary Search (tsc)', color='red', marker='s', linewidth=2)

# Configure the axes and labels
plt.xscale('log')  # Log scale for X-axis since sizes range from 1K to 5M
plt.title('Binary Search vs Ternary Search: Array Comparisons', fontsize=14, fontweight='bold')
plt.xlabel('Array Size (Log Scale)', fontsize=12)

# Updated Y-axis label to reflect the single worst-case search
plt.ylabel('Comparisons (Single Worst-Case Search)', fontsize=12)

# Add grid, legend, and layout adjustments
plt.grid(True, which="both", ls="--", alpha=0.6)
plt.legend(fontsize=12)
plt.tight_layout()

# Save the plot to an image file and display it
plt.savefig('comparisons_plot.png', dpi=300)
print("Plot successfully saved as 'comparisons_plot.png'")

# Show the interactive window
plt.show()