#include <iostream>
#include <fstream>
#include <iomanip>
#include "classfile.h"

using namespace std;


using namespace std;

int main()
{
    vending_machine vm;
    // Read data from the file at the beginning of the program
    vm.readFromFile("database.txt");

    vm.mainmenu();

    // Write data to the file before exiting the program
    vm.writeToFile("database.txt");

}
