Dual-Code
=========

The Code for NIIT Trichy's Dual Code Event.

1) Declare an array for Open hashing. The hash function is the strlen(name) i.e hash[strlen(name)] resolves to the Root of a Left-InThreaded Binary Search tree responsible for storing all the names having the same length.

2)Also Keep two registers keeping track of the largest and the length of the second largest names, Because if we know the largest name then we won't have to traverse the tree storing the largest name, we can straight away start from the hash[second largest length].

3)Check if the Length of the second largest name i.e. in this program secondLargestlen is odd or even, 
if it's odd check if the root (hash[secondLargestlen]) has atleast one child, If it has at least one child then we just need to create the family tree using names having ODD length, Else we'll need to create an ODD tree and an even tree and Finally stitch them up by making the longest name the ROOT.

4)To create the Max Heap of names, We will be using a sequential representation of Trees, in this case it will be a stack.

5)Start traversing all the trees starting from secondLargestlen down to 1 and storing  
