
#include <iostream>
#include <fstream>
using namespace std;

struct Node {
Node* left;
Node* right;
Node* p; 


int flightID;
string Source;
string Destination;
string Airline;
float departureTime;
float arrivalTime;
float flightDuration;
int ticketPrice;
string Status;
bool hasSpecialNeeds;


Node(int flightID, string source, string destination, string airline, float depTime, float arrTime, int tPrice, string status, bool specialNeeds) {
    this->flightID = flightID;
    this->Source = source;
    this->Destination = destination;
    this->Airline = airline;
    this->departureTime = depTime;
    this->arrivalTime = arrTime;
    this->flightDuration = arrTime - depTime; // Calculate flight duration
    this->ticketPrice = tPrice;
    this->Status = status;
    this->hasSpecialNeeds = specialNeeds; // Default value for special needs
    left = nullptr;
    right = nullptr;
    p = nullptr;
}
};

class BST {
public:
Node* root;

BST() {
root = nullptr;
}

void insert(int flightID, string source, string destination, string airline, float depTime, float arrTime, int tPrice, string status, bool hasSpecialNeeds)
{
    Node* z = new Node(flightID, source, destination, airline, depTime, arrTime, tPrice, status, hasSpecialNeeds);
    Node* y = nullptr;
    Node* x = root;

    // Follow the BST path until an empty child position is found.
    while (x != nullptr) {
        y = x;
        if (z->flightID < x->flightID)
            x = x->left;
        else
            x = x->right;
    }

    z->p = y;

    if (y == nullptr)
        root = z;
    else if (z->flightID < y->flightID)
        y->left = z;
    else
        y->right = z;
}

Node* search(int flightID)
{
    Node* x = root;

    while (x != nullptr && x->flightID != flightID) {
        if (flightID < x->flightID)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}

Node* minimum(Node* x)
{
    // Keep moving left while a left child exists.
    if (x == nullptr)
        return nullptr;

    while (x->left != nullptr) {
        x = x->left;
    }

    return x;
}

void inorder(Node* x)
{
    if (x != nullptr)
    {
        inorder(x->left);
        cout << x->flightID << " ";
        cout << x->Source << " to " << x->Destination << " \n";  
        inorder(x->right);
    }
}

void transplant(Node* u, Node* v)
{
    // TODO 1: If u is the root, make v the new root.
    // TODO 2: Otherwise, connect v to the correct side of u's parent.
    // TODO 3: If v is not nullptr, update v's parent pointer.

    if (u == root)
    {
        root = v;
    }
    else if (u == u->p->left)
    {
        u->p->left = v;
    }
    else
    {
        u->p->right = v;
    }

    if (v != nullptr)
    {
        v->p = u->p;
    }
}

void deleteNode(int flightID)
{
    Node* z = search(flightID);

    if (z == nullptr)
    {
        cout << "flightID not found.\n";
        return;
    }

    // CASE 1: z has no left child.
    // Replace z with its right child.
    if (z->left == nullptr)
    {
        transplant(z, z->right);
    }

    // CASE 2: z has a left child but no right child.
    else if (z->right == nullptr)
    {
        transplant(z, z->left);
    }

    // CASE 3 and CASE 4: z has both children.
    else
    {
        // Find the inorder successor.
        Node* y = minimum(z->right);

        // CASE 3: Successor is z's direct right child.
        if (y == z->right)
        {
            transplant(z, y);

            y->left = z->left;
            y->left->p = y;
        }

        // CASE 4: Successor is deeper inside z's right subtree.
        else
        {
            // Replace y with y's right child.
            transplant(y, y->right);

            // Attach z's original right subtree to y.
            y->right = z->right;
            y->right->p = y;

            // Replace z with y.
            transplant(z, y);

            // Attach z's original left subtree to y.
            y->left = z->left;
            y->left->p = y;
        }
    }

    delete z; // Free the memory for the removed node.
}

void FlightDurETA(int flightID, float arrTime, float depTime) 
{
    Node* flightNode = search(flightID);
    int depHours = depTime;
    int depMinutes = (depTime - depHours) * 100;

    int arrHours = arrTime;
    int arrMinutes = (arrTime - arrHours) * 100;

    int totalDepMinutes = depHours * 60 + depMinutes;
    int totalArrMinutes = arrHours * 60 + arrMinutes;

    int duration = totalArrMinutes - totalDepMinutes;
    int eta = totalDepMinutes + duration;


    int hours = duration / 60;
    int minutes = duration % 60;

    int ehours = eta / 60;
    int eminutes = eta % 60;

    cout << "Flight Duration: " << hours << " hours " << minutes << " minutes";

    cout << "\nEstimated Time of Arrival (ETA): " << ehours << "."
        << eminutes;

    if(ehours > arrHours || eminutes > arrMinutes)
    {
        cout << "\nFlight is delayed.\n";
    }
    else if (ehours < arrHours || eminutes < arrMinutes)
    {
        cout << "\nFlight is early.\n";
    }
    
    else
    {
        cout << "\nFlight is on time.\n";
    }
}

void display(int flightId, string source, string destination) 
    {
        cout << "Flight ID: " << flightId << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
    }


bool specialNeeds(int flightId, bool specialNeeds) 
    {       
        if (specialNeeds) 
        {
            cout << "Airline personnel of Flight " << flightId << " have been notified.\n";
                return true;
            } 
            else 
            {
                cout << "Thank you for providing the information.\n";
                return false;
            }
    }



void saveToFile(Node* x, ofstream& out)
{
    if (x != nullptr)
    {
        saveToFile(x->left, out);

        out << x->flightID << " "
            << x->Source << " "
            << x->Destination << " "
            << x->Airline << " "
            << (x->departureTime < 10 ? "0" : "") << x->departureTime << " ";
        out << (x->arrivalTime < 10 ? "0" : "") << x->arrivalTime << " ";
        out << x->ticketPrice << " "
            << x->Status << " "
            << (x->hasSpecialNeeds ? "(disaility/special needs present)" : "(no disabilities or special needs)") << endl; 
            saveToFile(x->right, out);
    }
}



void saveRecords()
{
    ofstream out("flights.txt");

    if (!out)
    {
        cout << "Error opening file.\n";
        return;
    }

    saveToFile(root, out);

    out.close();

    cout << "Flight records saved successfully.\n";
}



void loadRecords()
{
    ifstream in("flights.txt");

    if (!in)
    {
        return;
    }

    int flightID;
    string source, destination, airline, status;
    float depTime, arrTime;
    int tPrice;
    string specialNeeds;

    while (in >> flightID >> source >> destination >> airline
              >> depTime >> arrTime >> tPrice >> status >> specialNeeds)
    {
        bool hasSpecialNeeds = (specialNeeds == "(disaility/special needs present)");
        insert(flightID, source, destination, airline,
               depTime, arrTime, tPrice, status, hasSpecialNeeds);
    }

    in.close();

    cout << "Flight records loaded successfully.\n";
}
};

int main()
{
    BST tree;


    tree.loadRecords(); 

    int choice;
    int flightId;
    string source;
    string destination;
    string airline;
    float depTime;
    float arrTime;
    int tPrice;
    string status;
    string specialNeeds; 
    bool hasSpecialNeeds;

    do
    {
        cout << "\n FLIGHT MANAGEMENT SYSTEM \n";
        cout << "1. Add Flight\n";
        cout << "2. Delete Flight\n";
        cout << "3. Search Flight\n";
        cout << "4. Display Flight Duration and ETA\n";
        cout << "5. Display All Flights\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {

            case 1:
            {
                cout << "\nEnter flightID to insert: ";
                cin >> flightId;

                cout << "Enter source of flight: ";
                cin >> source;

                cout << "Enter destination of flight: ";
                cin >> destination;

                cout << "Enter airline of flight: ";
                cin >> airline;

                cout << "Enter departure time of flight: ";
                cin >> depTime;

                cout << "Enter arrival time of flight: ";
                cin >> arrTime;

                cout << "Enter price of ticket: ";
                cin >> tPrice;

                cout << "Enter status of flight: ";
                cin >> status;

                cout << "\n\n";

                cout << "Are there any people with disabilities or special needs on the flight? (yes/no): ";   
                cin >> specialNeeds;
                hasSpecialNeeds = tree.specialNeeds(flightId, specialNeeds == "yes" || specialNeeds == "Yes");



                tree.insert(flightId, source, destination, airline, depTime, arrTime, tPrice, status, hasSpecialNeeds);
                
                //tree.insert(101, "New York", "Los Angeles", "Delta Airlines", 08.30, 11.00, 200, "On Time");


                cout << "\nFlight inserted successfully.\n";
                tree.saveRecords(); 
                break;
            }

            case 2:
            {
                cout << "\nEnter flightID to delete: ";
                cin >> flightId;

                Node* result = tree.search(flightId);
                if (result != nullptr)
                {
                    cout << "\nFlight found.\n";

                    tree.deleteNode(flightId);
                    cout << "Flight deleted successfully.\n";
                    tree.saveRecords(); 
                }
                else
                {
                    cout << "Flight not found.\n";
                }

                break;
            }

            case 3:
            {
                cout << "\nEnter flightID to search: ";
                cin >> flightId;

                Node* result = tree.search(flightId);

                if (result != nullptr)
                {
                    cout << "\nFlight found.\n";

                    if (result->hasSpecialNeeds == true)
                    {
                        cout << "\n*** SPECIAL NEEDS ***\n";
                        cout << "This flight has people with disabilities or special needs on it.\n";
                    }

                    cout << "Flight Record:\n";

                    tree.display(result->flightID, result->Source, result->Destination);
                }
                else
                {
                    cout << "Flight not found.\n";
                }

                break;
            }

            case 4:
            {
                cout << "\nEnter flightID to display duration and ETA: ";
                cin >> flightId;

                Node* result = tree.search(flightId);
                if (result != nullptr)
                {
                    tree.FlightDurETA(flightId, result->arrivalTime, result->departureTime);
                }
                else
                {
                    cout << "Flight not found.\n";
                }

                break;
            }

            case 5:
            {
                cout << "\nAll Flights:\n";
                tree.inorder(tree.root);
                cout << endl;
                break;
            }

            case 6:
            {
                tree.saveRecords(); 
                cout << "\nExited Successfully!\n";
                break;
            }

            default:
            {
                cout << "\nInvalid choice! Please enter 1-6.\n";
                break;
            }

        }

    } while (choice != 6);

    return 0;


}
















// int main() 
// {
//     BST tree;
//     int choice;
//     int flightId;
//     string source;
//     string destination;
//     string airline;
//     float depTime;
//     float arrTime;
//     int tPrice;
//     string status;

    
//     do{
//         cout << " 1.Add Flight: ";
//         cout << " 2.Delete Flight: ";
//         cout << " 3.Search Flight: ";
//         cout << " 4.Exit: ";

//         cout << "Enter your choice: ";
//         cin >> choice;
        
//         switch (choice) 
//         {
            
//             case 1: 
//             {
//                 cout <<" Enter flightID to insert: ";
//                 cin >> flightId;
//                 cout <<" Enter source of flight: ";
//                 cin >> source;
//                 cout <<" Enter destination of flight: ";
//                 cin >> destination; 
//                 cout <<" Enter airline of flight: ";    
//                 cin >> airline;
//                 cout <<" Enter departure time of flight: ";
//                 cin >> depTime; 
//                 cout <<" Enter arrival time of flight: ";
//                 cin >> arrTime;
//                 cout <<" Enter price of ticket: ";
//                 cin >> tPrice;
//                 cout <<" Enter status of flight: ";
//                 cin >> status;


//                 tree.insert(flightId, source, destination, airline, depTime, arrTime, tPrice, status);
//                 cout << "Flight inserted successfully.\n";
//                 break;
//             }

//             case 2: 
//             {
//                 cout << "Enter flightID to delete: ";
//                 cin >> flightId;

//                 tree.deleteNode(flightId);

//                 cout << "Flight deleted successfully.\n";
//                 break;
//             }

//             case 3:
//             {
            
//                 cout << "Enter flightID to search: ";
//                 cin >> flightId;

//                 Node* result = tree.search(flightId);

//                 if (result != nullptr)
//                 {
//                     cout << "Flight found.\n";
//                     cout << "Flight Record: ";
//                     tree.display(flightId, source, destination);
//                 }
//                 else
//                 {
//                     cout << "Flight not found.\n";
//                 }
//                 break;
//             }

//             case 4:        {
            
//                 cout << "Exited Successfully! ";
//                 break;
//             }

//         }


//         return 0;
    
//     }while (choice != 4);
// }