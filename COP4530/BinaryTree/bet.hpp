/*
 Project 4
 Jean Roquebert
 COP4530
 bet.h
 nov 12, 2019
 fall 2019
 */

#include <iostream>
#include <stack>
#include <list>



/*      helper functions        */
bool mathOperator(string a)
{
    if (a == "+" || a == "-" || a == "*" || a == "/" )
        return true;
     else
        return false;
}

bool formatCheck(const list<Token>& check)
{
    int operand=0;
    int op=0;
    
    if (mathOperator(check.front().getValue() ) )
        return false;
    
    for (auto i=check.begin();i!=check.end();i++)
    {
        if (mathOperator(i->getValue() ))
            op++;
        else
        {
            while(((i->getValue() )==" " ) && i!=check.end())
                {i++;}
            
            operand++;
        }
        if (op>operand-1)
            return false;
    }
    return true;
    
}

string ListToString(const list<Token>& mylist)
{
    string mystring="";
    auto j=mylist.begin();

    for (int i=0;i<mylist.size();i++)
    {
        if(j!=mylist.end())
        {
            mystring=mystring+j->getValue();
            if (i<mylist.size()-1)
            {
                mystring=mystring+" ";
            }
        }
        j++;
    }
    
    return mystring;
}














/*      public functions        */

template<typename T>
BET<T>::BET()
{
    Node=nullptr;
}
/* default zero-parameter constructor. Builds an empty tree. */


template<typename T>
BET<T>::BET(const list<Token> & postfix)
{
    Node = nullptr;
    buildFromPostfix(postfix);
}
/* one-parameter constructor, where parameter "postfix" is a list representing a postfix expression.
 The tree should be built based on the postfix expression. */


template<typename T>
BET<T>::BET(const BET<T>& rhs)
{
    Node = nullptr;
    Node = clone(rhs.Node);
}
/* copy constructor -- makes appropriate deep copy of the tree */



template<typename T>
BET<T>::~BET()
{
    empty();
}
/* destructor -- cleans up all dynamic space in the tree */





template<typename T>
bool BET<T>::buildFromPostfix(const list<Token> & postfix)
{
    
    Node = nullptr;
    while(!betStack.empty())
        betStack.pop();
    
    std::string post = ListToString(postfix);
    std::string token;
    for(std::string::iterator i = post.begin(); i!= post.end(); ++i)
    {
        token += *i;
        if(*i == ' ' || i == (post.end()-1) || *i == true)
        {
            if(*i == ' ')
                token.pop_back();
            if((token >= "A" && token <= "Z") || (token >= "a" && token <= "z") || (token >= "0" && token <= "9") || (token == "_"))
            {
                BinaryNode *n = new BinaryNode(token,nullptr,nullptr);
                betStack.push(n);
            }
            else if(mathOperator(token))
            {
                
                BinaryNode *rr, *ll;
                if(!betStack.empty()){
                    rr = betStack.top();
                    betStack.pop();
                }
                else
                {
                    return false;
                    break;
                }
                
                if(!betStack.empty())
                {
                    ll = betStack.top();
                    betStack.pop();
                }
                else
                {
                    return false;
                    break;
                }
                BinaryNode *op = new BinaryNode(token,ll,rr);
                betStack.push(op);
            }
            token = "";
        }
    }
    
    Node = betStack.top();
    
    
    
    if((betStack.size() >= 1 && (Node->data >= "A" && Node->data <= "Z")) || (Node->data >= "a" && Node->data <= "z") || (Node->data >= "0" && Node->data <= "9") || (Node->data == "_")){
        std::cout << "Wrong postfix expression" << std::endl;
        if(!empty()){
            Node = nullptr;
            while(!betStack.empty())
                betStack.pop();
        }
    }
    return true;
}
/* parameter "postfix" is a list representing a postfix expression. A tree should be built based on each postfix expression. Tokens in the postfix expression are separated by spaces. If the tree contains nodes before the function is called, you need to first delete the existing nodes. Return true if the new tree is built successfully. Return false if an error is encountered. */



template<typename T>
const BET<T>& BET<T>::operator=(const BET<T>& rhs)
{
    makeEmpty(Node);
    Node = clone(rhs.Node);
    return *this;
}
/*  assignment operator -- makes appropriate deep copy. */


template<typename T>
void BET<T>::printInfixExpression()
{
    printInfixExpression(Node);
    std::cout << std::endl;
}
/*  Print out the infix expression. Should do this by making use of the private (recursive) version */


template<typename T>
void BET<T>::printPostfixExpression()
{
    printPostfixExpression(Node);
    std::cout << std::endl;
}
/*  Print the postfix form of the expression. Use the private recursive function to help    */

template<typename T>
size_t BET<T>::size()
{
    return size(Node);
}
/*  Return the number of nodes in the tree (using the private recursive function)   */

template<typename T>
size_t BET<T>::leaf_nodes()
{
    return leaf_nodes(Node);
}
/*  Return the number of leaf nodes in the tree. (Use the private recursive function to help)  */

template<typename T>
bool BET<T>::empty()
{
    if(Node==nullptr)
        return true;
    
    return false;
}
/*  return true if the tree is empty. Return false otherwise.   */

















/*  private functions   */

template<typename T>
void BET<T>::printInfixExpression(BET::BinaryNode *n)
{
    if(n==nullptr)
        return;
    
    if(n->data == "*" || n->data=="/")
    {
        if(n->left->data=="+" || n->left->data=="-")
        {
            cout<<" (";
            if(n->left != nullptr)
                printInfixExpression(n->left);  
            cout<<" )";
        }
        else
            printInfixExpression(n->left);
        
        cout<<" "<<n->data;
        
        if(n->right->data=="+" || n->right->data=="-")
        {
            cout<<" (";
            if(n->right != nullptr)
                printInfixExpression(n->right);
            cout<<" )";
        }
        else
            printInfixExpression(n->right);
        
    }
    else
    {
        if(n->left != nullptr)
            printInfixExpression(n->left);
        
        cout<<" "<<n->data;
        
        if(n->right != nullptr && !isalnum(n->right->data[0]))
        {
            cout<<" (";
            printInfixExpression(n->right);
            cout<<" )";
        }
        else
            printInfixExpression(n->right);
    }
}
/*  print to the standard output the corresponding infix expression. Note that you may need to add parentheses depending on the precedence of operators. You should not have unnecessary parentheses.   */


template<typename T>
void BET<T>::makeEmpty(BinaryNode* &t)
{
    if(t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t=nullptr;
}
/*  delete all nodes in the subtree pointed to by t.    */


template<typename T>
typename BET<T>::BinaryNode * BET<T>::clone(BinaryNode *t) const
{
    if(t == nullptr)
        return nullptr;
    else
        return new BinaryNode{t->data,clone(t->left),clone(t->right)};
}
/*  clone all nodes in the subtree pointed to by t. Can be called by functions such as the assignment operator=.   */


template<typename T>
void BET<T>::printPostfixExpression(BET<T>::BinaryNode *n)
{
    if(n==nullptr)
        return;
    if(n->left != nullptr)
        printPostfixExpression(n->left);
    if(n->right != nullptr)
        printPostfixExpression(n->right);
    
    cout<< n->data << " ";
}
/*  print to the standard output the corresponding postfix expression.  */


template<typename T>
size_t BET<T>::size(BET<T>::BinaryNode *t)
{
    int count=1;
    if(t==nullptr)
        return 0;
    
    if(t->left != nullptr)
    {
        count+=size(t->left);
        count+=size(t->right);
    }
    return count;
}
/*  return the number of nodes in the subtree pointed to by t.  */


template<typename T>
size_t BET<T>::leaf_nodes(BET<T>::BinaryNode *t)
{
    int count=0;
    if(t==nullptr)
        return 0;
    
    if(t->left==nullptr)
        return 1;
    else
        count+=leaf_nodes(t->left);
    count+=leaf_nodes(t->right);
    
    return count;
}
/*  return the number of leaf nodes in the subtree pointed to by t.   */
