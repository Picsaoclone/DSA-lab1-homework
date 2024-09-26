#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    string url;
    Node* prev;
    Node* next;

    Node(string url) : url(url), prev(nullptr), next(nullptr) {}
};

class BrowserHistory {
public:
    Node* head;    // Head node for the homepage
    Node* current; // Current node in the history

    // Constructor to initialize with homepage URL
    BrowserHistory(string homepage) {
        head = new Node(homepage);  // Start with homepage
        current = head;             // Current points to the head
    }

    // Visit a new URL and clear forward history
    void visit(string url) {
        Node* newNode = new Node(url);
        current->next = newNode;   // Link current to the new node
        newNode->prev = current;   // Link new node back to current
        current = newNode;         // Move current to the new node
    }

    // Move back in history by a given number of steps
    string back(int steps) {
        while (steps > 0 && current->prev != nullptr) {
            if (current->prev == head) {
                current = current->prev; // Move to the head node
                break; // Stop the loop
            }
            current = current->prev; // Move to the previous node
            steps--;
        }
        return current->url; // Return the current URL
    }
    // Move forward in history by a given number of steps
    string forward(int steps) {
        while (steps > 0 && current->next != nullptr) {
            current = current->next; // Move to the next node
            steps--;
        }
        return current->url; // Return the current URL
    }
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->url << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    ~BrowserHistory() {
        Node* temp;
        while (head) { // Cleanup all nodes starting from head
            temp = head;
            head = head->next;
            delete temp;
        }
    }
    
};

// Function to process input and simulate the browser history
void processBrowserHistory() {
    string homepage;
    cin >> homepage; // Read the homepage URL

    BrowserHistory* browserHistory = new BrowserHistory(homepage); // Create BrowserHistory instance
	cout<<"null"<<endl;
    string command;
    while (cin >> command) {
        if (command == "visit") {
            string url;
            cin >> url;  // Read URL for visit
            browserHistory->visit(url);
            cout << "null" << endl;  // Output for visit
        } else if (command == "back") {
            int steps;
            cin >> steps;  
            cout << browserHistory->back(steps) << endl;  // Output current URL after back
        } else if (command == "forward") {
            int steps;
            cin >> steps;  // Read number of steps for forward
            cout << browserHistory->forward(steps) << endl;  // Output current URL after forward
        }
    }
	browserHistory->display();
    delete browserHistory;  // Cleanup
}

int main() {
    processBrowserHistory();  // Process browser history commands
    return 0;
}

