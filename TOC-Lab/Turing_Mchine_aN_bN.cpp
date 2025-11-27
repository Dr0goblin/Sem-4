#include <iostream>
#include <string>
using namespace std;

int main() {
    string tape;
    cout << "Enter a string of a's and b's: ";
    cin >> tape;

    int head = 0;

    while (true) {
        while (head < tape.size() && (tape[head] == 'X' || tape[head] == 'Y'))
            head++;

        if (head >= tape.size()) {
            cout << "Accepted"<<endl;
            break;
        }

        if (tape[head] == 'a') {
            tape[head] = 'X';
            int i = head + 1;
            while (i < tape.size() && tape[i] != 'b')
                i++;
            if (i == tape.size()) {
                cout << "Rejected"<<endl;
                break;
            }
            tape[i] = 'Y';
        }
        else if (tape[head] == 'b') {
            tape[head] = 'Y';
            int i = head + 1;
            while (i < tape.size() && tape[i] != 'a')
                i++;
            if (i == tape.size()) {
                cout << "Rejected"<<endl;
                break;
            }
            tape[i] = 'X';
        }
        else {
            cout << "Rejected"<<endl;
            break;
        }

        head = 0;
    }
    system("pause");
    return 0;
}
