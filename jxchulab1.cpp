#include <iostream>
#include <string>
using namespace std;

// Define the Cargo struct in the global scope
struct Cargo {
    string uld;      // Unit type
    string abbr;     // Abbreviation
    string uldid;    // Unit identifier
    int air;         // Aircraft type
    int wt;          // Weight
    string dest;     // Destination
};

// Function prototypes
void inputCargo(Cargo*& cargo);
void outputCargo(const Cargo* cargo);

int main() {
    // Pointer to dynamically allocate Cargo struct
    Cargo* cargo = new Cargo;

    // Get input from the user
    inputCargo(cargo);

    // Display the cargo information
    outputCargo(cargo);

    // Clean up dynamically allocated memory
    delete cargo;

    return 0;
}

// Function to input data into the Cargo struct
void inputCargo(Cargo*& cargo) {
    cout << "Enter Unit Type (Container or Pallet): ";
    getline(cin, cargo->uld);
    cout << "Enter Unit Abbreviation (e.g., AYF, PAG): ";
    getline(cin, cargo->abbr);
    cout << "Enter Unit Identifier (e.g., AYF12345IB): ";
    getline(cin, cargo->uldid);
    cout << "Enter Aircraft Type (e.g., 737): ";
    cin >> cargo->air;
    cout << "Enter Weight (in pounds): ";
    cin >> cargo->wt;
    cin.ignore(); // Clear the newline character in the input buffer
    cout << "Enter Destination (3-letter IATA code): ";
    getline(cin, cargo->dest);
}

// Function to output the contents of the Cargo struct
void outputCargo(const Cargo* cargo) {
    cout << "\n--- Cargo Information ---\n";
    cout << "Unit Type: " << cargo->uld << endl;
    cout << "Unit Abbreviation: " << cargo->abbr << endl;
    cout << "Unit ID: " << cargo->uldid << endl;
    cout << "Aircraft: " << cargo->air << endl;
    cout << "Weight: " << cargo->wt << " pounds" << endl;
    cout << "Destination: " << cargo->dest << endl;
}
