#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "classfile.h"
using namespace std;

void vending_machine::adminsubmenu() {
    int choice1;

    cout << "\n\n";
    cout << setw(90) << "|--------------------Admin Menu----------------------|" << endl;
    cout << setw(81) << "|\t\t 1. Add New Item                         |" << endl;
    cout << setw(81) << "|\t\t 2. Search Item with Item_ID             |" << endl;
    cout << setw(81) << "|\t\t 3. Update Item Record                   |" << endl;
    cout << setw(81) << "|\t\t 4. Delete Item with Item_ID             |" << endl;
    cout << setw(81) << "|\t\t 5. Show Items                           |" << endl;
    cout << setw(81) << "|\t\t 6. Back to Main Menu.                   |" << endl;
    cout << setw(90) << "|----------------------------------------------------|" << endl;

    cout << setw(70) << "Enter your choice : ";
    cin >> choice1;

    switch (choice1) {
        case 1:
            system("CLS");
            insert();
            adminsubmenu();
            break;
        case 2:
            system("CLS");
            search();
            adminsubmenu();
            break;
        case 3:
            system("CLS");
            //sort();
            show();
            update();
            adminsubmenu();
            break;
        case 4:
            system("CLS");
            del();
            adminsubmenu();
            break;
        case 5:
            system("CLS");
            sort();
            show();
            adminsubmenu();
            break;
        case 6:
            system("CLS");
            mainmenu();
            break;
        default:
            cout << setw(64) << "Invalid Choice";
            adminsubmenu();
            }
}

// reading file because of checking if it already exists or not

void vending_machine::insert() {
    cout << "\n";
    cout << setw(95) << "_________Adding Items to Vending Machine Management System________" << endl;
    Node* new_node = new Node;

    // Validate and get a positive ID
    do {
        cout << "\n";
        cout << setw(70) << "Enter Item ID        : ";
        cin >> new_node->id;

        if (cin.fail() || new_node->id <= 0) {
            cout << "\n";
            cout << setw(73) << "Please enter a valid positive integer for ID." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    } while (cin.fail() || new_node->id <= 0);

    // Check if the ID already exists
    Node* idCheck = head;
    while (idCheck != nullptr) {
        if (idCheck->id == new_node->id) {
            cout << "\n";
            cout << setw(90) << "Item with the same ID already exists. Try a different ID." << endl;
            delete new_node; // Release memory allocated for new_node
            return;
        }
        idCheck = idCheck->next;
    }

    cout << setw(70) << "Enter Item Name      : ";
    cin >> new_node->name;

    cout << setw(70) << "Enter Item Price(RM) : ";
    // Validate and get a positive price
    do {
        cin >> new_node->price;
        if (cin.fail() || new_node->price <= 0.00) {
            cout << "\n";
            cout << setw(73) << "Please enter a valid positive number for price : " ;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    } while (cin.fail() || new_node->price <= 0.00);

    // Get a positive quantity
    do {
        cout << setw(70) << "Enter Item Quantity  : ";
        cin >> new_node->quantity;
        cout << "\n";
        if (cin.fail() || new_node->quantity <= 0) {
            cout << setw(73) << "Please enter a valid positive integer for quantity." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    } while (cin.fail() || new_node->quantity <= 0);

    new_node->next = nullptr; // Ensure the next pointer is initialized to NULL

    if (head == nullptr) {
        head = new_node;
    } else {
        Node* ptr = head;
        while (ptr->next != nullptr) {
            ptr = ptr->next;
        }
        ptr->next = new_node;
    }

    // Append the new values to the file
    ofstream file("database.txt", ios::app); // Open the file in append mode

    if (!file.is_open()) {
        cout << setw (90) << "Error opening file for appending." << endl;
        return;
    }

    // Write data to the file
    file << new_node->id << "  " << new_node->name << "  " << new_node->price << "  " << new_node->quantity << "\n";

    file.close(); // Close the file

    cout << "\n";
    cout << setw(75) << " New Item has been Inserted.";
}

void vending_machine::search() {
    int t_id;
    if (head == nullptr) {
        cout <<"\n";
        cout << setw(90) << "There is no Item in the vending machine at this moment." << endl;
    } else {
        cout <<"\n";
        cout << setw(95) << "_________Searching Items to Vending Machine Management System________" << endl;
        cout <<"\n";
        Node* ptr = head;
        bool itemFound = false;  // Flag to check if the item is found
        do {
        cout << "\n";
        cout << setw(65) << "Search ID:  ";
        cin >> t_id;

        if (cin.fail() || t_id <= 0) {
            cout << "\n";
            cout << setw(73) << "Please enter a valid positive integer for ID." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    } while (cin.fail() || t_id <= 0);

        while (ptr != nullptr) {
            if (t_id == ptr->id) {
                cout << "\n";
                cout << setw(88) << "Item is found and it's information are as follows: \n" << endl;
                cout << setw(70) << "Item ID         : " << ptr->id << endl;
                cout << setw(70) << "Item Name       : " << ptr->name << endl;
                cout << setw(70) << "Item Price(RM)  : " << ptr->price << endl;
                cout << setw(70) << "Item Quantity   : " << ptr->quantity << endl;

                itemFound = true;  // Flag set to true when the item is found
                break;
            }
            ptr = ptr->next;
        }

        if (!itemFound) {
            cout << setw(68) << "Item not found." << endl;
        }
    }
}

void vending_machine::update() {
    int t_id;
    if (head == NULL) {
        cout << setw(95) << "Linked List is empty";
        return;  // No need to continue if the list is empty
    }

    cout << "\n";
    cout << setw(95) << "_________Updating Items to Vending Machine Management System________" << endl;
    cout << "\n";

    Node* ptr = head;
    bool itemFound = false;  // Flag to track if the item is found

    do {
        cout << "\n";
        cout << setw(65) << "Update ID:  ";
        cin >> t_id;

        if (cin.fail() || t_id <= 0) {
            cout << "\n";
            cout << setw(73) << "Please enter a valid positive integer for ID." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        } else {
            // If ID is valid, break out of the loop
            break;
        }
    } while (true);

    while (ptr != NULL) {
        if (t_id == ptr->id) {
            cout << "\n";
            cout << setw(89) << "Item is found and its information are as follows: \n" << endl;
            cout << setw(70) << "Item ID         : " << ptr->id << endl;
            cout << setw(70) << "Item Name       : " << ptr->name << endl;
            cout << setw(70) << "Item Price(RM)  : " << ptr->price << endl;
            cout << setw(70) << "Item Quantity   : " << ptr->quantity << endl;

            cout << "\n";
            cout << setw(75) << "Enter updated information ";
            cout << "\n";
            cout << setw(70) << "Item Name       : ";
            cin >> ptr->name;

            // Validate and get a positive price
            do {
                cout << setw(70) << "Item Price(RM)  : ";
                cin >> ptr->price;
                cout << "\n";
                if (cin.fail() || ptr->price <= 0.00) {
                    cout << setw(73) << "Please enter a valid positive number for price. " << endl;
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
            } while (cin.fail() || ptr->price <= 0.00);

            // Get a positive quantity
            do {
                cout << setw(70) <<  "Item Quantity   : ";
                cin >> ptr->quantity;
                cout << "\n";
                if (cin.fail() || ptr->quantity <= 0) {
                    cout << setw(73) << "Please enter a valid positive integer for quantity: " << endl;
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
            } while (cin.fail() || ptr->quantity <= 0);

            cout << setw(88) << "Item Record has been successfully updated.";
            itemFound = true;  // Set the flag to true when the item is found
            break;
        }
        ptr = ptr->next;
    }

    if (!itemFound) {
        cout << setw(68) << "Item not found." << endl;
    } else {
        // Update the file after modifying the linked list
        updateFile();
    }
}

void vending_machine::updateFile() {
    ofstream file("database.txt", ios::out); // Open the file in write mode
    ofstream out_of_stock("out_of_stock.txt", ios::out); // Open the file for zero quantity items

    if (!file.is_open() || !out_of_stock.is_open()) {
        cout << "Error opening files for writing." << endl;
        return;
    }

    Node* ptr = head;
    while (ptr != NULL) {
        if (ptr->quantity <= 0) {
            // Write data to the file for zero quantity items
            out_of_stock << ptr->id << "  " << ptr->name << "  " << ptr->price << "  " << ptr->quantity << "\n";
        } else {
            // Write data to the main file for non-zero quantity items
            file << ptr->id << "  " << ptr->name << "  " << ptr->price << "  " << ptr->quantity << "\n";
        }

        ptr = ptr->next;
    }

    file.close(); // Close the file
    out_of_stock.close(); // Close the file for zero quantity items
}

void vending_machine::del() {
        int t_id;
        cout <<"\n";
        cout << setw(95) << "_________Deleting Items to Vending Machine Management System________" << endl;
    if (head == nullptr) {
        cout << setw(95) << "Linked List is empty";
    } else {
        cout <<"\n";
        /*cout << setw(70) << "Enter ID to delete:  ";
        cin >> t_id;*/
        Node* pre = nullptr;
        Node* ptr = head;
        do {
            cout << "\n";
            cout << setw(65) << "Delete ID:  ";
            cin >> t_id;

            if (cin.fail() || t_id <= 0) {
                cout << "\n";
                cout << setw(73) << "Please enter a valid positive integer for ID.\n" ;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
        } while (cin.fail() || t_id <= 0);

        // Find the node with the given ID
        while (ptr != nullptr && ptr->id != t_id) {
            pre = ptr;
            ptr = ptr->next;
        }

        if (ptr == nullptr) {
        cout << setw(68) << "Item not found." << endl;
        } else {
            if (pre == nullptr) {
                // If the node to be deleted is the head
                head = ptr->next;
            } else {
                pre->next = ptr->next;
            }

            // Delete the node
            delete ptr;
            ptr = nullptr;
            cout << setw(88) << "Item Record has been successfully deleted.";

            // Update the file after deletion
            updateFile();
        }
    }
}

