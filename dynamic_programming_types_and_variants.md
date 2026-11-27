# Dynamic Programming (DP): Types, Patterns, and Variants in C++

A practical reference covering the major dynamic-programming families,
common variants, recognition clues, recurrence patterns, and
optimization techniques.

> **Important:** DP categories overlap. For example, a problem can be
> simultaneously *tree DP*, *bitmask DP*, and *counting DP*. The
> categories below describe different dimensions of a solution: the
> structure of the states, the problem being solved, or the technique
> used to optimize transitions.

------------------------------------------------------------------------

## 1. What is Dynamic Programming?

Dynamic Programming is a problem-solving technique for problems that can
be expressed using:

1.  **States** -- what information describes a subproblem.
2.  **Transitions** -- how a state is computed from smaller or
    previously solved states.
3.  **Base cases** -- states whose answers are already known.
4.  **Evaluation order** -- the order in which states are computed.
5.  **Final answer** -- the state or combination of states that answers
    the original problem.

DP is especially useful when a problem has:

-   **Overlapping subproblems:** the same subproblem is needed multiple
    times.
-   **Optimal substructure:** a solution can be built from solutions to
    smaller subproblems.

A useful design question is:

> What is the smallest amount of information I need to remember so that
> the remaining decisions and the answer can be computed correctly?

That information becomes the DP state.

### A basic example: Fibonacci numbers

Recurrence:

\[ F(n) = F(n-1) + F(n-2) \]

Base cases:

\[ F(0)=0,`\quad `{=tex}F(1)=1 \]

A naive recursive implementation repeats work. DP stores each result and
avoids recalculating it.

------------------------------------------------------------------------

## 2. Main implementation approaches

These are the two fundamental ways to implement DP, plus common memory
refinements.

### 2.1 Top-down DP (Memoization)

Start with the original problem and recursively solve the subproblems.
Store each answer so it is calculated only once.

``` cpp
int solve(int n, vector<int>& memo) {
    if (n <= 1) return n;

    if (memo[n] != -1) return memo[n];

    return memo[n] = solve(n - 1, memo) + solve(n - 2, memo);
}
```

**Characteristics** - Usually resembles the mathematical recurrence. -
Computes only states that are actually reached. - Uses recursion and a
memo table. - Recursion depth can cause stack limitations.

### 2.2 Bottom-up DP (Tabulation)

Start from base cases and fill the table in an order that ensures
dependencies are already computed.

``` cpp
int fibonacci(int n) {
    if (n <= 1) return n;

    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; ++i)
        dp[i] = dp[i - 1] + dp[i - 2];

    return dp[n];
}
```

**Characteristics** - No recursion required. - The evaluation order is
explicit. - Often easier to optimize memory. - May compute states that
are never needed.

### 2.3 Space-optimized DP

If a state depends only on a small number of previous states, keep only
those values rather than the entire table.

``` cpp
int fibonacci(int n) {
    if (n <= 1) return n;

    int prev2 = 0, prev1 = 1;

    for (int i = 2; i <= n; ++i) {
        int cur = prev1 + prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}
```

This reduces Fibonacci storage from O(n) to O(1).

### 2.4 Rolling-array DP

Keep only the previous one or few rows/layers of a larger DP table.
Common in grid DP, string DP, and multidimensional DP.

### 2.5 In-place DP

Reuse the input or DP array itself, updating entries carefully. The loop
direction matters: for example, 0/1 knapsack usually iterates capacity
downward, while unbounded knapsack usually iterates upward.

------------------------------------------------------------------------

## 3. DP families by state structure

### 3.1 Linear / 1D DP

A state is indexed by one main variable, often a position, length,
amount, or time.

Examples: - Fibonacci - Climbing stairs - Minimum cost to reach the
end - House Robber - Decode Ways

Typical form:

\[ dp\[i\] = f(dp\[i-1\], dp\[i-2\], `\ldots`{=tex}) \]

Recognition clue: the answer for a prefix or position can be built from
a few earlier positions.

### 3.2 Grid / 2D DP

A state represents a cell or pair of coordinates.

Examples: - Unique Paths - Minimum Path Sum - Paths with obstacles -
Dungeon Game - Longest Common Subsequence (also string DP)

Typical form:

\[ dp\[i\]\[j\] = f(dp\[i-1\]\[j\], dp\[i\]\[j-1\], `\ldots`{=tex}) \]

Recognition clue: movement or decisions occur across rows and columns.

### 3.3 Multidimensional DP

A state has three or more dimensions, such as position, remaining
capacity, and number of items selected.

Example:

\[ dp\[i\]\[w\]\[k\] \]

could mean the best value using the first `i` items, capacity `w`, and
exactly `k` selections.

Use only dimensions that are necessary. Large state spaces can become
expensive.

### 3.4 State-machine DP

The state records which mode, status, or condition the process is
currently in.

Examples: - Stock trading with holding/not holding - Trading with a
cooldown - Trading with a transaction limit - Tasks with
available/unavailable states

Example state meanings: - `hold[i]`: best result after day `i` while
holding a stock. - `cash[i]`: best result after day `i` while not
holding a stock.

Recognition clue: the same position has different future possibilities
depending on the current status.

### 3.5 Prefix / suffix DP

Compute answers for prefixes or suffixes of an array or string.

Examples: - Maximum subarray variants - Prefix segmentation - Combining
left-side and right-side information - Some partitioning problems

A common technique is to compute `left[i]` and `right[i]`, then combine
them.

------------------------------------------------------------------------

## 4. Knapsack and resource-allocation DP

Knapsack is a large family of DP problems involving choices under a
capacity or resource limit.

### 4.1 0/1 Knapsack

Each item can be selected at most once.

State: `dp[w]` = maximum value achievable with capacity at most `w`.

Transition:

\[ dp\[w\] = `\max`{=tex}(dp\[w\], dp\[w-weight_i\] + value_i) \]

For a one-dimensional implementation, iterate `w` **downward** so the
current item is not reused.

``` cpp
for (int i = 0; i < n; ++i) {
    for (int w = capacity; w >= weight[i]; --w) {
        dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
    }
}
```

Variants: - Maximum value under capacity - Exact-fill knapsack - Subset
Sum - Equal Partition - Count subsets with a given sum - Minimum number
of items to reach a sum

### 4.2 Unbounded Knapsack

Each item can be selected unlimited times.

For one-dimensional DP, capacity usually iterates **upward**:

``` cpp
for (int i = 0; i < n; ++i) {
    for (int w = weight[i]; w <= capacity; ++w) {
        dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
    }
}
```

Variants: - Coin Change (minimum coins) - Coin Change (number of
combinations) - Rod Cutting - Minimum cost to reach a target

### 4.3 Bounded Knapsack

Each item has a limited quantity. Common approaches: - Expand each
quantity into 0/1 items. - Binary decomposition of quantities. -
Monotonic queue optimization.

### 4.4 Multiple-choice Knapsack

Choose at most one option from each group. Examples include selecting
one product from each category under a budget.

### 4.5 Multi-constraint Knapsack

More than one resource limit, such as weight and volume. The state may
be `dp[weight][volume]`.

------------------------------------------------------------------------

## 5. Subsequence and sequence DP

These problems ask about selecting elements while preserving their
order, often without requiring them to be adjacent.

### 5.1 Longest Increasing Subsequence (LIS)

`dp[i]` can mean the length of the longest increasing subsequence ending
at index `i`.

\[ dp\[i\] = 1 + `\max`{=tex}(dp\[j\]) `\quad `{=tex}`\text{for }`{=tex}
j\<i, a\[j\]\<a\[i\] \]

The basic solution is O(n²). A patience-sorting / binary-search method
computes the LIS length in O(n log n).

Variants: - Longest decreasing subsequence - Longest non-decreasing
subsequence - Number of LIS - Weighted LIS - Longest bitonic subsequence

### 5.2 Longest Common Subsequence (LCS)

For strings `a` and `b`:

-   If characters match, extend the previous diagonal.
-   Otherwise, take the best result from dropping one character from
    either string.

\[ dp\[i\]\[j\] =
```{=tex}
\begin{cases}
dp[i-1][j-1]+1 & a[i-1]=b[j-1]\\
\max(dp[i-1][j],dp[i][j-1]) & \text{otherwise}
\end{cases}
```
\]

Typical complexity: O(nm).

Variants: - Print an actual LCS - Longest common substring (different
recurrence) - Shortest common supersequence - Edit-distance-related
problems

### 5.3 Maximum subarray DP

Kadane's algorithm:

\[ bestEndingHere = `\max`{=tex}(a\[i\], bestEndingHere+a\[i\]) \]

Track the best value seen overall.

Variants: - Maximum circular subarray - Maximum product subarray -
Maximum subarray with constraints - Maximum sum with non-adjacent
elements

------------------------------------------------------------------------

## 6. String DP

States commonly use indices into one or more strings.

Major patterns: - **Edit Distance:** minimum insertions, deletions, and
replacements to transform one string into another. - **LCS:** longest
subsequence common to two strings. - **Longest Common Substring:**
longest contiguous common segment. - **Wildcard Matching:** match text
against `?` and `*` patterns. - **Regular Expression Matching:** DP over
text and pattern positions. - **Palindrome DP:** whether a substring is
a palindrome, or the minimum changes/cuts needed. - **Word Break:**
whether a prefix can be segmented into dictionary words. - **Distinct
Subsequences:** count ways one string can appear as a subsequence of
another. - **Interleaving String:** determine whether a string is an
interleaving of two others.

Common state: `dp[i][j]` = answer for prefixes ending at positions `i`
and `j`, or for substring `[i..j]`, depending on the problem.

------------------------------------------------------------------------

## 7. Interval / range DP

A state represents a contiguous interval `[l, r]`.

Typical recurrence:

\[ dp\[l\]\[r\] = `\min`{=tex}/`\max`{=tex}\_{k `\in [l,r]`{=tex}}
`\left`{=tex}(dp\[l\]\[k\] + dp\[k+1\]\[r\] + cost(l,k,r)`\right`{=tex})
\]

Common evaluation order: increasing interval length.

Examples: - Matrix Chain Multiplication - Burst Balloons - Minimum Cost
to Cut a Stick - Optimal Binary Search Tree - Strange Printer - Some
palindrome partitioning problems

Recognition clue: the problem repeatedly splits a range into smaller
ranges, or combines two subintervals.

------------------------------------------------------------------------

## 8. Partition DP

Split a sequence into groups or segments while optimizing a cost.

Typical form:

\[ dp\[i\] = `\min`{=tex}\_{j\<i}(dp\[j\] + cost(j+1,i)) \]

Examples: - Minimum cuts / minimum segments - Partition Array for
Maximum Sum - Divide an array into `k` groups - Text line wrapping -
Some clustering and scheduling problems

Important variants: - Exactly `k` partitions - At most `k` partitions -
Equal-sum partition - Minimum/maximum cost partition

------------------------------------------------------------------------

## 9. Tree DP

A state is computed using information from a node and its children.

Examples: - Maximum independent set on a tree - Tree diameter - Minimum
vertex cover - Count connected subtrees - Maximum matching on a tree

Example: maximum-weight independent set on a tree.

For each node `u`: - `take[u]`: best result if `u` is selected. -
`skip[u]`: best result if `u` is not selected.

\[ take\[u\] = weight\[u\] + `\sum`{=tex}\_{v `\in `{=tex}children(u)}
skip\[v\] \]

\[ skip\[u\] = `\sum`{=tex}\_{v `\in `{=tex}children(u)}
`\max`{=tex}(take\[v\],skip\[v\]) \]

A DFS postorder computes child states before the parent.

### 9.1 Rerooting DP

Compute an answer for every possible root, rather than only one fixed
root.

Often uses: 1. A bottom-up pass to compute subtree information. 2. A
top-down pass to transfer information from parent to child.

Examples: - Sum of distances from every node - Best answer when each
node is considered the root - Counts or aggregates over all rooted
subtrees

------------------------------------------------------------------------

## 10. DAG DP and graph DP

### 10.1 DAG DP

If a directed graph is acyclic, process vertices in topological order.

Examples: - Longest path in a DAG - Number of paths in a DAG - Minimum
cost path in a DAG - Scheduling with dependencies

A DAG is useful because its topological order gives a valid DP
evaluation order.

### 10.2 General graph DP

DP on arbitrary graphs is harder because cycles can create circular
dependencies. Common solutions include: - Condensing strongly connected
components into a DAG. - Adding a state that makes progress monotonic. -
Using bitmask DP for small graphs. - Using shortest-path algorithms when
the problem is fundamentally a path problem.

Do not assume every graph problem is naturally a DP problem.

------------------------------------------------------------------------

## 11. Bitmask DP / DP over subsets

Use an integer's bits to represent which elements have been selected.

For `n` elements, there are `2^n` subsets.

Example state: `dp[mask][i]` = best cost after visiting the subset
represented by `mask` and ending at vertex `i`.

Common applications: - Traveling Salesperson Problem (TSP) - Assignment
problem - Shortest Hamiltonian path - Pairing problems - Counting
arrangements - Small-set scheduling

Typical complexity can be O(n² 2ⁿ), so this is usually for relatively
small `n`.

### Variants

-   `dp[mask]`: one value per subset.
-   `dp[mask][last]`: subset plus last chosen element.
-   Subset partition DP.
-   Bitmask DP with an additional resource or status dimension.

------------------------------------------------------------------------

## 12. Digit DP

Count numbers in a range that satisfy digit-based conditions.

Typical state dimensions: - Current digit position - Whether the chosen
prefix is already smaller than the limit (`tight`) - Whether the number
has started (leading-zero handling) - Previous digit or other constraint
state - Additional property state, such as digit sum or remainder

Examples: - Count numbers with digit sum equal to `S`. - Count numbers
without adjacent equal digits. - Count numbers whose value is divisible
by `m`. - Count numbers containing or avoiding a pattern.

A common technique is:

\[ answer(L,R)=count(R)-count(L-1) \]

where `count(X)` counts valid integers from zero through `X`.

------------------------------------------------------------------------

## 13. DP on probabilities and expected values

States store probabilities or expected costs rather than only integer or
boolean answers.

Examples: - Probability of reaching a target - Expected number of
moves - Random walks on acyclic state spaces - Coin/dice probability
problems - Stochastic games

Typical transition:

\[ E\[state\] = `\sum`{=tex}\_{next} P(state
`\to `{=tex}next)`\cdot `{=tex}(cost + E\[next\]) \]

The dependency structure must permit the equations to be evaluated or
solved. Cyclic expectation equations may require algebraic methods
rather than simple tabulation.

------------------------------------------------------------------------

## 14. Game DP / minimax DP

Used when players take turns and both make optimal decisions.

A state may represent the remaining interval, remaining stones, current
player, or game configuration.

Common forms: - Winning/losing state (boolean DP) - Maximum score
difference - Minimax value - Grundy numbers for impartial games

Examples: - Predict the Winner - Stone Game family - Take 1, 2, or 3
stones - Interval-picking games

A common score-difference recurrence:

\[ dp\[l\]\[r\] =
`\max`{=tex}(a\[l\]-dp\[l+1\]\[r\], a\[r\]-dp\[l\]\[r-1\]) \]

------------------------------------------------------------------------

## 15. Profile DP

Used for grid problems with small width and potentially large height.
The state is a bitmask describing the boundary between processed and
unprocessed rows/columns.

Examples: - Domino tiling - Grid independent sets with small width -
Counting ways to tile a narrow board - Certain connectivity problems on
narrow grids

The complexity often grows exponentially with the grid width, not its
height.

------------------------------------------------------------------------

## 16. SOS DP (Sum Over Subsets DP)

A technique for computing an aggregate over all submasks of every
bitmask efficiently.

For example:

\[ F\[mask\] = `\sum`{=tex}\_{sub `\subseteq `{=tex}mask} A\[sub\] \]

A direct approach can be expensive. SOS DP computes all such values in
roughly O(n 2ⁿ).

Applications: - Subset-sum aggregation - Counting compatible masks -
Bitmask frequency queries - Subset maximum/sum transforms

------------------------------------------------------------------------

## 17. Other useful specialized DP patterns

### 17.1 Divide-and-Conquer DP optimization

Speeds up certain partition DP recurrences when the optimal split points
are monotonic.

A common target is reducing O(k n²) to O(k n log n), under the required
monotonicity assumptions.

### 17.2 Knuth optimization

Optimizes some interval DP problems when the cost and optimal split
points satisfy specific conditions.

A common improvement is O(n³) to O(n²). It does **not** apply to every
interval DP.

### 17.3 Convex Hull Trick (CHT) DP

Optimizes transitions that can be represented as queries for the minimum
or maximum of lines.

Example shape:

\[ dp\[i\] = `\min`{=tex}\_j(m_j x_i+b_j) \]

Useful when transition costs can be transformed into linear functions.

Variants: - Monotonic slopes and queries (deque-based) - Arbitrary
slopes (often Li Chao tree)

### 17.4 Monotonic queue / deque optimization

Optimizes transitions involving a minimum or maximum over a sliding
window.

Example:

\[ dp\[i\] = cost\[i\] + `\min`{=tex}\_{j `\in [i-k,i-1]`{=tex}} dp\[j\]
\]

Can reduce an O(nk) transition to O(n).

### 17.5 Lagrangian / WQS binary search

Used for some optimization problems involving an exact or bounded number
of choices/groups. Add a penalty per choice, solve the penalized
problem, and binary-search the penalty when the required monotonicity
holds.

### 17.6 Matrix exponentiation for linear recurrences

If a DP recurrence is linear and the transition is fixed, represent it
as matrix multiplication. This can compute the state after a very large
number of steps in O(log n) matrix multiplications.

Example: Fibonacci in O(log n).

### 17.7 Meet-in-the-middle with DP / subset enumeration

Split a set into two halves, enumerate or DP over each half, then
combine. Often useful when `n` is too large for O(2ⁿ) but small enough
for about O(2ⁿ/²) per half.

------------------------------------------------------------------------

## 18. DP transition optimization techniques: quick comparison

  -----------------------------------------------------------------------
  Technique               Typical situation       Main idea
  ----------------------- ----------------------- -----------------------
  Space optimization      Only recent states are  Keep fewer states
                          needed                  

  Rolling array           Previous rows/layers    Reuse storage
                          are enough              

  Monotonic deque         Sliding-window min/max  Maintain candidate
                                                  states

  Divide-and-conquer      Monotone optimal split  Search split points
  optimization                                    recursively

  Knuth optimization      Special interval DP     Narrow split-point
                          conditions              range

  Convex Hull Trick       Linear-function         Maintain/query lines
                          transitions             

  Li Chao tree            Line min/max queries,   Dynamic line structure
                          arbitrary slopes        

  SOS DP                  Aggregate over all      Bitwise transform
                          submasks                

  Matrix exponentiation   Fixed linear recurrence Exponentiate transition
                                                  matrix

  Binary grouping         Bounded quantities      Convert counts into 0/1
                                                  bundles
  -----------------------------------------------------------------------

These are optimizations, not separate replacements for defining the
state and recurrence. First derive a correct DP; then determine whether
its transitions can be optimized.

------------------------------------------------------------------------

## 19. How to recognize which DP family a problem may need

  -----------------------------------------------------------------------
  Problem clue                        DP family to investigate
  ----------------------------------- -----------------------------------
  Answer for position `i` depends on  1D / sequence DP
  earlier positions                   

  Movement across rows and columns    Grid DP

  Choose items under a capacity       Knapsack DP

  Choose a subsequence preserving     Subsequence DP
  order                               

  Compare or transform two strings    String DP

  Split a contiguous range at a       Interval DP
  chosen point                        

  Divide an array/string into groups  Partition DP

  Parent-child relationships          Tree DP

  Directed acyclic dependencies       DAG DP

  Small `n`, choices are              Bitmask DP
  subsets/permutations                

  Count integers satisfying digit     Digit DP
  constraints                         

  Two players make optimal moves      Game DP / minimax

  Narrow grid, many rows              Profile DP

  Need answers for every possible     Rerooting DP
  root                                

  Transition takes min/max over a     Monotonic deque optimization
  recent window                       

  Transition is a minimum/maximum     Convex Hull Trick
  over lines                          

  Interval split points appear        Consider Knuth or
  monotonic                           divide-and-conquer optimization
  -----------------------------------------------------------------------

A clue suggests a family; it does not prove that DP is the right
technique. Derive the state and transition to confirm.

------------------------------------------------------------------------

## 20. A systematic method for solving a DP problem

Use this checklist.

### Step 1: Define the state in plain English

For example:

`dp[i]` = minimum cost to reach position `i`.

Avoid starting with code before you can explain what each state means.

### Step 2: Identify the choices

At position `i`, can you come from `i-1`, `i-2`, or another previous
state?

### Step 3: Write the recurrence

For example:

\[ dp\[i\] = cost\[i\] + `\min`{=tex}(dp\[i-1\],dp\[i-2\]) \]

### Step 4: Define base cases

For example:

\[ dp\[0\]=cost\[0\] \]

Also handle small input sizes and unreachable states.

### Step 5: Choose top-down or bottom-up

Use memoization if recursive dependencies are natural or only a subset
of states is reachable. Use tabulation when a clear evaluation order
exists or recursion depth is a concern.

### Step 6: Calculate complexity

If there are `S` states and each state examines `T` transitions:

-   Time is often O(S × T).
-   Space is often O(S), excluding input and recursion stack.

### Step 7: Optimize only after correctness

Consider rolling arrays, in-place updates, or advanced transition
optimizations only after the basic recurrence is correct.

### Step 8: Reconstruct the solution if required

If the problem asks for the actual selected items/path/partition, store
parent decisions or revisit the recurrence to reconstruct choices.

------------------------------------------------------------------------

## 21. Suggested learning roadmap

A practical order for learning DP:

1.  Fibonacci and climbing stairs -- basic 1D DP.
2.  House Robber -- choice-based 1D DP.
3.  Grid paths and minimum path sum -- 2D DP.
4.  0/1 Knapsack and Subset Sum -- resource DP.
5.  Coin Change -- unbounded knapsack.
6.  LIS -- subsequence DP.
7.  LCS and Edit Distance -- string DP.
8.  Matrix Chain Multiplication -- interval DP.
9.  Partition DP -- splitting into groups.
10. Tree independent set -- tree DP.
11. DAG shortest/longest paths -- DAG DP.
12. Bitmask DP and TSP -- subset states.
13. Digit DP -- digit constraints.
14. Game DP -- optimal opposing decisions.
15. Rerooting and profile DP.
16. Transition optimizations -- deque, divide-and-conquer, Knuth, CHT,
    SOS.

For each problem, practise explaining the state, transition, base cases,
iteration order, and complexity before coding.

------------------------------------------------------------------------

## 22. Final mental model

Do not try to memorize DP as a list of unrelated algorithms.

Most DP problems can be understood by asking:

-   **What is my state?** Position, interval, subset, node, digit, time,
    capacity, or mode?
-   **What decisions can I make?**
-   **Which smaller states does this state depend on?**
-   **Am I minimizing, maximizing, counting, or calculating a
    probability?**
-   **Can I evaluate the states in a valid order?**
-   **Can I reduce memory or optimize the transitions?**

The DP family name helps you recognize a pattern. The state and
recurrence are what actually solve the problem.
