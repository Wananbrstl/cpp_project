#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

string sub(string num1, string num2) {
    int n1 = num1.size();
    int n2 = num2.size();
    int idx = 0;
    bool carry = false;
    string res;
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    while(idx < n1) {
        int number1 = (num1[idx] - '0');
        int number2 = (n2 > idx ? num2[idx] - '0' : 0);
        int curr = number1 - number2 - (carry ? 1 : 0);
        carry = curr < 0;
        curr = (curr + 10) % 10;
        res.push_back(curr + '0');
        idx++;
    }
    while(idx >= 0 && res[idx] == '0') {
        idx --;
        res.pop_back();
    }
    reverse(res.begin(), res.end());
    return res;
}

int main (int argc, char *argv[])
{
    string num1, num2;
    cin >> num1 >> num2;
    bool neg = false;
    if(num1.size() < num2.size() || (num1.size() == num2.size() && num1 < num2)) {
        neg = true;
        swap(num1, num2);
    }
    string res = sub(num1, num2);
    if(res.empty()) cout << "0";
    else cout << (neg ? "-" : "") << res << endl;
    return 0;
}
