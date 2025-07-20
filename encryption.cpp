#include "encryption.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <unistd.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

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
    for (size_t i = 0; i < content.length(); ++i) {
        char& ch = content[i];
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ch = static_cast<char>((ch - base + shift + 26) % 26 + base);
        }
    }
    return true;
}

string encryptFile(const string& inputName, bool encrypt) {
    printWorkingDirectory();

    fs::path filePath = inputName;

    if (!fs::exists(filePath)) {
        filePath = fs::current_path() / inputName;
        if (!fs::exists(filePath)) {
            cerr << "Error: File not found: " << inputName << endl;
            return "";
        }
    }

    ifstream inFile(filePath);
    if (!inFile) {
        cerr << "Error: Unable to open file: " << filePath << endl;
        return "";
    }

    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    if (performCaesarCipher(content, encrypt)) {
        string baseName = filePath.filename().string();
        string outputName = encrypt ? "encrypted_" + baseName : "decrypted_" + baseName;
        fs::path outputPath = filePath.parent_path() / outputName;

        ofstream outFile(outputPath);
        if (!outFile) {
            cerr << "Error: Unable to create output file: " << outputPath << endl;
            return "";
        }

        outFile << content;
        outFile.close();

        cout << "Success! Output saved to: " << outputPath << endl;
        return outputPath.string(); // ✅ Return full path
    }

    return "";
}
