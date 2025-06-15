/**~*~*~* 
 Name : Chu Jia Xian
===========================================
 Heaps - ADT: This program will read data about overbooked customers,
 find their priority and serial numbers, build a heap, then display
 customers in priority sequence
*~*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include "Customer.h"
#include "Heap.h"

using namespace std;

/* Write your code here */ 
int compareCustomer(const Customer &a, const Customer &b);

int main()
{
    // Get input file name
    string inputFileName;
    cout << "Input file name: ";
    getline(cin, inputFileName);
    cout << endl;
    
    /* Write your code here */ 
    ifstream in(inputFileName);
    if (!in) {
        cerr << "Cannot open " << inputFileName << endl;
        return 1;
    }

    // read and build heap
    Heap<Customer> heap;
    string line;
    int seqCounter = 1;         // sequence number to track arrival order of customers
    int servedCount = 0;        // how many customers have been served so far

    while (getline(in, line))
    {
        if (line.empty()) continue;

        istringstream iss(line);
        char code;
        iss >> code;
        if (code == 'A')
        {
            int years;
            int mileage;
            string name;

            iss >> years >> mileage;
            getline(iss, name);
            if (!name.empty() && name[0]==' ')  // remove whitespace at the front of the name
                name.erase(0,1);

            Customer c(years, mileage, seqCounter++, name);
            heap.insertHeap(c, compareCustomer);
        }
        else if (code == 'S')
        {
            Customer served;
            if (heap.deleteHeap(served, compareCustomer)) {   // delete the first in priority list
                cout << served << "\n";
                ++servedCount;
            }
        }
    }
    in.close();

    // summary of served
    cout << "Served overbooked customers: " << servedCount << "\n\n";
   
    // remaining = rejected
    int rejectedCount = 0;
    Customer rej;
    while (heap.deleteHeap(rej, compareCustomer)) {
        cout << rej << "\n";
        ++rejectedCount;
    }
    // summary of rejected
    cout << "Rejected overbooked customers: "<< rejectedCount << "\n";
    
    return 0;
}

/* Write your code here */ 
int compareCustomer(const Customer &a, const Customer &b)
{
    if      (a.getSerial() > b.getSerial()) return  1;
    else if (a.getSerial() < b.getSerial()) return -1;
    else                                     return  0;
}
