#include "encryption.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <unistd.h> // Required for getcwd() on macOS/Linux

using namespace std;

// Function to print the working directory (for debugging)
void printWorkingDirectory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        cout << "Current working directory: " << cwd << endl;
    } else {
        cerr << "Error: Unable to get the current directory!" << endl;
    }
}

bool performCaesarCipher(string& content, bool encrypt) {
    int shift = encrypt ? 3 : -3;

    for (size_t i = 0; i < content.length(); ++i) {  // Traditional loop for compatibility
        char& ch = content[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ch = static_cast<char>((ch - base + shift + 26) % 26 + base);
        }
    }
    return true;
}

bool encryptFile(const string& filename, bool encrypt) {
    printWorkingDirectory(); // Debugging: Show working directory

    // Open the input file
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error: Unable to open file '" << filename << "'. Make sure the file exists." << endl;
        return false;
    }

    // Read file content
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    if (performCaesarCipher(content, encrypt)) {
        // Generate output filename
        string outputFilename = encrypt ? "encrypted_" + filename : "decrypted_" + filename;
        ofstream outFile(outputFilename);
        if (!outFile) {
            cerr << "Error: Unable to create output file: " << outputFilename << endl;
            return false;
        }

        outFile << content;
        outFile.close();
        
        cout << "Success! Output saved to: " << outputFilename << endl;
        return true;
    }

    return false;
}
