#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>


bool isValidPhone(const std::string& phone) {
    if (phone.empty()) return false;

    int start = 0;
    if (phone[0] == '+') start = 1;  // allow leading +

    if (start == phone.size()) return false; // just "+" is invalid

    for (int i = start; i < phone.size(); i++) {
        if (!isdigit(phone[i])) return false;
    }
    return true;
}