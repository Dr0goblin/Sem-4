#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream file("lexical_analyzer_input_file.txt");
    string word;
    
    cout << "Lexical Analysis Result:\n";
    
    while(file >> word) {
        if(word == "int" || word == "float" || word == "if" || word == "else" || 
           word == "while" || word == "return") {
            cout << "KEYWORD: " << word << endl;
        }
        else if(isalpha(word[0])) {
            cout << "IDENTIFIER: " << word << endl;
        }
        else if(isdigit(word[0])) {
            cout << "NUMBER: " << word << endl;
        }
        else if(word == "=") {
            cout << "OPERATOR: =" << endl;
        }
        else if(word == "<" || word == ">") {
            cout << "OPERATOR: " << word << endl;
        }
        else if(word == "(") {
            cout << "DELIMITER: (" << endl;
        }
        else if(word == ")") {
            cout << "DELIMITER: )" << endl;
        }
        else if(word == "{") {
            cout << "DELIMITER: {" << endl;
        }
        else if(word == "}") {
            cout << "DELIMITER: }" << endl;
        }
        else if(word == ";") {
            cout << "DELIMITER: ;" << endl;
        }
    }
    
    file.close();
    return 0;
}
