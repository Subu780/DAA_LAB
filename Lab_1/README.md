# DAA Lab 1

Lab 1 of the Design and Analysis of Algorithms (DAA) coursework. This repository contains six distinct C programming assignments.

Several of these assignments programmatically generate text data and pipe commands to graphing software to help visualize time complexities and mathematical trends.

---

## Directory Structure

The repository is divided into six subdirectories. Each folder is completely self-contained with its own C source code, compiled executable (`a.exe`), generated assets (data and plots), and a dedicated documentation file explaining the specific problem and logic.

```text
Lab_1/
├── Question_1/
│   ├── a.exe
│   ├── q1.c
│   ├── growth_data.txt
│   ├── growth_graph.png
│   └── README.md
├── Question_2/
│   ├── a.exe
│   ├── q2.c
│   ├── line_graph_data.txt
│   ├── coin_simulation.png
│   └── README.md
├── Question_3/
│   ├── a.exe
│   ├── q3.c
│   ├── bubble_sort_comparison.png
│   └── README.md
├── Question_4/
│   ├── a.exe
│   ├── q4.c
│   ├── toh_data.txt
│   ├── toh_plot.png
│   └── README.md
├── Question_5/
│   ├── a.exe
│   ├── q5.c
│   └── README.md
└── Question_6/
    ├── a.exe
    ├── q6.c
    └── README.md
```

---

## Prerequisites and Installation

To fully utilize this repository, you must have a C compiler (like GCC) installed. 

Additionally, **Questions 1, 2, 3, and 4 rely on Gnuplot** to generate graphical visualizations directly from the C code. If Gnuplot is not installed and accessible in your system's PATH variable, the C programs will successfully calculate the data but will fail to draw the `.png` graphs.

### How to Install Gnuplot

You can install Gnuplot directly using the instructions below based on your operating system:

#### Linux (Debian/Ubuntu)
Open your terminal and run the following commands exactly as written:
```bash
sudo apt-get update
sudo apt-get install gnuplot
```

#### macOS
Mac users can install Gnuplot using the Homebrew package manager. Open your terminal and run:
```bash
brew install gnuplot
```

#### Windows
Windows users have two options for installing Gnuplot:

**Option 1: Command Line (winget)**
Open Command Prompt or PowerShell and run:
```bash
winget install Gnuplot.Gnuplot
```

**Option 2: Manual Download via Website**
1. Navigate to the official Gnuplot SourceForge page: `https://sourceforge.net/projects/gnuplot/files/gnuplot/`
2. Download the latest release executable installer (e.g., `gp110-win64-mingw.exe`).
3. Run the downloaded installer.
4. Finish the installation.

*Note: Regardless of which method you choose on Windows, you must completely restart your terminal or IDE (like VS Code) after installation for the PATH changes to take effect.*

---

## Lab Overview

Below is a summary of each question along with its specific compilation and execution commands. 

*Note for Linux/macOS users: If a script utilizes the math library (such as Question 1 and Question 2), you must explicitly link it by appending the `-lm` flag to your compilation command.*

### Question 1: Asymptotic Order of Growth
Generates data for various mathematical functions and plots them to visually prove their asymptotic order of growth for sufficiently large inputs.
*   **Compile:** `gcc -o a.exe q1.c -lm`
*   **Execute:** `./a.exe`

### Question 2: Coin Toss Simulation
Simulates a probability experiment and plots a line graph showing the convergence of probability over successive coin toss trials.
*   **Compile:** `gcc -o a.exe q2.c -lm`
*   **Execute:** `./a.exe`

### Question 3: Bubble Sort Performance Analysis
Simulates and compares the number of array comparisons made between a standard Bubble Sort and an optimized (early-exit) Bubble Sort, outputting the results as a quadratic comparison graph.
*   **Compile:** `gcc -o a.exe q3.c`
*   **Execute:** `./a.exe`

### Question 4: Tower of Hanoi
Recursively solves the Tower of Hanoi puzzle, counting the total moves for `n` disks, and plots the resulting exponential O(2^n) time complexity.
*   **Compile:** `gcc -o a.exe q4.c`
*   **Execute:** `./a.exe`

### Question 5: Partition Point
Implements an optimized O(log n) binary search algorithm to find the exact transition index in a strictly segregated binary array (0s followed by 1s).
*   **Compile:** `gcc -o a.exe q5.c`
*   **Execute:** `./a.exe`

### Question 6: Element Uniqueness
Implements an O(n) time complexity solution to check for duplicate numbers in an array using a direct access hash (frequency) array, noting the stack memory limitations for large input ranges.
*   **Compile:** `gcc -o a.exe q6.c`
*   **Execute:** `./a.exe`