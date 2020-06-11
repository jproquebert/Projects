/* distance.cpp
 * CPP file to define the distance class
 * Jean Roquebert - Homework#2
 * Due June 14, 2019
 */

#include<iostream>
#include<cmath>
#include "distance.hpp"

Distance::Distance(int s, int m, int l, char f)     //constructor
{
    int PrintMed,PrintSmall;
    int sm,sm2,sm3;
    int med,med2,med3,med1,la;
    
    if ((s<0) or (m<0) or (l<0))    //if any parameter is negative, distance is 0
    {
        s=0;
        m=0;
        l=0;
    }
    
    format=f;
    
    if ((format!='I') and (format!='M') and (format!='N'))
    {
        format='I';     //sets format to imperial if any invalid character is selected
    }
    
    switch (format)
    {
        case 'I':
            
            if (s>=12)  //rolls over inches into feet when inches exceeds 12
            {
                sm=(s%12);
                sm2=s/12;
                
                med=m+sm2;
                PrintMed=med;
            }
            else        //no rollover when inches is less than 12
            {
                sm=s;
                med=m;
            }
            
            if (med>=5280)      //rolls over feet into miles when inches exceeds 5280
            {
                PrintMed=(med%5280);    //value of feet to be printed
                la=l+(med/5280);        //value of miles to be printed
            }
            else        //no rollover when feet doesn't exceed 5280
            {
                la=l;
                PrintMed=med;
            }
            
            PrintSmall=sm;      //value of inches to be printed
            break;
            
            
        case 'M':
            med2=0;sm=0;med=0;la=0;
            
            if (s>=100)     //carries over centimeters into meters when they exceed 100
            {
                sm=(s%10000);
                sm2=(sm%1000);
                sm3=(sm2%100);      //value of cm to be printed out
                
                med=m+(s/100);
                PrintMed=med;
            }
            else
            {
                sm3=s;
                med=m;
                PrintMed=med;
            }
            if (med>=1000)  //carries over meters into kilometers when they exceed 1000
            {
                med1=(med%10000);
                med2=(med1%1000);
                med3=(med2%100);
                PrintMed=med3;      //value of meters to be printed out
                la=l+(med/1000);        //value of kilometers to be printed out
                
            }
            else{
                PrintMed=med;
                la=l;}
            
            PrintSmall=sm3;     //value of centimeters to be printed
            break;
            
            
            
        case 'N':
            sm=0;med=0;la=0;
            if (s>=72)          //rolls over inches into fathoms when inches exceeds 72
            {
                sm=(s%72);          //value of inches to be printed out
                med=m+(s/72);
                PrintMed=med;
            }
            else
            {
                sm=s;
                med=m;
            }
            if (med>=1013)      //rolls over fathoms into nautical miles when nautical miles exceeds 1013
            {
                med1=(med/1013);    //value of fathoms to be printed
                PrintMed=med%1013;  //value of nautical miles to be printed
                la=l+med1;
            }
            else
            {
                PrintMed=med;
                la=l;
            }
            PrintSmall=sm;
            break;
            
        default:
            break;
    }
    
    large=la;
    medium=PrintMed;
    small=PrintSmall;
    
}



Distance::Distance(double miles)
{
    int l=miles;
    double m=(miles-l)*5280;        //number of feet
    int m0=m;
    int s=round((m-m0)*12);     //number of inches
    
    large=l;
    medium=m0;
    small=s;
    format='I';
    
}



Distance::Distance(const Distance &v)       //references
{
    small=v.small;
    medium=v.medium;
    large=v.large;
    format=v.format;
}



void Distance::setFormat(char f)
{
    if (format=='I')
    {
        int imperialsmall=(small)+(medium*12)+(large*12*5280);      //converts feet and miles into inches
        
        if (f=='N') //transforms imperial into nautical
        {
            int nauticalsmall=imperialsmall;        //inches is used in both nautical and imperial
            small=nauticalsmall%72;             //inches to be printed in nautical format
            medium=(nauticalsmall/72)%1013;     //fathoms printed in nautical format
            large=nauticalsmall/72/1013;        //nautical miles printed
            format='N';
        }
        else if (f=='M')        //converts imperial into metric
        {
            int metricsmall=round(imperialsmall*2.54);      //centimeters = amount of inches x 2.54
            small=metricsmall%100;              //cm to be printed out
            medium=(metricsmall/100)%1000;      //meters to be printed out
            large=metricsmall/100/1000;     //km to be printed out
            format='M';
        }
    }
    
    else if (format=='M')
    {
        int metricsmall=(small)+(medium*100)+(large*100*1000);  //converts meters and kilometers into centimeters to help with calculations
        
        if (f=='N') //converts metric into nautical
        {
            int nauticalsmall=round(metricsmall/(2.54));    //converts cm into inches
            small=(nauticalsmall)%72;
            medium=(nauticalsmall/72)%1013;
            large=nauticalsmall/72/1013;
            format='N';
        }
        else if (f=='I')    //converts metric into imperial
        {
            int imperialsmall=round(metricsmall/(2.54));        //converts cm into inches
            small=(imperialsmall)%12;
            medium=(imperialsmall/12)%5280;
            large=imperialsmall/12/5280;
            format='I';
        }
    }
    
    else if (format=='N')
    {
        int nauticalsmall=(small)+(medium*72)+(large*72*1013);  //converts fathoms and nautical miles into inches
        
        if (f=='M') //converts nautical into metric
        {
            int metricsmall=round(nauticalsmall*2.54);      //converts inches into cm
            small=metricsmall%100;
            medium=(metricsmall/100)%1000;
            large=metricsmall/100/1000;
            format='M';
        }
        else if (f=='I')    //converta nautical into imperial
        {
            int imperialsmall=nauticalsmall;    //inches is used in both imperial and nautical
            small=imperialsmall%12;
            medium=(imperialsmall/12)%5280;
            large=imperialsmall/12/5280;
            format='I';
        }
    }
}



Distance Distance::substract(const Distance a)
{
    int sum;
    int printsmall,printmed,printlarge;
    
    if (a.format==format)
    {
        int num1,num2;      //variables used to represent the numeric value of the unit conversion factors
        
        if (format=='I')
        {
            num1=12;        //12 inches = 1 foot
            num2=5280;      //5280 feet = 1 mile
        }
        else if (format=='N')
        {
            num1=72;        //72 inches = 1 fathom
            num2=1013;      //1013 fathoms = 1 nautical mile
        }
        else if (format=='M')
        {
            num1=100;       //100 cm = 1 meter
            num2=1000;      ///1000 meters = 1 km
        }
        
        sum=(small-a.small) + (medium-a.medium)*num1 + (large-a.large)*num1*num2; //formula to substract two distances in equal metric systems
        
        printsmall=(sum)%num1;      //smallest value, in inches or cm to be printed out
        printmed=(sum/num1)%num2;       //fathoms, feet or meters
        printlarge=(sum/num1/num2);     //kilometers, nautical miles and miles
        
        return Distance(printsmall,printmed,printlarge,a.format);
    }
    else
    {
        return Distance (small,medium,large,format);        //if metric systems are different, return calling object
    }
}



Distance Distance::add(const Distance d)
{
    int sum;
    int printsmall,printmed,printlarge;
    
    if (d.format==format)
    {
        int num1,num2;      //variables used to represent the numeric value of the unit conversion factors
        
        if (format=='I')
        {
            num1=12;        //12 inches = 1 foot
            num2=5280;      //5280 feet = 1 mile
        }
        else if (format=='N')
        {
            num1=72;        //72 inches = 1 fathom
            num2=1013;      //1013 fathoms = 1 nautical mile
        }
        else if (format=='M')
        {
            num1=100;       //100 cm = 1 meter
            num2=1000;      ///1000 meters = 1 km
        }
        
        sum=(d.small+small) + (d.medium+medium)*num1 + (d.large+large)*num1*num2; //adding two distances in same metric system
        printsmall=(sum)%num1;
        printmed=(sum/num1)%num2;
        printlarge=(sum/num1/num2);
        
        return Distance(printsmall,printmed,printlarge,d.format);
    }
    else
    {
        return Distance (small,medium,large);       //return calling object if formats dont match
    }
}



int Distance::compare(Distance c)
{
    int num1=0;
    int num2=0;
    
    if (c.format!=format)   //return -2 if formats dont match
    {
        return -2;
    }
    else        // if formats match
    {
        if ((c.small==small)and(c.medium==medium)and(c.large==large))
        {
            return 0;       //return 0 if distances are equal
        }
        else
        {
            if (c.format=='I')          //conversion factors
            {
                num1=12;
                num2=5280;
            }
            else if (c.format=='N')
            {
                num1=72;
                num2=1013;
            }
            else if (c.format=='M')
            {
                num1=100;
                num2=1000;
            }
            
            if ((c.large*num1*num2 + c.medium*num1 + c.small)>(large*num1*num2 + medium*num1 + small))
            {
                return -1;      //return -1 if caller is smaller
            }
            else
                return 1;   //return 1 if caller is larger
        }
    }
}

Distance Distance::operator+(const Distance &d)     //same functionality as add function
{
    int sum;
    int printsmall,printmed,printlarge;
    
    if (d.format==format)
    {
        int num1,num2;      //conversion factors
        
        if (format=='I')
        {
            num1=12;
            num2=5280;
        }
        else if (format=='N')
        {
            num1=72;
            num2=1013;
        }
        else if (format=='M')
        {
            num1=100;
            num2=1000;
        }
        
        sum=(d.small+small) + (d.medium+medium)*num1 + (d.large+large)*num1*num2;
        printsmall=(sum)%num1;
        printmed=(sum/num1)%num2;
        printlarge=(sum/num1/num2);
        
        return Distance(printsmall,printmed,printlarge,d.format);
    }
    else
    {
        return Distance (small,medium,large);
    }
}


Distance Distance::operator-(const Distance &a)     //same functionality as substraction function
{
    int sum;
    int printsmall,printmed,printlarge;
    
    if (a.format==format)
    {
        int num1,num2;      //conversion factors
        
        if (format=='I')
        {
            num1=12;
            num2=5280;
        }
        else if (format=='N')
        {
            num1=72;
            num2=1013;
        }
        else if (format=='M')
        {
            num1=100;
            num2=1000;
        }
        
        sum=(small-a.small) + (medium-a.medium)*num1 + (large-a.large)*num1*num2;
        printsmall=(sum)%num1;
        printmed=(sum/num1)%num2;
        printlarge=(sum/num1/num2);
        
        return Distance(printsmall,printmed,printlarge,a.format);
    }
    else
    {
        return Distance (small,medium,large,format);
    }
    
}



ostream& operator<<(ostream &out, const Distance &v)
{
    switch(v.format)
    {
        case 'I':
            cout<<"The distance is "<<v.large<<" miles, "<<v.medium<<" feet, "<<v.small<<" inches."<<endl;
            break;
            
        case 'M':
            cout<<"The distance is "<<v.large<<" Kilometers, "<<v.medium<<" meters, "<<v.small<<" centimeters."<<endl;
            break;
            
        case 'N':
            cout<<"The distance is "<<v.large<<" nautical miles, "<<v.medium<<" fathoms, "<<v.small<<" inches."<<endl;
            break;
            
        default:
            cout<<"The distance is "<<v.large<<" miles, "<<v.medium<<" feet, "<<v.small<<" inches."<<endl;
            break;
            
    }
    return out;
}



istream& operator>>(istream& in, Distance &d) //reading a distance from user
{
    int l,m,s,sum;
    int num1,num2;
    in>>l;
    in>>m;
    in>>s;
    in>>d.format;
    
    if (d.format=='I')      //same conversion factors, to help print with correct format
    {
        num1=12;
        num2=5280;
    }
    else if (d.format=='N')
    {
        num1=72;
        num2=1013;
    }
    else if (d.format=='M')
    {
        num1=100;
        num2=1000;
    }
    else
    {
        num1=12;
        num2=5280;
    }
    sum=s + m*num1 + l*num1*num2;
    d.small=(sum)%num1;
    d.medium=(sum/num1)%num2;
    d.large=(sum/num1/num2);
    
    return in;
}



bool operator==(const Distance &x,  Distance &y)
{
    if (y.format!=x.format)
    {
        y.setFormat(x.format);  //modifying format to the same as first function
    }
    
    if ((x.small==y.small) and (x.medium==y.medium) and (x.large==y.large))
        return true;
    else
        return false;
}

bool operator!=(const Distance &x,  Distance &y)
{
    if (y.format!=x.format)
    {
        y.setFormat(x.format);  //modifying format to the same as first function
    }
    
    if ((x.small!=y.small) or (x.medium!=y.medium) or (x.large!=y.large))
        return true;
    else
        return false;
}

bool operator<(const Distance &x,  Distance &y)
{
    int num1=0;
    int num2=0;
    
    if (y.format!=x.format)
    {
        y.setFormat(x.format);  //modifying format to the same as first function
    }
    if (x.format=='I')
    {
        num1=12;
        num2=5280;
    }
    else if (x.format=='N')
    {
        num1=72;
        num2=1013;
    }
    else if (x.format=='M')
    {
        num1=100;
        num2=1000;
    }
    else
    {
        num1=12;
        num2=5280;
    }
    
    if ((x.large*num1*num2 + x.medium*num1 + x.small)<(y.large*num1*num2 + y.medium*num1 + y.small))
        return true;
    else
        return false;
}

bool operator>(const Distance &x,  Distance &y)
{
    int num1=0;
    int num2=0;
    
    if (y.format!=x.format)
    {
        y.setFormat(x.format);  //modifying format to the same as first function
    }
    if (x.format=='I')
    {
        num1=12;
        num2=5280;
    }
    else if (x.format=='N')
    {
        num1=72;
        num2=1013;
    }
    else if (x.format=='M')
    {
        num1=100;
        num2=1000;
    }
    else
    {
        num1=12;
        num2=5280;
    }
    
    
    if ((x.large*num1*num2 + x.medium*num1 + x.small)>(y.large*num1*num2 + y.medium*num1 + y.small))
        return true;
    else
        return false;
}



bool operator<=(const Distance &x,  Distance &y)
{
    int num1=0;
    int num2=0;
    
    if (y.format!=x.format)
    {
        y.setFormat(x.format);  //modifying format to the same as first function
    }
    if (x.format=='I')
    {
        num1=12;
        num2=5280;
    }
    else if (x.format=='N')
    {
        num1=72;
        num2=1013;
    }
    else if (x.format=='M')
    {
        num1=100;
        num2=1000;
    }
    else
    {
        num1=12;
        num2=5280;
    }
    
    if (((x.large*num1*num2 + x.medium*num1 + x.small)<(y.large*num1*num2 + y.medium*num1 + y.small)) or ((x.small==y.small) and (x.medium==y.medium) and (x.large==y.large)))
        return true;
    else
        return false;
}

bool operator>=(const Distance &x,  Distance &y)
{
    int num1=0;
    int num2=0;
    
    if (y.format!=x.format)
    {
        y.setFormat(x.format);  //modifying format to the same as first function
    }
    if (x.format=='I')
    {
        num1=12;
        num2=5280;
    }
    else if (x.format=='N')
    {
        num1=72;
        num2=1013;
    }
    else if (x.format=='M')
    {
        num1=100;
        num2=1000;
    }
    else
    {
        num1=12;
        num2=5280;
    }
    
    if (((x.large*num1*num2 + x.medium*num1 + x.small)>(y.large*num1*num2 + y.medium*num1 + y.small)) or ((x.small==y.small) and (x.medium==y.medium) and (x.large==y.large)))
        return true;
    else
        return false;
}

