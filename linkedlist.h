#include <iostream>     // IO library
#include <iomanip>      // Set width library
#include <string>
#include <windows.h>    // Set console color and sleep library
using namespace std;

class Node {
public:
    int orderIndex; // Index of the ordered item
    int quantity;   // Quantity of the ordered item
    Node* next;     // Pointer to the next node

    Node(int index, int qty) : orderIndex(index), quantity(qty), next(NULL) {}
};

class LinkedList {
private:
    Node* head; // Head of the linked list

public:
    LinkedList() : head(NULL) {}

    void addOrder(int orderIndex, int quantity) {
        Node* newNode = new Node(orderIndex, quantity);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void removeOrder(int orderIndex) {
        if (!head) return;

        if (head->orderIndex == orderIndex) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }

        Node* temp = head;
        while (temp->next && temp->next->orderIndex != orderIndex) {
            temp = temp->next;
        }

        if (temp->next) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
    }

    void displayOrders(string items[], float prices[]) {
        Node* temp = head;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "\t\t----------------------------------------------------------------\n";
        cout << "\t\t" << left << setw(10) << "Product No" 
                  << setw(10) << "Quantity" 
                  << setw(25) << "Item" 
                  << setw(15) << "Unit Price" 
                  << setw(15) << "Total Price" << endl;
        cout << "\t\t----------------------------------------------------------------\n";
        while (temp) {
            cout << "\t\t" << left << setw(10) << (temp->orderIndex + 1) // Display product number
                      << setw(10) << temp->quantity 
                      << setw(25) << items[temp->orderIndex] 
                      << setw(15) << fixed << setprecision(2) << prices[temp->orderIndex]
                      << setw(15) << fixed << setprecision(2) << temp->quantity * prices[temp->orderIndex] << "\n";
            temp = temp->next;
        }
        cout << "\t\t----------------------------------------------------------------\n";
    }
};
