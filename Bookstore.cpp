#include "Bookstore.h"

Bookstore::Bookstore()
{
    root = NULL;//ctor
}

Bookstore::~Bookstore()
{
    //dtor
}

///-1
///stores books in the array/hash depending on the genre read in from the text file.
///each genre has a specified index in the array
int Bookstore::genreCheck(std::string genre)
{
    if (genre == "Science Fiction"){
        return 0;
    }else if (genre == "Mystery"){
        return 1;
    }else if (genre == "Political Science"){
        return 2;
    }else if (genre == "Literature"){
        return 3;
    }else if (genre == "Satire"){
        return 4;
    }else if (genre == "Anthology"){
        return 5;
    }else if (genre == "Philosophy"){
        return 6;
    }else if (genre == "Poetry"){
        return 7;
    }else{
        return -1;
    }
}

///-2
///creates a new bookNode from the data parsed in and adds it to the hashtable
///depending on the book's genre, it is added to the tree at the genre's index.
void Bookstore::addBooktoTable(std::string genre, std::string title, std::string author, int quantity, int price)
{
    int index = genreCheck(genre); //depending on the genre read in, the index is stored as this function's return value
    if(hashTable[index] == NULL){ //there isn't a book at this index yet.  add book as the root of the tree
        BookNode *newBook =  new BookNode(genre, title, author, quantity, price);
        hashTable[index] = newBook;
        root = newBook;
        //cout << hashTable[index] << endl;
        //cout << root->title << " added as root of index " << index << endl;
        //cout << hashTable[index]->title << endl;
    }else{ //there is already an existing root
        BookNode *root = hashTable[index]; //pointer to the root
        //call function to add book to tree at this index.
        addBooktoTree(root, genre, title, author, quantity,price);
    }
}

///-3
///called when there is already a book at the root position in that genre's index
void Bookstore::addBooktoTree(BookNode *root,std::string genre, std::string title, std::string author, int quantity, int price)
{
    BookNode *tmp = root; //new pointer to the root
    BookNode *newparent = NULL;
    BookNode *B = new BookNode(genre, title, author, quantity, price); //create a movie node reading in initial values
    while (tmp !=NULL){
        newparent = tmp;
        if (B->title < tmp->title){ //compare new node's title to root's title
            tmp = tmp->leftChild;
        }else{
            tmp = tmp->rightChild;
        }
    }
    if( B->title < newparent->title){ //add as left child
        newparent->leftChild = B;
        B->parent = newparent;
        //cout << "inserted: " << B->title << " left child of: " << newparent->title <<endl;
    }else{ //add as a right child
        newparent->rightChild = B;
        B->parent = newparent;
        //cout << "inserted: " << B->title << " right child of: " << newparent->title <<endl;
    }
}

///-4
///search method used to find a book in the tree
BookNode* Bookstore::search(std::string title)
{
    BookNode *tmp= NULL;
    for (int x = 0 ; x < tableSize; x ++){
        tmp = hashTable[x];
        while (tmp != NULL){
            if (tmp->title > title){
                tmp = tmp->leftChild;
            }else if (tmp->title < title){
                tmp = tmp->rightChild;
            }else{
                return tmp;

            }
        }
    }
    return NULL;
}

///-5
///used to find a specific book in the tree
void Bookstore::findBook(std::string title)
{
    BookNode *book = search(title);
    if (book!=NULL){
        cout << "Title: " << book->title << endl;
        cout << "Author: " << book->author << endl;
        cout << "Price: $" << book->price << endl;
        cout << "Quantity:" << book->quantity << endl;
    }else{
        cout << "book wasn't found" << endl;
    }

}

///-6
///the next two are a recursive call to print the inventory alphabetically.
void Bookstore::printInventory()
{
    for (int x = 0 ; x < tableSize; x ++){
        printInventory(hashTable[x]);
    }
}

///-6
void Bookstore::printInventory(BookNode *current)
{
    if (current->leftChild != NULL){
        printInventory(current ->leftChild);
    }
    cout<<"Book: "<<current->title<<", In Stock: "<<current->quantity<<endl;
    if (current->rightChild != NULL){
        printInventory(current->rightChild);
    }
}

///-7
BookNode* Bookstore::treeMinimum(BookNode *node)
{
    for (int x = 0 ; x < tableSize; x++){
        //huh?
        while (node->leftChild != NULL){
            node = node->leftChild;
        }
        return node;
    }
}

///-8
///Delete one node from BST
void Bookstore::deleteBook(std::string title)
{
    BookNode *found = search(title); //finds the node to delete
    if (found != NULL){ //if the node with this title is found in tree
        int index = genreCheck(found->genre);
        if (found->leftChild == NULL && found->rightChild == NULL){//delete node with no children
            if (found->parent->leftChild == found){
                found->parent->leftChild = NULL;
            }else{
                found->parent->rightChild = NULL;
            }
            delete found;
        }else if (found->leftChild == NULL || found->rightChild == NULL){ // delete node with one child
            if (found->leftChild != NULL && found->rightChild == NULL){ // node has a left child
                BookNode *x = found->leftChild;
                if(found->parent == NULL){
                    x->parent == NULL;
                    hashTable[index] = x;
                }else if (found->parent->leftChild==found){ //if the node to be deleted is a left child
                    found->parent->leftChild = x;
                    x->parent = found->parent; // these operations move pointers around node to be deleted

                }else{
                    found->parent->rightChild = x;
                    x->parent = found->parent; // these operations move pointers around node to be deleted
                }
                delete found;
            }else if (found->leftChild == NULL && found->rightChild != NULL){ // node has a right child
                BookNode *x = found->rightChild; //pointer to the right child
                if(found->parent == NULL){
                    x->parent == NULL;
                    hashTable[index] = x;
                }else if (found->parent->leftChild==found){ //if the node to be deleted is a left child
                    found->parent->leftChild = x;
                    x->parent = found->parent;
                }else if (found->parent->rightChild == found){
                    found->parent->rightChild = x;
                    x->parent = found->parent;
                }
                // these operations move pointers around node to be deleted
                delete found;
            }
        }else if (found->leftChild != NULL && found->rightChild != NULL){ // node has two children
            BookNode *minimum = treeMinimum(found->rightChild); //finds the minimum value in the right subtree of the node to be deleted
            if (found->rightChild == minimum){ //1st case: replacement is deleted node's right child
                //cout<<"i made it to rightchild min"<<endl;
                if(found->parent == NULL){
                    minimum->parent == NULL;
                    hashTable[index] = minimum;
                }else if (found->parent->leftChild == found){
                    found->parent->leftChild = minimum; //a:move around deleted node: parent's left child is now deleted node's right child
                }else{
                    found->parent->rightChild = minimum;
                }
                minimum->parent = found->parent;//reverse op for a
                 //cout << minimum->parent->title << endl;
                found->leftChild->parent = minimum; //b: deleted node's right child is now parent of deleted node's left child
                minimum->leftChild = found->leftChild;//reverse op for b
                //cout << found->title << endl;
                //cout << minimum->leftChild->title << endl;
                delete found;
            }else if (found->rightChild != minimum){
                minimum->parent->leftChild = minimum->rightChild;
                if (minimum->rightChild != NULL){
                    minimum->rightChild->parent = minimum->parent;
                }
                if (found->parent != NULL){
                    if (found->parent->leftChild == found){
                        found->parent->leftChild = minimum;
                        minimum->parent = found->parent;
                    }else{
                        found->parent->rightChild = minimum;
                        minimum->parent = found->parent;
                    }
                }else{
                    hashTable[index] = minimum;
                }
                minimum->leftChild = found->leftChild;
                found->leftChild->parent = minimum; // possibly move this line?
                minimum->rightChild = found->rightChild;
                found->rightChild->parent = minimum;
                delete found;
            }

        }
    }else{
        cout << "Movie not found." << endl;
    }
}

///-9
///removes books from inventory one by one
///when quantity reaches 0, the book is removed from inventory
void Bookstore::purchaseBook(std::string title)
{
    BookNode *book = search(title);
    if (book != NULL){
        if (book->quantity >0){
            book->quantity -- ;
            cout << "Book Purchased" << endl;
            cout << "Book Info:" << endl;
            cout << "===========" << endl;
            cout << "Title:" << book->title << endl;
            cout << "Author:" << book->author << endl;
            cout << "Quantity:" << book->quantity << endl;
                if(book->quantity == 0){
                //If movie is out of stock
                deleteBook(title);
                }
        }
    }else{
        cout << "book not found" << endl;
    }

}

///-10
///method that prints all of the books in one genre
void Bookstore::searchGenre(std::string genre)
{
    int index = genreCheck(genre);
    if (index != -1){
        printInventory(hashTable[index]);
    }else{
        cout << "not a genre at this bookstore" << endl;
    }
}
