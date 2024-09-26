#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string song;
    Node* next;
    Node* prev;

    Node(string value) : song(value), next(nullptr), prev(nullptr) {}
};

class DoublyCircularLinkedList {
public:
    Node* head;
    Node* current;

    DoublyCircularLinkedList() : head(nullptr), current(nullptr) {}

    // Add a song to the playlist
    void addSong(string songName) {
        Node* newNode = new Node(songName);
        if (head == nullptr) {
            head = newNode; // If the list is empty, set the head to the new node
            head->next = head; // Link the new node to itself (circular)
            head->prev = head; // Link the new node to itself (circular)
            current = head; // Set current to the head
        } else {
            Node* tail = head->prev; // Find the current tail
            tail->next = newNode; // Link the new song after the tail
            newNode->prev = tail; // Link the new song back to the tail
            newNode->next = head; // Make the new node point to head (circular)
            head->prev = newNode; // Update head's prev to the new node
        }
    }

    // Play the next song
    void playNext() {
        if (current != nullptr) {
            current = current->next;
        }
    }

    // Play the previous song
    void playPrev() {
        if (current != nullptr) {
            current = current->prev;
        }
    }

    // Remove a song by name
    void removeSong(string songName) {
        if (head == nullptr) return; // If the list is empty, do nothing

        Node* temp = head;

        do {
            if (temp->song == songName) {
                // If there's only one song in the list
                if (temp->next == temp) {
                    delete temp;
                    head = nullptr;
                    current = nullptr;
                    return;
                }

                // If removing the head
                if (temp == head) {
                    head->prev->next = head->next; // Link the tail to the next song
                    head->next->prev = head->prev; // Link the next song back to the tail
                    head = head->next; // Move head to the next song
                } else {
                    // Link the previous node to the next node
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }

                if (current == temp) {
                    current = temp->next; // Move to the next song after removing current
                }

                delete temp;
                return;
            }
            temp = temp->next;
        } while (temp != head);
    }

    // Display the playlist starting from the current song
    void display() {
        if (head == nullptr) {
            cout << "empty" << endl;
            return;
        }

        Node* temp = current;
        do {
            cout << temp->song << " ";
            temp = temp->next;
        } while (temp != current); // Loop until we reach the starting song again
        cout << endl;
    }
};

int main() {
    DoublyCircularLinkedList playlist;
    int n;
    cin >> n;
    string command, songName;

    for (int i = 0; i < n; ++i) {
        cin >> command;
        if (command == "ADD") {
            cin >> songName;
            playlist.addSong(songName);
        } else if (command == "NEXT") {
            playlist.playNext();
        } else if (command == "PREV") {
            playlist.playPrev();
        } else if (command == "REMOVE") {
            cin >> songName;
            playlist.removeSong(songName);
        } else if (command == "DISPLAY") {
            playlist.display(); // Display from the current node
        }
    }

    return 0;
}

