# Question 2

## Problem
Given square matrices with $n$ rows and $n$ columns, find the worst-case computational complexity of various matrix operations and validate them through implementation.

## Folder Structure
```
Question_2/
├── q2.c
├── a.out
└── README.md
```

## Mathematical Explanation

### Operations and Their Complexities

**(i) Matrix Addition**
- **Complexity:** $O(n^2)$
- Add corresponding elements: $C[i][j] = A[i][j] + B[i][j]$
- Must visit all $n^2$ elements

**(ii) Matrix Multiplication**
- **Complexity:** $O(n^3)$
- Standard algorithm: $C[i][j] = \sum_{k=0}^{n-1} A[i][k] \times B[k][j]$
- Three nested loops over $n$ elements each
- Strassen's algorithm achieves $O(n^{2.807})$

**(iii) Check if zero matrix**
- **Complexity:** $O(n^2)$
- Check if all $n^2$ elements are zero
- Must examine every element

**(iv) Check if symmetric**
- **Complexity:** $O(n^2)$
- Verify $A[i][j] = A[j][i]$ for all $i, j$
- Only need to check upper/lower triangle: $\frac{n^2 - n}{2}$ comparisons

**(v) Computing determinant**
- **Complexity:** $O(n!)$ (naive recursive approach)
- Cofactor expansion: $\det(A) = \sum_{j=1}^{n} (-1)^{i+j} a_{ij} \det(M_{ij})$
- Better methods exist: LU decomposition is $O(n^3)$

**(vi) Transpose in place**
- **Complexity:** $O(n^2)$
- Swap $A[i][j]$ with $A[j][i]$ for $i < j$
- Visit upper triangle elements

**(vii) Eigenvalues and eigenvectors**
- **Complexity:** $O(n^3)$ (QR algorithm, power iteration)
- Solve characteristic equation: $\det(A - \lambda I) = 0$
- Complex iterative numerical methods required
- Not implemented in this solution
