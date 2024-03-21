#ifndef CLASSFILE_H_INCLUDED
#define CLASSFILE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class vending_machine
{
private:
    struct Node {
        int id, quantity;
        string name;
        float price;
        Node* next;
    };

public:
    Node* head = NULL;
    // Main menu
    void mainmenu();

    // CRUD operations
    void insert();
    void update();
    void search();
    void del();
    void sort();
    void show();

    // File operations
    void updateFile();
    void writeToFile(const string& database);
    void readFromFile(const string& database);

    // Utility functions
    bool isSorted();

    // Administrative menu
    void adminsubmenu();
    void usersubmenu();

    // Purchase operation
    void purchaseItem();
};

#endif // CLASSFILE_H_INCLUDED
