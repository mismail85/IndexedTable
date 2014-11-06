#ifndef STRING_H
#define STRING_H
#include <string>
#include <vector>

using namespace std;

class String : public std::string
{
public:
    String();
    String(string &str);

    void split(vector<string> &tokens, char sep);
    String& trim();

private:
    String& ltrim();
    String& rtrim();
};

#endif // STRING_H
