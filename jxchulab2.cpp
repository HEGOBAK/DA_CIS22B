#include <iostream>
#include <string>
using namespace std;

class Cargo {
private:
    string uld;       // Unit type
    string abrv;      // Abbreviation
    string uldid;     // Unit identifier
    int air;          // Aircraft type
    int wt;           // Weight
    string dest;      // Destination

public:
    Cargo() {
        uld = "Unknown";
        abrv = "Unknown";
        uldid = "Unknown";
        air = 0;
        wt = 0;
        dest = "Unknown";
    }

    Cargo(const string& uld, const string& abrv, const string& uldid, int air, int wt, const string& dest) {
        this->uld = uld;
        this->abrv = abrv;
        this->uldid = uldid;
        this->air = air;
        this->wt = wt;
        this->dest = dest;
    }

    // Destructor
    ~Cargo() {
        cout << "Cargo object destroyed.\n";
    }

    // Mutators (Setters)
    void setUldType(const string& uld) { this->uld = uld; }
    void setAbbrev(const string& abrv) { this->abrv = abrv; }
    void setUldId(const string& uldid) { this->uldid = uldid; }
    void setAircraft(int air) { this->air = air; }
    void setWeight(int wt) { this->wt = wt; }
    void setDestination(const string& dest) { this->dest = dest; }

    // Accessors (Getters)
    string getUldType() const { return uld; }
    string getAbbrev() const { return abrv; }
    string getUldId() const { return uldid; }
    int getAircraft() const { return air; }
    int getWeight() const { return wt; }
    string getDestination() const { return dest; }

    void input() {
        cout << "Enter Unit Type (Container or Pallet): ";
        getline(cin, uld);
        cout << "Enter Unit Abbreviation (e.g., AYF, PAG): ";
        getline(cin, abrv);
        cout << "Enter 5-digit code for Unit ID: ";
        string code;
        getline(cin, code);
        uldid = abrv + code + "IB";
        cout << "Enter Aircraft Type (e.g., 737): ";
        cin >> air;
        cout << "Enter Weight (in pounds): ";
        cin >> wt;
        cin.ignore();
        cout << "Enter Destination (3-letter IATA code): ";
        getline(cin, dest);
    }

    void output() const {
        cout << "\n--- Cargo Information ---\n";
        cout << "Unit Load Type: " << uld << endl;
        cout << "Unit Abbreviation: " << abrv << endl;
        cout << "Unit Identifier: " << uldid << endl;
        cout << "Aircraft Type: " << air << endl;
        cout << "Unit Weight: " << wt << " pounds\n";
        cout << "Destination Code: " << dest << endl;
    }
};

int main() {
	// Create a Cargo object using the default constructor
    Cargo* cargo1 = new Cargo;
    cout << "Default Constructor Object:" << endl;
    cargo1->output(); 
    delete cargo1; 

    // Create a Cargo object on the heap and input data
    Cargo* cargo2 = new Cargo;
    cout << "\nEnter details for a new Cargo object:\n";
    cargo2->input();
    cout << "\nCargo object after input:" << endl;
    cargo2->output();
    delete cargo2; 
	

    return 0;
}
