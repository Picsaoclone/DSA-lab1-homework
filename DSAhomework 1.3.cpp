#include <iostream>
#include <string>
using namespace std;

class Token {
public:
    Token* next;
    string tokenID;
    int expiredTime;

    Token(string id, int time) : tokenID(id), next(nullptr), expiredTime(time) {}
};

class AuthenticationManager {
public:
    Token* head;
    int timeToLive;

    AuthenticationManager(int ttl) {
        timeToLive = ttl;
        head = nullptr;
    }

    // Generate a new token
    void generate(string tokenID, int currentTime) {
        Token* newToken = new Token(tokenID, currentTime + timeToLive);
        // Add token to head
        newToken->next = head;
        head = newToken;	
    }

    // Renew an unexpired token
    void renew(string tokenID, int currentTime) {
        Token* temp = head;
        while (temp != nullptr) {
            if (temp->tokenID == tokenID && temp->expiredTime > currentTime) {
                temp->expiredTime = currentTime + timeToLive;
                return; // Exit once the token is renewed
            }
            temp = temp->next;
        }
    }

    // Count unexpired tokens and remove expired ones
    int countUnexpiredTokens(int currentTime) {
        int count = 0;
        Token* temp = head;
        Token* prev = nullptr;

        while (temp != nullptr) {
            if (temp->expiredTime > currentTime) {
                count++; // Count unexpired tokens
                prev = temp; // Keep track of the last unexpired token
            } else {
                // Remove expired token
                if (prev == nullptr) {
                    head = temp->next; // Update head if expired token is at the head
                } else {
                    prev->next = temp->next; // Bypass expired token
                }
                Token* deletedToken = temp; // Save expired token
                temp = temp->next; // Move to next token
                delete deletedToken; // Delete expired token
                continue; // Skip to next iteration
            }
            temp = temp->next; // Move to next token
        }
        return count; // Return the count of unexpired tokens
    }
};

int main() {
	string initial;
	cin>>initial;
	cin.ignore();
    int timeToLive;
    cin >> timeToLive; // Read timeToLive
    AuthenticationManager* authManager = new AuthenticationManager(timeToLive);
    cout << "null" << endl; // Output for the constructor

    string command;
    while (cin >> command) {
        if (command == "generate") {
            string tokenId;
            int currentTime;
            cin >> tokenId >> currentTime; 
            authManager->generate(tokenId, currentTime);
            cout << "null" << endl; // Output for generate
        } else if (command == "renew") {
            string tokenId;
            int currentTime;
            cin >> tokenId >> currentTime; 
            authManager->renew(tokenId, currentTime);
            cout << "null" << endl; // Output for renew
        } else if (command == "countUnexpiredTokens") {
            int currentTime;
            cin >> currentTime; 
            cout << authManager->countUnexpiredTokens(currentTime) << endl; // Output count of unexpired tokens
        }
    }

    delete authManager; // Cleanup
    return 0;
}

