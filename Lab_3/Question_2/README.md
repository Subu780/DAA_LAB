# Defective Coin Finder (Divide & Conquer)

## File Directory
```text
Question_2/
├── a.exe
├── q2.c
└── README.md
```

## Overview
This project simulates a quality control scenario in a coin manufacturing facility. A worker may have over-shaped a single coin, making it lighter than the rest. The program's goal is to process an array of `n` coins to either find the exact index of the defective (lighter) coin or confirm that the entire batch is perfectly weighted. 

Normal coins are represented with a weight of `1`, and a defective coin is represented with a weight of `-1`. The algorithm guarantees a time complexity of O(log2 n + c).

## The Logic and Algorithm
To achieve logarithmic time complexity, the program uses a **Divide and Conquer** algorithm that mimics a physical balance weighing scale.

### The Steps:
1. **Divide**: At each step, the algorithm takes the current sequence of coins and splits it into two equal halves.
   - If the current number of coins is **even**, the pile is split perfectly down the middle.
   - If the current number of coins is **odd**, the pile is split into two equal halves, and the very last coin is temporarily set aside.

2. **Weigh**: The algorithm calculates the total sum of the weights of the left half and the right half.

3. **Conquer (Compare)**:
   - **Left is lighter (Sum Left < Sum Right):** The defective coin must be in the left half. The right half is discarded, and the algorithm recurses on the left half.
   - **Right is lighter (Sum Right < Sum Left):** The defective coin must be in the right half. The left half is discarded, and the algorithm recurses on the right half.
   - **Both sides balance (Sum Left == Sum Right):** All coins in both halves are perfectly normal. 
     - If the total number of coins was even, the entire batch is perfect (Return -1).
     - If the total number of coins was odd, the one coin we set aside is our only suspect. If its weight is -1, it is the defective coin.

4. **Base Case**: The recursion continues halving the search space until only 1 coin remains. It then simply checks if that remaining coin is equal to -1.

## Program Features
The program features two modes of operation:
* **Option 1 (Manual Input):** Allows the user to specify the size of the array and manually type out the sequence of 1s and -1s.
* **Option 2 (Random Generation):** The user specifies the size of the array, and the system automatically generates it. It uses a weighted probability system where there is a 90% chance of inserting a defective coin at a random index, and a 10% chance of generating a perfectly flawless batch.

## How to Compile and Run
Open your terminal or command prompt and run:
```bash
gcc defective_coin.c -o defective_coin
./defective_coin
```

## Sample Output
```bash
Enter 1 to input coins manually, or 2 to generate a random batch: 2

Enter the total number of coins for the random batch: 1000000
[Simulation Info] A defective coin was secretly placed at index 32029.

Inspection Report
STATUS: FAIL - Algorithm isolated defective coin at index 32029.
```