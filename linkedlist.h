#include <iostream>     // IO library
#include <iomanip>      // Set width library
#include <string>
#include <windows.h>    // Set console color and sleep library

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

    void displayOrders(std::string items[], float prices[]) {
        Node* temp = head;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        std::cout << "\t\t----------------------------------------------------------------\n";
        std::cout << "\t\t" << std::left << std::setw(10) << "Product No" 
                  << std::setw(10) << "Quantity" 
                  << std::setw(25) << "Item" 
                  << std::setw(15) << "Unit Price" 
                  << std::setw(15) << "Total Price" << std::endl;
        std::cout << "\t\t----------------------------------------------------------------\n";
        while (temp) {
            std::cout << "\t\t" << std::left << std::setw(10) << (temp->orderIndex + 1) // Display product number
                      << std::setw(10) << temp->quantity 
                      << std::setw(25) << items[temp->orderIndex] 
                      << std::setw(15) << std::fixed << std::setprecision(2) << prices[temp->orderIndex]
                      << std::setw(15) << std::fixed << std::setprecision(2) << temp->quantity * prices[temp->orderIndex] << "\n";
            temp = temp->next;
        }
        std::cout << "\t\t----------------------------------------------------------------\n";
    }
};