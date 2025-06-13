/* *~*~*
 Name: Chu Jia Xian
======================================== 
 Implementation file for the Heap class: 
 min-heap of integers
*~**/

#include "Heap.h"

/*  
 The private member function _reHeapUp rearranges the heap after insert by moving the
 last item up to the correct location in the heap
*/
void Heap::_reHeapUp(int lastndx)
{
    int parent = _findParent(lastndx);
    // if not at root and child is smaller than parent, swap and keep going up
    if (parent != -1 && heapAry[lastndx] < heapAry[parent])
    {
        int tmp = heapAry[lastndx];
        heapAry[lastndx] = heapAry[parent];
        heapAry[parent]  = tmp;
        _reHeapUp(parent);
    }
}

/*  
 The private member function _reHeapDown rearranges the heap after delete by moving the
 data in the root down to the correct location in the heap
*/
void Heap::_reHeapDown(int rootdex)
{
    int left = _findLeftChild(rootdex);
    if (left != -1) // there is at least a left child
    {
        int right = _findRightChild(rootdex);
        // pick the smaller child
        int smallerChild = left;
        if (right != -1 && heapAry[right] < heapAry[left])
            smallerChild = right;

        // if root is larger than that child, swap and recurse down
        if (heapAry[rootdex] > heapAry[smallerChild])
        {
            int tmp = heapAry[rootdex];
            heapAry[rootdex]        = heapAry[smallerChild];
            heapAry[smallerChild]   = tmp;
            _reHeapDown(smallerChild);
        }
    }
}

/*  
 The public member function insertHeap inserts a new item into a heap.
 It calls _reheapUp.
*/
bool Heap::insertHeap(int newItem)
{
	if (isFull())
        return false;

    // place at end, bubble up, then increment count
    heapAry[count] = newItem;
    _reHeapUp(count);
    ++count;
    return true;
}

/*  
 The public member function deleteHeap deletes the root of the heap and
 passes back the root's data. It calls _reheapDown.
*/
bool Heap::deleteHeap(int &returnItem)
{
    if (isEmpty())
        return false;

    // take out the minimum
    returnItem = heapAry[0];
    // move last into root, shrink, then push it down
    heapAry[0] = heapAry[count - 1];
    --count;
    _reHeapDown(0);
    return true;
}cd