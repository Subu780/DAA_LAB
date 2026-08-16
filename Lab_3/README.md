# Lab 3

## Prerequisites
To compile and run the programs in this repository, you will need:
*   **GCC**: For compiling C programs.
*   **Python & Matplotlib**: For executing plotting and analysis scripts (e.g., generating `comparisons_plot.png`).

## Lab Questions

**1. Binary vs Ternary Search**
* Design and implement a C program to search for an element in a sorted list of size n using both binary and ternary search, and validate why binary search performs better.[cite: 1]

**2. Search the Defective Coin**
* Provide a divide and conquer algorithm (and C implementation) to find a single lighter defective coin (if one exists) among n coins using a balance scale, achieving a time complexity of log2 n + c.[cite: 1]

**3. Max and Min using D&C Approach**
* Develop and implement a divide and conquer algorithm in C to find the maximum and minimum elements in an array of size n, ensuring the number of comparisons is bounded by 3n/2.[cite: 1]

**4. Matrix Multiplication using D&C Approach**
* Write a C program to multiply two n × n square matrices using Strassen’s method.[cite: 1]

**5. Multiply special-pattern square matrices using D&C approach**
* Design an O(n^2) divide-and-conquer algorithm to multiply two n × n matrices that possess a specific recursive block structure (identical diagonal blocks and identical off-diagonal blocks), and validate its complexity.[cite: 1]

**6. Use of loop invariants in sorting**
* Write pseudocode and a C implementation for the described sorting algorithm (Selection Sort).[cite: 1] 
* Identify its loop invariant (initialisation, maintenance, and termination), explain why it only needs to run for the first (n − 1) elements, and provide its worst-case and best-case running times in Θ-notation.