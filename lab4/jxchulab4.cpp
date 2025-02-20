#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Cargo class definition
class Cargo {
private:
    string uld;   // Unit type (Container, Pallet, or Combo Flat)
    string abrv;  // Abbreviation (e.g., AYF, PAG, CFE)
    string uldid; // Unique identifier
    int air;      // Aircraft type (e.g., 737)
    double wt;    // Weight (stored in pounds)
    string dest;  // Destination (IATA code)

public:
    // Default constructor
    Cargo() : uld("Unknown"), abrv("Unknown"), uldid("Unknown"), air(0), wt(0), dest("Unknown") {}

    // Parameterized constructor
    Cargo(const string& uld, const string& abrv, const string& uldid, int air, double wt, const string& dest)
        : uld(uld), abrv(abrv), uldid(uldid), air(air), wt(wt), dest(dest) {}

    // Copy Constructor
    Cargo(const Cargo& other) {
        uld = other.uld;
        abrv = other.abrv;
        uldid = other.uldid;
        air = other.air;
        wt = other.wt;
        dest = other.dest;
    }

    // Destructor
    ~Cargo() {
        cout << "Cargo object " << uldid << " destroyed.\n";
    }

    // Output function
    void display() const {
        cout << "\n--- Cargo Information ---\n";
        cout << "Unit Load Type: " << uld << endl;
        cout << "Unit Abbreviation: " << abrv << endl;
        cout << "Unit Identifier: " << uldid << endl;
        cout << "Aircraft Type: " << air << endl;
        cout << "Unit Weight: " << wt << " pounds\n";
        cout << "Destination Code: " << dest << endl;
    }
};

// Function to read cargo data from a file
void readCargoFromFile() {
    string filename;
    cout << "Enter the input file name: ";
    cin >> filename;

    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Could not open file " << filename << ". Exiting program.\n";
        exit(EXIT_FAILURE);
    }

    string cargostring;
    vector<Cargo*> cargoList;

    while (getline(inputFile, cargostring)) {
        istringstream cargoISS(cargostring);
        string type1, type2, abrv, uld, dest;
        int plane;
        double weight;

        cargoISS >> type1;

        if (type1 == "Combo") {
            cargoISS >> type2 >> abrv >> uld >> plane >> weight >> dest;
            type1 += " " + type2;  // Combine "Combo" and "Flat" into "Combo Flat"
        } else {
            cargoISS >> abrv >> uld >> plane >> weight >> dest;
        }

        // Create a Cargo object
        Cargo* temp = new Cargo(type1, abrv, uld, plane, weight, dest);
        cargoList.push_back(temp); // Store pointer instead of copying
    }

    inputFile.close();

    // Display all Cargo objects
    for (const Cargo* cargo : cargoList) {
        cargo->display();
    }

	// Cleanup memory
	for (Cargo* cargo : cargoList) {
		delete cargo;
	}
}

int main() {
    readCargoFromFile();
    return 0;
}
