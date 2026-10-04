# Question 9

## Description

The Collatz Conjecture (3n+1 problem): start with any positive integer n. If n is even, replace it with n/2; if n is odd, replace it with 3n+1. Repeat until n becomes 1. The conjecture says every positive integer eventually reaches 1, but nobody has proved it. This is an open problem, so the program does **not** try to prove anything. It only simulates and analyses trajectories, for a single starting value and for every value in an interval [a, b].

## File structure

```
question_9/
├── question_9.c    (source code)
├── a.out           (compiled executable)
└── README.md       (this file)
```

Compile and run:

```
gcc -o a.out question_9.c
./a.out
```

## Explanation

The program first asks what to analyse (single value or interval) and then shows the usual menu (manual or random input). The code is split into small functions:

- `nextTerm(n)`: applies one Collatz step.
- `willOverflow(n)`: checks whether 3n+1 would still fit in 64 bits (n must be at most (ULLONG_MAX - 1) / 3). Values are stored in `unsigned long long`, and since the sequence can climb far above the starting value, this check is what handles integer overflow. If the check fails, the program stops that trajectory and says so instead of printing a wrong wrapped-around number.
- `getTrajectory(n, ...)`: walks from n to 1 and stores every term in a heap array. It starts with room for 64 terms and doubles the size with `realloc` when full, because the length of a trajectory is not known in advance. It also returns the highest value reached.
- `countSteps(n, ...)`: same walk but without storing anything. It is used for intervals so that millions of numbers can be checked without keeping every path.
- `analyseSingle(n)`: prints the full trajectory, the number of steps to reach 1 and the highest value.
- `analyseInterval(a, b)`: runs `countSteps` for every number in [a, b], keeping the step counts in a `malloc`'d array, and reports the start with the longest trajectory, the start with the highest peak, and the average number of steps. For small intervals (20 numbers or fewer) it also prints a table. The interval size is limited to 5,000,000 numbers.

Number of steps means how many times the rule is applied before reaching 1, so 1 itself takes 0 steps.

## Complexity analysis

There is no proven bound on the number of steps, since proving that the sequence always ends is exactly the open problem. So the cost is written in terms of S(n), the number of steps for starting value n.

- Single value: time O(S(n)) and space O(S(n)) for the stored trajectory (the array doubles, so the amortised cost per term is O(1)).
- Interval: time O(S(a) + S(a+1) + ... + S(b)), which is (b - a + 1) times the average number of steps. Space is O(b - a + 1) for the step list, and O(1) extra for each walk because `countSteps` stores nothing.
- Experiments show S(n) grows slowly (roughly like log n on average; for 1 to 100000 the average is about 108 steps), but this is observed, not proved.

## Sample input and output

**Option 1 (single value, manual input)**

```
Enter 1 to analyse a single starting value
Enter 2 to analyse an interval [a, b]
Your choice: 1

Enter 1 to give input manually
Enter 2 to generate random input
Your choice: 1
Enter starting value n (n >= 1): 7

Trajectory of 7:
7 -> 22 -> 11 -> 34 -> 17 -> 52 -> 26 -> 13 -> 40 -> 20 -> 
10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
Steps to reach 1 : 16
Highest value    : 52
```

**Option 1 (interval, manual input)**

```
Enter 1 to analyse a single starting value
Enter 2 to analyse an interval [a, b]
Your choice: 2

Enter 1 to give input manually
Enter 2 to generate random input
Your choice: 1
Enter a and b (1 <= a <= b, at most 5000000 numbers): 1 10

       Start    Steps        Highest value
           1        0                    1
           2        1                    2
           3        7                   16
           4        2                    4
           5        5                   16
           6        8                   16
           7       16                   52
           8        3                    8
           9       19                   52
          10        6                   16

Interval [1, 10] (10 numbers)
Longest trajectory : start 9 takes 19 steps
Highest peak       : start 7 reaches 52
Average steps      : 6.70
```

**Option 2 (random input, interval)**

```
Enter 1 to analyse a single starting value
Enter 2 to analyse an interval [a, b]
Your choice: 2

Enter 1 to give input manually
Enter 2 to generate random input
Your choice: 2
Generated interval [454, 6031]


Interval [454, 6031] (5578 numbers)
Longest trajectory : start 3711 takes 237 steps
Highest peak       : start 4591 reaches 8153620
Average steps      : 81.55
```

(The random sample changes on every run.)

**A bigger interval (1 to 100000)**

```
Interval [1, 100000] (100000 numbers)
Longest trajectory : start 77031 takes 350 steps
Highest peak       : start 77671 reaches 1570824736
Average steps      : 107.54
```

**Overflow handling (n = 18446744073709551615)**

```
Trajectory of 18446744073709551615:
18446744073709551615
Stopped early: the next 3n+1 would overflow 64 bits.
```
