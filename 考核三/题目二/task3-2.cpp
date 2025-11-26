#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

const int MAX_LEN = 20;
const int MAX_NEW_LEN = 2 * MAX_LEN + 10;

void manacher(char* str, char* result) {
    int len = 0;
    char* p = str;
    while (*p != '\0') { len++; p++; }
    if (len == 0) { *result = '\0'; return; }

    char newStr[MAX_NEW_LEN] = {0};
    char* newP = newStr;
    *newP++ = '^';
    p = str;
    while (*p != '\0') { *newP++ = '#'; *newP++ = *p++; }
    *newP++ = '#';
    *newP++ = '$';

    int radius[MAX_NEW_LEN] = {0};
    int center = 0, right = 0;
    int maxRadius = 0, maxCenter = 0;

    newP = newStr + 1;
    while (*newP != '$') {
        int i = static_cast<int>(newP - newStr);
        int mirror = 2 * center - i;

        if (i < right && mirror >= 0) {
            radius[i] = (right - i) < radius[mirror] ? (right - i) : radius[mirror];
        } else {
            radius[i] = 0;
        }

        while (i + radius[i] + 1 < MAX_NEW_LEN && i - radius[i] - 1 > 0
               && newStr[i + radius[i] + 1] == newStr[i - radius[i] - 1]) {
            radius[i]++;
        }

        if (i + radius[i] > right) {
            center = i;
            right = i + radius[i];
        }

        if (radius[i] > maxRadius) {
            maxRadius = radius[i];
            maxCenter = i;
        }

        newP++;
    }

    int start = (maxCenter - maxRadius) / 2;
    char* resPtr = result;
    p = str + start;
    for (int i = 0; i < maxRadius; i++) {
        *resPtr++ = *p++;
    }
    *resPtr = '\0';
}

int main() {
    char input[MAX_LEN + 1] = {0};
    std::cout << "请输入20字符以内的字符串：";
    std::cin >> input;

    char longestPalin[MAX_LEN + 1] = {0};
    manacher(input, longestPalin);

    std::cout << "\n最长回文子串：" << longestPalin << std::endl;
    return 0;
}

