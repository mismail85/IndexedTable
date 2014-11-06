#include <iostream>
#include <fstream>
#include <vector>

#include "table.h"
#include "Order.h"
#include "string.h"

using namespace std;

#define COLUMNS_COUNT 4

void loadData(const string filePath, Table & table)
{
    String line;
    ifstream myfile (filePath.c_str());
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            vector<string> cells;
            line.split(cells, ',');
            if(cells.size() == COLUMNS_COUNT){
                Order *order = new Order;
                order->orderId = ((String)cells[0]).trim();
                order->companyName = ((String)cells[1]).trim();
                order->address = ((String)cells[2]).trim();
                order->orderedItem = ((String)cells[3]).trim();

                table.insert(order);
            }
            else
                cout<< "File bad format"<<endl;
        }
        myfile.close();
        cout<< "File loaded successfully" << endl;
    }

    else cout << "Unable to open file "<< filePath << endl;
}

void displayInstructions()
{
    cout<< "Enter one of the following numbers"<< endl;
    cout <<"1 - To enter file path" << endl;
    cout <<"2 - To find orders by Company name" << endl;
    cout <<"3 - To find orders to a specific address" << endl;
    cout <<"4 - To delete a prticular order"<< endl;
    cout <<"5 - To display how often each item has been ordered"<< endl;
    cout <<"6 - To print all orders"<< endl;
}

int main(int argc, char *argv[])
{

    Table table;
    int number;

    while(true){
        displayInstructions();

        cin>> number;
        cin.clear();
        cin.ignore(256, '\n');

        switch(number){
        case 1:{
            string filePaht;
            cout <<"Enter File Paht:" << endl;
            cin >> filePaht;
            loadData(filePaht, table);
        }
            break;

        case 2:{
            string company;
            cout<< "Enter company name:" <<endl;
            getline(std::cin, company);
            table.findByCompanyName(company);
        }
            break;

        case 3:{
            string address;
            cout<< "Enter Address:" << endl;
            getline(std::cin, address);
            table.findByAddress(address);
        }
            break;

        case 4:{
            string orderId;
            cout<<"Enter Order ID:"<<endl;
            getline(cin, orderId);
            if(!table.remove(orderId))
                cout << "could not delete that order, please make sure you enterd the Id correctly"<< endl;
        }
            break;

        case 5:{
            table.printProductsCount();
        }
            break;

        case 6:
            table.printAll();
            break;
        }
        cout << "=============================================\n"<<endl;
    }


    return 0;
}
