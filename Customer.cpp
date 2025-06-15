/**~*~*~* 
 Name : Chu Jia Xian
===========================================
 Implementation file for the Customer class
*~*/
#include <iostream>
#include <string> 
#include "Customer.h"

using namespace std;

/* Write your code here */
Customer::Customer()
{
	year = 0;
	mileage = 0; 
	seq = 0; 
	name = "";
}

Customer::Customer(int yrs, int mil, int seqNo, const string &nm)
{
	year = yrs;
	mileage = mil; 
	seq = seqNo; 
	name = nm;
}