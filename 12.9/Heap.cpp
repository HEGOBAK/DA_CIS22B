/* *~*~*
 Name: Chu Jia Xian
======================================
 Implementation file for the Heap class: 
 min- or max-heap of integers
*~**/

#include "Heap.h"

/*  
 The private member function _reHeapUp rearranges the heap after insert by moving the
 last item up to the correct location in the heap
*/
void Heap::_reHeapUp(int lastndx, bool (*compare)(int, int))
{
    int parent = _findParent(lastndx);
    if (parent != -1 && compare(heapAry[lastndx], heapAry[parent]))
    {
        int tmp = heapAry[lastndx];
        heapAry[lastndx] = heapAry[parent];
        heapAry[parent] = tmp;
		_reHeapUp(parent, compare);
    }
}

/* 
 The private member function _reHeapDown rearranges the heap after delete by moving the
 data in the root down to the correct location in the heap
*/
void Heap::_reHeapDown(int rootndx, bool (*compare)(int, int))
{
    int left = _findLeftChild(rootndx);
    if (left == -1) 
        return;

    int right = _findRightChild(rootndx);
    int bestChild = left;

    if (right != -1 && compare(heapAry[right], heapAry[left]))
        bestChild = right;

    if (compare(heapAry[bestChild], heapAry[rootndx]))
    {
        int tmp = heapAry[rootndx];
        heapAry[rootndx] = heapAry[bestChild];
        heapAry[bestChild] = tmp;
		        _reHeapDown(bestChild, compare);
    }
}

/* 
 The public member function insertHeap inserts a new item into a heap.
 It calls _reheapUp.
*/
bool Heap::insertHeap(int itemIn, bool (*compare)(int, int))
{
    if (isFull()) 
        return false;

    heapAry[count] = itemIn;
    _reHeapUp(count, compare);
    ++count;
    return true;
}

/* 
 The public member function deleteHeap deletes the root of the heap and
 passes back the root's data. It calls _reheapDown.
*/
bool Heap::deleteHeap(int &itemOut, bool (*compare)(int, int))
{
    if (isEmpty()) 
        return false;

    itemOut      = heapAry[0];
    heapAry[0]   = heapAry[count - 1];
    --count;
    _reHeapDown(0, compare);
    return true;
}