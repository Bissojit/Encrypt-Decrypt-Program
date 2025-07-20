#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
using namespace std;

// Returns empty string on failure, or full output file path on success
string encryptFile(const string& filename, bool encrypt);

#endif // ENCRYPTION_H
