#include <iostream>
#include <fstream>
#include <vector>

#include "table.h"
#include "Order.h"
using namespace std;



void split(vector<string> &tokens, const string &text, char sep) {
    int start = 0, end = 0;
    while ((end = text.find(sep, start)) != string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
}

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

int main(int argc, char *argv[])
{
    string line;
    ifstream myfile ("D:/workspace/LiquidLabs/docs/sample");
    if (myfile.is_open())
    {
        Table table;
        while ( getline (myfile,line) )
        {
            vector<string> cells;
            split(cells, line, ',');

            Order *order = new Order;
            order->orderId = trim(cells[0]);
            order->companyName = trim(cells[1]);
            order->address = trim(cells[2]);
            order->orderedItem = trim(cells[3]);

            table.insert(order);

        }
        table.remove("002");
        table.findByCompanyName("Cheapskates");

        myfile.close();
    }

    else cout << "Unable to open file";

    return 0;
}
