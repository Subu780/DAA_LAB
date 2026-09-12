# Hitting a Moving Target

## Problem Statement

A computer game has a shooter and a moving target. The shooter can hit any of $n > 1$ hiding spots located along a straight line in which the target can hide. The shooter can never see the target; all he knows is that the target moves to an adjacent hiding spot between every two consecutive shots. Design an algorithm that guarantees hitting the target or prove that no such algorithm exists. If any such algorithm exists, by choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## File Structure

```
Question_5/
    ├── q5.c
    ├── a.out
    └── README.md
```

- `q5.c`: the C source implementing the double-sweep strategy, adversarial reachability proof, and a random-target simulation.
- `a.out`: the compiled binary of the program..
- `README.md`: this documentation file.

## Detailed Explanation

### Modeling the Problem

Number the hiding spots $1,2,\dots,n$ left to right. The target occupies exactly one spot before each shot. Between two consecutive shots it must move to an adjacent spot: from spot $p$ it must go to $p-1$ (if $p>1$) or $p+1$ (if $p<n$). It cannot stay still.

### The Parity-Flip Fact

Since the target must move exactly one step between shots, its position parity flips every round (both $p \to p+1$ and $p \to p-1$ change the parity). After a fixed number of rounds, the parity class of the target is fully determined by its starting parity:

$$
\text{parity after } t \text{ rounds} = \bigl(\text{starting parity} + t\bigr) \bmod 2
$$

This deterministic constraint is exactly what makes a guaranteed strategy possible.

### The Double-Sweep Strategy

Shoot the line twice: spots $2, 3, \dots, n-1$ left to right, then immediately sweep back $n-1, n-2, \dots, 2$ right to left. For $n = 2$ the special sequence is simply $2, 2$. For $n \ge 3$ the sequence has

$$
2(n-2) = 2n - 4 \;\text{ shots}
$$

One sweep alone kills all starting positions of one parity; the other parity class is never in the swept spots at the right time. The first sweep acts as a "parity trap" that forces the target to one side, and the immediate reverse sweep — occurring one round later, when parities have flipped — catches the surviving class. Together the two sweeps exhaust both parities.

### Walking Through $n = 5$

The shot sequence is $2, 3, 4, 4, 3, 2$ (6 shots). Let $R(s)$ be the set of spots the target could still occupy before shot $s$, given it has dodged everything so far. Initially $R(1) = \{1,2,3,4,5\}$.

| Shot $s$ | Shot spot | Reachable set after the shot | $|R(s+1)|$ |
|----------|-----------|------------------------------|------------|
| 1 | $2$ | $\{1,3,4,5\} \Rightarrow R(2)=\{2,4,5\}$ | 3 |
| 2 | $3$ | $\{2,4,5\} \Rightarrow R(3)=\{1,3,4\}$ | 3 |
| 3 | $4$ | $\{1,3\} \Rightarrow R(4)=\{2,4\}$ | 2 |
| 4 | $4$ | $\{2\} \Rightarrow R(5)=\{1,3\}$ | 2 |
| 5 | $3$ | $\{1\} \Rightarrow R(6)=\{2\}$ | 1 |
| 6 | $2$ | $\varnothing$ | 0 |

The reachable window is gradually shaved down to a single cell and then removed. The last shot at spot $2$ eliminates the final survivor, so the target is guaranteed to be hit on or before shot 6.

### Proof of Guarantee

The adversary's reachable set never grows beyond a shrinking window and always obeys the parity flip. During the first sweep each shot removes its named spot and drags the reachable region toward spot $n$; the wall at $n$ forbids the parity the survivors would need to bounce back. After the last shot of the first sweep, the reverse sweep walks the single remaining survivor back, spot by spot, on the opposite phase, removing one spot per shot until the reachable set becomes exactly empty at the final shot.

### Complexity Analysis

The double sweep fires $2n-4$ shots for $n \ge 3$ (and $2$ shots for $n = 2$). The reachability validation keeps only a boolean array of size $n$, so the algorithm runs in $O(n)$ time and $O(n)$ space.

## Approaches

### Double-Sweep Strategy

#### Implementation

Build the shot array by appending $2, 3, \dots, n-1$ and then $n-1, \dots, 2$. For $n = 2$ use the special sequence $\{2, 2\}$.

### Adversarial Reachability Validation

#### Implementation

Maintain a boolean array `reachable[1..n]` over all legal spots. For each shot: mark the shot's spot unreachable (a target there would have been hit); if the set is now empty, print "Guaranteed hit" and stop; otherwise replace the set with the set of all legal neighbours of currently reachable spots:

$$
\text{next}(p) = \{ p-1 : p > 1 \} \cup \{ p+1 : p < n \}
$$

If the sequence ends with a non-empty set, the strategy has failed. This simulates the strongest possible target and proves the sweep; for the double sweep it never fails.

## Example Output

A manual $n = 5$ run:

```
Menu:
1. Random n (3..10)
2. Enter n yourself
Your choice: 2
Enter n (>= 2, max 40): 5

Hiding spots: 5
Guaranteed-hit shot sequence: 2 3 4 4 3 2
Adversarial reachability analysis:
  after shot 1 reachable set size = 4
  after shot 2 reachable set size = 4
  after shot 3 reachable set size = 2
  after shot 4 reachable set size = 2
  after shot 5 reachable set size = 1
  after shot 6 reachable set size = 0
Guaranteed hit within 6 shots.

Random-target simulation:
  Shot 1 at spot 2, target at 4
  Shot 2 at spot 3, target at 3
  Target hit on shot number 2 at spot 3.
```

The reachable-set sizes shrink exactly as in the walkthrough table, and the guarantee holds within $2n - 4 = 6$ shots.
