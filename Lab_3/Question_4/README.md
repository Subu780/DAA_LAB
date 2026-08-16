# Strassen's Matrix Multiplication (Divide & Conquer)

## File Directory
```text
Question_4/
├── a.exe
├── q4.c
└── README.md
```

## Overview
This project implements Strassen's algorithm in C (`q4.c`) to multiply two square matrices of size $n \times n$. Strassen's method is a sophisticated Divide and Conquer algorithm that mathematically reduces the total number of multiplication operations required, achieving a better asymptotic time complexity of $O(n^{2.81})$ compared to the standard $O(n^3)$ approach.

## How the Program Works
The program executes through the following sequence of operations:

* **Initialization & Input:** The user provides the dimension $n$ of the matrices. The program prompts the user to either input the matrix elements manually or generate them using a random number generator. 
* **Dynamic Padding:** Strassen's algorithm inherently requires the matrix dimensions to be a power of 2 so it can be evenly halved during recursion. If the user enters a non-power-of-2 size (e.g., $n = 3$), the program dynamically calculates the next power of 2 (e.g., $m = 4$) and pads the matrices with extra zeros.
* **Divide Phase:** The padded matrices A and B are split into four smaller submatrices (quadrants) of size $\frac{n}{2} \times \frac{n}{2}$.
* **Conquer Phase (Strassen's Trick):** Instead of calculating the 8 standard products, the algorithm performs exactly 7 recursive multiplications (M1 through M7) using specific combinations of matrix additions and subtractions.
* **Combine Phase:** The 4 quadrants of the resulting matrix C are reconstructed by adding and subtracting the M matrices according to Strassen's formulas.
* **Base Case:** The recursion continues halving the matrices until it reaches a 1 x 1 matrix, at which point it simply multiplies the two scalar values together.
* **Output:** The program extracts and prints only the original $n \times n$ portion of the final matrix, completely hiding the zero-padded boundaries from the user.

## Mathematical Derivation of Time Complexities (Substitution Method)

### Standard Divide & Conquer Multiplication: $O(n^3)$
The standard divide-and-conquer strategy partitions the $n \times n$ matrices into four submatrices (quadrants) of size $\frac{n}{2} \times \frac{n}{2}$. 

To calculate the four quadrants of the resulting matrix $C$, the algorithm performs exactly **8 recursive multiplications** and 4 matrix additions. The matrix additions take $O(n^2)$ time. Let this addition time be represented by $cn^2$. 

The recurrence relation is:
$$T(n) = 8T\left(\frac{n}{2}\right) + cn^2$$

Using the **Substitution Method**, we expand the recurrence iteratively:
$$T(n) = 8 \left[ 8T\left(\frac{n}{4}\right) + c\left(\frac{n}{2}\right)^2 \right] + cn^2$$
$$T(n) = 8^2 T\left(\frac{n}{4}\right) + 8c\left(\frac{n^2}{4}\right) + cn^2$$
$$T(n) = 8^2 T\left(\frac{n}{4}\right) + 2cn^2 + cn^2$$

Expanding another step:
$$T(n) = 8^2 \left[ 8T\left(\frac{n}{8}\right) + c\left(\frac{n}{4}\right)^2 \right] + 2cn^2 + cn^2$$
$$T(n) = 8^3 T\left(\frac{n}{8}\right) + 4cn^2 + 2cn^2 + cn^2$$

Generalizing for $k$ steps:
$$T(n) = 8^k T\left(\frac{n}{2^k}\right) + cn^2 \sum_{i=0}^{k-1} 2^i$$

Assume $n = 2^k$, which means $k = \log_2 n$. The recursion reaches the base case $T(1) = 1$. Substituting $k$:
$$T(n) = 8^{\log_2 n} T(1) + cn^2 \left( \frac{2^{\log_2 n} - 1}{2 - 1} \right)$$

Using the logarithmic property $8^{\log_2 n} = n^{\log_2 8} = n^3$, and knowing $2^{\log_2 n} = n$:
$$T(n) = n^3 + cn^2 (n - 1)$$
$$T(n) = n^3 + cn^3 - cn^2$$

Because the $n^3$ terms dominate the equation, the final time complexity is exactly:
$$T(n) = O(n^3)$$

### Strassen's Matrix Multiplication: $O(n^{2.81})$
Strassen's algorithm optimizes standard multiplication by explicitly reducing the number of recursive calls from 8 down to 7. The cost is 18 matrix additions/subtractions, which still takes $cn^2$ time. 

The recurrence relation is:
$$T(n) = 7T\left(\frac{n}{2}\right) + cn^2$$

Using the **Substitution Method**, we expand the recurrence:
$$T(n) = 7 \left[ 7T\left(\frac{n}{4}\right) + c\left(\frac{n}{2}\right)^2 \right] + cn^2$$
$$T(n) = 7^2 T\left(\frac{n}{4}\right) + \frac{7}{4}cn^2 + cn^2$$

Expanding another step:
$$T(n) = 7^2 \left[ 7T\left(\frac{n}{8}\right) + c\left(\frac{n}{4}\right)^2 \right] + \frac{7}{4}cn^2 + cn^2$$
$$T(n) = 7^3 T\left(\frac{n}{8}\right) + \left(\frac{7}{4}\right)^2 cn^2 + \frac{7}{4}cn^2 + cn^2$$

Generalizing for $k$ steps:
$$T(n) = 7^k T\left(\frac{n}{2^k}\right) + cn^2 \sum_{i=0}^{k-1} \left(\frac{7}{4}\right)^i$$

Assume $n = 2^k$, meaning $k = \log_2 n$. The geometric series sum formula is $\frac{r^k - 1}{r - 1}$. Substituting $k$:
$$T(n) = 7^{\log_2 n} T(1) + cn^2 \left[ \frac{\left(\frac{7}{4}\right)^{\log_2 n} - 1}{\frac{7}{4} - 1} \right]$$

Using the property $7^{\log_2 n} = n^{\log_2 7}$, and simplifying the geometric series:
$$T(n) = n^{\log_2 7} + cn^2 \left( \frac{4}{3} \right) \left[ \frac{7^{\log_2 n}}{4^{\log_2 n}} - 1 \right]$$
$$T(n) = n^{\log_2 7} + \frac{4}{3}cn^2 \left[ \frac{n^{\log_2 7}}{n^2} - 1 \right]$$
$$T(n) = n^{\log_2 7} + \frac{4}{3}c (n^{\log_2 7} - n^2)$$

The term $n^{\log_2 7}$ dominates the $n^2$ term. Since $\log_2 7 \approx 2.81$, the final time complexity is:
$$T(n) = \Theta(n^{\log_2 7}) = O(n^{2.81})$$

## Comparison: Standard D&C vs. Strassen

| Feature | Standard D&C | Strassen's Algorithm |
| :--- | :--- | :--- |
| **Time Complexity** | $O(n^3)$ | $O(n^{2.81})$ |
| **Recursive Multiplications**| 8 | 7 |
| **Additions per Split** | 4 | 18 |

## How to Compile and Run
To compile and execute the program, use the following commands in your terminal:
```bash
gcc q4.c -o a.exe
./a.exe
```

### Example Output
```text
Enter 1 to input matrices manually, or 2 to generate randomly: 2
Enter the dimension of the square matrices (n): 10

Generating random matrices...

Matrix A:
3 9 0 0 4 8 3 0 6 6 
0 0 9 3 7 4 5 3 1 1 
6 0 0 9 1 0 5 7 7 2 
5 2 1 4 3 2 1 8 1 4 
6 1 8 5 3 5 9 8 7 3 
4 6 5 8 4 2 3 0 7 1 
2 5 7 7 8 8 3 6 7 1 
7 6 9 0 8 8 2 9 7 5 
8 6 8 5 1 4 2 1 7 0 
8 7 3 3 3 1 3 7 0 5 

Matrix B:
2 9 0 9 1 6 0 3 6 6 
3 2 5 1 9 3 1 2 7 1 
5 5 0 0 0 4 2 9 9 4 
4 2 6 2 6 5 2 6 3 5 
4 5 3 0 6 3 5 3 9 2 
1 8 7 6 3 2 7 8 2 2 
8 6 7 6 3 5 0 3 4 3 
8 1 0 7 3 1 5 3 1 0 
2 1 8 0 3 5 6 5 3 4 
7 9 9 9 4 7 7 1 4 2 

Resultant Matrix C (A * B):
135 207 236 156 183 160 163 148 187 96 
162 161 119 90 103 120 115 182 191 94 
176 139 166 169 131 165 114 148 128 130 
153 144 108 165 117 119 115 113 127 81 
263 257 225 232 162 224 180 260 244 171 
146 159 190 97 170 175 115 190 212 141 
215 221 233 154 213 193 208 272 262 151 
254 297 225 237 207 225 242 275 311 160 
140 191 161 131 140 180 112 217 224 155 
192 200 135 203 160 164 111 135 201 109 
```