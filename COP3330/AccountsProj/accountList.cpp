/* accountList.cpp
 * cpp file to define the Account class and derived classes
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


Account::Account(char n[50] , int an, char at, double b, int nt)
{
    strcpy(name,n);
    accnumber=an;
    acctype=at;
    balance=b;
    numtransactions=nt;
}

void Account::shortSummary()
{
    cout<<"Name: "<<name<<endl;
    
    switch (acctype)
    {
        case 'C':
            cout<<"Account type: Checking account"<<endl;
            break;
        case 'S':
            cout<<"Account type: Savings account"<<endl;
            break;
        case 'A':
            cout<<"Account type: Credit Card account"<<endl;
            break;
        default:
            cout<<"Invalid account type"<<endl;
    }
    
    cout<<"Balance: "<<balance<<endl;
    cout<<"Number of Transactions: "<<numtransactions<<endl;
}

char* Account::getName()
{
    return name;
}
void Account::setName(char n[50])
{
    strcpy(name,n);
}

int Account::getAccnumber()
{
    return accnumber;
}
void Account::setAccnumber(int x)
{
    accnumber=x;
}

char Account::getAcctype()
{
    return acctype;
}
void Account::setAcctype(char c)
{
    acctype=c;
}

double Account::getBalance()
{
    return balance;
}

void Account::setBalance(double x)
{
    balance=x;
}

int Account::getNumtransactions()
{
    return numtransactions;
}
void Account::setNumtransactions(int x)
{
    numtransactions=x;
}

double Account::getDeposits()
{
    return 0;
}
void Account::setDeposits(double)
{
}

double Account::getWithdrawals()
{
    return 0;
}
void Account::setWithdrawals(double)
{
}
double Account::getInterestRate()
{
    return 0;
}
void Account::setInterestRate(double)
{
}
double Account::getCreditLimit()
{
    return 0;
}
void Account::setCreditLimit(double x)
{
}

void Account::transaction(double amount, char type)
{
}

double Account::getPayments()
{
    return 0;
}
void Account::setPayments(double x)
{
}

double Account::getUsage()
{
    return 0;
}
void Account::setUsage(double x)
{
}
void Account::calcInterest()
{
}
















CheckingAccount::CheckingAccount(char n[50] , int anumber, char atype, double bal, int numtran) : Account(n, anumber, 'C', bal, numtran)
{
    deposits=0;
    withdrawals=0;
}

double CheckingAccount::getDeposits()
{
    return deposits;
}
void CheckingAccount::setDeposits(double x)
{
    deposits=x;
}
double CheckingAccount::getWithdrawals()
{
    return withdrawals;
}
void CheckingAccount::setWithdrawals(double x)
{
    withdrawals=x;
}
void CheckingAccount::transaction(double amount,char type)
{
    if (type=='D')  //deposit
    {
        balance=balance+amount;
        deposits=deposits+amount;
        numtransactions++;
    }
    else if (type=='W')  //withdrawal
    {
        balance=balance-amount;
        withdrawals=withdrawals+amount;
        numtransactions++;
    }
}
void CheckingAccount::calcInterest()
{
}





SavingsAccount::SavingsAccount(char n[50], int anumber, char atype, double bal, int numtran, double i): Account(n, anumber, 'S', bal, numtran)
{
    interestrate=i;
    deposits=0;
    withdrawals=0;
}
double SavingsAccount::getDeposits()
{
    return deposits;
}
void SavingsAccount::setDeposits(double x)
{
    deposits=x;
}
double SavingsAccount::getWithdrawals()
{
    return withdrawals;
}
void SavingsAccount::setWithdrawals(double x)
{
    withdrawals=x;
}
double SavingsAccount::getInterestRate()
{
    return interestrate;
}
void SavingsAccount::setInterestRate(double x)
{
    interestrate=x;
}
void SavingsAccount::transaction(double amount,char type)
{
    if (type=='D')  //deposit
    {
        balance=balance+amount;
        deposits=deposits+amount;
        numtransactions++;
    }
    else if (type=='W')  //withdrawal
    {
        balance=balance-amount;
        withdrawals=withdrawals+amount;
        numtransactions++;
    }
}
void SavingsAccount::calcInterest()
{
    double x= (interestrate*balance)/400;
    transaction(x,'D');
}






CreditCardAccount::CreditCardAccount(char n[50], int anumber, char atype, double bal, int numtran, double clim, double i): Account(n,anumber,'A',bal,numtran)
{
    creditlimit=clim;
    interestrate=i;
    payments=0;
    usage=0;
}
double CreditCardAccount::getCreditLimit()
{
    return creditlimit;
}
void CreditCardAccount::setCreditLimit(double x)
{
    creditlimit=x;
}

double CreditCardAccount::getInterestRate()
{
    return interestrate;
}
void CreditCardAccount::setInterestRate(double x)
{
    interestrate=x;
}

double CreditCardAccount::getPayments()
{
    return payments;
}
void CreditCardAccount::setPayments(double x)
{
    payments=x;
}

double CreditCardAccount::getUsage()
{
    return usage;
}
void CreditCardAccount::setUsage(double x)
{
    usage=x;
}
void CreditCardAccount::transaction(double amount,char type)
{
    int newbalance=0;
    if (type=='U')  //card use
    {
        newbalance=balance+amount;
        
        if (newbalance<=creditlimit)
        {
            balance=balance+amount;
            usage=usage+amount;
            numtransactions++;
        }
    }
    else if (type=='P')  //payment
    {
        newbalance=balance-amount;
        
        if (newbalance>=0)
        {
            balance=balance-amount;
            payments=payments+amount;
            numtransactions++;
        }
    }
}
void CreditCardAccount::calcInterest()
{
    double x= balance * (pow (( 1 + (interestrate/400)) , 4)) - balance;
    
    balance=balance+x;
    usage=usage+x;
    numtransactions++;
}




AccountList::AccountList()
{
    size=0;
    accarray=new Account*[size];
}
AccountList::~AccountList()
{
    *accarray=NULL;
    for (int i=0;i<size;i++)
    {
        delete[] accarray[i];
    }
    delete[] accarray;
    size=0;
}
bool AccountList::importFile(char *n)
{
    Account **temp=new Account*[size];
    
    for (int i=0;i<size;i++)
    {
        temp[i]=accarray[i];
    }
    int oldsize=size;
    
    ifstream infile;
    infile.open(n);
    
    if (infile)
    {
        infile>>size;
        *accarray=new Account[size+oldsize];
        int transacs;
        infile>>transacs;
        infile.ignore();
        for (int i=oldsize;i<oldsize+size;i++)
        {
            char x[50];
            infile.getline(x,50,',');
            int acnum;
            infile>>acnum;
            infile.ignore();
            char actype;
            infile>>actype;
            infile.ignore();
            double bal;
            infile>>bal;
            infile.ignore();
            
            double irate,climit;
                if (actype=='C')    //checking
                {
                    accarray[i]= new CheckingAccount(x,acnum,actype,bal,0);
                }
                    
                if (actype=='A')    //credit card
                {
                    infile>>irate;
                    infile.ignore();
                    infile>>climit;
                    infile.ignore();
                    accarray[i]= new CreditCardAccount(x, acnum,actype,bal,0,climit,irate);
                }
                    
                if (actype=='S')    //savings
                {
                    infile>>irate;
                    infile.ignore();
                    accarray[i]=new SavingsAccount(x,acnum,actype,bal,0,irate);
                }
        }
        
        for (int i=oldsize;i<oldsize+transacs;i++)
        {
            int acnum;
            char transtype;
            double amount;
            infile>>acnum;
            infile.ignore();
            infile>>transtype;
            infile.ignore();
            infile>>amount;
            
            for (int j=oldsize;j<oldsize+size;j++)
            {
                if (accarray[j]->getAccnumber()==acnum)
                {
                    accarray[j]->transaction(amount,transtype);
                }
            }
        }
        for (int i=0;i<oldsize;i++)
        {
            accarray[i]=temp[i];
        }
        size=size+oldsize;
        return true;
    }
    else
    {
        return false;
    }
}
bool AccountList::createReportFile(char *n)
{
    ofstream outfile;
    outfile.open(n);
    
    if (outfile)
    {
        outfile<<"Checking Accounts"<<endl;
        outfile<<"                       Name           Accno        Balance        NumTrans         Deposits       Withdrawals"<<endl;
        outfile<<"-------------------------------------------------------------------------------------------------------------"<<endl;
        for (int i=0;i<size;i++)
        {
            if (accarray[i]->getAcctype()=='C')
            {
                outfile<<setw(30)<<accarray[i]->getName()<<right;
                outfile<<setw(15)<<internal<<accarray[i]->getAccnumber()<<right;
                outfile<<setw(15)<<accarray[i]->getBalance()<<right;
                outfile<<setw(15)<<accarray[i]->getNumtransactions()<<right;
                outfile<<setw(15)<<accarray[i]->getDeposits()<<right;
                outfile<<setw(15)<<accarray[i]->getWithdrawals()<<right<<endl;
            }
        }
        outfile<<endl<<endl;
        outfile<<"Savings Accounts"<<endl;
        outfile<<"                       Name           Accno        Balance        NumTrans         Deposits       Withdrawals"<<endl;
        outfile<<"-------------------------------------------------------------------------------------------------------------"<<endl;
        for (int i=0;i<size;i++)
        {
            if (accarray[i]->getAcctype()=='S')
            {
                outfile<<setw(30)<<accarray[i]->getName()<<right;
                outfile<<setw(15)<<internal<<accarray[i]->getAccnumber()<<right;
                outfile<<setw(15)<<accarray[i]->getBalance()<<right;
                outfile<<setw(15)<<accarray[i]->getNumtransactions()<<right;
                outfile<<setw(15)<<accarray[i]->getDeposits()<<right;
                outfile<<setw(15)<<accarray[i]->getWithdrawals()<<right<<endl;
            }
        }
        outfile<<endl<<endl;
        outfile<<"Credit Card Accounts"<<endl;
        outfile<<"                       Name           Accno        Limit        Balance         NumTrans       Payments       Usage"<<endl;
        outfile<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
        for (int i=0;i<size;i++)
        {
            if (accarray[i]->getAcctype()=='A')
            {
                outfile<<setw(30)<<accarray[i]->getName()<<right;
                outfile<<setw(15)<<internal<<accarray[i]->getAccnumber()<<right;
                outfile<<setw(15)<<accarray[i]->getCreditLimit()<<right;
                outfile<<setw(15)<<accarray[i]->getBalance()<<right;
                outfile<<setw(15)<<accarray[i]->getNumtransactions()<<right;
                outfile<<setw(15)<<accarray[i]->getPayments()<<right;
                outfile<<setw(15)<<accarray[i]->getUsage()<<right<<endl;
            }
        }
        outfile.close();
        return true;
    }
    else
    {
        return false;
    }
}

void AccountList::showList()
{
    cout<<"Checking Accounts"<<endl;
    cout<<"                       Name           Accno        Balance        NumTrans                                   "<<endl;
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
    for (int i=0;i<size;i++)
    {
        if (accarray[i]->getAcctype()=='C')
        {
            cout<<setw(30)<<accarray[i]->getName()<<right;
            cout<<setw(15)<<internal<<accarray[i]->getAccnumber()<<right;
            cout<<setw(15)<<accarray[i]->getBalance()<<right;
            cout<<setw(15)<<accarray[i]->getNumtransactions()<<right<<endl;
        }
    }
    cout<<endl<<endl;
    cout<<"Savings Accounts"<<endl;
    cout<<"                       Name           Accno        Balance        NumTrans                                   "<<endl;
    cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
    for (int i=0;i<size;i++)
    {
        if (accarray[i]->getAcctype()=='S')
        {
            cout<<setw(30)<<accarray[i]->getName()<<right;
            cout<<setw(15)<<internal<<accarray[i]->getAccnumber()<<right;
            cout<<setw(15)<<accarray[i]->getBalance()<<right;
            cout<<setw(15)<<accarray[i]->getNumtransactions()<<right<<endl;
        }
    }
    cout<<endl<<endl;
    cout<<"Credit Card Accounts"<<endl;
    cout<<"                       Name           Accno        Balance         NumTrans                                        "<<endl;
    cout<<"-------------------------------------------------------------------------------------------------------------------"<<endl;
    for (int i=0;i<size;i++)
    {
        if (accarray[i]->getAcctype()=='A')
        {
            cout<<setw(30)<<accarray[i]->getName()<<right;
            cout<<setw(15)<<internal<<accarray[i]->getAccnumber()<<right;
            cout<<setw(15)<<accarray[i]->getBalance()<<right;
            cout<<setw(15)<<accarray[i]->getNumtransactions()<<right<<endl;
        }
    }
}
void AccountList::calcInterest()
{
    for (int i=0;i<size;i++)
    {
        accarray[i]->calcInterest();
    }
}






