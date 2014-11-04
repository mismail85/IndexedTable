#ifndef ORDER_H
#define ORDER_H
#include <string>

using namespace std;

class Order{
public:
    Order(){}
    Order(const Order& order){
        orderId = order.orderId;
        companyName = order.companyName;
        address = order.address;
        orderedItem =order.orderedItem;
    }

    string orderId;
    string companyName;
    string address;
    string orderedItem;

    string toString(){
        return orderId + "," + companyName + ", " + address + ", " + orderedItem;
    }
};
#endif // ORDER_H
