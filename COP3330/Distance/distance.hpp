/* distance.h
 * header file to declare the distance class
 * Jean Roquebert - Homework#2
 * Due June 14, 2019
 */


#include <iostream>
using namespace std;

class Distance
{
    friend bool operator== (const Distance &x,  Distance &y);
    friend bool operator!= (const Distance &x,  Distance &y);
    friend bool operator< (const Distance &x,  Distance &y);
    friend bool operator<= (const Distance &x,  Distance &y);
    friend bool operator>= (const Distance &x,  Distance &y);
    friend bool operator> (const Distance &x,  Distance &y);
    
public:
    Distance (int s,int m=0,int l=0,char f='I'); //constructor
    explicit Distance (double miles);   //explicit constructor
    Distance(const Distance &v);
    
    void setFormat(char f);
    friend ostream& operator<<(ostream& out, const Distance &v);
    friend istream& operator>>(istream& in,   Distance &d);
    
    Distance add(const Distance d);
    Distance substract(const Distance a);
    int compare( Distance c);
    
    Distance operator+(const Distance &d);
    Distance operator-(const Distance &a);  
    
private:
    
    int small,medium,large;
    char format;
};
