# Binary Search Tree Analysis

## Core operations

Students should analyze the following BST operations:

- insertion;
- search;
- deletion;
- traversal;
- minimum/maximum lookup;
- subtree height.

## Required discussion

Provide a short analysis comparing the complexity of the following operations:

- best-case vs. worst-case behavior;
- average-case behavior for a balanced BST;
- worst-case behavior for a skewed tree;
- recursive vs. iterative implementations;
- how tree height affects search cost.

## Expected Big-O summary

Students should identify the Big-Oh complexity for:

- `insert`
- `search`
- `remove`
- `inorderTraversal`
- `height`

For a balanced binary search tree, expected operations are near O(log n), while a degenerate tree can degrade to O(n).

## Analysis

### Big-O summary

h is the height of the tree. For a balanced tree h is about log n, and for a skewed tree h = n.

Operation, Best case, Average (balanced), Worst (skewed), Extra space 

 `insert`, O(1), O(log n), O(n),  O(h) recursion stack 
 `search` / `contains`, O(1) , O(log n) , O(n) , O(h) recursion stack 
 `remove` , O(1) , O(log n) , O(n) , O(h) recursion stack 
 `minimum` / `maximum` , O(1) , O(log n) , O(n) , O(h) recursion stack 
 `inorderTraversal` (and pre/post) , O(n) , O(n) , O(n) , O(h) stack + O(n) result 
 `height` , O(n) , O(n) , O(n) , O(h) recursion stack 

The best case for insert, search and remove is when the value is at (or belongs right under) the root.

### How height affects search

Insert, search, remove and min/max all follow a single path from the root down, so they cost O(h). Each comparison throws away one whole subtree. In a balanced tree every level roughly doubles the number of nodes, so h is about log2(n) and searching 1,000,000 values takes around 20 comparisons. In a skewed tree each node has only one child, so the tree is basically a linked list and h = n.

Traversals and `height` have to visit every node no matter what shape the tree is, so they are always O(n).

### Best vs. worst tree shape

- **Best:** a balanced (or complete) tree, where the left and right subtrees of every node are about the same height. You get this when values are inserted in a mixed-up order, or the middle value first. In the tests, inserting {50, 30, 70, 20, 40, 60, 80} gives height 3 for 7 nodes.
- **Worst:** a degenerate tree. Inserting sorted data like {1, 2, 3, 4, 5, 6, 7} puts every node on the right, so the height is 7, the same as the number of nodes, and every operation becomes O(n).

### Removal cases

1. **Leaf:** just delete it.
2. **One child:** the parent links straight to that child.
3. **Two children:** copy the in-order successor (the smallest value in the right subtree) into the node, then remove the successor from the right subtree. The successor has no left child, so removing it is always case 1 or 2.

Finding the successor is still on one root-to-leaf path, so removal stays O(h).

### Recursive vs. iterative

This implementation uses recursion for everything. Recursion fits trees well because each subtree is itself a BST, so the code ends up short and matches the definition. Insert and remove can simply return the new subtree root, which takes care of relinking the parent pointer.

The cost is the call stack. Recursion uses O(h) extra memory, so it's O(log n) when balanced but O(n) when skewed, and a very tall skewed tree could overflow the stack. Iterative insert, search and min/max only need a pointer that walks down the tree, so they use O(1) extra space. Iterative traversals need an explicit stack, so they still use O(h) space and are messier to write. The Big-O time is the same either way. Iterative just avoids the function call overhead and the stack overflow risk.

### When a BST is efficient vs. inefficient

**Efficient when:**
- the data comes in random or mixed order, so the tree stays close to balanced;
- you need fast search, insert and delete, plus sorted output (an in-order traversal gives sorted order in O(n));
- you need ordered queries like min, max, or nearest value.

**Inefficient when:**
- the data is inserted in sorted or nearly sorted order, so the tree becomes a list and everything is O(n);
- the data rarely changes and is only searched, where a sorted array with binary search is simpler and uses less memory;
- you only need lookups without order, where a hash table averages O(1).

A self-balancing tree fixes the worst case by keeping h at O(log n) all the time.
