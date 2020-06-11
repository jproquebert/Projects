/* accountList.h
 * header file to declare the Account class and derived classes
 * Jean Roquebert - Homework#5
 * Due July 24, 2019
 */


#include <fstream>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

class Account
{
    public:
    Account(char n[50]=" " , int an=0, char at=0, double b=0, int nt=0);
    void shortSummary();
    
    char* getName();
    void setName(char n[50]);
    
    int getAccnumber(); 
    void setAccnumber(int);
    
    char getAcctype();
    void setAcctype(char);
    
    double getBalance();
    void setBalance(double);
    
    int getNumtransactions();
    void setNumtransactions(int);
    
    virtual double getDeposits();
    virtual void setDeposits(double);
    
    virtual double getWithdrawals();
    virtual void setWithdrawals(double);
    
    virtual double getInterestRate();
    virtual void setInterestRate(double);
    
    virtual void transaction(double amount, char type);
    
    virtual double getPayments();
    virtual void setPayments(double);
    
    virtual double getUsage();
    virtual void setUsage(double);
    
    virtual double getCreditLimit();
    virtual void setCreditLimit(double);
    
    virtual void calcInterest();
    
    protected:
        char name[50];
        int accnumber;
        char acctype;
        double balance;
        int numtransactions;
};

class CheckingAccount : public Account
{
    public:
        CheckingAccount(char n[50]=" " , int anumber=0, char atype='C', double bal=0, int numtran=0);
   
        double getDeposits();
        void setDeposits(double);
    
        double getWithdrawals();
        void setWithdrawals(double);
    
        void transaction(double amount,char type);
    
        virtual void calcInterest();
    
    private:
        double deposits, withdrawals;
};

class SavingsAccount : public Account
{
    public:
        SavingsAccount(char n[50]=" " , int anumber=0, char atype='S', double bal=0, int numtran=0, double i=0);
    
        double getDeposits();
        void setDeposits(double);
    
        double getWithdrawals();
        void setWithdrawals(double);
    
        double getInterestRate();
        void setInterestRate(double);
    
        void transaction(double amount,char type);
        void calcInterest();
    
    private:
        double interestrate,deposits,withdrawals;
};

class CreditCardAccount : public Account
{
    public:
        CreditCardAccount(char n[50]=" ", int anumber=0, char atype='A', double bal=0, int numtran=0, double clim=0, double i=0);
    
        double getCreditLimit();
        void setCreditLimit(double);
    
        double getInterestRate();
        void setInterestRate(double);
    
        double getPayments();
        void setPayments(double);
    
        double getUsage();
        void setUsage(double);
    
        void transaction(double amount,char type);
        void calcInterest();
    
    private:
    
        double creditlimit,interestrate,payments,usage;
};



class AccountList
{
    public:
    AccountList();
    ~AccountList();
    bool importFile(char *n);
    bool createReportFile(char *n);
    void showList();
    void calcInterest();
 
    
    private:
        int size;
    Account **accarray;
};


















