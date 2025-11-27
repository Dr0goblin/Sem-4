#include <iostream>
#include <string>
using namespace std;

class DFA {
    int state;
public:
    DFA() { 
        state = 0; 
    }
    
    void process(char c) {
        switch(state) {
            case 0: 
                if(c == 'b') state = 1;
                else state = 4;
                break;
            case 1: 
                if(c == 'a') state = 2;
                else state = 1;
                break;
            case 2: 
                if(c == 'b') state = 3;
                else state = 2;
                break;
            case 3: 
                if(c == 'a') state = 3;
                else state = 1;
                break;
            case 4: 
                state = 4;
                break;
        }
    }
    
    bool accept() { 
        return state == 3; 
    }
    
    void reset() { 
        state = 0; 
    }
};

int main() {
    DFA dfa;
    string tests[] = {"baba", "babababa", "ba", "aba"};
    int i, j;
    
    for(i = 0; i < 4; i++) {
        dfa.reset();
        for(j = 0; j < tests[i].length(); j++) {
            dfa.process(tests[i][j]);
        }
        cout << tests[i] << " : " << (dfa.accept() ? "Accepted" : "Rejected") << endl;
    }
    
    system("pause");
    return 0;
}
