# Question 5: Lexicographically Smallest Connected Component Permutation

Given a permutation $A$ of $1..n$ and a list of allowed swaps $(u,v)$ (swap the elements at positions $u$ and $v$, any number of times), find the lexicographically smallest permutation reachable.

## File Structure

```
question 5/
├── question 5.c
├── a.out
└── readme.md
```

## Explanation

### Input representation
$n$, the permutation $A[1..n]$ and the allowed swaps as an edge list on positions $1..n$. The only structure needed is a DSU over the positions, so the edge list is consumed directly by `union`. Option 2 generates a random permutation of 7-11 elements and 3-6 random swaps.

### Idea
Swapping along edges lets an element travel anywhere inside its **connected component** of the position graph, and any arrangement of the values within a component is reachable (repeated adjacent-pair swaps along a spanning tree generate every permutation of the component). Components are independent, so the lexicographically smallest result is obtained by placing, **inside every component, its values in increasing order at its positions in increasing order**. Greedy justification: position 1 should hold the smallest value of its component, then position 2 the next smallest of its component, and so on; no choice at an earlier position can be improved by a later one.

### Avoiding sorting
`A` is a permutation of $1..n$, so no explicit sorting is required:
1. Union all swap pairs, then compute `root[i]` for every position.
2. Build, for each component, the list of its positions in increasing order (counting sort by root, filled by scanning $i=1..n$).
3. Scan the values $v=1,2,\dots,n$ in increasing order; the position of $v$ in $A$ gives its component $r$, and $v$ is written to the next unused position of $r$'s list.

Each component therefore receives its values in sorted order for free.

### Complexity
- DSU unions: $O(m\,\alpha(n))$; finds and the counting sort: $O(n\,\alpha(n))$; the final value scan: $O(n)$.
- Total time $O\bigl((n+m)\,\alpha(n)\bigr)$, space $\Theta(n+m)$.
- (The straightforward approach of sorting each component costs $O(n\log n)$.)

## Compile and Run

```bash
gcc "question 5.c" -o a.out
./a.out
```

Every program shows a menu: **1** enter input manually, **2** generate random input, **0** exit.

## Sample Output

A manual run (option 1) followed by one random run (option 2), then exit. The random run is different every time the program is executed.

```
===== Lexicographically Smallest Permutation =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 1
Enter n (1-1000000): 6
Enter the permutation of 1..6: 4 2 6 1 5 3
Enter number of allowed swaps m (0-1000000): 3
Enter 3 swaps as 'u v' (positions 1..6):
1 3
3 5
2 6

n = 6, allowed swaps: 3
Original permutation: 4 2 6 1 5 3

Connected components (positions -> values before => after):
  positions {1,3,5}  values {4,6,5} => {4,5,6}
  positions {2,6}  values {2,3} => {2,3}
  positions {4}  values {1} => {1}

Smallest permutation: 4 2 5 1 6 3

===== Lexicographically Smallest Permutation =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 2
Generated random input: n = 7, m = 5
Swaps: (3,4) (6,1) (7,3) (4,5) (6,5)

n = 7, allowed swaps: 5
Original permutation: 6 5 1 7 2 4 3

Connected components (positions -> values before => after):
  positions {1,3,4,5,6,7}  values {6,1,7,2,4,3} => {1,2,3,4,6,7}
  positions {2}  values {5} => {5}

Smallest permutation: 1 5 2 3 4 6 7

===== Lexicographically Smallest Permutation =====
1. Enter input manually
2. Generate input randomly
0. Exit
Choice: 0
```
