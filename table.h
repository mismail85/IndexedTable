#ifndef TABLE_H
#define TABLE_H
#include <set>
#include <map>

#include "Order.h"

struct order_compare {
    bool operator() (const Order* lo, const Order* ro) const{

        return lo->orderId < ro->orderId;
    }
};

class Table
{
public:
    Table();
    ~Table();

    void insert(Order* order);
    bool remove(const string orderId);

    void findByCompanyName(const string &key);
    void findByAddress(const string &key);

    void printAll();
    void printRange(pair<multimap<string, Order*>::iterator, multimap<string, Order*>::iterator> &);

private:
    void removeFromCompanyIndex(const Order & order);
    void removeFromAddressIndex(const Order & order);

    set<Order*, order_compare> m_set;
    multimap<string, Order*> m_companyIndex;
    multimap<string, Order*> m_addressIndex;
};

#endif // TABLE_H
