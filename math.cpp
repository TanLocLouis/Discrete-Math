#include <bits/stdc++.h>

using namespace std;

void show_rules() {
    cout << "-----RULES------" << endl;
    cout << "and:     ^" << endl;
    cout << "or:      v" << endl;
    cout << "not:     -" << endl;
    cout << "implies: >" << endl;
    cout << "example: ((p^q)v(-pvq))" << endl;
    cout << "----------------" << endl;
}

struct List {
    char val;
    List* next;
};

List* createNode(char val, List* point) {
   List* newNode = new List;
   newNode->val = val;
   newNode->next = point;

   return newNode;
}

vector<char> calc(vector<char> tmp) {
    vector<char> ans;
    List* head = new List;
    List* dummy = head;
    
    for (char c : tmp) {
        head->next = createNode(c, nullptr);
        head = head->next;
    }

    List* prev = head;
    head = dummy;
    char a, opr, b;
    while (head->next->next) {
        a = head->val;
        opr = head->next->val;
        b = head->next->next->val;
        List* bNode = head->next->next;
        // not logic
        if (opr == '-') {
            if (b == '1') 
                head->next = createNode('0', bNode->next);
            else
                head->next = createNode('1', bNode->next);
        }
        prev = head;
        head = head->next;
    }

    head = dummy;
    while (head->next->next) {
        a = head->val;
        opr = head->next->val;
        b = head->next->next->val;
        List* bNode = head->next->next;
        // and logic
        if (opr == '^') {
            head = prev;
            if (a == '1' && b == '1') 
                head->next = createNode('1', bNode->next);
            else
                head->next = createNode('0', bNode->next);
        }
        // or logic
        if (opr == 'v') {
            head = prev;
            if (a == '0' && b == '0') 
                head->next = createNode('0', bNode->next);
            else
                head->next = createNode('1', bNode->next);
        }
        prev = head;
        head = head->next;
    }

    head = dummy;
    while (head->next->next) {
        a = head->val;
        opr = head->next->val;
        b = head->next->next->val;
        List* bNode = head->next->next;
        // and logic
        if (opr == '>') {
            head = prev;
            if (a == '1' && b == '0') 
                head->next = createNode('0', bNode->next);
            else
                head->next = createNode('1', bNode->next);
        }
        prev = head;
        head = head->next;
    }

    head = dummy->next->next;
    while (head->next) {
        ans.push_back(head->val);
        head = head->next;
    }
    return ans;
}

void solve(string s) {
    vector<char> trace; // trace is s cloned
    bool flag = true;
    int level = 0;
    for (char c : s) {
        trace.push_back(c);
        if (flag && c == '(') level++;
        if (c == ')') flag = false;
    }
    int num = level;

    for (int i = 0; i < num; i++) {
        vector<char> solve, tmp;
        int cnt = 0;
        for (char c : trace) {
            if (c == '(') {
                cnt++;
            }
            
            if (cnt == level)
                tmp.push_back(c);
            else
                solve.push_back(c);

            if (c == ')') {
                vector<char> res;
                if (tmp.size() >= 1) { // )) case
                    res = calc(tmp);
                } else {
                    tmp.push_back(')');
                }

                for (char c : res) solve.push_back(c);
                tmp.clear();
                cnt--;
            }

        }
        
        if (i == num - 1) {
            for (char c : solve)
                cout << c;
        }
        
        trace = solve;
        level--;
    }
}

int main() {
    show_rules();

    string str, ans;
    cout << "Input string: ";
    cin >> str;
    cout << "Input your answer: ";
    cin >> ans;

    cout << "p--q--r--s-------input----your answer" << endl;
    string statement = str, ans1 = ans;

    for (int p = 0; p <= 1; p++)
        for (int q = 0; q <= 1; q++)
            for (int r = 0; r <= 1; r++)
                for (int s = 0; s <= 1; s++) {
                    for (int i = 0; i < statement.length(); i++) {
                        if (statement[i] == 'p') statement[i] = (char) (p + 48);
                        if (statement[i] == 'q') statement[i] = (char) (q + 48);
                        if (statement[i] == 'r') statement[i] = (char) (r + 48);
                        if (statement[i] == 's') statement[i] = (char) (s + 48);

                        if (ans1[i] == 'p') ans1[i] = (char) (p + 48);
                        if (ans1[i] == 'q') ans1[i] = (char) (q + 48);
                        if (ans1[i] == 'r') ans1[i] = (char) (r + 48);
                        if (ans1[i] == 's') ans1[i] = (char) (s + 48);
                    }

                    cout << p << "  " << q << "  " << r << "  " << s << "    |    ";
                    solve(statement); cout << "     |     ";
                    solve(ans1); cout << "     |";
                    cout << endl;
                    cout << "---------------------------------------" << endl;

                    statement = str;
                    ans1 = ans;
                }

    return 0;
}
