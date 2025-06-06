/**~*~*~* 
 Specification file for the HashNode class
====================================================
Name: Chu Jia Xian
IDE:
*~*/

#ifndef _HASH_NODE
#define _HASH_NODE

// To do: convert to a template

template<typename ItemType>
class HashNode
{
private:
    ItemType item;
    int occupied;    // 1 -> occupied, 0 -> empty from start, -1 -> empty after removal 
    int collisions;  // number of collisions 

public:
    // constructors
    HashNode() {occupied = 0; collisions = 0;}
    HashNode(const ItemType &anItem) {item = anItem; occupied = 1; collisions = 0;}
    HashNode(const ItemType &anItem, int ocp, int nCol)
             {item = anItem; occupied = ocp; collisions = nCol;}
    // setters
    void setItem(const ItemType & anItem) {item = anItem;}
    void setOccupied(int ocp) {occupied = ocp;}
    void setCollisions(int nCol) {collisions = nCol;}
    
    // getters
    ItemType getItem() const {return item;}
    int getOccupied() const {return occupied;}
    int getCollisions() const {return collisions;}
};

#endif
