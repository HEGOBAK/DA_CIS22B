/**~*~*~* 
 Hashing - Linear Probe: insert, search, and delete 
====================================================
Name: Chu Jia Xian
IDE:
*~*/

#include <iostream>
#include <sstream>

#include "HashTable.h"

using namespace std;

void buildHash(HashTable &hash);
void searchManager(const HashTable &hash);
void deleteManager(HashTable &hash);
void insertManager(HashTable &hash);

int main()
{
    HashTable hash;
    
    buildHash(hash);
    cout << "Load Factor: " << hash.getLoadFactor() << endl;    
    searchManager(hash);
    deleteManager(hash);
    insertManager(hash);
    
    return 0;
}

/* 
This function builds a hash table with data from an array
It calls the insert() function that inserts the new data at the right location in the hash table.
*/
void buildHash(HashTable &hash)
{
    
    Student list[] = {{"Tom", 2.5}, {"Bob", 3.2}, {"Boc", 3.2}, {"Linda", 3.9}, {"Tim", 4.0},
        {"Vic", 3.9}, {"Ann", 3.5}, {"Dylan", 3.1}, {"obB", 2.2}, {"oBb", 3.7},
        {"Bbo", 3.3}, {"bBo", 3.9}, {"boB", 2.3}, {"", 0}};
   
    for (int i = 0; list[i].getName() != ""; i++)
    {
		hash.insert(list[i]);
        /* insert list[i] into the hash table: call hash insert  */ 
    }
   
}

/*
This function searches a hash table with user provided data.
It calls the hash search function in a loop.
To stop searching enter "#"
*/
void searchManager(const HashTable &hash)
{
   cout << endl << "~*~ Test Search ~*~" << endl;
   cout << "Enter name [# to stop searching]:" << endl;
   string name;
   getline(cin, name);
   while (name != "#")
   {
        Student item;
        int nc = hash.search(item, name);
        if (nc != -1)
        {
            cout << item.getName() << " " << item.getGpa() << " (" << nc << " collisions!)" << endl;
        }
        else
        {
            cout << name << " not found!" << endl;
        }
        getline(cin, name);
    }
}

/*
This function deletes user provided data data from a hash table
It calls the hash delete function in a loop.
To stop deleting enter "#"
*/
void deleteManager(HashTable &hash)
{
   cout << endl << "~*~ Test Delete ~*~" << endl;
   cout << "Enter name [# to stop deleting]:" << endl;
   string name;
   getline(cin, name);
   while (name != "#")
   {
        Student itemOut;
        if (hash.remove(itemOut, name))
        {
            cout << itemOut.getName() << " " << itemOut.getGpa() << " - deleted!" << endl;
        }
        else
        {
            cout << name << " not found!" << endl;
        }
        cout << "Load Factor: " << hash.getLoadFactor() << endl;
        getline(cin, name);
    }
}

/* 
This function inserts user provided data into the hash table
It rejects duplicates.
It calls hash search and hash insert in a loop.
To stop getting user input enter "#"
*/
void insertManager(HashTable &hash)
{
   cout << endl << "~*~ Test Insert - reject duplicates ~*~" << endl;
   cout << "Enter name [# to stop reading]:" << endl;
   string name;
   getline(cin, name);
   while (name != "#")
   {
        Student found;
        if (hash.search(found, name) != -1)
        {
            cout << "Duplicate key: " << found.getName() << " - rejected!" << endl;
        }
        else
        {
            cout << "Enter gpa:" << endl;
            double gpa;
            cin >> gpa;
            cin.ignore();
            Student newStudent(name, gpa);
            hash.insert(newStudent);
            cout << name << " - inserted (" << hash.search(newStudent, name) << " collisions)" << endl;
        }
        cout << "Load Factor: " << hash.getLoadFactor() << endl;
        cout << "Enter name [# to stop reading]:" << endl;
        getline(cin, name);
    }
}
