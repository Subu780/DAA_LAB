# Laboratory 7

Design and Analysis of Algorithms (DAA)

## Table of Contents

1. [Overview](#overview)
2. [How to Run Any Program](#how-to-run-any-program)
3. [Questions](#questions)
   - [Question 1: Invert the Coin Triangle](#question-1)
   - [Question 2: Super Egg Testing Experiment](#question-2)
   - [Question 3: Reve's Puzzle](#question-3)
   - [Question 4: Security Switches](#question-4)
   - [Question 5: Hitting a Moving Target](#question-5)
   - [Question 6: The Best Time to Be Alive](#question-6)
   - [Question 7: Matrix Chain Multiplication](#question-7)

## Overview

Lab 7 covers seven classic algorithm-design problems. Each problem lives in its own folder with three files:

- `qN.c` — the C program implementing the algorithm(s)
- `a.out` — the pre-compiled executable of that program
- `README.md` — a detailed write-up with the problem statement, full explanation, approach, complexity analysis, and example output

Every program uses the same interaction pattern: a small menu with **Option 1 = random input** and **Option 2 = manual input**, so you can either generate a test case instantly or type your own values.

## How to Run Any Program

To run any program:

1. Go to the respective question folder:

   ```
   cd Lab_7/Question_N
   ```

2. Compile the source code:

   ```
   gcc qN.c -o a.out
   ```

3. Run the compiled program:

   ```
   ./a.out
   ```

Follow the on-screen menu. All programs accept **1** for random input (seeded with the current time) or **2** for manual input. For manual input, type the requested values and press Enter after each one.

## Questions

### Question 1: Invert the Coin Triangle

Invert an equilateral triangle of coins in the minimum number of moves, validating the compact formula and the DP recurrence with a menu-driven C program.

- Folder: `Lab_7/Question_1`
- Menu: 1 = random size, 2 = enter the size $n$
- Approach: closed form $M(n) = \frac{n(n+1)}{2}$ and the DP recurrence $dp[i] = dp[i-1] + i$

### Question 2: Super Egg Testing Experiment

Find the minimum number of egg droppings guaranteed to locate the highest safe floor, generalised to $E$ eggs and $F$ floors via dynamic programming.

- Folder: `Lab_7/Question_2`
- Menu: 1 = random eggs and floors, 2 = enter eggs and floors yourself
- Approach: top-down memoized DP and bottom-up tabular DP, recurrence $\text{eggDrop}(e,f) = 1 + \min_x \max(\text{eggDrop}(e-1,x-1),\ \text{eggDrop}(e,f-x))$
- Hint: for the classic 2-egg 100-floor case, use manual input with eggs = 2 and floors = 100; the answer is 14

### Question 3: Reve's Puzzle

Transfer $n$ disks between four pegs (never placing a larger disk on a smaller one) in the minimum number of moves, solved optimally in 33 moves for 8 disks using the Frame-Stewart algorithm.

- Folder: `Lab_7/Question_3`
- Menu: 1 = random disks (1–10), 2 = enter the number of disks (1–15), 3 = classic 8-disk Reve case
- Approach: Frame-Stewart DP with recurrence $T(n) = \min_k[\,2T(k) + (2^{n-k} - 1)\,]$ plus a recursive generator that prints and counts the actual moves
- Hint: menu option 3 (or enter 8) gives exactly 33 moves

### Question 4: Security Switches

Turn off $n$ security switches, all initially on, in the minimum number of moves under the restricted toggling rules.

- Folder: `Lab_7/Question_4`
- Menu: 1 = random switches (1–10), 2 = enter the number of switches (1–20)
- Approach: BFS shortest-path search over the $2^n$ states (prints the optimal toggle sequence for $n \le 10$) validated against the closed form $M(n) = \left\lfloor \frac{2^{n+1} - 1}{3} \right\rfloor$

### Question 5: Hitting a Moving Target

Guarantee hitting a target that moves to an adjacent hiding spot between shots, using the parity-based double sweep and an adversarial reachability proof.

- Folder: `Lab_7/Question_5`
- Menu: 1 = random $n$ (3–10), 2 = enter $n$ yourself ($\ge 2$)
- Approach: double sweep (2, 3, …, n−1 then n−1, …, 2) with a reachability check proving a hit within $2n-4$ shots; also simulates one random target

### Question 6: The Best Time to Be Alive

Find the year(s) when the largest number of scientists were alive, honouring the death-before-birth same-year convention.

- Folder: `Lab_7/Question_6`
- Menu: 1 = random scientists, 2 = manual entry (number of scientists, then name, birth year, death year per line)
- Approach: sweep-line over birth/death events with complexity $O(m \log m)$; a person is alive in year $y$ iff $\text{birth} \le y < \text{death}$

### Question 7: Matrix Chain Multiplication (MCM)

Find the minimum number of scalar multiplications to multiply a chain of matrices, and print the optimal parenthesization.

- Folder: `Lab_7/Question_7`
- Menu: 1 = random dimensions, 2 = manual input (number of matrices, then the $n+1$ dimensions)
- Approach: bottom-up DP with recurrence $m[i][j] = \min_{i \le k < j}[\,m[i][k] + m[k+1][j] + p[i-1]p[k]p[j]\,]$ and split-table reconstruction, $O(n^3)$ time / $O(n^2)$ space