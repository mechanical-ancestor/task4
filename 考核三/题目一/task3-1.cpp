#include <iostream>
#include <cctype>
using namespace std;

int main() {
    char sentence[100];
    cout << "请输入一段英语句子：";
    cin.getline(sentence, 100);


    int count_a = 0;
    cout << "\n==== 字母a的统计结果 ====\n";
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (tolower(sentence[i]) == 'a') {
            count_a++;
            cout << "位置" << i << "：字符'" << sentence[i] << "'\n";
        }
    }
    cout << "字母a总共出现了" << count_a << "次\n";


    int max_len = 0;
    int current_len = 0;
    char longest_word[50];
    char current_word[50];
    int word_idx = 0;

    cout << "\n==== 最长单词的结果 ====\n";
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (isalpha(sentence[i])) {
            current_word[word_idx] = sentence[i];
            word_idx++;
            current_len++;
        } else {
            current_word[word_idx] = '\0';
            if (current_len > max_len) {
                max_len = current_len;
                for (int j = 0; j < word_idx; j++) {
                    longest_word[j] = current_word[j];
                }
                longest_word[word_idx] = '\0';
            }
            word_idx = 0;
            current_len = 0;
        }
    }

    current_word[word_idx] = '\0';
    if (current_len > max_len) {
        max_len = current_len;
        for (int j = 0; j < word_idx; j++) {
            longest_word[j] = current_word[j];
        }
        longest_word[word_idx] = '\0';
    }

    cout << "最长单词是：" << longest_word << "（长度" << max_len << "）\n";

    return 0;
}

