# Nihongo
For JapanesePreparation
[Uploading CPP_UTCG_Pipeline_IMPROVED.drawio…]()

 Advanced Templates and Generic Programming

Since you've already started implementing a generic linked list, this is a natural next step.

    Function templates
    Class templates
    Template specialization
    Partial specialization
    Variadic templates
    Template argument deduction
    SFINAE
    Type traits
    Concepts (C++20)
    constexpr templates
    Fold expressions
    CRTP

    
Dynamic Programming (DP) — Complete Study Handbook
1. Introduction: What is Dynamic Programming?

Dynamic Programming is a problem-solving technique where we:

Break a bigger problem into smaller subproblems.
Solve those subproblems.
Store their answers.
Reuse stored answers instead of calculating them repeatedly.
Two important properties

1. Overlapping Subproblems

The same smaller problem gets calculated multiple times.

2. Optimal Substructure

The solution to a bigger problem can be constructed using solutions to smaller problems.

Three ways to implement DP
Approach	Explanation
Recursion	Break the problem into smaller problems
Memoization	Recursion + storing calculated answers
Tabulation	Iteratively calculate smaller states first
2. The 15 Fundamental DP Patterns
Pattern 1: Fibonacci / 1D DP
Core concept

The current answer depends on previously calculated answers.

Example: Fibonacci.

text
0, 1, 1, 2, 3, 5, 8, 13...


Recurrence:

cpp
dp[i] = dp[i-1] + dp[i-2];

DP state
cpp
dp[i]


Meaning: Answer to the problem at position i.

Variations
Fibonacci Number
Climbing Stairs
Min Cost Climbing Stairs
House Robber
House Robber II
Decode Ways
Maximum Sum of Non-Adjacent Elements
Jump Game
How to recognize it

Look for:

Current position depends on previous positions.
You can reach a position through different previous states.
You need maximum, minimum, or number of ways.
Pattern 2: 0/1 Knapsack
Core concept

Every item has two choices:

Include the item.
Exclude the item.

Each item can be selected at most once.

DP state
cpp
dp[i][w]


Meaning: Maximum value obtainable using the first i items with capacity w.

Recurrence

If the item fits:

cpp
dp[i][w] = max(
    value[i] + dp[i-1][w-weight[i]],
    dp[i-1][w]
);


If it doesn't fit:

cpp
dp[i][w] = dp[i-1][w];

Variations
0/1 Knapsack
Subset Sum
Equal Sum Partition
Count Subsets with Given Sum
Minimum Subset Sum Difference
Target Sum
Count Partitions with Given Difference
How to recognize it

Look for:

Array of items.
Each element can be selected or skipped.
A capacity or target sum.
Maximum value, minimum difference, counting, or possibility.
Important observation

Several problems use the same include/exclude structure but change the operation:

Problem	Operation
Knapsack	Maximum
Subset Sum	Boolean OR
Count Subsets	Addition
Minimum Difference	Minimum
Pattern 3: Unbounded Knapsack
Core concept

You can select an item multiple times.

Unlike 0/1 Knapsack, selecting an item doesn't remove it from future consideration.

DP state
cpp
dp[i][w]


Meaning: Best answer using the first i item types with capacity w.

Recurrence
cpp
dp[i][w] = max(
    value[i] + dp[i][w-weight[i]],
    dp[i-1][w]
);


Notice:

cpp
dp[i][w-weight[i]]


We use i, not i-1, because the same item can be selected again.

Variations
Unbounded Knapsack
Coin Change
Minimum Number of Coins
Rod Cutting
Maximum Ribbon Cut
Integer Break
How to recognize it

Look for:

Unlimited availability of each item.
Repeated selection allowed.
Target amount or capacity.
Maximum profit, minimum coins, or counting combinations.
Pattern 4: Subset Sum Family

This is closely related to 0/1 Knapsack.

Core concept

Determine whether a subset of elements can form a particular sum.

Example:

text
arr = {1,2,3,4,5}
target = 5


Possible subsets:

text
{5}
{1,4}
{2,3}

DP state
cpp
dp[i][sum]


Meaning: Can we achieve sum using the first i elements?

Recurrence
cpp
dp[i][sum] =
    dp[i-1][sum] ||
    dp[i-1][sum-arr[i]];


The include choice is valid only if:

cpp
arr[i] <= sum

Variations
Subset Sum
Equal Sum Partition
Count Subsets
Minimum Subset Sum Difference
Target Sum
Count Partitions with Given Difference
How to recognize it

Look for:

Selecting some elements.
Target sum.
Partitioning an array.
Counting combinations of elements.
Pattern 5: Grid DP
Core concept

Calculate the answer for each cell using neighboring cells.

Example:

text
S  0  0
0  0  0
0  0  E


Find the number of ways to reach the destination.

DP state
cpp
dp[i][j]


Meaning: Number of ways or minimum cost to reach cell (i,j).

Example recurrence

For movement only right and down:

cpp
dp[i][j] = dp[i-1][j] + dp[i][j-1];


For minimum path sum:

cpp
dp[i][j] = grid[i][j] +
           min(dp[i-1][j], dp[i][j-1]);

Variations
Unique Paths
Unique Paths II
Minimum Path Sum
Maximum Path Sum
Triangle
Cherry Pickup
Dungeon Game
Falling Path Sum
How to recognize it

Look for:

Matrix or grid.
Starting cell and destination.
Movement restrictions.
Number of paths or minimum/maximum cost.
Pattern 6: Longest Common Subsequence (LCS)
Core concept

Compare two sequences and find the longest subsequence common to both.

A subsequence maintains relative order but doesn't need to be continuous.

Example:

text
A = ABCDGH
B = AEDFHR


Common subsequence:

text
ADH

DP state
cpp
dp[i][j]


Meaning: LCS length using the first i characters of A and first j characters of B.

Recurrence

If characters match:

cpp
dp[i][j] = 1 + dp[i-1][j-1];


Otherwise:

cpp
dp[i][j] = max(
    dp[i-1][j],
    dp[i][j-1]
);

Variations
Longest Common Subsequence
Longest Common Substring
Shortest Common Supersequence
Minimum Insertions and Deletions
Longest Palindromic Subsequence
Print LCS
Sequence Pattern Matching
How to recognize it

Look for:

Two strings or sequences.
Common subsequence.
Matching characters.
Insertion/deletion transformations.
Pattern 7: Longest Increasing Subsequence (LIS)
Core concept

Find the longest subsequence in which elements are strictly increasing.

Example:

text
arr = {10,9,2,5,3,7,101,18}


One LIS:

text
2,3,7,18


Length = 4.

DP state
cpp
dp[i]


Meaning: Length of the longest increasing subsequence ending at index i.

Recurrence
cpp
if(arr[i] > arr[j])
{
    dp[i] = max(dp[i], dp[j] + 1);
}


Where j < i.

Variations
Longest Increasing Subsequence
Maximum Sum Increasing Subsequence
Longest Bitonic Subsequence
Number of LIS
Largest Divisible Subset
Longest String Chain
Russian Doll Envelopes
How to recognize it

Look for:

Increasing or decreasing sequences.
Selecting elements while preserving order.
Longest or maximum-sum subsequence.
Pattern 8: Matrix Chain Multiplication / Interval DP
Core concept

Divide a range into smaller ranges and find the optimal way to combine them.

Example:

text
A1 x A2 x A3 x A4


Matrix multiplication order affects the total number of operations.

We want the minimum cost.

DP state
cpp
dp[i][j]


Meaning: Minimum cost to solve the range from i to j.

Recurrence

Try every possible partition point k:

cpp
for(int k = i; k < j; k++)
{
    // Calculate left cost
    // Calculate right cost
    // Calculate combining cost
}


General structure:

cpp
dp[i][j] = min(
    dp[i][k] +
    dp[k+1][j] +
    cost(i,k,j)
);

Variations
Matrix Chain Multiplication
Palindrome Partitioning
Burst Balloons
Minimum Cost to Cut a Stick
Boolean Parenthesization
Strange Printer
How to recognize it

Look for:

Dividing arrays or strings into ranges.
Trying every possible partition.
Minimum or maximum cost of combining intervals.
Pattern 9: String DP
Core concept

Solve string transformation or matching problems using smaller string states.

DP state

Often:

cpp
dp[i][j]


Meaning: Answer for the first i characters of one string and first j characters of another.

Variations
Edit Distance
Wildcard Matching
Regular Expression Matching
Distinct Subsequences
Interleaving String
Minimum Insertions to Make Palindrome
Palindrome Partitioning
Example: Edit Distance

Operations:

Insert
Delete
Replace

If characters match:

cpp
dp[i][j] = dp[i-1][j-1];


Otherwise:

cpp
dp[i][j] = 1 + min({
    dp[i-1][j],
    dp[i][j-1],
    dp[i-1][j-1]
});

How to recognize it

Look for:

String transformations.
Matching patterns.
Insertions, deletions, replacements.
Subsequence or substring relationships.
Pattern 10: Tree DP
Core concept

Calculate the answer for a node using answers from its children.

Example:

text
        10
       /  \
      5    20
     / \
    2   8


The answer at a parent may depend on its left and right child answers.

DP state

Often:

cpp
dp[node]


Or multiple states:

cpp
dp[node][0]
dp[node][1]

Variations
Diameter of Binary Tree
Maximum Path Sum
House Robber III
Maximum Independent Set
Tree Matching
Minimum Vertex Cover on Trees
How to recognize it

Look for:

Tree structure.
Parent-child relationships.
Maximum or minimum values over subtrees.
Choosing or skipping nodes.
Pattern 11: Graph DP / DAG DP
Core concept

Calculate answers along graph edges.

For a Directed Acyclic Graph (DAG), process nodes in topological order.

DP state
cpp
dp[node]


Meaning: Best answer reaching or starting from a particular node.

Example recurrence

For longest path in a DAG:

cpp
dp[v] = max(dp[v], dp[u] + 1);


For every edge:

text
u -> v

Variations
Longest Path in DAG
Shortest Path in DAG
Number of Paths in DAG
Maximum Path Weight
Cheapest Flights Within K Stops
How to recognize it

Look for:

Directed acyclic graphs.
Paths with maximum or minimum cost.
Number of ways to reach nodes.
Dependencies between nodes.

Note: General graphs can contain cycles, so ordinary DAG DP cannot be applied directly.

Pattern 12: State Machine DP
Core concept

The answer depends on the current state of the system.

Example: Stock Buy and Sell.

Possible states:

text
BUY
SELL
HOLD
COOLDOWN


The allowed transitions depend on the current state.

DP state
cpp
dp[day][state]


Meaning: Maximum profit on a particular day while being in a particular state.

Variations
Best Time to Buy and Sell Stock
Stock Buy and Sell II
Stock Buy and Sell III
Stock with Transaction Fee
Stock with Cooldown
Maximum Profit with K Transactions
How to recognize it

Look for:

Actions that change what you can do next.
Buy/sell/hold decisions.
Cooldown restrictions.
Limited number of operations.
Different modes or states.
Pattern 13: Bitmask DP
Core concept

Represent a subset of elements using binary bits.

Example:

For four elements:

text
0000 = No elements selected
0001 = Element 0 selected
0011 = Elements 0 and 1 selected
1111 = All elements selected

DP state
cpp
dp[mask]


Or:

cpp
dp[mask][i]


Meaning: Answer for a particular selected subset, sometimes ending at element i.

Variations
Traveling Salesman Problem
Assignment Problem
Minimum Cost to Visit All Cities
Shortest Superstring
Minimum Team Selection
How to recognize it

Look for:

A relatively small number of elements.
Selecting subsets.
Visiting each element once.
Assignment or permutation optimization.
Pattern 14: Digit DP
Core concept

Count numbers satisfying specific digit-related constraints.

Example:

How many numbers between 1 and 1000 have no repeated digits?

Instead of checking every number, construct numbers digit by digit and remember relevant states.

DP state

Common state parameters include:

cpp
dp[position][tight][started][mask]


Meaning:

position: Current digit position.
tight: Whether we are restricted by the upper bound.
started: Whether a non-leading-zero digit has been selected.
mask: Which digits have already been used.
Variations
Count Numbers with Unique Digits
Count Numbers Without Consecutive Ones
Count Numbers with a Given Digit Sum
Count Numbers Containing Specific Digits
Count Numbers Divisible by K
How to recognize it

Look for:

Count numbers in a range.
Digit restrictions.
Digit sums.
Repeated or forbidden digits.
Pattern 15: DP Optimization
Core concept

Sometimes a normal DP recurrence is too slow.

We optimize the transition calculation without changing the fundamental DP idea.

Important techniques
Divide and Conquer DP Optimization
Convex Hull Trick
Monotonic Queue Optimization
Knuth Optimization
Space Optimization
Prefix Sum Optimization
Example

A straightforward DP might require:

text
O(N²)


An optimized transition may reduce it to:

text
O(N log N)

Variations
Optimized Partition DP
Convex Hull Trick DP
Knuth Optimization Problems
Sliding Window DP
Space-Optimized Knapsack
How to recognize it

Look for:

DP with large input constraints.
Nested loops that are too slow.
Repeated transition calculations.
Monotonicity or mathematical properties that allow optimization.
3. DP Pattern Recognition Cheat Sheet

When reading an unfamiliar problem, use this table.

Problem description	Pattern to investigate
Current answer depends on previous positions	1D DP
Select or skip each element	0/1 Knapsack
Select elements multiple times	Unbounded Knapsack
Form a target sum	Subset Sum
Divide an array into two subsets	Subset Sum
Move through a matrix	Grid DP
Compare two strings	LCS / String DP
Find increasing subsequence	LIS
Split an interval optimally	Interval DP
Calculate using child nodes	Tree DP
Find optimal paths in DAG	Graph DP
Buy, sell, hold, cooldown	State Machine DP
Select subsets using small N	Bitmask DP
Count numbers with digit constraints	Digit DP
Normal DP is too slow	DP Optimization

Important: These are clues, not rigid rules. A problem may combine multiple patterns.

4. The Most Important Part: How to Derive DP State and Recurrence

This is the skill that matters most in interviews.

Do not start by writing code.

Follow this process.

Step 1: Understand what the problem asks

Is it asking for:

Maximum?
Minimum?
Number of ways?
Whether something is possible?
Longest or shortest sequence?
Step 2: Identify the changing information

Ask:

What information changes when I solve a smaller version of this problem?

Examples:

Problem	Changing information
Knapsack	Number of items and remaining capacity
Subset Sum	Number of elements and remaining target
LCS	Position in string A and position in string B
Grid DP	Row and column
LIS	Current index and previous selected index
Tree DP	Current node and decision state

These changing parameters often become your DP state.

Step 3: Define the state in plain English

For example:

cpp
dp[i][w]


Means:

Maximum value obtainable using the first i items with capacity w.

If you cannot explain your state in one sentence, do not start coding yet.

Step 4: Identify the choices

Ask:

What decisions can I make at this state?

Examples:

Knapsack:

Include.
Exclude.

Grid:

Move right.
Move down.

LCS:

Characters match.
Characters don't match.

Stock:

Buy.
Sell.
Hold.
Step 5: Derive the recurrence

Translate each choice into a smaller state.

For 0/1 Knapsack:

cpp
include = value[i] + dp[i-1][w-weight[i]];

exclude = dp[i-1][w];

answer = max(include, exclude);


For Subset Sum:

cpp
include = dp[i-1][sum-arr[i]];

exclude = dp[i-1][sum];

answer = include || exclude;

Step 6: Establish base cases

Ask:

What if no elements remain?
What if the target becomes zero?
What if the input is empty?
What if we reach the destination?
Step 7: Implement recursion first

Make sure the recurrence is correct.

Step 8: Add memoization

Store answers to avoid repeated calculations.

Step 9: Convert to tabulation

Identify which smaller states must be calculated first.

Step 10: Optimize space

Only do this after understanding the complete DP table.

5. Recommended Interview Preparation Order

Do not study all 15 patterns simultaneously.

Follow this sequence.

Beginner
Fibonacci
Climbing Stairs
House Robber
0/1 Knapsack
Subset Sum
Equal Sum Partition
Count Subsets
Unbounded Knapsack
Coin Change
Rod Cutting
Intermediate
Unique Paths
Minimum Path Sum
Longest Common Subsequence
Longest Common Substring
Longest Increasing Subsequence
Edit Distance
Longest Palindromic Subsequence
Target Sum
Minimum Subset Sum Difference
Stock Buy and Sell
Advanced
Matrix Chain Multiplication
Palindrome Partitioning
Burst Balloons
DP on Trees
Longest Path in DAG
Bitmask DP
Digit DP
Probability DP
DP Optimization
6. Important Interview Advice

You do not need to memorize hundreds of DP solutions.

Focus on mastering:

State definition.
Recurrence derivation.
Base cases.
Recursion tree.
Memoization.
Tabulation.
Space optimization.

A person who understands 15 fundamental patterns can often approach many unfamiliar DP problems systematically.

However, recognizing a pattern does not automatically solve a problem. You still need to derive and validate its state transitions.

7. Your DP Learning Checklist

For every problem, verify whether you can:

Explain the problem in simple language.
Identify the DP pattern.
Define the state.
Explain what each state represents.
Identify all possible choices.
Derive the recurrence.
Establish base conditions.
Draw the recursion tree.
Implement recursive C++ code.
Add memoization.
Convert to tabulation.
Explain time and space complexity.
Test edge cases.
Solve it again without looking at the solution.

Final principle: Learn to derive DP, not memorize DP.

----------------------------
1. Singleton Pattern

Ensures only one instance of a class exists.
text

       Singleton
    ----------------
    - instance
    ----------------
    + getInstance()
    + operation()
          |
          |
     Single Object

2. Factory Method Pattern

Creates one product through a factory method.
text

           IProduct
              |
       ---------------
       |             |
    Product1      Product2


           IFactory
              |
       ---------------
       |             |
    Factory1      Factory2
       |             |
       v             v
    Product1      Product2

3. Abstract Factory Pattern

Creates families of related products.
text

                IFactory
                   |
           -----------------
           |               |
        Factory1        Factory2
           |               |
       ----------      ----------
       |        |      |        |
    ProductA1 ProductB1 ProductA2 ProductB2


       IProductA       IProductB
           |               |
       ----------      ----------
       |        |      |        |
      PA1      PA2    PB1      PB2

4. Builder Pattern

Separates the construction of a complex object from its representation.
text

             Director
                |
                v
           IBuilder
                |
          -------------
          |           |
       Builder1    Builder2
          |           |
          v           v
        Product     Product

5. Prototype Pattern

Creates new objects by cloning existing objects.
text

          IPrototype
               |
        ----------------
        |              |
    Prototype1     Prototype2
        |              |
        | clone()      | clone()
        v              v
      Object         Object

2. Structural Design Patterns
6. Adapter Pattern

Allows incompatible interfaces to work together.
text

          Client
             |
             v
        ITarget
             |
             v
         Adapter
             |
             v
        Adaptee

7. Bridge Pattern

Separates abstraction from implementation.
text

        Abstraction
             |
             | has-a
             v
        IImplementor
             |
       --------------
       |            |
   Impl1          Impl2

8. Composite Pattern

Treats individual objects and groups of objects uniformly.
text

          Component
              |
       ----------------
       |              |
      Leaf        Composite
                       |
                       |
                  Components
                       |
                 -------------
                 |           |
                Leaf        Leaf

9. Decorator Pattern

Adds additional responsibilities dynamically.
text

          Component
              |
       ----------------
       |              |
    Concrete       Decorator
    Component          |
                       |
                  Component
                       |
                 ConcreteDecorator

10. Facade Pattern

Provides a simplified interface to a complex subsystem.
text

          Client
             |
             v
           Facade
             |
      -----------------
      |       |       |
   System1 System2 System3

11. Proxy Pattern

Provides a substitute or placeholder for another object.
text

           ISubject
               |
        ----------------
        |              |
       Proxy       RealSubject
        |
        | has-a
        v
    RealSubject

12. Flyweight Pattern

Shares common object state to reduce memory consumption.
text

            Client
               |
               v
         FlyweightFactory
               |
               v
          IFlyweight
               |
        ----------------
        |              |
    Flyweight1     Flyweight2

3. Behavioral Design Patterns
13. Observer Pattern

One-to-many relationship between publisher and subscribers.
text

          IPublisher
               |
               v
           Publisher
               |
        Subscriber List
               |
       -----------------
       |       |       |
      Sub1    Sub2    Sub3
       |       |       |
       v       v       v
   notification()

14. Strategy Pattern

Encapsulates interchangeable algorithms.
text

           Context
              |
              | has-a
              v
          IStrategy
              |
       ----------------
       |              |
    Strategy1      Strategy2

15. State Pattern

Changes object behavior based on its internal state.
text

            Context
               |
               | has-a
               v
            IState
               |
        ----------------
        |              |
      State1         State2

16. Command Pattern

Encapsulates a request as an object.
text

          Client
             |
             v
         ICommand
             |
       --------------
       |            |
   Command1      Command2
       |            |
       v            v
    Receiver     Receiver

17. Template Method Pattern

Defines the skeleton of an algorithm in a base class.
text

          AbstractClass
                |
         templateMethod()
                |
         ----------------
         |              |
      Class1           Class2
         |              |
     step1()         step1()
     step2()         step2()

18. Chain of Responsibility Pattern

Passes a request through a chain of handlers.
text

       Client
          |
          v
       Handler1
          |
          v
       Handler2
          |
          v
       Handler3

19. Iterator Pattern

Provides sequential access to elements without exposing the underlying representation.
text

          IIterator
              |
       ----------------
       |              |
    Iterator1     Iterator2


          Aggregate
              |
       ----------------
       |              |
    Collection1   Collection2

20. Mediator Pattern

Centralizes communication between objects.
text

          IMediator
              |
           Mediator
          /   |   \
         /    |    \
      Obj1   Obj2   Obj3

21. Memento Pattern

Captures and restores an object's previous state.
text

          Originator
              |
              v
           Memento
              ^
              |
          Caretaker

22. Visitor Pattern

Separates operations from the objects on which they operate.
text

           IVisitor
               |
        ----------------
        |              |
     Visitor1       Visitor2


          IElement
              |
        ----------------
        |              |
     Element1       Element2

23. Interpreter Pattern

Defines a grammar and provides an interpreter for expressions.
text

       AbstractExpression
                |
         ----------------
         |              |
    TerminalExpr   NonTerminalExpr

Category	Design Pattern	Main Purpose
Creational	Singleton	Single instance
Creational	Factory Method	Create products
Creational	Abstract Factory	Create product families
Creational	Builder	Build complex objects
Creational	Prototype	Clone objects
Structural	Adapter	Interface compatibility
Structural	Bridge	Separate abstraction and implementation
Structural	Composite	Tree structures
Structural	Decorator	Add responsibilities
Structural	Facade	Simplify subsystem
Structural	Proxy	Control object access
Structural	Flyweight	Share objects
Behavioral	Observer	Notify subscribers
Behavioral	Strategy	Interchange algorithms
Behavioral	State	State-dependent behavior
Behavioral	Command	Encapsulate requests
Behavioral	Template Method	Algorithm skeleton
Behavioral	Chain of Responsibility	Pass requests through handlers
Behavioral	Iterator	Traverse collections
Behavioral	Mediator	Centralize communication
Behavioral	Memento	Restore previous state
Behavioral	Visitor	Separate operations
Behavioral	Interpreter	Interpret grammar


<img width="696" height="447" alt="image" src="https://github.com/user-attachments/assets/666a7084-caa6-4a78-9e3f-df1a7eea4797" />



<img width="789" height="479" alt="image" src="https://github.com/user-attachments/assets/c9255749-bdf9-4288-b974-da666f9ee9e2" />


cpp
// Observer Pattern

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Both Publisher and Subscriber depend on abstractions rather than concrete implementations.
This is an application of the Dependency Inversion Principle (DIP).

Your design also demonstrates:
    1. Interface-based programming.
    2. Runtime polymorphism.
    3. Loose coupling.
    4. One-to-many relationships.
    5. Separation of responsibilities.
*/

class IPublisher;

class ISubscriber
{
public:
    virtual void registerSubcribtion(IPublisher *publsiher) = 0;
    virtual void notification() = 0;
};

class IPublisher
{
public:
    virtual void subscribe(ISubscriber *subcriber) = 0;
    virtual void unsubscribe(ISubscriber *subcriber) = 0;
    virtual void notify() = 0;
};

class Publisher : public IPublisher
{
    std::vector<ISubscriber *> subcriberlist;

public:
    void subscribe(ISubscriber *subcriber)
    {
        subcriberlist.emplace_back(subcriber);
    }

    void notify()
    {
        for (auto subs : subcriberlist)
        {
            subs->notification();
        }
    }

    void unsubscribe(ISubscriber *subscriber)
    {
        subcriberlist.erase(
            std::remove(
                subcriberlist.begin(),
                subcriberlist.end(),
                subscriber
            ),
            subcriberlist.end()
        );
    }
};

class Subscriber1 : public ISubscriber
{
public:
    void registerSubcribtion(IPublisher *publsiher)
    {
        publsiher->subscribe(this);
    }

    void notification()
    {
        std::cout << "Receive Notification 1" << "\n";
    }
};

class Subscriber2 : public ISubscriber
{
public:
    void registerSubcribtion(IPublisher *publsiher)
    {
        publsiher->subscribe(this);
    }

    void notification()
    {
        std::cout << "Receive Notification 2" << "\n";
    }
};

class Subscriber3 : public ISubscriber
{
public:
    void registerSubcribtion(IPublisher *publsiher)
    {
        publsiher->subscribe(this);
    }

    void notification()
    {
        std::cout << "Receive Notification 3" << "\n";
    }
};

int main()
{
    ISubscriber *subs1 = new Subscriber1();
    ISubscriber *subs2 = new Subscriber2();
    ISubscriber *subs3 = new Subscriber3();

    IPublisher *pubs = new Publisher();

    subs1->registerSubcribtion(pubs);
    subs2->registerSubcribtion(pubs);
    subs3->registerSubcribtion(pubs);

    pubs->notify();

    return 0;
}

𝗥𝗼𝘂𝗻𝗱 1 – 𝗧𝗲𝗰𝗵𝗻𝗶𝗰𝗮𝗹 𝗥𝗼𝘂𝗻𝗱:

𝗤𝘂𝗲𝘀𝘁𝗶𝗼𝗻: 𝗗𝗲𝘀𝗶𝗴𝗻 𝗮 𝗛𝗶𝘁 𝗖𝗼𝘂𝗻𝘁𝗲𝗿.
Focus: Ability to handle high-concurrency write requests and memory-efficient data storage. Discussion involved using circular buffers or buckets to manage time-based counts within a specific window.
Follow-up: Scaling the counter to handle millions of requests per second and ensuring accuracy in a distributed environment.

𝗥𝗼𝘂𝗻𝗱 2 – 𝗖𝗼𝗻𝗰𝘂𝗿𝗿𝗲𝗻𝗰𝘆 & 𝗣𝗿𝗼𝗯𝗹𝗲𝗺 𝗦𝗼𝗹𝘃𝗶𝗻𝗴:
Technical Deep Dive: Basic questions on concurrency, thread lifecycle, and race conditions.
Implementation: Design and implement a word auto-complete suggestion feature for keyboards.
Approach: Utilized a Trie (Prefix Tree) data structure to store words and provided an efficient search algorithm for prefix matching.
Follow-up: Optimizing the Trie for memory and adding weightage/frequency to suggestions.

𝗥𝗼𝘂𝗻𝗱 3 – 𝗔𝗹𝗴𝗼𝗿𝗶𝘁𝗵𝗺𝘀 & 𝗦𝘆𝘀𝘁𝗲𝗺𝘀 𝗟𝗼𝗴𝗶𝗰:
DSA Question: Find the median of two sorted arrays.
System Logic: Strategy for zero-downtime key rotation in a Master-Slave architecture.
Problem Scenario: Master nodes SSH into slave nodes using a private key; slave nodes verify using a public key.

𝗥𝗼𝘂𝗻𝗱 4 – 𝗕𝗲𝗵𝗮𝘃𝗶𝗼𝗿𝗮𝗹 𝗥𝗼𝘂𝗻𝗱:
Discussion: Deep dive into past projects and technical challenges faced in the last 4 years.
Focus: Conflict resolution within a team, handling tight deadlines, and the rationale behind choosing Yugabyte.
