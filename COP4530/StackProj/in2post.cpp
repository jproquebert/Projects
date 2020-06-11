/*
 Jean Roquebert
 COP4530
 Fall 2019
 due oct 29, 2019
 in2post.cpp, project #3
 */

#include "stack.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;
using namespace cop4530;


bool isNumber(char a)
{
    if (isdigit(a))
        return true;
    else
        return false;
}

bool isVariable(char a)
{
    if (isalpha(a))
        return true;
    else
        return false;
}

bool isOperator(char a)
{
    if (a == '+' || a == '-' || a == '*' || a == '/' || a == '(' || a == ')')
    {
        return true;
    } else
        return false;
}

bool mathOperator(char a)
{
    if (a == '+' || a == '-' || a == '*' || a == '/' )
    {
        return true;
    } else
        return false;
}

/* check if string contains a letter variable*/
bool checkforvariable(string postfix)
{
    for(int i = 0;i< postfix.length();i++)
    {
        if(isVariable(postfix[i]) == true)
        {
            return true;
        }
    }
    return false;
}


/*  hierarchy of operators  */
int opweight(char op)
{
    int weight = 0;
    switch(op)
    {
        case '+':
            weight = 1;
            break;
        case '-':
            weight = 1;
            break;
        case '*':
            weight = 2;
            break;
        case '/':
            weight = 2;
            break;
    }
    return weight;
}



/* calculates mathematical results */
double Evaluate(string expression)
{
    Stack<double> S;
    double operand1,operand2;
    string temp="";
    double result = 0;
    
    for(int i = 0;i< expression.length();i++)
    {
        if (isOperator(expression[i]))
        {
            operand2 = S.top();
            S.pop();
            operand1 = S.top();
            S.pop();
            
            
            if(expression[i] == '*')
            {
                result = operand1 * operand2;
            }
            else if(expression[i] == '-')
            {
                result = operand1 - operand2;
            }
            else if(expression[i] == '+')
            {
                result = operand1 + operand2;
            }
            else if(expression[i] == '/')
            {
                result = operand1 / operand2;
            }
            else
            {
                cout<<"Error"<<endl;
            }
            
            S.push(result);
        }
        
        else if(isNumber(expression[i]))
        {
            
            int operand = 0;
            while(i<expression.length() && isNumber(expression[i]))
            {
                operand = (operand*10) + (expression[i] - '0');
                i++;
            }
            i--;
            S.push(operand);
        }
        
        else if(isspace(expression[i]))
            continue;
        
    }
    return S.top();
}



/* converting infix to postfix stack */
string infixToPostfix(const string& infix)
{
    unsigned long size = infix.size();
    char temp[size];
    strncpy(temp, infix.c_str(), sizeof(temp));
    char postfix[strlen(temp)];
    
    Stack<char> s;
    int k = 0;
    char ch;
    
    for (int i = 0; i < infix.size(); i++)
    {
        ch = temp[i];
        if (ch == '(')
        {
            s.push(ch);
            continue;
        }
        else if (ch == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                postfix[k++] = s.top();
                postfix[k++] = ' ';
                s.pop();
            }
            
            if (!s.empty())
            {
                s.pop();
            }
            
            continue;
        }
        else if (opweight(ch) == 0)   /* not + - * or / */
        {
            postfix[k++] = ch;
        }
        else
        {
            if (s.empty())
            {
                s.push(ch);
            }
            else
            {
                while (!s.empty() && s.top() != '(' && opweight(ch) <= opweight(s.top()))
                {
                    postfix[k++] = s.top();
                    postfix[k++] = ' ';
                    s.pop();
                }
                
                s.push(ch);
            }
        }
    }
    while (!s.empty())
    {
        postfix[k++] = s.top();
        s.pop();
    }
    postfix[k] = '\0';
    string postfixStr = postfix;
    return postfixStr;
}



/* checks for format errors */
bool CheckFormat(string& infix)
{
    int front=0,back=0, ops=0, operand=0;
    for (int i=0; i<infix.size(); i++)
    {
        if(infix[i]=='(')
            front++;
        else if(infix[i]==')')
            back++;
        else if(infix[i]=='*' || infix[i]=='/' || infix[i]=='+' || infix[i]=='-')
            ops++;
        else if(isalnum(infix[i]))
        {
            operand++;
            while(i < infix.size() && !isspace(infix[i]))
            {i++;}
        }
        
        if(back>0 && front==0)
        {
            /* ) without a ( before it  */
            cout<<"Error: cannot find a matching (."<<endl;
            cout<<"Found in input: "<<infix<<endl;
            return false;
        }
    }
    
    
    if (infix[infix.size()-1]=='(')
    {
        /*  ending with a (  */
        cout<<"Error Deck top=("<<endl;
        cout<<"Found in input: "<<infix<<endl;
        return false;
    }
    
    else if(back>front)
    {
        /*  ) without a closing ( */
        cout<<"Error: cannot find a matching (."<<endl;
        cout<<"Found in input: "<<infix<<endl;
        return false;
    }
    else if(front>back)
    {
        /*  ( without a closing ) */
        cout<<"Error: cannot find a matching )."<<endl;
        cout<<"Found in input: "<<infix<<endl;
        return false;
    }
    
    for (int i=0;i<infix.length();i++)
    {
        if (mathOperator(infix[i]) && mathOperator(infix[2+i]))
        {
            /*  consecutive opcodes    */
            cout<<"Consective Opcodes: "<<infix[i]<<" "<<infix[i+2]<<endl;
            cout<<"Found in input: "<<infix<<endl;
            return false;
        }
        if (isNumber(infix[i]) && infix[i+2]=='(')
        {
            /*  number followed by (    */
            if (isNumber(infix[i-1]))
            {
                cout<<"Number (: "<<infix[i-1]<<""<<infix[i]<<" "<<infix[i+2]<<endl;
            }
            else
            {
                cout<<"Number (: "<<infix[i]<<" "<<infix[i+2]<<endl;
            }
            cout<<"Found in input: "<<infix<<endl;
            return false;
        }
        else if (infix[i]=='(' && infix[i+2]==')')
        {
            /*  empty () set    */
            cout<<"Error: cannot have an opcode or ( before )."<<endl;
            cout<<"Found in input: "<<infix<<endl;
            return false;
        }
    }
    if (mathOperator(infix[0]))
    {
        /*  first character is an operator with less than 2 operands   */
        cout<<"Operator ["<<infix[0]<<"] Only has one operand"<<endl;
        cout<<"Found in input: "<<infix<<endl;
        return false;
    }
    
    
    if(ops+1!=operand)
    {
        if (mathOperator(infix[infix.size()-1]))
        {
            /*  operator at the end */
            cout<<"Operator ["<<infix[infix.size()-1]<<"] Only has one operand"<<endl;
            cout<<"Found in input: "<<infix<<endl;
            return false;
        }
    }
    
    int k=0;
    for (int i=0;i<infix.length();i++)
    {
        /*  consecutive numbers */
        if(isNumber(infix[i]) && isNumber(infix[i+2]))
        {
            if (isNumber(infix[i-1]))
            {
                k++;
                cout<<"Consective Numbers: "<<infix[i-1]<<infix[i]<<infix[i+1]<<infix[i+2]<<endl;
            }
            else
            {
                k++;
                cout<<"Consective Numbers: "<<infix[i]<<infix[i+1]<<infix[i+2]<<endl;
            }
            
        }
        
        if (i==infix.length()-1)
        {
            if (k>0)
            {
                cout<<"Found in input: "<<infix<<endl;
                return false;
            }
            
        }
    }
    
    if(back!=front)
        return false;
    

    return true;
}


int main()
{
    string input,postfix;
    string result1;
    ifstream inFile;
    string filename;
    
    cout<<"\nEnter file name: ";
    getline(cin, filename);
    
    inFile.open(filename);
    
    
    if (!inFile)
    {
        cerr << "Unable to open file " <<filename;
        exit(1);   /* call system to stop   */
    }
    
    while(getline(inFile,input))
    {
        if(CheckFormat(input)==false)
        {
            if (inFile.fail())
            {
                break;
            }
            cout<<"Format Error"<<endl<<endl<<endl;  /*: Infix expression: "<<input<<" has format errors and cannot be converted\n"<<endl<<endl;*/
        }
        else
        {
            string post = infixToPostfix(input);
            
            for (signed long i = post.size() - 1; i >= 0; i--)
            {
                if (post[i] == ' ' && post[i] == post[i - 1])
                {
                    post.erase(post.begin() + i);
                }
            }
            cout<<post;
            
            if (checkforvariable(post) == true)
            {
                /*  print entire postfix format equation if it contains a variable */
                result1 = post;
                cout <<endl<<"postfix evaluation: "<<" = \n"<< result1 << endl<<endl;
            }
            else
            {
                /*  print the result if postfix contains NO variables   */
                 cout <<endl<<"Postfix evaluation: "<<" = \n" << Evaluate(post) << endl<<endl;
            }
        }
    }
    
    inFile.close();
}


