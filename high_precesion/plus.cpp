#include <algorithm>
#include <bits/stdc++.h>
#include <cassert>
#include <cmath>

void deleteZero(std::string& a){
    int idx = 0;
    while(a[idx] == '0') idx++;
    a = a.substr(idx, a.size() - idx);
}
std::string plus(std::string& a,std::string& b) {
    deleteZero(a);
    deleteZero(b);
    if(a == b) return a;

    std::string res = "";
    int idxa = a.size() - 1;
    int idxb = b.size() - 1;
    bool carry = false;
    bool nega = a[0] == '-' ? true : false;
    bool negb = b[0] == '-' ? true : false;
    bool neg_res = (nega == negb && nega == true);

    //BUG:
    if(nega != negb) {
        if(nega == true && a.size() > b.size()) neg_res = true;
        else if(negb == true && b.size() > a.size()) neg_res = true;
    }

    /*BUG: 请问一正一负怎么办？*/
    while(idxa >= 0 || idxb >= 0) {
        int current_num = (carry ? 1 : 0);
        int num1 = idxa >= 0 ? (a[idxa--] - '0') : 0;
        int num2 = idxb >= 0 ? (b[idxb--] - '0') : 0;
        current_num += nega ? -num1 : num1;
        current_num += negb ? -num2 : num2;

        current_num = abs(current_num);
        carry = current_num > 9;
        if(carry) current_num -= 10;
        res.push_back(current_num + '0');
    }
    if(carry) res.push_back('1');

    if(neg_res) res.push_back('-'); //BUG:

    std::reverse(res.begin(), res.end());
    return res;
}

int main (int argc, char *argv[])
{
    std::string num1, num2;
    std::cin >> num1 >> num2;
    std::cout << plus(num1, num2) << std::endl;
    return 0;
}
