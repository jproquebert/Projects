/*
 Project 5
 Jean Roquebert
 COP4530
 pass_server.h
 nov 29, 2019
 fall 2019
 */

#ifndef PASS_SERVER_H
#define PASS_SERVER_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>

#include "hashtable.h"
 
using namespace cop4530;

template <typename K, typename V>
class PassServer : public HashTable <K, V>
{
   public:
    PassServer(int size = 101);
    ~PassServer();
    bool load(const char *filename);
    bool addUser(std::pair<string, string> & kv);
    bool addUser(std::pair<string,string> && kv);
    bool removeUser(const string & k);
    bool changePassword(const pair<string, string> &p, const string & newpassword);
    bool find(const string & user) const;
    void dump();
    size_t size() const;
    bool write_to_file(const char *filename) const;

   private:
    
    typename HashTable<string,string>::HashTable<string,string>* server;
    string encrypt(const string & str);
};

#endif
