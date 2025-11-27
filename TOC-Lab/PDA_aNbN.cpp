#include <iostream>
#include <string>
#include <stack>
using namespace std;

class PDA {
    stack<char> s;
    
public:
    PDA() {
        s.push('Z');
    }
    
    bool process(string str) {
        int i;
        
        for(i = 0; i < str.length() && str[i] == 'a'; i++) {
            s.push('a');
        }
        
        for(; i < str.length() && str[i] == 'b'; i++) {
            if(s.top() == 'a') {
                s.pop();
            } else {
                return false;
            }
        }
        
        return (i == str.length() && s.top() == 'Z');
    }
    
    void reset() {
        while(!s.empty()) s.pop();
        s.push('Z');
    }
};

int main() {
    PDA pda;
    string tests[] = {"ab", "aabb", "aaabbb", "a", "b", "abc", "aab", "abb"};
    int i;
    
    for(i = 0; i < 8; i++) {
        pda.reset();
        bool result = pda.process(tests[i]);
        cout << tests[i] << " : " << (result ? "Accepted" : "Rejected") << endl;
    }
    
    system("pause");
    return 0;
}
