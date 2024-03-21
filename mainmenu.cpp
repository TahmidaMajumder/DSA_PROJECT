#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include "classfile.h"
using namespace std;

void vending_machine::mainmenu() {
    system("color f1");
    int choice;
    string u_name, pass;
    char ch;
    cout << "\n";
    cout << setw(85) << "Welcome To Vending Machine System Application" << endl;
    cout << "\n";
    cout << setw(85) << "-----------Vending Machine System------------" << endl;
    cout << "\n";
    cout << setw(63) << "1. Admin" << endl;
    cout << setw(62) << "2. User" << endl;
    cout << setw(62) << "3. Exit" << endl;
    cout << "\n";
    cout << setw(85) << "---------------------------------------------" << endl;
    cout << setw(70) << "Enter your choice : ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "\n";
            cout << setw(65) << "Enter Username : ";
            cin >> u_name;
            cout << setw(65) << "Enter Password : ";
            ch = getch();
            while(ch != 13){//character 13 is enter
                pass.push_back(ch);
                cout << '*';
                ch = getch();
            }
            system("CLS");
            if(u_name == "Admin" && pass == "admin"){
                adminsubmenu();
            }
            else{
                system("CLS");
                cout << "\n";
                cout << setw(75) <<"Wrong Username and Password." << endl;
                mainmenu();
            }
        case 2:
            usersubmenu();
        case 3:
             exit(3);

        default:
            system("CLS");
            cout << setw(68)<< "Invalid choice." << endl;
            //system("CLS");
            mainmenu();
    }
}
