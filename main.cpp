///Sarah Barili
///CSCI2270
///Guohui Ding
///Final Project

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Bookstore.h"

using namespace std;

int main(/*int argc, char*argv[]*/)
{
    Bookstore Bstore;
    //Bstore.initializeHash();
    string data;
    ifstream inFile("Books.txt");
    if(inFile.good()){ //error check
        //cout << "opened successfully" << endl;
        while(getline(inFile, data)){
            string genre;
            string title;
            string author;
            int quant;
            int price;
            stringstream ss(data);//create a stringstream variable from the string data
            string piece;
            getline(ss,piece,',');
            stringstream genrestream(piece);
            genre = genrestream.str(); //stores genre
            getline(ss,piece,',');
            stringstream titlestream(piece); //creates a second string stream for title info
            title = titlestream.str(); //stores the movie title under m_title as a string
            getline(ss,piece,',');
            stringstream authorstream(piece); //creates a second string stream for title info
            author = authorstream.str(); //stores the movie title under m_title as a string
            getline(ss,piece,',');
            stringstream pricestream(piece);
            pricestream >> price; //stores the year
            getline(ss,piece,',');
            stringstream qstream(piece);
            qstream >> quant; //stores the number of copies in quant
            Bstore.addBooktoTable(genre, title, author, quant, price);
        }
    }
    //Bstore.printInventory();

    bool ans = true;
    int choice;

    while (ans != false){

        cout << "======Main Menu======" << endl;
        cout << "1. Find a Book" << endl;
        cout << "2. Purchase Book" << endl;
        cout << "3. Print the bookstore's inventory" << endl;
        cout << "4. Delete a book" << endl;
        cout << "5. Search a genre" << endl;
        cout << "6. Quit" << endl;

        cin >> choice;

        if (choice == 1){
            string title;
            cout << "Enter title: " << endl;
            cin.ignore();
            getline(cin,title);
            Bstore.findBook(title);
        }else if (choice == 2){
            string title;
            cout << "Enter title: " << endl;
            cin.ignore();
            getline(cin,title);
            Bstore.purchaseBook(title);
        }else if(choice == 3){
            Bstore.printInventory();
        }else if(choice == 4){
            string title;
            cout << "Enter title: " << endl;
            cin.ignore();
            getline(cin,title);
            Bstore.deleteBook(title);
        }else if(choice == 5){
            string gen;
            cout << "Select from genres: Science Fiction, Mystery, Political Science, Literature, Satire,Anthology, Philosophy, or Poetry: "<< endl;
            cin.ignore();
            getline(cin,gen);
            Bstore.searchGenre(gen);
        }else if (choice ==6){
            ans = false;
            cout << "Goodbye!" << endl;
        }
    }
    return 0;
}



