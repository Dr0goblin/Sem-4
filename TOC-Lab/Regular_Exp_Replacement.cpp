#include <iostream>
#include <string>
using namespace std;

int main() {
    string text = "Hello we are ce";
    string result = "";
    
    for(int i = 0; i < text.length(); i++) {
        if(text[i] == 'e') {
            result += 'i';
        } else {
            result += text[i];
        }
    }
    
    cout << "Original: " << text << endl;
    cout << "Modified: " << result << endl;
    
    system("pause");
    return 0;
}
