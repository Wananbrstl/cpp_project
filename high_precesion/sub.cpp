#include <iostream>
#include <string>
#include <assert.h>
#include <algorithm>

void deleteZero(std::string& num) {
    int idx = 0;
    while(idx < num.size() && num[idx] == '0') idx++;
    if(idx == num.size()) num = "0";
    // std::cout << "origin num = " << num << std::endl;
    num = num.substr(idx, num.size() - idx );
    // std::cout << "after num = " << num << std::endl;
}

/* num1 - num2 */
std::string sub(std::string& num1, std::string& num2) {
    assert(num1[0] != '-' && num2[0] != '-');
    if(num1 == num2) return "0";
    bool neg = false;

    deleteZero(num1);
    deleteZero(num2);

    // std::cout << num1 << "\t" << num2 << std::endl;

    if(num1.size() < num2.size()) {
        std::swap(num1, num2);
        neg = true;
    } else if(num1.size() == num2.size()) {
        for(int i = 0; i < num1.size(); ++i) {
            if(num1[i] < num2[i]) {
                std::swap(num1, num2);
                neg = true;
                break;
            }
        }
    }

    // std::cout << num1 << "\t" << num2 << "\n";

    std::string res = "";
    int idx1 = num1.size() - 1, idx2 = num2.size() - 1;
    bool carry = false;
    while(idx1 >= 0 || idx2 >= 0) {
        int current_num = carry ? -1 : 0;
#ifdef DEBUG
        std::cout << current_num << "\t";
#endif
        current_num += num1[idx1--] - '0';
#ifdef DEBUG
        std::cout << current_num << "\t";
#endif
        current_num -= idx2 >= 0 ? num2[idx2--] - '0' : 0;
#ifdef DEBUG
        std::cout << current_num << "\t";
#endif
        carry = current_num < 0 ? true : false;
        current_num = (current_num + 10) % 10;
#ifdef DEBUG
        std::cout << current_num << "\n";
#endif
        res.push_back(current_num + '0');
    }
    
    std::reverse(res.begin(), res.end());
    deleteZero(res);

    return neg ? "-"+res : res;
}

int main (int argc, char *argv[])
{
    std::string num1 = "000012", num2 = "000013";
    std::cin >> num1 >> num2;
    std::cout << sub(num1, num2) << "\n";
    return 0;
}
