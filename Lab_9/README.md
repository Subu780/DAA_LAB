# LAB 9

## [Question 1](./Question_1): Fractional Knapsack with Deterioration Rate

There are $n$ items with value $v_i$, weight $w_i$ and decay rate $\lambda_i>0$. An item consumed at time $t$ has effective density $\frac{v_i}{w_i}-\lambda_i t$. With capacity $W$, decide the consumption order and how much of each item to take so that the total value is maximised.

## [Question 2](./Question_2): Huffman Coding

Given symbol frequencies, build a prefix-free binary code of minimum expected length and print the canonical Huffman codebook, in which codes are ordered by length (and then by symbol).

## [Question 3](./Question_3): Minimum Refuelling Stops (Reverse Greedy)

A vehicle starts with fuel $F$ and must reach a target at distance $D$. Station $i$ is at distance $d_i$ and gives $f_i$ fuel. Find the minimum number of refuelling stops needed to reach the target, or report that it is impossible.

## [Question 4](./Question_4): Minimum Cost to Connect Sticks

Sticks have lengths $L_1,\dots,L_n$. Joining sticks of lengths $x$ and $y$ costs $x+y$ and gives one stick of length $x+y$. Find the minimum total cost to join all sticks into one.

## [Question 5](./Question_5): Candy Distribution (Bi-directional Slope Greedy)

$n$ children stand in a line, each with a rating. Every child gets at least one candy, and a child with a higher rating than an immediate neighbour must get more candies than that neighbour. Find the minimum total number of candies.

## [Question 6](./Question_6): Reorganise String with K-Distance Apart

Given a string $S$ and an integer $K$, rearrange $S$ so that equal characters are at least $K$ positions apart. If this is impossible, return an empty string.

## [Question 7](./Question_7): Minimise Deviation in Array

Given an array of positive integers, you may multiply any odd element by $2$ or divide any even element by $2$, any number of times. The deviation is $\max(A)-\min(A)$. Minimise it.

## [Question 8](./Question_8): Minimum Number of Meeting Rooms

Given meeting intervals $[s_i,e_i)$, find the minimum number of conference rooms required so that no two overlapping meetings share a room.

## [Question 9](./Question_9): Hu-Tucker Greedy Simulation

Given an ordered sequence of weights $w_1,\dots,w_n$, build a binary tree whose leaves keep the strict in-order sequence of indices and which minimises $\sum_i w_i\cdot\text{depth}(i)$ (an optimal alphabetic tree).

## [Question 10](./Question_10): Greedy Superstring Conjecture (Open Problem)

Given strings $s_1,\dots,s_n$, find the shortest string that contains every $s_i$ as a substring. The program compares the classic greedy max-overlap algorithm with the exact optimum on small inputs, in the context of the (reportedly disproved, not yet officially validated) 2-approximation conjecture.

---

## How to run any question

```bash
cd Question_N
gcc -O2 -o a.out qN.c -lm
./a.out
```
