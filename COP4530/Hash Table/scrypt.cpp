/*
 Project 5
 Jean Roquebert
 COP4530
 scrypt.cpp
 nov 29, 2019
 fall 2019
 */

#include <iostream>
#include <utility>
#include <unistd.h>
#include <string>
#include <cstring>
#include <stdlib.h>

using namespace std;

int main()
{
   pair <string, string> p;
   char salt[] = "$1$########";
   string key = "Rumpelstilskin";

   char * password = new char [100];
   strcpy ( password, crypt(key.c_str(), salt));
   cout << "Plaintext = " << key << endl;
   cout << "Encrypted = " << password << endl;
   delete [] password;
   return 0;
}

