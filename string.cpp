#include "string.h"

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

String::String()
{
}

String::String(string &str)
{
    this->assign(str);
}

/**
 * @brief split
 * @param tokens
 * @param text
 * @param sep
 * Splits an string (text)into tokens using a separator
 */
void String::split(vector<string> &tokens, char sep) {
    int start = 0, end = 0;
    while ((end = find(sep, start)) != string::npos) {
        tokens.push_back( substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back( substr(start));
}

// trim from start
String& String::ltrim() {
    erase( begin(), std::find_if( begin(), end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return *this;
}

// trim from end
String& String::rtrim() {
    erase(std::find_if( rbegin(), rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), end());
    return *this;
}

// trim from both ends
String& String::trim() {
    assign(rtrim());
    assign(ltrim());
    return *this;
}
