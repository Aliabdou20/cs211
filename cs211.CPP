#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cctype>

using namespace std;

unordered_set<string> keywords = {"int", "float", "if", "else", "while", "return"};
unordered_set<char> operators = {'+', '-', '*', '/', '='};
unordered_set<char> delimiters = {';', '(', ')', '{', '}'};

bool isKeyword(const string &str) {
    return keywords.count(str) > 0;
}

void tokenize(const string &code) {
    int i = 0, n = code.length();

    while (i < n) {
        char ch = code[i];

        if (isspace(ch)) {
            i++;
        } else if (isalpha(ch) || ch == '_') {
            string word;
            while (isalnum(code[i]) || code[i] == '_') {
                word += code[i++];
            }
            if (isKeyword(word)) cout << "<KEYWORD, " << word << ">\n";
            else cout << "<IDENTIFIER, " << word << ">\n";
        } else if (isdigit(ch)) {
            string number;
            while (isdigit(code[i])) {
                number += code[i++];
            }
            cout << "<NUMBER, " << number << ">\n";
        } else if (operators.count(ch)) {
            cout << "<OPERATOR, " << ch << ">\n";
            i++;
        } else if (delimiters.count(ch)) {
            cout << "<DELIMITER, " << ch << ">\n";
            i++;
        } else {
            i++;
        }
    }
}

int main() {
    ifstream file("sample_code.txt");
    if (!file) {
        cout << "Error opening file.\n";
        return 1;
    }

    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    tokenize(code);
    return 0;
}