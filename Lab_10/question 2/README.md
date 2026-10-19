# Question 2: Dynamic Connected Components in a Grid (Number of Islands II)

An $R\times C$ grid starts as all water. Land cells $(r_1,c_1),\dots,(r_k,c_k)$ are added one by one; after each addition print the number of 4-directionally connected islands.

## File Structure

```
question 2/
├── question 2.c
├── a.out
└── readme.md
```

## Explanation

### Input representation
A 2-D position is **flattened** into a single DSU index
$$id(r,c)=r\cdot C+c\qquad(0\le r<R,\ 0\le c<C)$$
so the DSU has $RC$ elements. The input is $R$, $C$, the number of operations $k$ and then $k$ pairs `r c` (0-indexed). A boolean array `land[]` records which cells are land; water cells are not part of any set yet. Option 2 generates a random grid of about $4\text{-}6\times5\text{-}8$ and 10-16 additions.

### Idea
Keep `count` = current number of islands. When a new land cell $x$ is added:
1. If it is out of the grid or already land, nothing changes.
2. Otherwise make it a singleton set and do `count++` (a new island).
3. For each of its (at most 4) land neighbours, perform `union`. **Every union that actually merges two different sets reduces the number of islands by one**, so do `count--` in that case.
4. Print `count`.

Because land is only ever added (never removed), the sets only merge, which is exactly what DSU supports. Each op therefore needs $\le 4$ unions plus $\le 8$ finds.

### Complexity
- Initialisation: $\Theta(RC)$ for the arrays.
- Each addition: $O(4\,\alpha(RC))$, so $k$ additions cost $O(k\,\alpha(RC))$.
- Total time $O(RC+k\,\alpha(RC))$; space $\Theta(RC)$.
- (A naive BFS/DFS recount after every addition costs $\Theta(k\cdot RC)$.)

## Compile and Run

```bash
gcc "question 2.c" -o a.out
./a.out
```

Every program shows a menu: **1** enter input manually, **2** generate random input, **0** exit.

## Sample Output

A manual run (option 1) followed by one random run (option 2), then exit. The random run is different every time the program is executed.

```
===== Dynamic Connected Components in a Grid =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 1
Enter rows R and columns C (R*C <= 4000000): 3 3
Enter number of land additions k (0-1000000): 7
Enter 7 positions as 'r c' (rows 0..2, columns 0..2):
0 0
0 1
1 2
2 1
1 1
0 0
5 5

Grid 3 x 3 (all water), 7 land additions

Op   1: add (0,0) -> islands = 1
Op   2: add (0,1) -> islands = 1
Op   3: add (1,2) -> islands = 2
Op   4: add (2,1) -> islands = 3
Op   5: add (1,1) -> islands = 1
Op   6: add (0,0) -> islands = 1  (already land, ignored)
Op   7: add (5,5) -> islands = 1  (out of grid, ignored)

Final grid ('.' = water, same letter = same island):
  A A . 
  . A A 
  . A . 

===== Dynamic Connected Components in a Grid =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 2
Generated random input: R = 5, C = 5, k = 16

Grid 5 x 5 (all water), 16 land additions

Op   1: add (0,4) -> islands = 1
Op   2: add (1,1) -> islands = 2
Op   3: add (0,3) -> islands = 2
Op   4: add (1,4) -> islands = 2
Op   5: add (2,4) -> islands = 2
Op   6: add (2,3) -> islands = 2
Op   7: add (2,0) -> islands = 3
Op   8: add (0,2) -> islands = 3
Op   9: add (4,0) -> islands = 4
Op  10: add (1,1) -> islands = 4  (already land, ignored)
Op  11: add (3,1) -> islands = 5
Op  12: add (4,1) -> islands = 4
Op  13: add (2,1) -> islands = 2
Op  14: add (2,3) -> islands = 2  (already land, ignored)
Op  15: add (1,2) -> islands = 1
Op  16: add (1,3) -> islands = 1

Final grid ('.' = water, same letter = same island):
  . . A A A 
  . A A A A 
  A A . A A 
  . A . . . 
  A A . . . 

===== Dynamic Connected Components in a Grid =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 0
```
