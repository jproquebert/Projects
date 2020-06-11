/* main.cpp
 * Main file to test the Account class and derived classes
 * Jean Roquebert - Homework#5
 * Due July 24, 2019
 */


#include <fstream>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <cstring>

#include "accountList.hpp"
using namespace std;


int main()
{
    AccountList list;
    int n=0;
    char filename[5000];
    
    while (n!=5)
    {
        cout<<"1. Import data into list"<<endl;
        cout<<"2. Export data from list"<<endl;
        cout<<"3. Print a list summary"<<endl;
        cout<<"4. Calculate interest for accounts"<<endl;
        cout<<"5. Quit"<<endl;
        cout<<"Enter your choice: ";
        cin>>n;
        cout<<endl;
        switch(n)
        {
            case 1: cout<<"Enter the file name: ";
                cin>>filename;
                cout<<endl;
                list.importFile(filename);
                
                if (list.importFile(filename))
                {
                    cout<<"File imported successfully"<<endl;
                }
                else
                {
                    cout<<"Could not import file"<<endl;
                }
                break;
                
            case 2: cout<<"Enter the file name: ";
                cin>>filename;
                cout<<endl;
                list.createReportFile(filename);
                
                if (list.createReportFile(filename))
                {
                    cout<<"File created successfully"<<endl;
                }
                else
                {
                    cout<<"Could not create file"<<endl;
                }
                break;
            case 3:
                list.showList();
                break;
            case 4:
                list.calcInterest();
                break;
            case 5: cout<<"Bye"<<endl;
                break;
            default: cout<<"Incorrect selection"<<endl;
                break;
        }
    }
    return 0;
}


