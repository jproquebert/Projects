/*
 Project 4
 Jean Roquebert
 COP4530
 bet.h
 nov 12, 2019
 fall 2019
 */

#ifndef bet_h
#define bet_h

#include <stack>
#include <list>
#include <string>


template<typename T>
class BET
{
    private:
    
    struct BinaryNode
    {
        string data;
        BinaryNode* left;
        BinaryNode* right;
        BinaryNode(const string & d=string{}, BinaryNode *l=nullptr, BinaryNode *r=nullptr)
        : data{d}, left{l}, right{r} {}
        BinaryNode(string && d, BinaryNode *l = nullptr, BinaryNode *r = nullptr)
        : data{std::move(d)}, left{l}, right{r} {}
    };
    
    public:
    
        BET();
        BET(const list<Token> & postfix);
        BET(const BET<T>&);
        ~BET();
        bool buildFromPostfix(const list<Token> & postfix);
        const BET<T> & operator=(const BET<T> &);
        void printInfixExpression();
        void printPostfixExpression();
        size_t size();
        size_t leaf_nodes();
        bool empty();
    
    
    
    
    private:
    
     void printInfixExpression(BinaryNode *n);
     void makeEmpty(BinaryNode* &t);
     BinaryNode * clone(BinaryNode *t) const;
     void printPostfixExpression(BinaryNode *n);
     size_t size(BinaryNode *t);
     size_t leaf_nodes(BinaryNode *t);
    
    
     stack<BinaryNode*> betStack;
     BinaryNode * Node;
    
};


#include "bet.hpp"
#endif /* bet_h */
