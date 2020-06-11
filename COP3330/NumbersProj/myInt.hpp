/* MyInt.h
 * .h file to declare the MyInt class
 * Jean Roquebert - Homework#4
 * Due July 9, 2019
 */

#include <cstring>
#include <iostream>
using namespace std;

class MyInt
{
    friend ostream& operator<<(ostream &out, const MyInt &m);
    friend istream& operator>>(istream &in, MyInt &m);
    friend bool operator== (const MyInt &x,  MyInt &y);
    friend bool operator!= (const MyInt &x,  MyInt &y);
    friend bool operator<= (const MyInt &x,  MyInt &y);
    friend bool operator< (const MyInt &x,  MyInt &y);
    friend bool operator>= (const MyInt &x,  MyInt &y);
    friend bool operator> (const MyInt &x,  MyInt &y);

    
public:
    MyInt();
    MyInt(int n);
    ~MyInt();
    MyInt(const char * n);
    MyInt(const MyInt &); //copy constructor
    MyInt& operator=(const MyInt&);   //= operator3
    MyInt operator+(const MyInt &x) const;
    MyInt& operator++(); //preincrement
    MyInt operator++(int);  //postincrement
    
    MyInt operator-(const MyInt &x) const;  //EXTRA CREDIT

    
private:
    int size;
    int *number;
    void grow();
    void shrink();
};








/*
 
 MyInt operator*(const MyInt &x) const;
 
 */


