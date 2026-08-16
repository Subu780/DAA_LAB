# Structured Matrix Multiplication in $O(n^2)$

## File Directory
The directory is organized as follows:
```text
Question_5/
├── a.exe
├── q5.c
└── README.md
```

## Overview
This project implements an optimized Divide and Conquer algorithm in C (`q5.c`) to multiply two $n \times n$ matrices (where $n = 2^k$) that possess a specific recursive block structure. The matrices are composed such that the main diagonal blocks are identical, and the off-diagonal blocks are identical:

$$M = \begin{pmatrix} M_1 & M_2 \\ M_2 & M_1 \end{pmatrix}$$

By leveraging this symmetry, the algorithm skips the standard 8 recursive multiplications (which take $O(n^3)$ time) and even bypasses Strassen's 7 multiplications. Instead, it computes the product using only **2 recursive multiplications**, dropping the overall time complexity to exactly $O(n^2)$.

## The Algebraic Trick
Let the two matrices be $A$ and $B$, both having the defined structure:
$$A = \begin{pmatrix} A_1 & A_2 \\ A_2 & A_1 \end{pmatrix}, \quad B = \begin{pmatrix} B_1 & B_2 \\ B_2 & B_1 \end{pmatrix}$$

The resulting matrix $C = A \times B$ will naturally have the exact same structure:
$$C = \begin{pmatrix} C_1 & C_2 \\ C_2 & C_1 \end{pmatrix}$$

To find $C_1$ and $C_2$, standard matrix multiplication dictates:
* $C_1 = A_1 B_1 + A_2 B_2$
* $C_2 = A_1 B_2 + A_2 B_1$

Computing these directly requires **4 multiplications**. To reduce this, we define two new terms:
* $P_1 = (A_1 + A_2) \times (B_1 + B_2) = A_1 B_1 + A_1 B_2 + A_2 B_1 + A_2 B_2$
* $P_2 = (A_1 - A_2) \times (B_1 - B_2) = A_1 B_1 - A_1 B_2 - A_2 B_1 + A_2 B_2$

Now, observe what happens when we add and subtract $P_1$ and $P_2$:
* $P_1 + P_2 = 2A_1 B_1 + 2A_2 B_2 = 2(A_1 B_1 + A_2 B_2) = 2C_1$
* $P_1 - P_2 = 2A_1 B_2 + 2A_2 B_1 = 2(A_1 B_2 + A_2 B_1) = 2C_2$

Therefore, the final quadrants are simply:
* $C_1 = \frac{P_1 + P_2}{2}$
* $C_2 = \frac{P_1 - P_2}{2}$

This mathematical maneuver computes $C$ using only **2 recursive multiplications** ($P_1$ and $P_2$).

## Time Complexity Validation (Substitution Method)
Because the algorithm recursively splits the matrix into halves and performs exactly 2 multiplications, along with matrix additions/subtractions that take $O(n^2)$ time, our recurrence relation is:

$$T(n) = 2T\left(\frac{n}{2}\right) + cn^2$$

Using the **Substitution Method**, we expand the recurrence:
$$T(n) = 2 \left[ 2T\left(\frac{n}{4}\right) + c\left(\frac{n}{2}\right)^2 \right] + cn^2$$
$$T(n) = 2^2 T\left(\frac{n}{4}\right) + 2c\left(\frac{n^2}{4}\right) + cn^2$$
$$T(n) = 2^2 T\left(\frac{n}{4}\right) + c\left(\frac{n^2}{2}\right) + cn^2$$

Expanding another step:
$$T(n) = 2^2 \left[ 2T\left(\frac{n}{8}\right) + c\left(\frac{n}{4}\right)^2 \right] + \frac{cn^2}{2} + cn^2$$
$$T(n) = 2^3 T\left(\frac{n}{8}\right) + c\left(\frac{n^2}{4}\right) + \frac{cn^2}{2} + cn^2$$

Generalizing for $k$ steps:
$$T(n) = 2^k T\left(\frac{n}{2^k}\right) + cn^2 \sum_{i=0}^{k-1} \left(\frac{1}{2}\right)^i$$

Assume $n = 2^k$, which means $k = \log_2 n$. The base case is $T(1) = 1$. Substituting $k$:
$$T(n) = 2^{\log_2 n} T(1) + cn^2 \sum_{i=0}^{\log_2 n - 1} \left(\frac{1}{2}\right)^i$$

Since $2^{\log_2 n} = n$, and the infinite geometric series $\sum_{i=0}^{\infty} (\frac{1}{2})^i$ converges exactly to $2$:
$$T(n) = n + cn^2 (2)$$
$$T(n) = 2cn^2 + n$$

Because the $n^2$ term dominates the linear $n$ term, the final time complexity is mathematically proven to be:
$$T(n) = O(n^2)$$

## How to Compile and Run
To compile and execute the program, use the following commands in your terminal:
```bash
gcc q5.c -o a.exe
./a.exe
```

### Example Output
```text
Enter 1 to input matrices manually, or 2 to generate randomly: 2
Enter the dimension of the square matrices (n must be power of 2): 16

Generating random structured matrices...

Matrix A:
1 4 9 0 2 9 2 4 7 7 9 5 0 5 8 2 
4 1 0 9 9 2 4 2 7 7 5 9 5 0 2 8 
9 0 1 4 2 4 2 9 9 5 7 7 8 2 0 5 
0 9 4 1 4 2 9 2 5 9 7 7 2 8 5 0 
2 9 2 4 1 4 9 0 0 5 8 2 7 7 9 5 
9 2 4 2 4 1 0 9 5 0 2 8 7 7 5 9 
2 4 2 9 9 0 1 4 8 2 0 5 9 5 7 7 
4 2 9 2 0 9 4 1 2 8 5 0 5 9 7 7 
7 7 9 5 0 5 8 2 1 4 9 0 2 9 2 4 
7 7 5 9 5 0 2 8 4 1 0 9 9 2 4 2 
9 5 7 7 8 2 0 5 9 0 1 4 2 4 2 9 
5 9 7 7 2 8 5 0 0 9 4 1 4 2 9 2 
0 5 8 2 7 7 9 5 2 9 2 4 1 4 9 0 
5 0 2 8 7 7 5 9 9 2 4 2 4 1 0 9 
8 2 0 5 9 5 7 7 2 4 2 9 9 0 1 4 
2 8 5 0 5 9 7 7 4 2 9 2 0 9 4 1 

Matrix B:
7 5 1 7 0 0 1 0 9 9 8 2 2 5 0 4 
5 7 7 1 0 0 0 1 9 9 2 8 5 2 4 0 
1 7 7 5 1 0 0 0 8 2 9 9 0 4 2 5 
7 1 5 7 0 1 0 0 2 8 9 9 4 0 5 2 
0 0 1 0 7 5 1 7 2 5 0 4 9 9 8 2 
0 0 0 1 5 7 7 1 5 2 4 0 9 9 2 8 
1 0 0 0 1 7 7 5 0 4 2 5 8 2 9 9 
0 1 0 0 7 1 5 7 4 0 5 2 2 8 9 9 
9 9 8 2 2 5 0 4 7 5 1 7 0 0 1 0 
9 9 2 8 5 2 4 0 5 7 7 1 0 0 0 1 
8 2 9 9 0 4 2 5 1 7 7 5 1 0 0 0 
2 8 9 9 4 0 5 2 7 1 5 7 0 1 0 0 
2 5 0 4 9 9 8 2 0 0 1 0 7 5 1 7 
5 2 4 0 9 9 2 8 0 0 0 1 5 7 7 1 
0 4 2 5 8 2 9 9 1 0 0 0 1 7 7 5 
4 0 5 2 2 8 9 9 0 1 0 0 7 1 5 7 

Resultant Matrix C (A * B):
279 326 336 305 280 253 271 278 318 253 301 282 201 282 230 245 
326 279 305 336 253 280 278 271 253 318 282 301 282 201 245 230 
336 305 279 326 271 278 280 253 301 282 318 253 230 245 201 282 
305 336 326 279 278 271 253 280 282 301 253 318 245 230 282 201 
280 253 271 278 279 326 336 305 201 282 230 245 318 253 301 282 
253 280 278 271 326 279 305 336 282 201 245 230 253 318 282 301 
271 278 280 253 336 305 279 326 230 245 201 282 301 282 318 253 
278 271 253 280 305 336 326 279 245 230 282 201 282 301 253 318 
318 253 301 282 201 282 230 245 279 326 336 305 280 253 271 278 
253 318 282 301 282 201 245 230 326 279 305 336 253 280 278 271 
301 282 318 253 230 245 201 282 336 305 279 326 271 278 280 253 
282 301 253 318 245 230 282 201 305 336 326 279 278 271 253 280 
201 282 230 245 318 253 301 282 280 253 271 278 279 326 336 305 
282 201 245 230 253 318 282 301 253 280 278 271 326 279 305 336 
230 245 201 282 301 282 318 253 271 278 280 253 336 305 279 326 
245 230 282 201 282 301 253 318 278 271 253 280 305 336 326 279 
```