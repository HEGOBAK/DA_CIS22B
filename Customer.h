/**~*~*~* 
 Name : Chu Jia Xian
===========================================
 Specification file for the Customer class
*~*/

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <string>
#include <iostream>

using namespace std;

class  Customer; // Forward Declaration

// Function Prototypes for friend functions
/* Write your code here */

class Customer
{
private:
    int year;
    int mileage;
    int seq;
	string name;
	
public:
   /* Write your code here */
   Customer();
   Customer(int yrs, int mil, int seqNo, const string &nm);
   
   int getYear()     const { return year; }
   int getMileage()  const { return mileage; }
   int getSeq()      const { return seq; }
   string getName()  const { return name; }
   
   // Priority = A/1000 + B – C
   int getPriority() const { return mileage/1000 + year - seq; }
   
   // Serial = priority*100 + (100 - C)
   int getSerial()   const { return getPriority()*100 + (100 - seq); }
   
   // For printing
   friend ostream& operator<<(ostream &os, const Customer &c)
   {
	   os << c.year << ' '
		  << c.mileage << " ("
		  << c.getSerial() << ") ["
		  << c.name << ']';
	   return os;
   }
};

#endif