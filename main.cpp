#include <iostream>
#include <string>
#include "encryption.h"

using namespace std;

int main() {
    string filename;
    char mode;

    cout << "Enter the filename (with full path if needed): ";
    getline(cin >> ws, filename); // Trim whitespace

    cout << "Encrypt (e) or Decrypt (d)? ";
    cin >> mode;

    if (mode == 'e' || mode == 'E') {
        if (encryptFile(filename, true)) {
            cout << "File encrypted successfully." << endl;
        } else {
            cerr << "Error: Unable to perform encryption." << endl;
        }
    } else if (mode == 'd' || mode == 'D') {
        if (encryptFile(filename, false)) {
            cout << "File decrypted successfully." << endl;
        } else {
            cerr << "Error: Unable to perform decryption." << endl;
        }
    } else {
        cerr << "Error: Invalid mode selected. Use 'e' for encryption or 'd' for decryption." << endl;
    }

    return 0;
}
