#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Abstract Base Class
class Cargo {
protected:
    string type;        // Container, Pallet, Combo Flat
    string abbreviation;
    string ULD;         // Unique Load Device Code
    string planeType;   // 737 or 767
    int weight;
    string destination;

public:
    // Default constructor
    Cargo() : type("Unknown"), abbreviation("Unknown"), ULD("Unknown"), planeType("Unknown"),weight(0), destination("Unknown") {}

    // Parameterized constructor
    Cargo(const string& uld, const string& abrv, const string& uldid, string air, int wt, const string& dest)
        : type(uld), abbreviation(abrv), ULD(uldid), planeType(air), weight(wt), destination(dest) {}

    // Copy Constructor
    Cargo(const Cargo& other) {
        type = other.type;
        abbreviation = other.abbreviation;
        ULD = other.ULD;
        planeType = other.planeType;
        weight = other.weight;
        destination = other.destination;
    }

    // Setters
    void setUldType(const string& uld) { this->type = uld; }
    void setAbbrev(const string& abrv) { this->abbreviation = abrv; }
    void setUldId(const string& uldid) { this->ULD = uldid; }
    void setAircraft(int air) { this->planeType = air; }
	void setWeight(double weight) { this->weight = weight; }
	void setDestination(const string& dest) { this->destination = dest; }

    string getUldType() const { return type; }
    string getAbbrev() const { return abbreviation; }
    string getUldId() const { return ULD; }
    string getAircraft() const { return planeType; }
    double getWeight() const { return weight; }
    string getDestination() const { return destination; }

    virtual ~Cargo() {}

    virtual int maxLoad() { return 0; } // Pure Virtual Function

    void display() const {
        cout << type << " " << abbreviation << " " << ULD << " " 
             << planeType << " " << weight << " " << destination << endl;
    }
};

// Derived Boeing737 Class
class Boeing737 : public Cargo {
public:
    Boeing737(string t, string abrv, string uld, string plane, int w, string dest)
        : Cargo(t, abrv, uld, plane, w, dest) {}

    int maxLoad() { return 46000; }
};

// Derived Boeing767 Class
class Boeing767 : public Cargo {
public:
    Boeing767(string t, string abrv, string uld, string plane, int w, string dest)
        : Cargo(t, abrv, uld, plane, w, dest) {}

    int maxLoad() { return 116000; }
};

// Node structure for Linked List
struct Node {
    Cargo* cargo;
    Node* next;

    // Explicitly initializing constructor
    Node(Cargo* c) {
        cargo = c;
        next = nullptr;
    }
};

// Linked List Class
class CargoList {
private:
    Node* head;
    int totalWeight;
    int maxCapacity;

public:
    CargoList(int maxLoad) {
        head = nullptr;
        totalWeight = 0;
        maxCapacity = maxLoad;
    }

    ~CargoList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp->cargo;
            delete temp;
        }
    }

    bool addCargo(Cargo* c) {
        if (totalWeight + c->getWeight() > maxCapacity) {
            cerr << "Error: Cannot add " << c->getAircraft() 
                 << " cargo, max weight exceeded.\n";
            delete c; // Prevent memory leak
            return false;
        }

        Node* newNode = new Node(c);
        newNode->next = head;
        head = newNode;
        totalWeight += c->getWeight();

        // Show total weight immediately after adding
        cout << "Added ULD (" << c->getUldId() << ") with weight (" << c->getWeight() << ") to cargo : " << c->getAircraft()
            << ". Current total weight of cargo " << c->getAircraft() << " : " << totalWeight << " lbs\n";

        return true;
    }
    
    void displayHelper(Node* node) const {
        if (!node) return;
        displayHelper(node->next);  // Recurse to the end first
        node->cargo->display();     // Then print on the way back
    }

    void display() const {
        displayHelper(head);  // Start from head
        cout << "Total Weight: " << totalWeight << " lbs\n";
    }
};

// Function to validate cargo type
bool isValidCargoType(const string& type) {
    return type == "Container" || type == "Pallet" || type == "Combo Flat";
}

// Function to validate aircraft type
bool isValidAircraft(const string& aircraft) {
    return aircraft == "737" || aircraft == "767";
}

// Function to validate unit load abbreviation based on aircraft type
bool isValidUnitLoad(const string& aircraft, const string& abrv) {
    if (aircraft == "737") {
        return abrv == "AYF" || abrv == "AYK" || abrv == "AAA" || abrv == "AYY" ||  // Containers
               abrv == "PAG" || abrv == "PMC" || abrv == "PLA" ||                   // Pallets
               abrv == "CFE" || abrv == "CFK" || abrv == "CFM";                     // Combo Flats
    } 
    else if (aircraft == "767") {
        return abrv == "AKE" || abrv == "APE" || abrv == "AKC" || abrv == "AQP" || abrv == "AQF" || abrv == "AAP" ||  // Containers
               abrv == "P1P" || abrv == "P6P" ||  // Pallets
               abrv == "CFQ" || abrv == "CFX" || abrv == "CFP"; // Combo Flats
    }
    return false;
}


// Function to validate cargo weight within aircraft limits
bool isValidWeight(const string& aircraft, int weight) {
    if (aircraft == "737") return weight > 0 && weight <= 46000;
    if (aircraft == "767") return weight > 0 && weight <= 116000;
    return false;
}

bool hasTooManyLines(const string& filename) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Error opening file to count lines.");
    }

    int lineCount = 0;
    string line;
    while (getline(file, line)) {
        ++lineCount;
        if (lineCount > 20) {
            return true;
        }
    }

    return false;
}


// Function to read input from file
void readInputFile(const string& filename, CargoList& list737, CargoList& list767) {
    ifstream inputFile(filename);
    if (!inputFile) {
        throw runtime_error("Invalid file name. Unable to open.");
    } else if (hasTooManyLines(filename)) {
        throw runtime_error("Invalid file name. Unable to open.");
    }

    cout << "\n----- Process..... -----" << endl;
    string line;
    while (getline(inputFile, line)) {
        istringstream cargoISS(line);
        string type1, type2, abrv, uld, plane, dest;
        int weight;

        cargoISS >> type1;
        if (type1 == "Combo") {
            cargoISS >> type2 >> abrv >> uld >> plane >> weight >> dest;
            type1 += " " + type2;
        } else {
            cargoISS >> abrv >> uld >> plane >> weight >> dest;
        }

        if (!isValidCargoType(type1) || !isValidAircraft(plane) || !isValidUnitLoad(plane, abrv) || !isValidWeight(plane, weight)) {
            cerr << "Invalid cargo data: " << line << endl;
            continue;
        }

        Cargo* cargo = nullptr;
        if (plane == "737") {
            cargo = new Boeing737(type1, abrv, uld, plane, weight, dest);
            if (!list737.addCargo(cargo)) continue;
        } else if (plane == "767") {
            cargo = new Boeing767(type1, abrv, uld, plane, weight, dest);
            if (!list767.addCargo(cargo)) continue;
        }
    }
    inputFile.close();
}

void action() {
	CargoList list737(46000);
    CargoList list767(116000);

    string filename;
    while (true) {
        cout << "Enter the data file name: ";
        cin >> filename;
        try {
            readInputFile(filename, list737, list767);
            break;
        } catch (const runtime_error& e) {
            cerr << e.what() << endl;
        }
    }

    cout << "\n--- Boeing 737 Cargo ---\n";
    list737.display();
    
    cout << "\n--- Boeing 767 Cargo ---\n";
    list767.display();
}



int main() {
    action();
    return 0;
}

// ========================== UNCOMMENT BELOW CODE FOR MAKEFILE SO YOU CAN TEST DATA QUICKLY ============================

// void action(const string& filename) {
//     CargoList list737(46000);
//     CargoList list767(116000);

//     try {
//         readInputFile(filename, list737, list767);
//     } catch (const runtime_error& e) {
//         cerr << e.what() << endl;
//         return; // Exit if file opening fails
//     }

//     cout << "\n--- Boeing 737 Cargo ---\n";
//     list737.display();
    
//     cout << "\n--- Boeing 767 Cargo ---\n";
//     list767.display();
// }

// int main(int argc, char* argv[]) {
//     if (argc < 2) {
//         cerr << "Usage: " << argv[0] << " <filename>\n";
//         return 1;
//     }

//     string filename = argv[1];
//     action(filename);

//     return 0;
// }
