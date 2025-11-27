#include <iostream>
#include <string>
using namespace std;

void findPrefix(string str) {
    cout << "Prefixes: ";
    for(int i = 0; i <= str.length(); i++) {
        cout << "'" << str.substr(0, i) << "' ";
    }
    cout << endl;
}

void findSuffix(string str) {
    cout << "Suffixes: ";
    for(int i = 0; i <= str.length(); i++) {
        cout << "'" << str.substr(str.length() - i) << "' ";
    }
    cout << endl;
}

void findSubstring(string str) {
    cout << "Substrings: ";
    for(int i = 0; i < str.length(); i++) {
        for(int j = 1; j <= str.length() - i; j++) {
            cout << "'" << str.substr(i, j) << "' ";
        }
    }
    cout << endl;
}

int main() {
    string str;
    cout << "Enter a string: ";
    cin >> str;
    
    findPrefix(str);
    findSuffix(str);
    findSubstring(str);
    
    system("pause");
    return 0;
}
