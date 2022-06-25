# trees-manager
Simple CLI program to load and save trees in files, check if one tree is contained in another and remove one subtree from another. Part of the course for structural programming.

Each Tree has a name and consists of Nodes, each Node has a value and a number of children. 
Values can be any integer, but a Node can't have two children with the same value.

Finding a Tree by given name takes (in worse case) O(k) time, where k is the length of the longest name of a loaded Tree. 
Note: O(k) doesn't depend on the number of trees that are loaded.

At the start of the program, the user is expected to write a command. The program should not stop when encountering an error. 
Instead, it should show the error and wait for the next command. 

The program must be able to load as many trees as the user wants (limited only by the physical memory)

# Commands:
**1. LOAD \<name\> \<file\>**

  \<name\> is a string that doesn't include a space.
  
  Reads a tree from the file <file>, gives it a name <name> and saves it in memory. 
  If a tree with such a name already exists, the user is asked if he wants to overwrite the old tree. 

**2. SAVE \<name\> \<file\>**
  
  Saves the tree with name <name> in the file <file>. If such a file already exists, the user is asked if he wants to overwrite it.

**3. CONTAINS \<tree1\> \<tree2\>**
  
Checks if \<tree2\> is contained in \<tree1\>. 
  Note: "Contained" in the sense of graph theory, not data structures.
  Two nodes are considered identical if their values are the same. 

**4. REMOVE \<tree1\> \<tree2\>**
  
  Removes \<tree2\> in \<tree1\>. If \<tree2\> is contained more than 1 time in \<tree1\> the program first removes the one that is farthest from the root.
  If any nodes in \<tree1\> become "parentless" after removing the \<tree2\> a new node is added to the parent of the root of the removed subtree. 
  The value of the new node is the sum of all the parentless nodes.
  Note that one removal of \<tree2\> can create a new occurrence of \<tree2\> in \<tree1\>.

**How the trees are read and written to a file:**
  
  Every line is a level of the tree. Each element in the tree is separated by another with one or more white spaces.
  Each brotherhood is separated with a '|'. Each line starts and ends with '|'.
  If a node is leaf (meaning it has no children) the next line must contain '| |' at the place where it's children are expected.
  Brotherhood means that all the nodes in it have the same parent.
  
# Examples:
**Example  file:**
  
| 1 |            -> root
  
| 2 3 4 |        -> root has 3 children 2, 3 and 4.
  
| 5 | 6 7 |  |   -> Node 2 has 1 child - 5. Node 3 has 2 childs - 6 and 7. Node 4 is a leaf.
  
|  |  |  |       -> Node 5, 6 and 7 are leafs.
  

  
**Example scenario:**
  
Content of “C:\Sample Trees\tree1.txt”
  
| 8 |
  
| 3 2 9 |
  
| 2 | 8 6 | 2 |
  
| 8 6 | 11 | 12 | 8 5 |
  
| 11 | 4 3 |  |  | 11 | 6 |
  
|  |  |  |  |  | 
  

Content of “C:\Sample Trees\tree2.txt”
  
| 2 |
  
| 8 6 |
  
| 11 |  |
  
|  |

  
Commands:
  
LOAD t1 C:\Sample Trees\tree1.txt
  
LOAD t2 C:\Sample Trees\tree2.txt
  
REMOVE t1 t2
  
SAVE t1 C:\Temp\result.txt
  

Content of “C:\Temp\result.txt”
  
| 8 |
  
| 3 12 9 |
  
| 7 |  | 2 |
  
|  | 8 5 |
  
| 11 | 6 |
  
|  |  |
  
