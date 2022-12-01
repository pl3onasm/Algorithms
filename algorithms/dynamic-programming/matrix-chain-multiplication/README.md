# Matrix Chain Multiplication

## Problem

Given a sequence (chain) of matrices, which are not necessarily square, find the most efficient way to multiply these matrices together. The problem is not to actually perform the matrix multiplications, but merely to determine in which order to perform them so as to minimize the total number of scalar multiplications.  
In other words, try to find the optimal parenthesization of the matrix product. A matrix product is associative, so the order in which the products are performed does not affect the result. However, the order can dramatically affect the number of scalar multiplications needed to compute that result.

This is visible from the code snippet below, where A is a $a \times b$ matrix, B is a $b \times p$ matrix, and P is an $a \times p$ matrix:

```c
void matrixProduct(int A[], int B[], int P[], int a, int b, int p){
  for (i = 0; i < a; i++){
    for (j = 0; j < b; j++){
      P[i][j] = 0;
      for (k = 0; k < p; k++)
        P[i][j] = P[i][j] + A[i][k] * B[k][j];
    }
  }
}
```

The running time is dominated by the innermost loop, which is executed $p \sdot r \sdot q$ times. If we need to multiply $n$ matrices, then the total number becomes $p_1 \sdot q_1 \sdot r_1 + p_2 \sdot q_2 \sdot r_2 + \dots + p_n \sdot q_n \sdot r_n$. How can we minimize this number?

The overall idea is similar to the one used in the rod cutting problem: while in rod cutting we tried to find the optimal cuts for a rod of length $n$ in order to maximize the total revenue, here we try to find the optimal spots to split the chain of matrices into subchains so as to minimize the number of scalar multiplications needed to compute the product of the entire chain. The optimal solution for a chain of length $n$ is then the optimal solution for a chain of length $k$ followed by the optimal solution for a chain of length $n-k$, where $ 1 \leq k \leq n-1$ is the optimal split point, and the cost is then the sum of the costs of the two subchains plus the cost of multiplying the two subchains together. To find the optimal split point, i.e. the one that minimizes the total cost, we need to try all possible values of $k$ and keep track of the minimum cost.

## Brute Force Solution

The brute force solution tackles the problem by trying all possible parenthesizations, thereby ignoring the fact that the same subproblem may be encountered multiple times in its recursive calls. The number of possible parenthesizations is in $\Omega(2^n)$, where $n$ is the number of matrices. The running time of this approach is in $O(2^n)$.

Implementation: [Matrix Chain Multiplication - Brute Force](https://github.com/pl3onasm/Algorithms/tree/main/algorithms/dynamic-programming/matrix-chain-multiplication/mcm-1.c)

## Top-Down Approach with Memoization

This approach seeks to maintain the top-down strategy of the brute force solution, while making use of memoization by maintaining a table with subproblem solutions in order to avoid recomputing the same subproblems over and over again. This strategy improves the running time to $O(n^3)$.
Implementation: [Matrix Chain Multiplication - Top down](https://github.com/pl3onasm/Algorithms/tree/main/algorithms/dynamic-programming/matrix-chain-multiplication/mcm-2.c)

## Bottom-up Approach

The bottom-up approach is similar, but it starts from the base cases and gradually builds up the solution to the original problem. Subproblems are thus solved in order of increasing chain length, so that at each point all subsolutions needed to solve the current subproblem are readily availabe. This is achieved by maintaining a table, where the solution to each subproblem is stored in a bottom-up fashion. The solution to the original problem is then the solution to the last subproblem in the table. The running time of this approach is $O(n^3)$.

Implementation: [Matrix Chain Multiplication - Bottom up](https://github.com/pl3onasm/Algorithms/tree/main/algorithms/dynamic-programming/matrix-chain-multiplication/mcm-3.c)

## Extended bottom-up approach

This extension of the previous approach also stores the optimal split points for each subproblem. This allows us to reconstruct the optimal parenthesization of the matrix chain. The running time of this approach is also in $O(n^3)$.