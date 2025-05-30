/**~*~*~* 
 Recursive Functions and BST ADT: 
   --> build BST from file: calls insertBST
   --> traverse in inorder, preorder, postorder  
   --> show leaves
   --> search  
=================
Name: Chu Jia Xian
IDE:
*~*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>

#include "BinarySearchTree.h"  
#include "College.h"

using namespace std;

void buildBST(const string &, BinarySearchTree<College> &);
void displayManager(const BinarySearchTree<College> &);
void searchManager(const BinarySearchTree<College> &);

int main()
{
    string filename;
    BinarySearchTree<College> bst;

    cout << "What is the input file's name? ";
    getline(cin, filename);
    buildBST(filename, bst);
    displayManager(bst);
    searchManager(bst);
    
    return 0;
}

// buildBST
void buildBST(const string &filename, BinarySearchTree<College> &bst)
{
    ifstream fin(filename);
    cout << "Reading data from \"" << filename << "\"";

    if(!fin)
    {
        cout << "Error opening the input file: \""<< filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(fin, line))
    {
       int rank, cost;
       string code, name;
    
       stringstream temp(line);   // create temp with data from line
       temp >> rank;              // read from temp
       temp >> code;
       temp.ignore();             // to ignore space in front of name
       getline(temp, name, ';');  // stop reading name at ';'
       temp >> cost;
       // create a College object and initialize it with data from file
       College aCollege(rank, code, name, cost);
       bst.insert(aCollege);
    }

    fin.close();
}

/*
Display manager: traversals, count, indented tree, and leaf nodes
Input Parameter: bst
*/
void displayManager(const BinarySearchTree<College> &bst)
{
   
    string option;
    
    // count
    cout << "Display count [Y/N]?" << endl;
    getline(cin, option);
    option[0] = toupper(option[0]);
    if (option == "Y")
    {
        cout << "The number of nodes in the BST is ";
        cout << bst.getCount() << endl;
    }
    
    // traversals
    cout << "Display Tree [In/Pre/posT/N]?" << endl;
    getline(cin, option); // I, P, T or N
    option[0] = toupper(option[0]);
    switch (option[0])
    {
       case 'I':
        cout << endl << "Inorder:" << endl;
        bst.inOrder(hDisplay);
        /* Write your code here: call inorder - use hDisplay */
        cout << endl;
        break;
       case 'P': 
        cout << endl << "Preorder:" << endl;
        bst.preOrder(hDisplay);
        /* Write your code here: call preorder - use hDisplay */
        cout << endl;
        break;  
       case 'T':
        cout << endl << "Postorder:" << endl;
        bst.postOrder(hDisplay);
        /* Write your code here: call postorder - use hDisplay */
        cout << endl;
        break;
       case 'N':
        break;
       default:
        cout << "Invalid option!" << endl;
        break;
    }

    // Indented Tree
    cout << "Display Indented List [Y/N]?" << endl;
    getline(cin, option);
    option[0] = toupper(option[0]);
    if (option == "Y") 
    {
        cout << "Indented List:" << endl;
        bst.printTree(iDisplay);
        /* Write your code here: call printTree - use iDisplay */
        cout << endl;
    }
    
    // Leaf Nodes
    cout << "Display Leaf Nodes [Y/N]?" << endl;
    getline(cin, option);
    option[0] = toupper(option[0]);
    if (option == "Y")
    {
        cout  << "Leaf Nodes:" << endl;
        bst.printLeafNodes(kDisplay);
        /* Write your code here: call printInnerNodes - use kDisplay */
        cout << endl;
    }
    
}

/* Write your code here: define buildBST and searchManager */

// searchManager
void searchManager(const BinarySearchTree<College> &bst)
{
    string targetCode = "";
    College aCollege;
    College found;


    cout << endl << " Search" << endl;
    cout <<   "========" << endl;;

    while(true)
    {
        cout << "Enter a college code (or Q to stop searching):"  << endl;
        getline(cin, targetCode);

        // guard against blank input
        if (targetCode.empty())
            continue;
        
        // uppercase every character:
        for (char &c : targetCode) {
            c = toupper(c);

        }
    
        if(targetCode != "Q")
        {
           /*
           Write your code here: call searchList()
           If found, display related data calling the vDisplay() function of the College class.
           if not found, display: targetCode - not found
           */

            aCollege.setCode(targetCode);
            if (bst.search(aCollege, found))
                vDisplay(found);
            else
                cout << "College" << " \"" << targetCode << "\" " << "- not found" << endl;
        }
        else
            break;
    }
    cout << "___________________END SEARCH SECTION _____" << endl;
}
