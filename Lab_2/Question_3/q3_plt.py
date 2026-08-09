import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# 1. Read the CSV
try:
    df = pd.read_csv('results.csv')
except FileNotFoundError:
    print("Error: Run the C program first to generate 'results.csv'")
    exit(1)

# Create labels combining k and n for the x-axis
labels = [f"k={k}\nn={n}" for k, n in zip(df['k_arrays'], df['n_elements'])]
x = np.arange(len(labels))

# 2. Setup the plot
fig, ax = plt.subplots(figsize=(10, 6))

# Use plot() instead of bar() to create line graphs
ax.plot(x, df['Method1_Time'], marker='o', label='Method 1 (Sequential) - $O(k^2n)$', color='red', linewidth=2, markersize=8)
ax.plot(x, df['Method2_Time'], marker='s', label='Method 2 (Divide & Conquer) - $O(kn \\log k)$', color='blue', linewidth=2, markersize=8)

# 3. Formatting
ax.set_ylabel('Execution Time (seconds)', fontsize=12)
ax.set_xlabel('Array Counts and Sizes', fontsize=12)
ax.set_title('Merging K Sorted Arrays: Sequential vs Divide & Conquer', fontsize=14, pad=15)
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend(fontsize=11)
ax.grid(True, linestyle='--', alpha=0.6)

# 4. Save and show
plt.tight_layout()
plt.savefig('q3_merge_plot.png', dpi=300)
print("Plot successfully saved as 'q3_merge_plot.png'")