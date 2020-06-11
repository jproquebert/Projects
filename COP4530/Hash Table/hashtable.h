/*
 Project 5
 Jean Roquebert
 COP4530
 hashtable.h
 nov 29, 2019
 fall 2019
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include <string>     /*    string.c_str(), string();  */
#include <algorithm>  /*    std::find  */
#include <functional> /*    std::hash  */
#include <iostream>   /*    std::cout, std::cerr   */
#include <fstream>    /*    ifstream and ofstream  */
#include <string.h>   /*    strcpy, strtok,    */

using namespace std;

/* max_prime is used by the helpful functions provided to you.  */
static const unsigned int max_prime = 1301081;

/* the default_capacity is used if the initial capacity of the underlying vector of the hash table is zero.*/
static const unsigned int default_capacity = 11;

 
/* SeparateChaining Hash table class    */
namespace cop4530
{
template <typename K, typename V>
    class HashTable
    {
    public:
        HashTable(size_t size = 101 ) ;
	    size_t size() const;
        ~HashTable();
        bool contains(const K & x) const;
        bool match(const std::pair<K,V>& kv) const;
        bool insert(const std::pair<K, V> & kv);
        bool insert (std::pair<K, V> && kv);
        bool remove(const K & k);
        void clear();
        bool load(const char* filename);
        void dump() const;
        bool write_to_file(const char *filename) const;

    private:
        size_t currentSize;
        void makeEmpty();
        void rehash();
        size_t myhash(const K& x) const;
        vector<list<pair<K,V> > > theList;
        unsigned long prime_below (unsigned long);
        void setPrimes(vector<unsigned long>&);
        static const unsigned int default_capacity = 11;
        static const unsigned int max_prime = 1301081;
        
        };

} /* end of namespace cop4530   */

#include "hashtable.hpp"

#endif
