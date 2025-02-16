#include <iostream>
#include <string>
using namespace std;

// Declare kilotopound function
double kilotopound(double kilogram);

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
        cout << "Cargo object destroyed.\n";
    }

    // Friend function to convert kg to pounds
    friend double kilotopound(double kg);

    // Setters
    void setUldType(const string& uld) { this->uld = uld; }
    void setAbbrev(const string& abrv) { this->abrv = abrv; }
    void setUldId(const string& uldid) { this->uldid = uldid; }
    void setAircraft(int air) { this->air = air; }
    
    void setWeight(double weight, char unit) {
        if (unit == 'K' || unit == 'k') {
            wt = kilotopound(weight); 
        } else {
            wt = weight;
        }
    }

    void setDestination(const string& dest) { this->dest = dest; }

    // Getters
    string getUldType() const { return uld; }
    string getAbbrev() const { return abrv; }
    string getUldId() const { return uldid; }
    int getAircraft() const { return air; }
    double getWeight() const { return wt; }
    string getDestination() const { return dest; }

    // Overloaded == operator
    bool operator==(const Cargo& other) const {
        return (uldid == other.uldid && abrv == other.abrv);
    }

    // Friend functions for input and output
    friend void inputCargo(Cargo& cargo);
    friend void outputCargo(const Cargo& cargo);
};

// Friend function to convert kilograms to pounds
double kilotopound(double kg) {
    return kg * 2.2;
}

// Friend function for input
void inputCargo(Cargo& cargo) {
    string uld, abrv, code, dest;
    int air;
    double weight;
    char unit;

    cout << "Enter Unit Type (Container, Pallet, or Combo Flat): ";
    getline(cin, uld);

    cout << "Enter Unit Abbreviation (e.g., AYF, PAG, CFE, CFK, CFM): ";
    getline(cin, abrv);

    cout << "Enter 5-digit code for Unit ID: ";
    getline(cin, code);
    cargo.uldid = abrv + code + "IB";

    cout << "Enter Aircraft Type (e.g., 737): ";
    cin >> air;
    cin.ignore();

    cout << "Enter Weight: ";
    cin >> weight;
    cout << "Enter unit (K for Kilograms, P for Pounds): ";
    cin >> unit;
    cin.ignore();

    cout << "Enter Destination (3-letter IATA code): ";
    getline(cin, dest);

    // Set values using setters
    cargo.setUldType(uld);
    cargo.setAbbrev(abrv);
    cargo.setAircraft(air);
    cargo.setWeight(weight, unit);
    cargo.setDestination(dest);
}

// Friend function for output
void outputCargo(const Cargo& cargo) {
    cout << "\n--- Cargo Information ---\n";
    cout << "Unit Load Type: " << cargo.getUldType() << endl;
    cout << "Unit Abbreviation: " << cargo.getAbbrev() << endl;
    cout << "Unit Identifier: " << cargo.getUldId() << endl;
    cout << "Aircraft Type: " << cargo.getAircraft() << endl;
    cout << "Unit Weight: " << cargo.getWeight() << " pounds\n";
    cout << "Destination Code: " << cargo.getDestination() << endl;
}

int main() {
    // Create unit1 with test data
    Cargo unit1("Container", "AYK", "AYK68943IB", 737, 1654, "PDX");

    // Convert weight if necessary
    cout << "Testing kilotopound function...\n";
    unit1.setWeight(1654, 'K'); // Convert 1654 kg to pounds

    // Output updated unit1 details
    outputCargo(unit1);

    // Copy constructor test
    Cargo unit2 = unit1;
    cout << "\nCopy Constructor Test (unit2):\n";
    outputCargo(unit2);

    // Default object unit3
    Cargo unit3;
    cout << "\nDefault Constructor Test (unit3):\n";
    outputCargo(unit3);

    // Test overloaded == operator
    if (unit1 == unit2)
        cout << "\nunit1 is the same as unit2\n";
    else
        cout << "\nunit1 is not the same as unit2\n";

    if (unit2 == unit3)
        cout << "\nunit2 is the same as unit3\n";
    else
        cout << "\nunit2 is not the same as unit3\n";

    return 0;
}