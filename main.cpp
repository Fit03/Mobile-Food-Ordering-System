#include <iostream>             // IO library
#include <iomanip>              // Set width library
#include <ctime>                // Date and time library
#include <string>               
#include "stack.h"              // Stack header
#include "linkedList.h"         // Linkedlist header
#include "sorting.h"            // Sorting header

using namespace std;

// Global variables
string CustName;
int order, quantity = 0, quantities[15] = {0};
float totalAmount = 0.0, pay, change;
float prices[15] = {3.50, 8.00, 7.00, 6.50, 6.00, 6.00, 6.00, 5.00, 7.50, 4.00, 3.00, 2.50, 3.00, 2.00, 3.00};
string items[15] = {"Nasi Bujang", "Nasi Kandar", "Mee Goreng Mamak", "Char Kuey Teow", "Nasi Goreng Cina", "Nasi Goreng Kampung", "Nasi Goreng Pattaya", "Ayam Percik", "Nasi Kerabu", "Kentang Goreng", "Teh Ais", "Teh O Ais Limau", "Extra Joss", "Sirap", "Kopi Ais"};
Stack orderStack(50);
LinkedList orderList;

void Welcome();
void Receipt();
void Title();
void Summary();
void Order();
void Menu();
const string currentDateTime();
void clr();

// Title function
void Title() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\n\n\n\n";
    cout << "\t\t     ******              ****         **      **         **     \n";
    cout << "\t\t    **////**            /**/         /**     /**        /**     \n";
    cout << "\t\t   **    //   ******   ******  ***** /**     /** **   **/**     \n";
    cout << "\t\t  /**        //////** ///**/  **///**/**********/**  /**/****** \n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "\t\t  /**         *******   /**  /*******/**//////**/**  /**/**///**\n";
    cout << "\t\t  //**    ** **////**   /**  /**//// /**     /**/**  /**/**  /**\n";
    cout << "\t\t   //****** //********  /**  //******/**     /**//******/****** \n";
    cout << "\t\t    //////   ////////   //    ////// //      //  ////// /////   \n\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "\t\t\t\t                {\n";
    cout << "\t\t\t\t             }   }   {\n";
    cout << "\t\t\t\t            {   {  }  }\n";
    cout << "\t\t\t\t             }   }{  {\n";
    cout << "\t\t\t\t           _{  }{  }  }_\n";
    cout << "\t\t\t\t          (  }{  }{  {  )\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "\t\t\t\t          |''---------''|\n";
    cout << "\t\t\t\t          |             /'''|\n";
    cout << "\t\t\t\t          |            | _  |\n";
    cout << "\t\t\t\t          |             / | |\n";
    cout << "\t\t\t\t          |             |/  |\n";
    cout << "\t\t\t\t          |             /  /\n";
    cout << "\t\t\t\t          |            |  /\n";
    cout << "\t\t\t\t          |            'T\n";
    cout << "\t\t\t\t           ''---------''\n\n\n";
    cout << "\t\t\t\t      ";
}

// Welcome function
void Welcome() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\n\t\t\t *************************************************" << endl;
    cout << "\t\t\t =================================================";
    cout << "\n\t\t\t\t       Welcome to CafeHub";
    cout << "\n\t\t\t =================================================";
    cout << "\n\t\t\t *************************************************" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "\n\n\t\t\t        Please Enter Your Name To Continue" << endl;    
    cout << "\n\t\t\t        Name: ";
    cin >> CustName;
}

// Menu function
void Menu() {
    clr();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\n\n\t\t\t\t=====>>>>PICK YOUR ORDER<<<<=====\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\t\t=====================================================================\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "\t\t\t  PRODUCT NUMBER\tPRODUCT\t\t\tPRICE\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\t\t=====================================================================\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    for (int i = 0; i < 15; i++) {
        cout << "\t\t\t         " << i + 1 << "\t    " << setw(20) << left << items[i] << "\tRM " << fixed << setprecision(2) << prices[i] << "\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\t\t=====================================================================\n";
    cout << "\t\t=====================================================================\n";
}

// Function for ordering items
void Order() {
    char additional;
    
    do {
        Menu();
        do {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << "\n\n\t\tSelect your order: ";
            cin >> order;

            if (order < 1 || order > 15) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                cout << "\t\tInvalid order number. Please try again.\n";
            }
        } while (order < 1 || order > 15);

        do {
            cout << "\t\tHow many " << items[order - 1] << " would you like to order: ";
            cin >> quantity;

            if (quantity <= 0) {
                cout << "\t\tQuantity cannot be zero or negative. Please try again.\n";
            }
        } while (quantity <= 0);

        quantities[order - 1] += quantity;
        float itemTotal = prices[order - 1] * quantity;
        totalAmount += itemTotal;

        orderStack.Push(order - 1);          // Push to stack
        orderList.addOrder(order - 1, quantity); // Add to linked list

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "\t\t" << quantity << " x " << items[order - 1] << " added to your order. Total: RM "
             << fixed << setprecision(2) << itemTotal << "\n";

        do {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << "\t\tDo you want to add more? (y/n): ";
            cin >> additional;
            additional = tolower(additional);

            if (additional != 'y' && additional != 'n') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                cout << "\t\tInvalid input. Please enter 'y' or 'n'.\n";
            }
        } while (additional != 'y' && additional != 'n');

    } while (additional == 'y');
    
    // Automatically return to the summary after ordering is finished
    Summary();
}

// Function to manage the summary of orders
void Summary() {
    char option;
    do {
        clr();
        cout << "\n\t\tCURRENT ORDERS:\n";
        orderList.displayOrders(items, prices);

        cout << "\t\tWhat would you like to do?\n";
        cout << "\t\t1. Undo last order\n";
        cout << "\t\t2. Remove a specific order\n";
        cout << "\t\t3. Add a new order\n";
        cout << "\t\t4. Exit summary and proceed to receipt\n";
        cout << "\t\tEnter your choice (1/2/3/4): ";
        cin >> option;

        if (option == '1') { // Undo last order
            int lastOrder = orderStack.Pop(); // Get the last order index
            if (lastOrder != -1 && quantities[lastOrder] > 0) {
                totalAmount -= prices[lastOrder] * quantities[lastOrder];
                quantities[lastOrder] = 0;
                orderList.removeOrder(lastOrder);
                cout << "\t\tLast order undone successfully.\n";
            } else {
                cout << "\t\tNo orders to undo.\n";
            }
        } else if (option == '2') { // Remove a specific order
            int removeOrderIndex;
            cout << "\t\tEnter the product number to remove: ";
            cin >> removeOrderIndex;

            if (removeOrderIndex >= 1 && removeOrderIndex <= 15 && quantities[removeOrderIndex - 1] > 0) {
                totalAmount -= prices[removeOrderIndex - 1] * quantities[removeOrderIndex - 1];
                quantities[removeOrderIndex - 1] = 0;
                orderList.removeOrder(removeOrderIndex - 1);
                cout << "\t\tOrder removed successfully.\n";
            } else {
                cout << "\t\tInvalid product number or no orders for the item.\n";
            }
        } else if (option == '3') { // Add a new order
            Order(); // Call the Order function to add more orders
            return; // Automatically go back to the summary after adding the order
        } else if (option == '4') { // Exit summary and proceed to receipt
            cout << "\t\tReturning to the receipt...\n";
            break; // Exit the loop to proceed to the receipt
        } else {
            cout << "\t\tInvalid choice. Please select again.\n";
        }

    } while (true);  // Continue until the user chooses to exit
}

// Function to display the receipt
void Receipt() {
    clr();
    BubbleSort(quantities, items, prices, 15); // Sort items by quantity

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\n\n\n\n";
    cout << "\t\t     ******              ****         **      **         **     \n";
    cout << "\t\t    **////**            /**/         /**     /**        /**     \n";
    cout << "\t\t   **    //   ******   ******  ***** /**     /** **   **/**     \n";
    cout << "\t\t  /**        //////** ///**/  **///**/**********/**  /**/****** \n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "\t\t  /**         *******   /**  /*******/**//////**/**  /**/**///**\n";
    cout << "\t\t  //**    ** **////**   /**  /**//// /**     /**/**  /**/**  /**\n";
    cout << "\t\t   //****** //********  /**  //******/**     /**//******/****** \n";
    cout << "\t\t    //////   ////////   //    ////// //      //  ////// /////   \n";
    cout << "\t\t\t\t      \n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "\t\t\tJALAN HANG TUAH JAYA, 76100 DURIAN TUNGGAL, MELAKA" << endl;
    cout << "\t\t\t\t      CONTACT NO. 0123456789" << endl;
    cout << "\n\t\t\t\t\tORDER FOR " << CustName << endl;
    cout << "\t\t\t\t      " << currentDateTime() << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "\n\t\t----------------------------------------------------------------\n";
    cout << "\t\t\t\t\tITEMS PURCHASED\n";
    cout << "\t\t----------------------------------------------------------------\n";
    cout << "\t\t" << left << setw(5) << "No." 
         << setw(10) << "Quantity" 
         << setw(25) << "Item" 
         << setw(15) << "Unit Price" 
         << setw(15) << "Total Price" << endl;
    cout << "\t\t----------------------------------------------------------------\n";

    // Display sorted items with sequential numbering
    int itemCount = 1; // Initialize a counter for the sequential number
    for (int i = 0; i < 15; i++) {
        if (quantities[i] > 0) {
            cout << "\t\t" << left << setw(5) << itemCount++ // Display sequential number
                 << setw(10) << quantities[i] 
                 << setw(25) << items[i] 
                 << setw(15) << fixed << setprecision(2) << prices[i] 
                 << setw(15) << fixed << setprecision(2) << quantities[i] * prices[i] << "\n";
        }
    }

    cout << "\t\t----------------------------------------------------------------\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\t\t\t\t\t          TOTAL........ RM " << fixed << setprecision(2) << totalAmount << endl;

    do {
        cout << "\t\t\t\t\t          PAY.......... RM " << fixed << setprecision(2);
        cin >> pay;
        if (pay < totalAmount) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << "\n\t\t\tYou have insufficient money. Please enter a valid amount.\n";
        }
    } while (pay < totalAmount);

    change = pay - totalAmount;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\t\t\t\t\t          CHANGE....... RM " << fixed << setprecision(2) << change << endl;
    cout << "\t\t----------------------------------------------------------------\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "\n\t\t\t          THIS RECEIPT SHALL BE VALID\n";
    cout << "\t\t\t\t   FOR ONE DAY FROM THE DATE\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\n\t\t\t      ***PLEASE SCREENSHOT THIS RECEIPT***" << endl;
}

// Function to clear the console
void clr() {
    system("cls");
}

// Function to get the current date and time
const string currentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M", &tstruct);
    return buf;
}

int main() {
    Title();
    // Start the loading screen
    for (int a = 0; a < 12; a++) {
        Sleep(300); // Pause for 0.3 seconds
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "* ";
    }
    Sleep(2000); // Pause for 2 seconds
    clr();

    // Start the main loop
    do {
        Welcome();
        clr();
        Order();
        Summary();
        Receipt();

        system("PAUSE"); // Pause until any key is pressed
        clr();
        Title();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "\n\t\t\t\t      Thank You, See You Again!";
        Sleep(2000);
        clr();
    } while (CustName == " ");
    
    return 0;
}
