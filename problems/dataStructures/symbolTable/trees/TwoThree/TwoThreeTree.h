/*
These contain one or two fields which indicate the range of 
values in its subtrees. 
If a node has two children, it will have one field; 

if the node has three children, it will have two fields. 

Each non-leaf node will contain a value in field 1 which is 
greater than the largest item in its left sub-tree, 
but less than or equal to the smallest item in its right sub-tree 
(or center sub-tree, if it has three children). I
f that node has three children, field 2 contains a value which 
is greater than the largest value in the center sub-tree, 
but less than or equal to the smallest item in its right sub-tree. 
The purpose of these values is to direct a search function to the
correct sub-tree and eventually to the correct data node.
*/
