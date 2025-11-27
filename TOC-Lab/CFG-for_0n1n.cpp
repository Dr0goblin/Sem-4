#include <iostream>
#include <string>
using namespace std;

string sentential_form(int k) {
    string left(k, '0');
    string right(k, '1');
    return left + "S" + right;
}

void print_derivation(int n) {
    cout << "Step 0: S\n";
    for (int k = 1; k <= n; ++k) {
        cout << "Step " << k << ": " << sentential_form(k) << "\n";
    }
    string final_string(n, '0');
    final_string += string(n, '1');
    cout << "Step " << (n+1) << ": " << final_string << "\n";
}

int main() {
    int n;
    cout << "Enter n (depth): ";
    if (!(cin >> n) || n < 0) return 0;
    print_derivation(n);
    system("pause");
    return 0;
}
