//CSCI 2270 -- Recitation 9 -- Final Project Phase 1
//SUMMARY
/*
For my final project, I will be updating a bookstore's inventory, storing books with the same genre in different indexes in the hash table; for genres that contain more than one book, the books will be stored as nodes in a binary search tree.  Basically, it's a hashtable where every index of the hash has a BST filled with books.  The hashtable is built initially when the program is run; an instance of the bookstore class is created, which initializes an empty hashtable of structs "BookNode", and a .txt file with the book data is read in.  This data is used to create the hashtable with all of its BST's, and it is built by BookNode until the end of the file.  After the Hashtable is created, a menu displays, where the user can make various requests of the program, including printing the entire inventory of the bookstore, buying a book, searching for a book, and deleting a book from the inventory.
*/

//HOW TO RUN
/*
After opening the project (terminal or codeblocks), the user will be prompted with a menu.  The user can just choose various menu options until exiting the program.
*/

//SYSTEM REQUIREMENTS
/*
program written for linux
*/

//OPEN ISSUES/BUGS
/*
invalid menu options in some cases may cause a segmentation fault or endless loop.  I attempted to eliminate most edge cases but I'm not sure if I got all of them
*/

