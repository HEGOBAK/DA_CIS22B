/**~*~*~* 
 Specification file for the Hash class
====================================================
Name: Chu Jia Xian
IDE:
*~*/


#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "HashNode.h"

template<typename ItemType>
class HashTable
{
private:
	HashNode<ItemType>* hashAry;
	int hashSize; // size of the hash table 
    int count;    // number of data items stored in the hash table
	
public:
	HashTable() { count = 0; hashSize = 53; hashAry = new HashNode<ItemType>[hashSize]; }
	HashTable(int n)	{ count = 0; hashSize = n;	hashAry = new HashNode<ItemType>[hashSize]; }
	~HashTable(){ delete [] hashAry; }

	int getCount() const	{ return count; }
   int getSize() const { return hashSize; }
   double getLoadFactor() const {return 100.0 * count / hashSize; }
   bool isEmpty() const	{ return count == 0; }
   bool isFull()  const	{ return count == hashSize; }
    
   bool insert(const ItemType &itemIn, int h(const ItemType &key, int size) );
   bool remove(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size));
   int  search(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size)) const;
};

/*
   Insert an item into the hash table
   It does not reject duplicates
*/
template<typename ItemType>
bool HashTable<ItemType>::insert( const ItemType &itemIn, int h(const ItemType &key, int size) )
{
    if ( count == hashSize)
        return false;
    
    /* Write your code here */
   
    // Compute initial index
    int hashCode = h(itemIn, hashSize);

    // Probe up to hashSize slots
    for (int i = 0; i < hashSize; ++i) {
        int idx = (hashCode + i) % hashSize;
        int occ = hashAry[idx].getOccupied();

        // If not occupied (either 0 or -1), place new item here
        if (occ != 1) {
            hashAry[idx].setItem(itemIn);
            hashAry[idx].setOccupied(1);
            hashAry[idx].setCollisions(i);
            ++count;
            return true;
        }
        // else (occ == 1), keep probing
    }

    // No free slot found
    return false;
}

/*
   Removes the item with the matching key from the hash table
   if found:
     - copies data in the hash node to itemOut
     - replaces data in the hash node with an empty record (occupied = -1: deleted!)
     - returns true
   if not found:
     - returns false
*/
template<typename ItemType>
bool HashTable<ItemType>::remove( ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size))
{
    /* Write your code here */
    int hashCode = h(key, hashSize);

    for (int i = 0; i < hashSize; ++i) {
        int idx = (hashCode + i) % hashSize;
        int occ = hashAry[idx].getOccupied();

        // If we hit an empty-from-start, key not in table
        if (occ == 0) {
            return false;
        }

        // If bucket is occupied, check
        if (occ == 1) {
            if (hashAry[idx].getItem() == key) {
                // Found it: copy it out
                itemOut = hashAry[idx].getItem();

                // Mark as empty-after-removal
                hashAry[idx].setOccupied(-1);
                hashAry[idx].setCollisions(0);
                --count;
                return true;
            }
        }
        // If occ == -1, continue probing
    }

    // Probed entire table; not found
    return false;
}

/*
   hash search - linear probe
   if found:
      - copy data to itemOut
      - returns the number of collisions for this key
   if not found, returns -1
*/
template<typename ItemType>
int HashTable<ItemType>::search(ItemType &itemOut, const ItemType &key, int h(const ItemType &key, int size)) const
{
   
    /* Write your code here */
    int hashCode = h(key, hashSize);

    for (int i = 0; i < hashSize; ++i) {
        int idx = (hashCode + i) % hashSize;
        int occ = hashAry[idx].getOccupied();

        // If bucket is empty-from-start, key not in table
        if (occ == 0) {
            return -1;
        }

        // If bucket is occupied, check
        if (occ == 1) {
            if (hashAry[idx].getItem() == key) {
                itemOut = hashAry[idx].getItem();
                return hashAry[idx].getCollisions();
            }
        }
        // If occ == -1, keep probing
    }

    // Probed entire table; not found
    return -1;
}

#endif // HASHTABLE_H_
