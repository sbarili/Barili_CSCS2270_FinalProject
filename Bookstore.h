#ifndef BOOKSTORE_H
#define BOOKSTORE_H
#include <string>
#include <iostream>

using namespace std;

struct BookNode
{
    std::string genre;
    std::string title;
    std::string author;
    int price;
    int quantity;
    BookNode *parent;
    BookNode *leftChild;
    BookNode *rightChild;

    BookNode(){};
    //creates a new book at the bookstore
    BookNode(std::string in_genre,std::string in_title, std::string in_author, int in_price, int in_quantity)
    {
        genre = in_genre;
        title = in_title;
        author = in_author;
        price = in_price;
        quantity  =in_quantity;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }

};

class Bookstore
{
    public:
        Bookstore();
        ~Bookstore();
        void printInventory();
        void deleteBook(std::string title);
        void addBooktoTree(BookNode *root, std::string genre, std::string title, std::string author, int quantity, int price);
        void addBooktoTable(std::string genre, std::string title, std::string author, int quantity, int price);
        void findBook(std::string title);
        void purchaseBook(std::string title);
        void searchGenre(std::string genre);
        int genreCheck(std::string genre);
        BookNode* search(std::string title);
        BookNode* treeMinimum(BookNode *node);
        //void initializeHash();

    protected:
    private:
        //void DeleteAll(BookNode * node); //use this for the post-order traversal deletion of the tree
        void printInventory(BookNode * node);
        BookNode *root;
        //int hashSum(std::string x);
        int tableSize = 8;
        BookNode *hashTable[8]= {};
};

#endif // BOOKSTORE_H
