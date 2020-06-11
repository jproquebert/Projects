/* MyInt.cpp
 * CPP file to define the MyInt class
 * Jean Roquebert - Homework#4
 * Due July 9, 2019
 */

#include <iostream>
#include <cstring>
#include "myInt.hpp"
using namespace std;

int chartoint(char c)       //function provided by professor, converts chars to int values.
{
    if (c < '0' || c > '9') return -1; // error
    return (c - '0'); // success
}

char inttochar(int x)       //function provided by professor. Converts ints to chars ascii value.
{
    if (x < 0 || x > 9) return '0'; // error
    return (static_cast<char>(x) + '0'); // success
}

MyInt::MyInt()      //default constructor, initializes to 0.
{
    size=0;
    number= new int[size];
    
    for (int i=0;i<=size;i++)
    {
        number[i]=0;
    }
}


MyInt::MyInt(int n)     //int constructor
{
    if (n<0)
    {
        size=0;
        number=new int[size];
        for (int i=0;i<=size;i++)
        {
            number[i]=0;
        }
        
    }
        else
        {
            size=0;
            int num=n;
            int next=n;
            
            while(num>=10)
            {
                num=num/10;
                size++;
            }
            
            number= new int[size];
            
            for (int i=size;i>=0;i--)
            {
                number[i]=next%10;
                next=next/10;
            }
    }
}

MyInt::MyInt(const char * n)      //array of "chars" constructor.
{
    int done=0;
    size=0;
    
    int length=strlen(n);
    
    for (int i=0;i<length;i++)
    {
        size=i;
    }
    
    number=new int[size];
    
    for (int i=0;i<=size;i++)
    {
        
        if ((n[i]>='0') and (n[i]<='9'))
         {
            number[i]=chartoint(n[i]);
         }
        else //(n[i] < '0' || n[i] > '9')
        {
            number[i]=0;
            done=1;
        }
    }
    
    if (done==1)
    {
        size=0;
        for (int i=0;i<=size;i++)
        {
            number[i]=0;
        }
    }
}

MyInt::~MyInt()
{
    delete [] number;
    size=0;
    number=NULL;
}

MyInt::MyInt(const MyInt &m)        //copy constructor
{
    
    size = m.size;
    
    if(number !=NULL)
    {
        delete [] number;
        number = NULL;
    }
    
    
    number = new int[m.size];
    for(int i=0; i<=size; i++)      //deep copy
    {
        number[i] = m.number[i];
    }
}

MyInt& MyInt::operator=(const MyInt &m)     //= overload
{
    size = m.size;
    
    if(number !=NULL)
    {
        delete [] number;       //deleting trash values
        number = NULL;
    }
    
    
    number = new int[m.size];
    
    for(int i=0; i<=size; i++)      //deep copy
    {
        number[i] = m.number[i];
    }
    
    return *this;
}

void MyInt::shrink()
{
    size=size-5;
}

void MyInt::grow()
{
    size=size+5;
}


ostream& operator<<(ostream &out, const MyInt &m)
{
    for (int i=0;i<=m.size;i++)
    {
        out<<inttochar(m.number[i]);
    }
    return out;
}

istream& operator>>(istream &in,  MyInt &m)
{
    MyInt temp;
    int psize=0;
    string p;
    in>>p;
    for (int i=0;;i++)
    {
        if ((p[i]<'0') or (p[i]>'9'))
        {
            break;
        }
        psize++;
    }
    
    temp.size=psize-1;
    temp.number=new int[temp.size];
    
    for (int i=0;i<=temp.size;i++)
    {
        temp.number[i]=chartoint(p[i]);
    }
    
    m=temp;
    return in;
}

bool operator== (const MyInt &x,  MyInt &y)
{
    bool check;
    if (x.size==y.size)
    {
        for (int i=0;i<=x.size;i++)
        {
            if (x.number[i]==y.number[i])
            {
                check=true;
            }
        }
        if (check==true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool operator!= (const MyInt &x,  MyInt &y)
{
    int check=0;
    if (x.size==y.size)
    {
        for (int i=0;i<=x.size;i++)
        {
            if (x.number[i]!=y.number[i])
            {
                check=1;
                break;
            }
        }
        if (check==1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool operator<= (const MyInt &x,  MyInt &y)
{
    if (x.size>y.size)
    {
        return false;
    }
    else
    {
        if (x.number<=y.number)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool operator< (const MyInt &x,  MyInt &y)
{
    if (x.size>y.size)
    {
        return false;
    }
    else
    {
        if (x.number<y.number)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool operator>= (const MyInt &x,  MyInt &y)
{
    if (x.size<y.size)
    {
        return false;
    }
    else
    {
        if (x.number>=y.number)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool operator> (const MyInt &x,  MyInt &y)
{
    if (x.size<y.size)
    {
        return false;
    }
    else
    {
        if (x.number>y.number)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

MyInt MyInt::operator+(const MyInt &x) const        //overloading addition
{
    MyInt sum;
    MyInt p,big,small;        // p is calling object, x is operand
    
    p=*this;
    
    if (p.size>=x.size)
    {
        sum.size=p.size;
        big=p;
        small=x;
    }
    else
    {
        sum.size=x.size;
        big=x;
        small=p;
    }
    
    sum.number=new int[sum.size];
    
    int carryover=0;
    int k=small.size;
    for (int i=sum.size;i>=0;i--)
    {
        
        sum.number[i]=big.number[i]+small.number[k]+carryover;
        if (sum.number[i]>9)
        {
            carryover=1;
            sum.number[i]=sum.number[i]-10;
        }
        else
        {
            carryover=0;
        }
        
        
        k--;
        if (k<=-1)
        {
            k=0;
            small.number[k]=0;
        }
    }
    if (carryover>=1)
    {
        sum.size++;
        MyInt temporal;
        temporal.size=sum.size;
        for (int i=0;i<=sum.size;i++)
        {
            temporal.number[i]=sum.number[sum.size];
            sum.number[sum.size]=sum.number[i];
            sum.number[i]=temporal.number[i];
        }
        sum.number[0]=carryover;
    }
    return sum;
}

MyInt MyInt::operator++(int a)      //postincrement
{
    MyInt temp;
    temp.size=size;
    temp.number=new int[temp.size];
    for (int i=0;i<=temp.size;i++)
    {
        temp.number[i]=number[i];
    }
    ++(*this);
    return temp;
}


MyInt& MyInt::operator++()      //preincrement
{
    
    int carryover=0;
    
    for (int i=size;i>=0;i--)
    {
        if (i==size)
        {
            number[i]=number[i]+1;
        }
        
        number[i]=number[i]+carryover;
        
        if (number[i]>9)
        {
            number[i]=number[i]-10;
            carryover=1;
        }
        else if(number[i]<10)
        {
            carryover=0;
        }
    }
    
    if (carryover>0)
    {
        size++;
        MyInt temporal;
        for (int i=0;i<=size;i++)
        {
            temporal.number[i]=number[size];
            number[size]=number[i];
            number[i]=temporal.number[i];
        }
        number[0]=carryover;
    }
    return *this;
}

MyInt MyInt::operator-(const MyInt &x) const
{
    MyInt min;
    MyInt p,big,small;
    p=*this;
    
    int pcount=0, xcount=0;
    
    for (int i=0;i<=p.size;i++)
    {
        pcount=pcount+p.number[i];
    }
    for (int i=0;i<=x.size;i++)
    {
        xcount=xcount+x.number[i];
    }
    
    if (p.size>=x.size)
    {
        big=p;
        small=x;
        min.size=big.size;
        min.number=new int[min.size];
        int k=small.size;
        
        for (int i=min.size;i>=0;i--)
        {
            if ((big.number[i]-small.number[k])<0)
            {
                min.number[i]=big.number[i]-small.number[k]+10;
                big.number[i-1]=big.number[i-1]-1;
            }
            else
            {
                min.number[i]=big.number[i]-small.number[k];
            }
            k--;
            if (k<=-1)
            {
                k=0;
                small.number[k]=0;
            }
        }
    }
    else if (x.size>p.size)
    {
        min.size=0;
        min.number= new int[size];
        
        for (int i=0;i<=size;i++)
        {
            min.number[i]=0;
        }
    }
    
    int j=0;
    while (min.number[j]==0)
    {
        MyInt temporal;
        for (int i=0;i<=min.size;i++)
        {
            min.number[i]=min.number[i+1];
        }
        j++;
    }
    return min;
}

/*
MyInt MyInt::operator*(const MyInt &x) const
{
    MyInt multiply;
    /*MyInt p,q;
    MyInt small,big;
    
    q=x;
    p.size=size;
    p.number = new int[p.size];
    for (int i=0;i<=p.size;i++)
    {
        p.number[i]=number[i];
    }
    
    
    if (p.size>=q.size)
    {
        big=p;
        small=q;
    }
    else if (q.size>p.size)
    {
        big=q;
        small=p;
    }
    
    multiply.size=big.size;
    
    multiply.number= new int[multiply.size];
    int carryover=0;
    int mult=0;
    
    for (int i=big.size;i>=0;i--)
    {
        for( int j=small.size;i>=0;i--)
        {
            mult=(big.number[i]*small.number[j])%10;
            multiply.number[i]=mult+carryover;
            carryover=(big.number[i]*small.number[j])/10;
        }
        
    }
    
    if (carryover>0)
    {
        multiply.size++;
        MyInt temporal;
        for (int i=0;i<=multiply.size;i++)
        {
            temporal.number[i]=multiply.number[multiply.size];
            multiply.number[multiply.size]=multiply.number[i];
            multiply.number[i]=temporal.number[i];
        }
        multiply.number[0]=carryover;
    }
    return multiply;
}



*/


