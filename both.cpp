#include <iostream>
#include <fstream>
#include <iomanip>
#include "classfile.h"
using namespace std;

void vending_machine::show() {
    ifstream file("database.txt", ios::in); // Open the file in read mode

    if (!file.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    // Clear existing linked list data
    //After deletation there could be garbage value residing in the linked list or
    // duplication of data could occur.
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Read data from the file and populate the linked list
    // ws skips the whitespace, in particular the newline, and carries on reading where the actual content is entered.
    // end-of-file (eof()) --> returns nonzero (meaning TRUE) when there are no more data to be read from an input file stream, and zero (meaning FALSE) otherwise.
    while (file >> ws, !file.eof()) {
        Node* new_node = new Node;
        file >> new_node->id >> new_node->name >> new_node->price >> new_node->quantity;

        new_node->next = nullptr;

        if (head == nullptr) {
            head = new_node;
        } else {
            Node* ptr = head;
            while (ptr->next != nullptr) {
                ptr = ptr->next;
            }
            ptr->next = new_node;
        }
    }

    file.close(); // Close the file


    // Check if the linked list is sorted, and sort it if necessary
    if (!isSorted()) {
        sort();
    }

    // Display the sorted data
    cout << "\n";
    cout << setw(98) << "                   Items Present in the Vending Machine                      " << endl;
    cout << setw(98) << "-----------------------------------------------------------------------------" << endl;
    cout << setw(98) << "|| Item ID ||     Item Name    || Item Price Per Unit(RM) || Item Quantity ||" << endl;
    cout << setw(98) << "-----------------------------------------------------------------------------" << endl;

    Node* ptr = head;
    if(head == nullptr){
        cout << setw(72) << "No items to display" << endl;
    }
    while (ptr != nullptr) {

        cout << setw(23) << "||" << setw(6) << ptr->id << setw(5) << "||"<< setw(14) << ptr->name << setw(6) << "||"<< setw(15) << ptr->price << setw(12) << "||"<< setw(9) << ptr->quantity << setw(8) << "||"<< endl;
        cout << setw(98) << "-----------------------------------------------------------------------------" << endl;

        // Move to the next node inside the loop
        ptr = ptr->next;
    }
}

// Function to check if the linked list is sorted
bool vending_machine::isSorted() {
    Node* current = head;

    while (current != nullptr && current->next != nullptr) {
        if (current->id > current->next->id) {
            return false;
        }
        current = current->next;
    }

    return true;
}


void vending_machine::sort() {
    if (head == NULL) {
        cout << setw(90) << "Linked List is empty";
        return;
    }

    int count = 0;
    Node *ptr = head;

    // Count the number of nodes in the linked list
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }

    // Bubble sort
    // It's in ascending order
    for (int i = 1; i <= count; i++) {
        ptr = head;
        Node *nextNode = ptr->next; // Initialize the next node
        for (int j = 1; j <= count - i; j++) {
            if (ptr->id > nextNode->id) {
                // Swap data if the current node is greater than the next node
                swap(ptr->id, nextNode->id);
                swap(ptr->name, nextNode->name);
                swap(ptr->price, nextNode->price);
                swap(ptr->quantity, nextNode->quantity);
            }

            ptr = ptr->next;
            nextNode = ptr->next; // Move to the next node
        }
    }
}

void vending_machine::writeToFile(const string& database) {
    ofstream file(database, ios::out); // Open the file in write mode

    if (!file.is_open()) {
        cout << setw(90) << "Error opening file for writing." << endl;
        return;
    }

    Node* ptr = head;

    // Write data to the file
    while (ptr != nullptr) {
        file << ptr->id << ' ' << ptr->name << ' ' << ptr->price << ' ' << ptr->quantity << '\n';
        ptr = ptr->next;
    }

    file.close(); // Close the file when done
}

// using passing by reference to avoid unnecessary copying
void vending_machine::readFromFile(const string& database) {
    ifstream file(database, ios::in); // Open the file in read mode

    if (!file.is_open()) {
        cout << setw(90) << "Error opening file for reading." << endl;
        return;
    }

    // Clear existing linked list data
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;

    // Read data from the file and populate the linked list
    while (!file.eof()) {
        Node* new_node = new Node;
        file >> new_node->id >> new_node->name >> new_node->price >> new_node->quantity;

        new_node->next = nullptr;

        if (head == nullptr) {
            head = new_node;
        } else {
            Node* ptr = head;
            while (ptr->next != nullptr) {
                ptr = ptr->next;
            }
            ptr->next = new_node;
        }
    }

    file.close(); // Close the file
}
