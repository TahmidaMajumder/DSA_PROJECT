#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "classfile.h"
using namespace std;

void vending_machine::usersubmenu() {
    int choice2;
    cout << "\n";
    cout << setw(68) << "1. Buy an Item." << endl;
    cout << setw(61) << "2. Exit." << endl;
    cout << "\n";
    cout << setw(70) << "Enter your choice : ";
    cin >> choice2;

    switch (choice2) {
        case 1:
            show();
            purchaseItem();
            break;
        case 2:
            system("CLS");
            mainmenu();
        default:
            cout << "Invalid Choice";
            usersubmenu();
            }
}

void vending_machine::purchaseItem() {
    int choice3;
    float totalAmount = 0.0;

    if (head == nullptr) {
        cout << "\n";
        cout << setw(85) << "No items in the vending machine to purchase." << endl;
        mainmenu();
    } else {
        do {
            int purchaseId, purchaseQuantity;

            // Input validation for purchaseId (integer)
            cout << "\n\n";
            cout << setw(75) << "Enter the Item ID you want to purchase: ";
            while (!(cin >> purchaseId) || purchaseId <= 0) {
                cout << "\n";
                cout << setw(75) << "Please enter a valid positive integer for ID : ";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }

            // Search for the selected item
            Node* ptr = head;
            while (ptr != nullptr && ptr->id != purchaseId) {
                ptr = ptr->next;
            }

            if (ptr == nullptr) {
                cout << setw(75) << "Item not found." << endl;
                continue; // Continue to the next iteration of the loop
            }

            // Input validation for purchaseQuantity (integer)
            cout << "\n";
            cout << setw(75) << "Enter the quantity you want to purchase: ";
            while (!(cin >> purchaseQuantity) || purchaseQuantity <= 0) {
                cout << endl;
                cout << setw(75) << "Invalid input. Please enter a valid positive quantity: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // Check if the requested quantity is available
            if (purchaseQuantity > ptr->quantity) {
                cout << setw(85) << "Not enough stock. Purchase canceled." << endl;
                break; // Exit the loop
            }

            float itemTotalPrice = ptr->price * purchaseQuantity;
            totalAmount += itemTotalPrice;

            cout << "\n";
            cout << setw(85) << "Do you want to buy more items? (1 for Yes, 0 for No): ";

            // Input validation for choice3 (integer)
            while (!(cin >> choice3) || (choice3 != 0 && choice3 != 1)) {
                cout << setw(85) << "Invalid input. Please enter 1 for Yes or 0 for No: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // Update the quantity
            ptr->quantity -= purchaseQuantity;

            // Continue the loop if the user wants to buy more items
        } while (choice3 == 1);
    }

    // Display the total amount
    if (totalAmount > 0) {
        cout << "\n";
        cout << setw(75) << "Total Amount to be Paid:  " << fixed << setprecision(2) << totalAmount << endl;

        float paidAmount;
        cout << "\n";
        cout << setw(75) << "Enter the amount you want to pay(RM): ";

        // Input validation for paidAmount (float)
        while (!(cin >> paidAmount)) {
            cout << setw(75) << "Invalid input. Please enter a valid amount: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (paidAmount == totalAmount) {
            // Update the file after modifying the linked list
            updateFile();
            cout << "\n";
            cout << setw(75) << "Purchase successful. Thank you!\n";
        } else if (paidAmount > totalAmount) {
            // Update the file after modifying the linked list
            updateFile();
            float afterPurchase = paidAmount - totalAmount;
            cout << "\n";
            cout << setw(75) << "Purchase successful. Thank you! Your remaining amount: " << fixed << setprecision(2) << afterPurchase << endl;
        } else {
            cout << "\n";
            cout << setw(75) << "Insufficient amount. Purchase canceled.\n";
        }
    }
}
