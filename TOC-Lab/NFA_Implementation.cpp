#include <iostream>
#include <string>
#include <vector>
using namespace std;

class NFA {
    vector<int> currentStates;
    
public:
    NFA() { 
        currentStates.push_back(0); 
    }
    
    void process(char c) {
        vector<int> nextStates;
        int i;
        
        for(i = 0; i < currentStates.size(); i++) {
            int state = currentStates[i];
            switch(state) {
                case 0:
                    if(c == '0') nextStates.push_back(0);
                    if(c == '1') {
                        nextStates.push_back(0);
                        nextStates.push_back(1);
                    }
                    break;
                case 1:
                    break;
            }
        }
        currentStates = nextStates;
    }
    
    bool accept() { 
        int i;
        for(i = 0; i < currentStates.size(); i++) {
            if(currentStates[i] == 1) return true;
        }
        return false;
    }
    
    void reset() { 
        currentStates.clear();
        currentStates.push_back(0); 
    }
};

int main() {
    NFA nfa;
    string tests[] = {"1", "01", "101", "1001", "0", "00", "10"};
    int i, j;
    
    for(i = 0; i < 7; i++) {
        nfa.reset();
        for(j = 0; j < tests[i].length(); j++) {
            nfa.process(tests[i][j]);
        }
        cout << tests[i] << " : " << (nfa.accept() ? "Accepted" : "Rejected") << endl;
    }
    
    system("pause");
    return 0;
}
