/*
 Project 5
 Jean Roquebert
 COP4530
 pass_server.cpp
 nov 29, 2019
 fall 2019
 */


#include <vector>
#include <list>
#include <string>     /* string.c_str(), string() */
#include <algorithm>  /* std::find */
#include <functional> /* std::hash */
#include <iostream>   /* std::cout, std::cerr */
#include <fstream>    /* ifstream and ofstream */
#include <string.h>   /* strcpy, strtok, */
#include <unistd.h>   /* crypt() */
#include <stdlib.h>   

#include "hashtable.h"
#include "pass_server.h"

using namespace std;
using namespace cop4530;




/*          public functions            */

template <typename K, typename V>
PassServer<K,V>::PassServer(int size)
{
    server=new HashTable<string,string>(size);
}
/* constructor, create a hash table of the specified size. You just need to pass this size parameter to the constructor of the HashTable. Therefore, the real hash table size could be different from the parameter size (because prime_below() will be called in the constructor of the HashTable). */

template <typename K, typename V>
PassServer<K,V>::~PassServer()
{
    server->clear();
    delete server;
}
/* destructor. You need to decide what you should do based on your design of PassServer (how you develop the adaptor class based on the adaptee HashTable). In essence, we do not want to have memory leak. */

template <typename K, typename V>
bool PassServer<K,V>::load(const char *filename)
{
    return server->load(filename);
}
/* load a password file into the HashTable object. Each line contains a pair of username and encrypted password with a whitespace between the two. */

template <typename K, typename V>
bool PassServer<K,V>::addUser(std::pair<string,  string> & kv)
{
    if(server->contains(kv.first))
        return false;
    kv.second=encrypt(kv.second);
    return server->insert(kv);
}
/* add a new username and password. The password passed in is in plaintext, it should be encrypted before insertion. */

template <typename K, typename V>
bool PassServer<K,V>::addUser(std::pair<string, string> && kv)
{
    if(server->contains(kv.first))
        return false;
    kv.second=encrypt(kv.second);
    return server->insert(kv);
}
/* move version of add User. */

template <typename K, typename V>
bool PassServer<K,V>::removeUser(const string & k)
{
    return server->remove(k);
}
/* delete an existing user with username k. */


template <typename K, typename V>
bool PassServer<K,V>::changePassword(const pair<string, string> &p, const string & newpassword)
{
    pair<string,string> copy =p;
    copy.second=encrypt(copy.second);
    if(server->match(copy) && newpassword!=p.second)
    {
        server->insert(make_pair(p.first,encrypt(newpassword)));
        return true;
    }
    else
        return false;
}
/* change an existing user's password. Note that both passwords passed in are in plaintext. They should be encrypted before you interact with the hash table. If the user is not in the hash table, return false. If p.second does not match the current password, return false. Also return false if the new password and the old password are the same (i.e., we cannot update the password). */


template <typename K, typename V>
bool PassServer<K,V>::find(const string & user) const
{
    return server->contains(user);
}
/* check if a user exists (if user is in the hash table). */


template <typename K, typename V>
void PassServer<K,V>::dump()
{
    server->dump();
}
/* show the structure and contents of the HashTable object to the screen. Same
 format as the dump() function in the HashTable class template. */

template <typename K, typename V>
size_t PassServer<K,V>::size() const
{
   return HashTable<K,V>::size();
}
/*  return the size of the HashTable (the number of username/password pairs in the table). */



template <typename K, typename V>
bool PassServer<K,V>::write_to_file(const char *filename) const
{
    return server->write_to_file(filename);
}
/* save the user name and password combination into a file. Same format as the write_to_file() function in the HashTable class template.
  */















/*          private functions           */
template <typename K, typename V>
string PassServer<K,V>::encrypt(const string& str)
{
    char salt[] = "$1$########";
    char * password = new char [100];
    strcpy(password,crypt(str.c_str(),salt));
    string pass=password;
    pass=pass.substr(11,22);
    return pass;
}








/* XXX: Please keep this line at the very end */
template class PassServer<string, string>;
