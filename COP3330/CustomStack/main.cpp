#include<iostream>
#include<string>
#include "stack.hpp"
using namespace std;
int main()
{
    int intArray[10] = {1,2,1,2,1,1,1,2,2,2};
    char chararray[10] = "(()()()";
    string strArray[10] = {"One","One","Two","Two","One","Two","Two", "One"};
    
    Stack<int> is;
    if(is.balanceStack(intArray,10))
        cout<<"Integer stack is balanced"<<endl;
    else    cout<<"Integer stack not balanced"<<endl;
    
    Stack<char> cs;
    if(cs.balanceStack(chararray,7))
        cout<<"Char stack is balanced"<<endl;
    else    cout<<"Char stack not balanced"<<endl;
    
    Stack<string> ss;
    if(ss.balanceStack(strArray,8))
        cout<<"String stack is balanced"<<endl;
    else    cout<<"String stack not balanced"<<endl;
    return 0;
}
