/*
  This program will read integers from the keyboard,
  insert them into a max-heap, and display them as
  they are deleted from the heap.
*/

#include <iostream>
#include "Heap.h"

using namespace std;

int main()
{
	
	Heap heap;
	
	
	// build heap
   int num;
   cout << "Enter integers [0 - to stop]" << endl;
   cin >> num;
   while ( num != 0)
   {
      heap.insertHeap(num);
      cin >> num;
   }

   cout << "Heap capacity: " << heap.getSize() << endl;
   cout << "Heap actual number of elements: " << heap.getCount() << endl;
  
	// print items as they are deleted from the heap (sorted)
   if (heap.isEmpty())
   {
      cout << "N/A";
   }
   while (!heap.isEmpty())
   {
      heap.deleteHeap(num);
      cout << num << " ";
   }
   cout << endl;

	return 0;
}