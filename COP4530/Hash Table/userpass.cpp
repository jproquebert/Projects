/*
 Project 5
 Jean Roquebert
 COP4530
 userpass.cpp
 nov 29, 2019
 fall 2019
 */


#include <utility>
#include <unistd.h>
#include <cstring>
#include <stdlib.h>

#include <iostream>
#include <string>

#include "hashtable.h"
#include "pass_server.h"

using namespace std;
using namespace cop4530;

void Menu()
{
   cout << "\n\n";
   cout << "l - Load From File" << endl;
   cout << "a - Add User" << endl;
   cout << "r - Remove User" << endl;
   cout << "c - Change User Password" << endl;
   cout << "f - Find User" << endl;
   cout << "d - Dump HashTable" << endl;
   cout << "s - HashTable Size" << endl;
   cout << "w - Write to Password File" << endl;
   cout << "x - Exit program" << endl;
   cout << "\nEnter choice : ";
}

int main()
{
    int size;
    string temp1="", temp2="",temp3="";
    char menu;
    
    cout<<"Enter preferred hash table capacity: ";
    cin>>size;
    PassServer<string,string> server(size);
    
    do {
        Menu();
        cin>>menu;
        menu=tolower(menu);
        switch (menu) {
            case 'l':
                cout<<"Enter password file name to load from: ";
                cin>>temp1;
                if(!server.load(temp1.c_str()))
                    cout<<"Error***** file not found\n";
                break;
            case 'a':
                cout<<"Enter username: ";
                cin>>temp1;
                cout<<"Enter password: ";
                cin>>temp2;
                if(server.addUser(make_pair(temp1,temp2)))
                    cout<<"User "<<temp1<<" added.\n";
                else
                    cout<<"*****Error: User already exists. Could not add user.\n\n";
                break;
            case 'r':
                cout<<"Enter username: ";
                cin>>temp1;
                if(server.removeUser(temp1))
                    cout<<"User "<<temp1<<" deleted.\n\n";
                else
                    cout<<"*****Error: User not found. Could not delete user\n\n";
                break;
            case 'c':
                cout<<"Enter username: ";
                cin>>temp1;
                cout<<"Enter password: ";
                cin>>temp2;
                cout<<"Enter new password: ";
                cin>>temp3;
                if(server.changePassword(make_pair(temp1,temp2),temp3))
                    cout<<"Password changed for user "<< temp1<<"\n\n";
                else
                    cout<<"*****Error: Could not change user password\n\n";
                break;
            case 'f':
                cout<<"Enter username: ";
                cin>>temp1;
                if(server.find(temp1))
                    cout<<"User \'"<<temp1<<"\' found.\n\n";
                else
                    cout<<"*****Error: User \'"<<temp1<<"\' not found.\n\n";
                break;
            case 'd':
                server.dump();
                break;
            case 's':
                cout<<"Size of hastable: "<<server.size();
                break;
            case 'w':
                cout<<"Enter password file name to write to: ";
                cin>>temp1;
                if(!server.write_to_file(temp1.c_str()))
                    cout<<"Error***** could not write to file";
                break;
            case 'x':
                break;
            default:
                cout<<"Invalid option try again\n";
        }
    } while(menu!='x');
    
    return 0;
}

