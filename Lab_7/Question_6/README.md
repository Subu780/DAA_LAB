# The Best Time to Be Alive

## Problem Statement

An editor of *The History of the World Science* wants to find out the time when the largest number of prominent scientists were alive. The prominent scientists are, by definition, the people mentioned in the book with the dates of their birth and death. (No living scientists are included in the book.) Devise an algorithm for this task if it has the book's index as its input. The entries in the index are sorted alphabetically and give the persons' birth and death years. If a person A died the same year person B was born, assume that the former event happened before the latter one. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## File Structure

```
Question_6/
    ├── q6.c
    ├── a.out
    └── README.md
```

- `q6.c`: the C source implementing the sweep-line algorithm, the menu, and the validation.
- `a.out`: the compiled binary of the program..
- `README.md`: this documentation file.

## Detailed Explanation

### Modeling a Life as an Interval

Each scientist's life is naturally modeled as a **half-open interval**

$$
[\text{birth},\; \text{death})
$$

The scientist is alive in every year from (and including) the birth year up to, but **not including**, the death year.

### Why Death-Exclusive Counting Is Forced

The convention states: *"If a person A died the same year person B was born, assume the former event happened before the latter one."* At the exact year $x$ where A dies and B is born, A's death occurs first, so A and B are **never simultaneously alive**. A is **not** counted alive in year $x$ (their death year), while B **is** counted alive in year $x$ (their birth year). This is exactly death-exclusive:

$$
\text{alive in year } y \iff \text{birth} \le y < \text{death}
$$

### The Sweep-Line / Event-Sorting Approach

Convert each interval $[\text{birth}, \text{death})$ into two events:

$$
\text{birth event}: (y = \text{birth},\; \Delta = +1), \qquad
\text{death event}: (y = \text{death},\; \Delta = -1)
$$

Sort all $2m$ events by year. At the **same year, process all death events before all birth events**, which enforces the death-before-birth convention. Sweep through the sorted events keeping a running count `alive`. After processing the full batch of events at year $y$, `alive` equals the number of people alive in year $y$. Record the maximum and the argmax years.

**Complexity:** the sorting dominates:

$$
O(m \log m)
$$

time and $O(m + R)$ space. This is independent of the year range $R$ and therefore scalable.

### Tie-Break Walkthrough

**Dataset:** $A(1600, 1650)$, $B(1640, 1680)$, $C(1650, 1690)$, $D(1700, 1750)$.

Sorted events (deaths before births at the same year) with the running count:

| Year | Events | Alive after | Years count persists | Alives |
|------|--------|-------------|----------------------|--------|
| 1600 | $A$ born $(+1)$ | 1 | 1600–1639 | $A$ |
| 1640 | $B$ born $(+1)$ | 2 | 1640–1649 | $A, B$ |
| 1650 | $A$ dies $(-1)$, $C$ born $(+1)$ | 2 | 1651–1679 | $B, C$ |
| 1680 | $B$ dies $(-1)$ | 1 | 1681–1689 | $C$ |
| 1690 | $C$ dies $(-1)$ | 0 | 1690–1699 | — |
| 1700 | $D$ born $(+1)$ | 1 | 1701–1749 | $D$ |
| 1750 | $D$ dies $(-1)$ | 0 | — | — |

The maximum is $\mathbf{2}$, achieved across **1640–1679**. At year 1650, $A$ is counted as dead (death-exclusive) and $C$ as born, so the composition switches from $\{A,B\}$ to $\{B,C\}$ — exactly the convention's effect.

## Approaches

### Sweep-Line / Event Sorting

#### Implementation

Each scientist yields a `(year, +1)` birth event and a `(year, -1)` death event. Events are sorted by year with deaths before births at equal years. A running count is maintained; after processing each distinct event year, if the count equals the running maximum, every year from this event year up to (not including) the next event year is appended to the argmax list.

## Example Output

Manual 4-scientist tie-break dataset:

```
Choose input method:
1. Random scientists
2. Manual input
Enter choice: Enter number of scientists (1-50): 
Number of scientists: 4
Name Birth Death
A 1600 1650
B 1640 1680
C 1650 1690
D 1700 1750

Sweep-line result: max 2 alive, years 1640 ... 1679
```

The sweep-line method reports a maximum of $2$ scientists alive, achieved across the years 1640–1679, exactly as the walkthrough predicts.
