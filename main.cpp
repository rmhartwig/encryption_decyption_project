/*
Ryan Hartwig Project 1
C++ Encryption and Decryption Program
CPSC 253
This program encrypts and decrypts text files using a simple cubic transformation.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

//function prototypes
vector<long long> encrypt(const string &message, int key);
string decrypt(const vector<long long> &cipher, int key);
void saveCipherToFile(const vector<long long> &cipher, const string &filename);
vector<long long> loadCipherFromFile(const string &filename);
void writeToFile(const string &filename, const string &content);

int main() {
    int choice;
    do { 
        //main menu loop
        cout << "\nMenu:\n";
        cout << "1. Encrypt a file\n";
        cout << "2. Decrypt a file\n";
        cout << "3. Write a plaintext file\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        //variables for file names, key, and message
        string inFile, outFile, message;
        int key;

        if (choice == 1) { //chosen to encrypt

            //get filenames and key
            cout << "Enter filename to encrypt: ";
            getline(cin, inFile);
            cout << "Enter filename to write encryption to: ";
            getline(cin, outFile);
            cout << "Enter key: ";
            cin >> key;
            cin.ignore();

            //read plaintext from file
            ifstream in(inFile);
            if (!in) {
                cerr << "Error: Could not open input file." << endl;
                continue;
            }
            string message((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
            in.close();

            //encrypt and save to file
            vector<long long> cipher = encrypt(message, key);
            saveCipherToFile(cipher, outFile);

        } else if (choice == 2) { //chosen to decrypt

            //get filenames and key
            cout << "Enter encrypted filename: ";
            getline(cin, inFile);
            cout << "Enter filename to write decryption to: ";
            getline(cin, outFile);
            cout << "Enter key: ";
            cin >> key;
            cin.ignore();

            //load ciphertext from file
            vector<long long> cipher = loadCipherFromFile(inFile);
            if (cipher.empty()) {
                cerr << "Error: No data read from ciphertext file." << endl;
                continue;
            }
            string plaintext = decrypt(cipher, key);

            //save plaintext to file
            ofstream out(outFile);
            if (!out) {
                cerr << "Error: Could not open output file." << endl;
                continue;
            }
            out << plaintext;
            out.close();

            cout << "Decryption complete. Plaintext saved to " << outFile << endl;

        } else if (choice == 3) { //chosen to write plaintext file
            cout << "Enter filename to create: ";
            getline(cin, outFile);
            cout << "Enter your message (single line): ";
            getline(cin, message);
            writeToFile(outFile, message);

        } else if (choice != 4) { //invalid choice
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);
    //exit message
    cout << "Program exited.\n";
    return 0;
}

// Encryption
vector<long long> encrypt(const string &message, int key) {
    vector<long long> result;
    for (char c : message) {
        // Apply the cubic transformation
        long long y = 46LL * pow((unsigned char)c + key, 3) + 1;
        result.push_back(y);
    }
    return result;
}

// Decryption
string decrypt(const vector<long long> &cipher, int key) {
    string result = "";
    for (long long y : cipher) {
        // Reverse the cubic transformation
        long long cubeRoot = round(cbrt((y - 1) / 46.0));
        char original = (char)(cubeRoot - key);
        result += original;
    }
    return result;
}

// Save ciphertext to file
void saveCipherToFile(const vector<long long> &cipher, const string &filename) {
    ofstream out(filename);
    if (!out) {//error handling
        cerr << "Error: Could not open file for writing: " << filename << endl;
        return;
    }
    for (long long y : cipher) {//write each value to file
        out << y << " ";
    }
    out.close();
    cout << "Ciphertext saved to " << filename << endl;
}

// Load ciphertext from file
vector<long long> loadCipherFromFile(const string &filename) {
    ifstream in(filename);
    vector<long long> cipher;
    long long value;
    if (!in) {//error handling
        cerr << "Error: Could not open file for reading: " << filename << endl;
        return cipher;
    }
    while (in >> value) {//read values into vector
        cipher.push_back(value);
    }
    return cipher;
}

// Write plaintext to file
void writeToFile(const string &filename, const string &content) {
    ofstream out(filename);
    if (!out) {//error handling
        cerr << "Error: Could not open file for writing: " << filename << endl;
        return;
    }
    out << content;//write content to file
    out.close();
    cout << "File written successfully: " << filename << endl;
}