#include "table.h"

#include <iostream>

Table::Table()
{
}

Table::~Table(){
    set<Order*>::iterator it;

    for (it=m_set.begin(); it!=m_set.end(); ++it){
        delete (*it);
    }
}

/**
 * @brief Table::insert
 * @param order
 * This function inserts an order to the data structure, also it creates two indeces
 * one for the company name and the other for the address
 */
void Table::insert(Order *order)
{
    m_set.insert(order);
    m_companyIndex.insert( pair<string, Order*>( order->companyName, order ) );
    m_addressIndex.insert( pair<string, Order*>( order->address, order ) );
}

/**
 * @brief Table::findByCompanyName
 * @param key
 * This function prints all the orders related to a company named by the key parameter
 * Complexity is O(Log(n))
 */
void Table::findByCompanyName(const string &key){
    pair<multimap<string, Order*>::iterator, multimap<string, Order*>::iterator>range  = m_companyIndex.equal_range(key);
    printRange( range );
}

/**
 * @brief Table::findByAddress
 * @param key
 * This function prints all the orders related a specific address key
 * Compexity is O(Log(n))
 */
void Table::findByAddress(const string &key)
{
    pair<multimap<string, Order*>::iterator, multimap<string, Order*>::iterator> range  = m_addressIndex.equal_range(key);
    printRange( range );
}

/**
 * @brief Table::remove
 * @param orderId
 * @return
 * This function removes an order by it's order id from the data structure and the
 * two indeces (company, address)
 * Complexity is O(Log(n))
 */
bool Table::remove(const string orderId)
{
    Order* order = new Order;
    order->orderId =orderId;
    set<Order*>::iterator it = m_set.find(order);
    delete order;
    if(it != m_set.end()){
        cout << "item no = "<< (*it)->orderId<< " has been deleted " << endl;

        removeFromCompanyIndex( *(*it) );
        removeFromAddressIndex( *(*it) );

        m_set.erase(it);
        delete (*it);
        return true;
    }
    return false;
}

void Table::removeFromCompanyIndex(const Order & order)
{
    pair<multimap<string, Order*>::iterator, multimap<string, Order*>::iterator> range = m_companyIndex.equal_range(order.companyName);
    for(multimap<string, Order*>::iterator it = range.first; it != range.second; ++it){
        if( it->second->orderId == order.orderId){
            m_companyIndex.erase(it);
            break;
        }
    }
}

void Table::removeFromAddressIndex(const Order & order)
{
    pair<multimap<string, Order*>::iterator, multimap<string, Order*>::iterator> range = m_addressIndex.equal_range(order.address);
    for(multimap<string, Order*>::iterator it = range.first; it != range.second; ++it){
        if( it->second->orderId == order.orderId){
            m_addressIndex.erase(it);
            break;
        }
    }
}

void Table::printRange(pair<multimap<string, Order*>::iterator, multimap<string, Order*>::iterator> &range)
{
    for(multimap<string, Order*>::iterator it = range.first; it != range.second; ++it){
        cout <<  it->second->orderId << "\t | ";
        cout << it->second->companyName << "\t | ";
        cout << it->second->address << "\t | ";
        cout << it->second->orderedItem;
        cout << '\n';
    }
}
/**
 * @brief Table::printProductsCount
 * This function prints the products and it's counts ordered descending
 * Complexity is O(n)
 */
void Table::printProductsCount()
{
    map<string, int> products;
    set<Order*>::iterator it;

    for (it=m_set.begin(); it!=m_set.end(); ++it){
        products[(*it)->orderedItem] += 1;
    }

    map<string, int>::iterator mapIt;
    set< pair<string, int>, pair_compare > orderedSet;
    for(mapIt = products.begin(); mapIt != products.end(); ++mapIt){
        orderedSet.insert(pair<string, int>(mapIt->first, mapIt->second));
    }

    set< pair<string, int> >::iterator setIt;
    for(setIt = orderedSet.begin(); setIt != orderedSet.end(); ++setIt){
        cout << "count of "<< setIt->first << "=" << setIt->second<< endl;
    }
}

void Table::printAll()
{
    set<Order*>::iterator it;

    for (it=m_set.begin(); it!=m_set.end(); ++it){
        cout << (*it)->orderId << "\t | ";
        cout << (*it)->companyName << "\t | ";
        cout << (*it)->address << "\t | ";
        cout << (*it)->orderedItem;
        cout << '\n';
    }
}
