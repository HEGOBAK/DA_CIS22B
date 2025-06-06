/**~*~*~* 
 Specification file for the Student class
====================================================
Name: Chu Jia Xian
IDE:
*~*/

#ifndef STUDENT_H
#define STUDENT_H

using std::string;

class Student; // Forward Declaration

// Function Prototypes for friend functions
/* Write the declaration of the hash function named key_to_index() */
int key_to_index(const class Student &key, int size);

class Student
{
private:
    double gpa;
    string name;
    
public:
    Student() {name = ""; gpa = -1;}                  // Constructor
    Student(string n, double g) {name = n; gpa = g;}  // Overloaded Constructor
    
    // Setters and getters
    void setName(string n) {name = n;}
    void setGpa(double g) {gpa = g;}
    string getName() const {return name;}
    double getGpa() const {return gpa;}
    
    // Overloaded operators
    /* Write your code here */
	bool operator==(const Student &other) const {
        return name == other.name; 
    }
    
    // friend functions
    /* Write your code here */
	friend int key_to_index(const Student &key, int size);
};
#endif
