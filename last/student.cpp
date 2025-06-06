// Implementation file for the Student class

#include<string>
#include "Student.h"

/*
 Hash function: takes the key and the size of the hash table, and calculates and 
 returns the index in the hash table.
*/
int key_to_index(const Student &key, int size)
{
    string k = key.getName();
    int keySize = k.size();
    int sum = 0;
    for (int i = 0; i < keySize; i++)
        sum += k[i];
    return sum % size;
}
