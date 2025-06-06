/**~*~*~* 
 Implementation file for the Hash class
===========================================
Name: Chu Jia Xian
IDE:
*~*/

#include <string>

#include "HashTable.h"

using namespace std;

/*
  A simple hash function 
*/
int HashTable::_hash(const string &key) const
{
    int size = key.size();
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += key[i];
    return sum % hashSize;
}


/*
  hash insert - linear probe
     - returns false if the hash table is full
     - returns true if itemIn is inserted into the hash table
*/
bool HashTable::insert(const Student &itemIn)
{
    if (count == hashSize) {
        // table is full
        return false;
    }

    const string key    = itemIn.getName();
    int         hashCode = _hash(key);

    // Probe until we find a bucket that is not occupied (i.e. occupied != 1).
    // occupied == 0 (empty-since-start) or occupied == -1 (tombstone) both count as free.
    for (int i = 0; i < hashSize; ++i) {
        int idx = (hashCode + i) % hashSize;
        int occ = hashAry[idx].getOccupied();

        if (occ != 1) {
            // We found a free bucket (either never-used or a tombstone).
            hashAry[idx].setItem(itemIn);
            hashAry[idx].setOccupied(1);
            hashAry[idx].setCollisions(i);
            ++count;
            return true;
        	}
        // Otherwise (occ == 1), keep probing
    	}

    // We probed every slot and found none free.
    return false;
}

/* 
   hash delete - linear probe
   - looks for key in hash table
   - if found:
       - copies its data to itemOut 
       - replaces data in the hash node with an "empty-after-delete" record
       - returns true
   - if not found - returns false
*/
bool HashTable::remove(Student &itemOut, string key)
{
    int hashCode = _hash(key);

    for (int i = 0; i < hashSize; ++i) {
        int idx = (hashCode + i) % hashSize;
        int occ = hashAry[idx].getOccupied();

        // Case A: truly never-used spot => key cannot be in table
        if (occ == 0) {
            return false;
        }

        // Case B: occupied and not yet deleted => check for match
        if (occ == 1) {
            if (hashAry[idx].getItem().getName() == key) {
                // copy the Student out
                itemOut = hashAry[idx].getItem();

                // mark as a tombstone
                hashAry[idx].setOccupied(-1);
                hashAry[idx].setCollisions(0);
                --count;
                return true;
            }
        }

        // If occ == -1 (tombstone), keep probing past it
    }

    // Entire table probed; key not found
    return false;
}

/*
   hash search - linear probe
   if found: 
      - copy data to itemOut
      - returns the number of collisions for this key 
   if not found, returns -1
*/
int HashTable::search(Student &itemOut, string key) const
{
   /* write your code here */
	int hashCode = _hash(key);

    for (int i = 0; i < hashSize; ++i) {
        int idx = (hashCode + i) % hashSize;
        int occ = hashAry[idx].getOccupied();

        // If this bucket was never used, key is not in table
        if (occ == 0) {
            return -1;
        }

        // If occupied, check for match
        if (occ == 1) {
            if (hashAry[idx].getItem().getName() == key) {
                itemOut = hashAry[idx].getItem();
                return hashAry[idx].getCollisions();
            }
        }
        // If occ == -1 (tombstone), or occupied but name != key, keep probing
    }

    // full loop without finding => not found
    return -1;
}
