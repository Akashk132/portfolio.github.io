#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <cmath>
#include <limits>
#include <set>
#include <climits>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional> // Required for std::function
#include <ctime>
#include <stack>
#include <iomanip>
#include <utility>
#include <fstream>


using namespace std;


// Class to manage bed availability
class BedAvailabilityTracker
{

private:
    vector<int> beds;  // Stores the bed statuses (0 for vacant, 1 for occupied)
    const int n = 51;  // Fixed number of beds (51)

    // Function to display the current status of all beds
    void displayBedStatus()
    {
        cout << "\nCurrent bed statuses:\n";
        for (int i = 0; i < n; i++)
        {
            cout << "Bed " << i << ": " << (beds[i] == 0 ? "Vacant" : "Occupied") << endl;
        }
    }


public:
    // Constructor to initialize the bed status with random values
    BedAvailabilityTracker()
    {
        beds.resize(n);
        srand(time(0));  // Seed the random number generator

        // Initialize the bed statuses with random values (0 for vacant, 1 for occupied)
        for (int i = 0; i < n; i++)
        {
            beds[i] = rand() % 2;  // Generates either 0 (vacant) or 1 (occupied)
        }
    }


    // Function to update the bed status (vacant/occupied)
    void updateBedStatus(int idx, int status)
     {
        if (status != 0 && status != 1)
        {
            cout << "Invalid status! Please enter 0 for vacant or 1 for occupied.\n";
            return;
        }
        if (idx < 0 || idx >= n)
        {
            cout << "Invalid bed index! Please enter a valid index.\n";
            return;
        }

        // Check if the bed is already in the same status
        if (beds[idx] == status)
        {
            cout << "The bed " << idx << " is already " << (status == 0 ? "vacant" : "occupied") << ". No changes made.\n";
        }
        else
        {
            beds[idx] = status;
            cout << "Bed " << idx << " status updated to " << (status == 0 ? "vacant" : "occupied") << ".\n";
        }

        // Display the updated bed statuses
        displayBedStatus();
    }

    // Function to display the current bed status when requested
    void showBedStatus()
    {
        displayBedStatus();
    }
};

// Node for Trie structure
struct TrieNode
{
    unordered_map<char, TrieNode*> children;
    vector<string> articles; // List of related articles
    bool isEndOfTopic = false; // Marks the end of a topic
};

// Healthcare System Code (unchanged)
class Graph
{
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int vertices)
    {
        V = vertices;
        adj.resize(V);
    }

    void addEdge(int u, int v, int weight)
    {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight));
    }

    vector<int> dijkstraWithPath(int source, vector<int>& parent)
    {
        vector<int> dist(V, INT_MAX);
        parent.resize(V, -1);
        dist[source] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(make_pair(0, source));

        while (!pq.empty())
            {
            int u = pq.top().second;
            pq.pop();

            for (auto& neighbor : adj[u])
                {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        return dist;
    }
};

class HealthcareSystem
{
private:
    map<int, string> locations;
    unordered_map<int, vector<string>> hospitalSpecialists;
    vector<int> healthcareFacilities;

public:
    void initializeData(Graph& cityGraph)
    {
        locations =
        {
            {0, "Colaba"},
            {1, "Nariman Point"},
            {2, "Fort"},
            {3, "Churchgate"},
            {4, "Breach Candy"},
            {5, "Worli"},
            {6, "Lower Parel"},
            {7, "Dadar"},
            {8, "Vile Parle"},
            {9, "Andheri"},
            {10, "Bandra"},
            {11, "Juhu"},
            {12, "Powai"},
            {13, "Kandivali"},
            {14, "Borivali"},
            {15, "Thane"},
            {16, "Kalyan"},
            {17, "Mulund"},
            {18, "Ghatkopar"},
            {19, "Versova"}
        };

        hospitalSpecialists =
        {
            {0, {"General Practitioner"}},
            {1, {"Pediatrics", "ENT"}},
            {2, {"Cardiology", "Neurology", "Dermatology"}},
            {3, {"Oncology", "Orthopedics"}},
            {4, {"Ophthalmology", "Gynecology", "Cardiology"}},
            {5, {"Neurology", "General Surgery"}},
            {6, {"Psychiatry", "Endocrinology"}},
            {7, {"Orthopedics", "Pulmonology"}},
            {8, {"Gastroenterology", "Urology"}},
            {9, {"Dermatology", "ENT"}},
            {10, {"Pediatrics", "Psychiatry"}},
            {11, {"Cardiology", "Orthopedics"}},
            {12, {"Neurology", "Gastroenterology"}},
            {13, {"Pulmonology", "Dermatology"}},
            {14, {"Orthopedics", "Gynecology"}},
            {15, {"Oncology", "Cardiology"}},
            {16, {"Neurology", "Ophthalmology"}},
            {17, {"ENT", "Orthopedics"}},
            {18, {"Cardiology", "Gastroenterology"}},
            {19, {"Psychiatry", "Dermatology"}}
        };

        healthcareFacilities = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

        // Example edges representing travel times between locations
        cityGraph.addEdge(0, 1, 4);
        cityGraph.addEdge(1, 2, 3);
        cityGraph.addEdge(2, 3, 2);
        cityGraph.addEdge(3, 4, 5);
        cityGraph.addEdge(4, 5, 4);
        cityGraph.addEdge(5, 6, 3);
        cityGraph.addEdge(6, 7, 5);
        cityGraph.addEdge(7, 8, 7);
        cityGraph.addEdge(8, 9, 6);
        cityGraph.addEdge(9, 10, 5);
        cityGraph.addEdge(10, 11, 3);
        cityGraph.addEdge(11, 12, 8);
        cityGraph.addEdge(12, 13, 7);
        cityGraph.addEdge(13, 14, 4);
        cityGraph.addEdge(14, 15, 9);
        cityGraph.addEdge(15, 16, 10);
        cityGraph.addEdge(16, 17, 6);
        cityGraph.addEdge(17, 18, 5);
        cityGraph.addEdge(18, 19, 4);
    }

    void displayAllSpecialties()
    {
        cout << "\nSelect a specialty from the list below:\n";
        map<int, string> specialties =
        {
            {1, "General Practitioner"},
            {2, "Pediatrics"},
            {3, "ENT"},
            {4, "Cardiology"},
            {5, "Neurology"},
            {6, "Dermatology"},
            {7, "Oncology"},
            {8, "Orthopedics"},
            {9, "Gynecology"},
            {10, "Psychiatry"},
            {11, "Ophthalmology"},
            {12, "Pulmonology"},
            {13, "Gastroenterology"},
            {14, "Urology"}
        };

        for (const auto& [id, specialty] : specialties)
        {
            cout << id << ". " << specialty << endl;
        }
    }

    void displayAllLocations()
    {
        cout << "\nAvailable Locations:\n";
        for (const auto& [id, location] : locations)
        {
            cout << id << ". " << location << endl;
        }
    }

    void searchNearestSpecialist(Graph& cityGraph)
    {
        int userLocation, specialtyChoice;
        vector<int> parent;

        cout << "\nEnter your current location (ID): ";
        displayAllLocations();
        cin >> userLocation;

        displayAllSpecialties();
        cout << "Enter the number corresponding to the specialty you need: ";
        cin >> specialtyChoice;

        string desiredSpecialty;
        switch (specialtyChoice)
        {
            case 1: desiredSpecialty = "General Practitioner"; break;
            case 2: desiredSpecialty = "Pediatrics"; break;
            case 3: desiredSpecialty = "ENT"; break;
            case 4: desiredSpecialty = "Cardiology"; break;
            case 5: desiredSpecialty = "Neurology"; break;
            case 6: desiredSpecialty = "Dermatology"; break;
            case 7: desiredSpecialty = "Oncology"; break;
            case 8: desiredSpecialty = "Orthopedics"; break;
            case 9: desiredSpecialty = "Gynecology"; break;
            case 10: desiredSpecialty = "Psychiatry"; break;
            case 11: desiredSpecialty = "Ophthalmology"; break;
            case 12: desiredSpecialty = "Pulmonology"; break;
            case 13: desiredSpecialty = "Gastroenterology"; break;
            case 14: desiredSpecialty = "Urology"; break;
            default:
                cout << "\nInvalid specialty choice. Please try again.\n";
                return;
        }

        vector<int> shortestDistances = cityGraph.dijkstraWithPath(userLocation, parent);

        int nearestFacility = -1;
        int minDistance = INT_MAX;

        for (int facility : healthcareFacilities)
            {
            if (find(hospitalSpecialists[facility].begin(), hospitalSpecialists[facility].end(), desiredSpecialty) != hospitalSpecialists[facility].end()) {
                if (shortestDistances[facility] < minDistance)
                {
                    minDistance = shortestDistances[facility];
                    nearestFacility = facility;
                }
            }
        }

        if (nearestFacility != -1)
        {
            cout << "\nThe nearest facility with " << desiredSpecialty << " is at " << locations[nearestFacility]
                 << " (Distance: " << minDistance << " km).\n";
        }
        else
        {
            cout << "\nNo nearby facility offers this specialty.\n";
        }
    }
};

// Class to manage medical treatments
class TreatmentSystem
{
public:
    // A map of treatments with their costs (in INR)
    map<int, pair<string, double>> treatments;

    // Constructor to initialize treatments with cost
    TreatmentSystem()
    {
        treatments[1] = {"General Checkup", 500}; // Cost in INR
        treatments[2] = {"X-Ray", 1500};
        treatments[3] = {"Blood Test", 700};
        treatments[4] = {"CT Scan", 3000};
        treatments[5] = {"MRI Scan", 5000};
        treatments[6] = {"Surgery", 20000};
        treatments[7] = {"Dental Checkup", 800};
        treatments[8] = {"Vaccination", 1000};
        treatments[9] = {"Ultrasound", 2500};
        treatments[10] = {"ECG", 1200};
        treatments[11] = {"Physiotherapy", 1500};
    }

    // Function to display the available treatments
    void displayTreatments()
     {
        cout << "\nAvailable Treatments:\n";
        for (const auto& treatment : treatments)
        {
            cout << treatment.first << ". " << treatment.second.first << " - INR " << treatment.second.second << endl;
        }
     }

    // Function to calculate the total cost based on selected treatments
    double calculateTotalCost(const vector<int>& selectedTreatments, const vector<int>& quantities)
    {
        double totalCost = 0.0;

        for (int i = 0; i < selectedTreatments.size(); ++i)
            {
            int treatmentId = selectedTreatments[i];
            int quantity = quantities[i];

            if (treatments.find(treatmentId) != treatments.end())
            {
                totalCost += treatments[treatmentId].second * quantity; // Add the cost * quantity
            }
        }

        return totalCost;
    }

    // Function to handle the user's interaction and calculate cost
    void solveAffordability()
     {
        cout << "Welcome to the Affordability Calculator for Medical Treatments!\n";
        cout << "This program will help you calculate the total cost of medical treatments based on your requirements.\n";

        vector<int> selectedTreatments; // Stores selected treatment IDs
        vector<int> quantities; // Stores the number of treatments selected for each

        int choice;
        char continueChoice;

        do
            {
            displayTreatments();

            cout << "\nEnter the treatment ID you want to choose (0 to stop selecting): ";
            cin >> choice;

            if (choice == 0)
            {
                break; // Exit if user chooses 0
            }

            // Check if the treatment ID is valid
            if (treatments.find(choice) != treatments.end())
                {
                int quantity;
                cout << "Enter the quantity for " << treatments[choice].first << ": ";
                cin >> quantity;

                // Add selected treatment and quantity to the respective lists
                selectedTreatments.push_back(choice);
                quantities.push_back(quantity);
            }
            else
            {
                cout << "Invalid treatment ID! Please try again.\n";
            }

            // Ask if the user wants to continue selecting more treatments
            cout << "\nDo you want to select another treatment? (Y/N): ";
            cin >> continueChoice;

        }

        while (continueChoice == 'Y' || continueChoice == 'y');

        // Calculate the total cost
        double totalCost = calculateTotalCost(selectedTreatments, quantities);
        cout << "\nThe total cost of the selected treatments is INR " << totalCost << endl;

        // Option to exit or restart the calculation
        cout << "\nWould you like to calculate again? (Y/N): ";
        cin >> continueChoice;

        if (continueChoice == 'Y' || continueChoice == 'y')
        {
            solveAffordability();  // Restart the calculation process
        }
        else
        {
            cout << "Thank you for using the Affordability Calculator. Stay healthy!\n";
        }
    }
};

// Appointment class to store details about an appointment
class Appointment
{
public:
    string name;
    string description;
    string timeSlot;
    Appointment(string n, string d, string t) : name(n), description(d), timeSlot(t) {}
};

// AVL Tree Node
class AVLNode
{
public:
    string timeSlot;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(string ts) : timeSlot(ts), left(nullptr), right(nullptr), height(1) {}
};

// AVL Tree class for managing time slots
class AVLTree
{
private:
    AVLNode* root;

    // Helper functions for AVL tree operations
    int height(AVLNode* node)
    {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode* node)
    {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLNode* node)
    {
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    // Rotate right
    AVLNode* rotateRight(AVLNode* y)
    {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Rotate left
    AVLNode* rotateLeft(AVLNode* x)
    {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode* balance(AVLNode* node)
    {
        // Balance the node if unbalanced
        int balance = balanceFactor(node);

        // Left heavy
        if (balance > 1)
        {
            if (balanceFactor(node->left) < 0)
            {
                node->left = rotateLeft(node->left);  // Left-Right case
            }
            return rotateRight(node);  // Left-Left case
        }

        // Right heavy
        if (balance < -1)
            {
            if (balanceFactor(node->right) > 0)
            {
                node->right = rotateRight(node->right);  // Right-Left case
            }
            return rotateLeft(node);  // Right-Right case
        }

        return node;
    }

    AVLNode* insert(AVLNode* node, string timeSlot)
    {
        // Perform normal BST insert
        if (!node) return new AVLNode(timeSlot);

        if (timeSlot < node->timeSlot)
        {
            node->left = insert(node->left, timeSlot);
        }
        else if (timeSlot > node->timeSlot)
        {
            node->right = insert(node->right, timeSlot);
        }
        else
        {
            return node;  // Duplicate time slots are not allowed
        }

        // Update the height and balance the tree
        updateHeight(node);
        return balance(node);
    }

    AVLNode* minValueNode(AVLNode* node)
    {
        AVLNode* current = node;
        while (current && current->left)
        {
            current = current->left;
        }
        return current;
    }

    AVLNode* deleteNode(AVLNode* root, string timeSlot)
    {
        if (!root) return root;

        // Perform normal BST delete
        if (timeSlot < root->timeSlot)
        {
            root->left = deleteNode(root->left, timeSlot);
        }
        else if (timeSlot > root->timeSlot)
        {
            root->right = deleteNode(root->right, timeSlot);
        }
        else
        {
            if (!root->left || !root->right)
            {
                AVLNode* temp = root->left ? root->left : root->right;
                if (!temp)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                {
                    *root = *temp;
                }

                delete temp;
            }
            else
            {
                AVLNode* temp = minValueNode(root->right);
                root->timeSlot = temp->timeSlot;
                root->right = deleteNode(root->right, temp->timeSlot);
            }
        }

        if (!root) return root;

        // Update height and balance the tree
        updateHeight(root);
        return balance(root);
    }

    void inOrder(AVLNode* node)
    {
        if (node)
        {
            inOrder(node->left);
            cout << node->timeSlot << " ";
            inOrder(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(string timeSlot)
    {
        root = insert(root, timeSlot);
    }

    void deleteTimeSlot(string timeSlot)
    {
        root = deleteNode(root, timeSlot);
    }

    void displayAvailableSlots()
    {
        inOrder(root);
        cout << endl;
    }

    bool find(string timeSlot)
    {
        AVLNode* current = root;
        while (current)
        {
            if (current->timeSlot == timeSlot) return true;
            if (current->timeSlot < timeSlot) current = current->right;
            else current = current->left;
        }
        return false;
    }
};

// Class to manage appointments
class AppointmentScheduler
{
private:
    unordered_map<string, Appointment*> appointments;
    AVLTree availableSlots;

public:
    AppointmentScheduler()
    {
        // Adding some predefined available time slots to the AVL Tree
        availableSlots.insert("09:00");
        availableSlots.insert("10:00");
        availableSlots.insert("11:00");
        availableSlots.insert("12:00");
        availableSlots.insert("13:00");
        availableSlots.insert("14:00");
        availableSlots.insert("15:00");
        availableSlots.insert("16:00");
        availableSlots.insert("17:00");
        availableSlots.insert("18:00");
        availableSlots.insert("19:00");
        availableSlots.insert("20:00");
        availableSlots.insert("21:00");
    }

    void bookAppointment()
    {
        string timeSlot, name, description;

        cout << "Enter time slot (e.g., 10:00): ";
        cin >> timeSlot;

        if (!availableSlots.find(timeSlot))
        {
            cout << "Time slot not available.\n";
            return;
        }

        cout << "Enter your name: ";
        cin >> name;

        cout << "Enter appointment description: ";
        cin.ignore();
        getline(cin, description);

        // Create an appointment and store it
        appointments[timeSlot] = new Appointment(name, description, timeSlot);
        availableSlots.deleteTimeSlot(timeSlot);

        cout << "Appointment booked successfully for " << name << " at " << timeSlot << endl;
    }

    void modifyAppointment()
    {
        string timeSlot, newTimeSlot, name, description;

        cout << "Enter the time slot of the appointment to modify: ";
        cin >> timeSlot;

        if (appointments.find(timeSlot) == appointments.end())
        {
            cout << "No appointment found at " << timeSlot << endl;
            return;
        }

        cout << "Enter new time slot: ";
        cin >> newTimeSlot;

        if (appointments.find(newTimeSlot) != appointments.end())
        {
            cout << "This time slot is already booked.\n";
            return;
        }

        // Modify the appointment
        Appointment* app = appointments[timeSlot];
        name = app->name;
        description = app->description;

        // Delete the old appointment and create a new one with the updated time slot
        appointments.erase(timeSlot);
        availableSlots.insert(timeSlot);

        appointments[newTimeSlot] = new Appointment(name, description, newTimeSlot);
        availableSlots.deleteTimeSlot(newTimeSlot);

        cout << "Appointment modified successfully.\n";
    }

    void cancelAppointment()
    {
        string timeSlot;

        cout << "Enter the time slot of the appointment to cancel: ";
        cin >> timeSlot;

        if (appointments.find(timeSlot) == appointments.end())
        {
            cout << "No appointment found at " << timeSlot << endl;
            return;
        }

        // Delete the appointment and restore the time slot to the AVL tree
        appointments.erase(timeSlot);
        availableSlots.insert(timeSlot);

        cout << "Appointment at " << timeSlot << " has been canceled.\n";
    }

    void displayAppointments()
    {
        cout << "Current appointments:\n";
        for (auto& app : appointments)
        {
            cout << "Time: " << app.second->timeSlot << ", Name: " << app.second->name << ", Description: " << app.second->description << endl;
        }
    }

    void displayAvailableSlots()
    {
        cout << "Available time slots: ";
        availableSlots.displayAvailableSlots();
    }
};

// Healthcare System
class HealthcareSystems
{
private:
    map<int, string> locations;  // Map of locations with IDs and names
    unordered_map<int, vector<string>> hospitalSpecialists;  // Hospital ID -> Specialists
    vector<int> healthcareFacilities;  // List of healthcare facilities (node IDs)

public:
    void initializeData(Graph& cityGraph)
    {
        // Initialize locations
        locations =
        {
            {0, "Colaba"},
            {1, "Nariman Point"},
            {2, "Fort"},
            {3, "Churchgate"},
            {4, "Breach Candy"},
            {5, "Worli"},
            {6, "Lower Parel"},
            {7, "Dadar"},
            {8, "Vile Parle"},
            {9, "Andheri"},
            {10, "Bandra"},
            {11, "Juhu"},
            {12, "Powai"},
            {13, "Kandivali"},
            {14, "Borivali"},
            {15, "Thane"},
            {16, "Kalyan"},
            {17, "Mulund"},
            {18, "Ghatkopar"},
            {19, "Versova"}
        };

        // Add specialists for every location
        hospitalSpecialists =
        {
            {0, {"General Practitioner"}},
            {1, {"Pediatrics", "ENT"}},
            {2, {"Cardiology", "Neurology", "Dermatology"}},
            {3, {"Oncology", "Orthopedics"}},
            {4, {"Ophthalmology", "Gynecology", "Cardiology"}},
            {5, {"Neurology", "General Surgery"}},
            {6, {"Psychiatry", "Endocrinology"}},
            {7, {"Orthopedics", "Pulmonology"}},
            {8, {"Gastroenterology", "Urology"}},
            {9, {"Dermatology", "ENT"}},
            {10, {"Pediatrics", "Psychiatry"}},
            {11, {"Cardiology", "Orthopedics"}},
            {12, {"Neurology", "Gastroenterology"}},
            {13, {"Pulmonology", "Dermatology"}},
            {14, {"Orthopedics", "Gynecology"}},
            {15, {"Oncology", "Cardiology"}},
            {16, {"Neurology", "Ophthalmology"}},
            {17, {"ENT", "Orthopedics"}},
            {18, {"Cardiology", "Gastroenterology"}},
            {19, {"Psychiatry", "Dermatology"}}
        };

        // List of healthcare facilities (hospitals)
        healthcareFacilities = {2, 3, 4, 5, 7, 9, 10, 12, 15, 18};

        // Add edges to the graph (distances between locations)
        cityGraph.addEdge(0, 1, 4);
        cityGraph.addEdge(1, 2, 2);
        cityGraph.addEdge(2, 3, 1);
        cityGraph.addEdge(3, 4, 2);
        cityGraph.addEdge(4, 5, 5);
        cityGraph.addEdge(5, 6, 4);
        cityGraph.addEdge(6, 7, 5);
        cityGraph.addEdge(7, 8, 8);
        cityGraph.addEdge(8, 9, 6);
        cityGraph.addEdge(9, 10, 7);
        cityGraph.addEdge(10, 18, 5);
    }

    void displayAllSpecialties()
    {
        cout << "\nAvailable Specialties for Each Location:\n";
        for (const auto& location : hospitalSpecialists)
            {
            cout << locations[location.first] << ":\n";
            for (const string& specialty : location.second)
            {
                cout << "- " << specialty << endl;
            }
        }
    }

    void displayLocations()
    {
        cout << "\nAvailable Locations with IDs:\n";
        for (const auto& location : locations)
        {
            cout << "ID: " << location.first << " - " << location.second << endl;
        }
    }

    void searchNearestSpecialist(Graph& cityGraph)
    {
        displayLocations();  // Show available locations with IDs

        int userLocation = -1;
        cout << "\nEnter your current location (node ID): ";
        cin >> userLocation;

        if (locations.find(userLocation) == locations.end())
        {
            cout << "Invalid location. Please try again.\n";
            return;
        }

        string desiredSpecialty;
        cout << "Enter the specialty you are looking for: ";
        cin.ignore();
        getline(cin, desiredSpecialty);

        vector<int> parent;
        vector<int> shortestDistances = cityGraph.dijkstraWithPath(userLocation, parent);

        int nearestFacility = -1;
        int minDistance = INT_MAX;

        for (int facility : healthcareFacilities)
            {
            if (find(hospitalSpecialists[facility].begin(), hospitalSpecialists[facility].end(), desiredSpecialty) != hospitalSpecialists[facility].end())
                {
                if (shortestDistances[facility] < minDistance)
                {
                    minDistance = shortestDistances[facility];
                    nearestFacility = facility;
                }
            }
        }

        if (nearestFacility != -1)
        {
            cout << "\nThe nearest facility with " << desiredSpecialty << " is at " << locations[nearestFacility]
                 << " (Distance: " << minDistance << " km).\n";
        }
        else
        {
            cout << "No nearby facility offers this specialty.\n";
        }
    }

    void solveGeographicalBarriers()
    {
        Graph cityGraph(20);
        initializeData(cityGraph);

        int choice;
        do {
            cout << "\nMenu:\n";
            cout << "1. Display all specialties\n";
            cout << "2. Search nearest specialist\n";
            cout << "3. Back to main menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    displayAllSpecialties();
                    break;
                case 2:
                    searchNearestSpecialist(cityGraph);
                    break;
                case 3:
                    cout << "Returning to main menu.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }

        while (choice != 3);
    }
};

// Class to manage appointments
class AppointmentSchedulers
{
private:
    unordered_map<string, Appointment*> appointments;
    AVLTree availableSlots;

public :
    AppointmentSchedulers()
    {
        // Adding some predefined available time slots to the AVL Tree
        availableSlots.insert("09:00");
        availableSlots.insert("10:00");
        availableSlots.insert("11:00");
        availableSlots.insert("12:00");
        availableSlots.insert("13:00");
        availableSlots.insert("14:00");
        availableSlots.insert("15:00");
        availableSlots.insert("16:00");
        availableSlots.insert("17:00");
        availableSlots.insert("18:00");
        availableSlots.insert("19:00");
        availableSlots.insert("20:00");
        availableSlots.insert("21:00");


    }

    void bookAppointment()
    {
        string timeSlot, name, description;

        cout << "Enter time slot (e.g., 10:00): ";
        cin >> timeSlot;

        if (!availableSlots.find(timeSlot))
        {
            cout << "Time slot not available.\n";
            return;
        }

        cout << "Enter your name: ";
        cin >> name;

        cout << "Enter appointment description: ";
        cin.ignore();
        getline(cin, description);

        // Create an appointment and store it
        appointments[timeSlot] = new Appointment(name, description, timeSlot);
        availableSlots.deleteTimeSlot(timeSlot);

        cout << "Appointment booked successfully for " << name << " at " << timeSlot << endl;
    }

    void modifyAppointment()
    {
        string timeSlot, newTimeSlot, name, description;

        cout << "Enter the time slot of the appointment to modify: ";
        cin >> timeSlot;

        if (appointments.find(timeSlot) == appointments.end())
        {
            cout << "No appointment found at " << timeSlot << endl;
            return;
        }

        cout << "Enter new time slot: ";
        cin >> newTimeSlot;

        if (appointments.find(newTimeSlot) != appointments.end())
        {
            cout << "This time slot is already booked.\n";
            return;
        }

        // Modify the appointment
        Appointment* app = appointments[timeSlot];
        name = app->name;
        description = app->description;

        // Delete the old appointment and create a new one with the updated time slot
        appointments.erase(timeSlot);
        availableSlots.insert(timeSlot);

        appointments[newTimeSlot] = new Appointment(name, description, newTimeSlot);
        availableSlots.deleteTimeSlot(newTimeSlot);

        cout << "Appointment modified successfully.\n";
    }

    void cancelAppointment()
    {
        string timeSlot;

        cout << "Enter the time slot of the appointment to cancel: ";
        cin >> timeSlot;

        if (appointments.find(timeSlot) == appointments.end())
        {
            cout << "No appointment found at " << timeSlot << endl;
            return;
        }

        // Delete the appointment and restore the time slot to the AVL tree
        appointments.erase(timeSlot);
        availableSlots.insert(timeSlot);

        cout << "Appointment at " << timeSlot << " has been canceled.\n";
    }

    void displayAppointments()
    {
        cout << "Current appointments:\n";
        for (auto& app : appointments)
        {
            cout << "Time: " << app.second->timeSlot << ", Name: " << app.second->name << ", Description: " << app.second->description << endl;
        }
    }

    void displayAvailableSlots()
    {
        cout << "Available time slots: ";
        availableSlots.displayAvailableSlots();
    }
};


class HealthInformationTrie
{
private:
    TrieNode* root;

    // Helper function for recursive display of topics
    void displayTopicsHelper(TrieNode* node, string currentTopic)
    {
        if (node->isEndOfTopic)
            {
            cout << "Topic: " << currentTopic << endl;
            cout << "Related Articles:" << endl;
            for (const string& article : node->articles)
            {
                cout << "- " << article << endl;
            }
            cout << endl;
        }
        for (auto& child : node->children)
        {
            displayTopicsHelper(child.second, currentTopic + child.first);
        }
    }

public:
    HealthInformationTrie()
    {
        root = new TrieNode();
    }

    // Insert a topic and its related articles into the Trie
    void insert(const string& topic, const vector<string>& articles)
    {
        TrieNode* current = root;
        for (char c : topic)
        {
            if (!current->children.count(c))
            {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfTopic = true;
        current->articles = articles;
    }

    // Search for a topic and display its articles
    void search(const string& topic)
    {
        TrieNode* current = root;
        for (char c : topic)
            {
            if (!current->children.count(c))
            {
                cout << "Topic not found: " << topic << endl;
                return;
            }
            current = current->children[c];
        }
        if (current->isEndOfTopic)
        {
            cout << "Topic Found: " << topic << endl;
            cout << "Related Articles:" << endl;
            for (const string& article : current->articles)
            {
                cout << "- " << article << endl;
            }
        }
        else
        {
            cout << "Topic not found: " << topic << endl;
        }
    }

    // Display all topics and their articles
    void displayAllTopics()
    {
        displayTopicsHelper(root, "");
    }
};

// Function to initialize the database with topics and articles
void initializeDatabase(HealthInformationTrie& trie)
{
    trie.insert("Diabetes", {"Managing blood sugar levels effectively through diet and exercise",
                              "Symptoms of type 1 and type 2 diabetes and how to differentiate them",
                              "Healthy eating habits for preventing complications"});

     trie.insert("Hypertension", {"Understanding the risks of untreated high blood pressure",
                                  "Lifestyle modifications for maintaining healthy blood pressure",
                                  "Different classes of antihypertensive medications and their uses"});

    trie.insert("Nutrition", {"Components of a balanced diet and their benefits",
                              "Role of vitamins and minerals in maintaining overall health",
                              "Top superfoods for boosting immunity and energy levels"});

    trie.insert("Asthma", {"Identifying common triggers for asthma attacks",
                           "Correct techniques for using inhalers and spacers",
                           "Long-term management strategies for persistent asthma"});

    trie.insert("Obesity", {"Factors contributing to obesity including genetics and environment",
                            "Effective approaches to weight loss through sustainable practices",
                            "Understanding the health risks linked to obesity"});

    trie.insert("Cancer", {"Recognizing early warning signs of common cancers",
                           "Understanding the differences between benign and malignant tumors",
                           "Overview of cancer treatments including chemotherapy and immunotherapy"});

    trie.insert("Mental Health", {"How to recognize signs of depression and anxiety",
                                  "Benefits of mindfulness and relaxation techniques",
                                  "Available therapy options including cognitive behavioral therapy"});

    trie.insert("Heart Disease", {"Preventing cardiovascular diseases through lifestyle changes",
                                  "Recognizing symptoms of a heart attack and acting quickly",
                                  "Long-term benefits of maintaining a healthy heart"});

    trie.insert("Allergies", {"Common allergens and their impact on the immune system",
                              "Techniques for managing seasonal allergies effectively",
                              "Latest treatment options including allergy shots"});

    trie.insert("Arthritis", {"Distinguishing between osteoarthritis and rheumatoid arthritis",
                              "Effective exercises to reduce joint pain and stiffness",
                              "Medications that help manage arthritis symptoms"});

    trie.insert("Smoking Cessation", {"Practical tips for quitting smoking permanently",
                                      "Health improvements observed after quitting smoking",
                                      "Resources available for smokers looking to quit"});

    trie.insert("Pregnancy", {"Essentials of prenatal care and regular health check-ups",
                              "Recommended dietary guidelines for pregnant women",
                              "Common complications during pregnancy and how to manage them"});

    trie.insert("Gut Health", {"Maintaining a healthy gut microbiome",
                               "Role of probiotics in gut health",
                               "Foods that promote digestive health"});

    trie.insert("Immune System", {"Ways to boost your immune system naturally",
                                  "The role of nutrition in immune health",
                                  "Common immune system disorders and their prevention"});

    trie.insert("Blood Circulation", {"Improving circulation through exercise",
                                      "Signs of poor blood circulation",
                                      "Dietary habits for better circulation"});

    trie.insert("Liver Health", {"Foods that support liver function",
                                 "How to recognize early signs of liver disease",
                                 "The impact of alcohol on liver health"});

    trie.insert("Kidney Health", {"Preventing kidney disease through hydration",
                                  "Signs of kidney problems and how to detect them early",
                                  "Managing kidney disease with lifestyle changes"});

    trie.insert("Mental Health in Children", {"Recognizing signs of anxiety and depression in children",
                                              "Effective communication with children on mental health",
                                              "Resources for supporting children's mental well-being"});

    trie.insert("Posture and Ergonomics", {"Importance of good posture in preventing back pain",
                                          "Setting up an ergonomic workspace",
                                          "Exercises to improve posture"});

    trie.insert("Healthy Aging", {"Staying physically active as you age",
                                  "Importance of mental health in aging",
                                  "How to maintain good nutrition throughout life"});

    trie.insert("Dehydration", {"Symptoms of dehydration and how to stay hydrated",
                                "The impact of dehydration on health",
                                "Tips for improving hydration habits"});

    trie.insert("Healthy Skin", {"Building a skincare routine for healthy skin",
                                 "How to prevent premature aging",
                                 "Dietary recommendations for glowing skin"});

    trie.insert("Breathing Exercises", {"Techniques for deep breathing and relaxation",
                                       "Benefits of breathing exercises for stress management",
                                       "Exercises to improve lung capacity"});

    trie.insert("Exercise for Seniors", {"Low-impact exercises for seniors",
                                         "The benefits of staying active in older age",
                                         "Precautions to take when exercising as a senior"});

    trie.insert("Alzheimer's Disease", {"Understanding the early signs and symptoms of Alzheimer's disease",
                                    "Current treatment options and approaches to manage cognitive decline",
                                    "Tips for supporting loved ones with Alzheimer's and improving quality of life"});

    trie.insert("Chronic Obstructive Pulmonary Disease (COPD)", {"Risk factors and causes of COPD",
                                                           "Managing symptoms and slowing disease progression",
                                                           "Lifestyle changes and medications for COPD patients"});

    trie.insert("Parkinson's Disease", {"Early signs and symptoms of Parkinson's disease",
                                   "Medications and therapies for managing Parkinson's disease",
                                   "Supportive care for people with Parkinson's to improve quality of life"});

    trie.insert("Multiple Sclerosis (MS)", {"Symptoms of multiple sclerosis and how it affects the nervous system",
                                       "Treatment options for managing MS symptoms and preventing flare-ups",
                                       "Living well with MS: tips for coping with the challenges"});

    trie.insert("Tuberculosis (TB)", {"Symptoms and stages of tuberculosis infection",
                                  "Risk factors for contracting tuberculosis and preventive measures",
                                  "Treatment regimens and the importance of completing TB medication"});

    trie.insert("HIV/AIDS", {"Understanding the transmission and prevention of HIV",
                        "Antiretroviral therapy (ART) for managing HIV",
                        "Living with HIV: coping strategies and improving quality of life"});

    trie.insert("Stroke", {"Recognizing the early signs of a stroke (FAST method)",
                       "Immediate treatment and recovery steps after a stroke",
                       "Preventive measures and lifestyle changes to reduce the risk of stroke"});

    trie.insert("Kidney Disease", {"Causes and risk factors for chronic kidney disease",
                               "Managing kidney disease through diet and medication",
                               "How to prevent kidney disease and the importance of regular check-ups"});

    trie.insert("Liver Disease", {"Common causes of liver disease, such as hepatitis and fatty liver",
                              "Signs and symptoms of liver disease and when to seek help",
                              "Treatment options and preventive measures for liver health"});

    trie.insert("Epilepsy", {"Understanding different types of seizures and their causes",
                        "Treatment and medication options for managing epilepsy",
                        "Support strategies for living with epilepsy and preventing seizures"});

    trie.insert("Anemia", {"Causes and types of anemia, such as iron-deficiency anemia",
                      "Symptoms of anemia and how to address them",
                      "Dietary recommendations and supplements to prevent or treat anemia"});

    trie.insert("Psoriasis", {"Identifying symptoms of psoriasis and its types",
                         "Medications and therapies available to manage psoriasis flare-ups",
                         "Lifestyle changes and skin care tips for people with psoriasis"});

    trie.insert("Gout", {"Understanding the causes of gout and the role of uric acid",
                    "Managing gout flare-ups with diet and medications",
                    "Preventing future gout attacks through lifestyle changes"});

    trie.insert("Celiac Disease", {"What is celiac disease and how it affects the digestive system",
                               "Living gluten-free: tips for managing celiac disease",
                               "Symptoms of celiac disease and the importance of early diagnosis"});

    trie.insert("Osteoporosis", {"How osteoporosis weakens bones and increases fracture risk",
                             "Preventing osteoporosis with calcium, vitamin D, and weight-bearing exercise",
                             "Managing osteoporosis through medications and lifestyle changes"});

    // Add more topics as needed...
}

// Function to display health tips
void displayHealthTips()
{
    cout << "--- Health Tips ---" << endl;
    cout << "1. Practice gratitude for better mental health." << endl;
    cout << "2. Limit screen time, especially before bed, to improve sleep quality." << endl;
    cout << "3. Take regular breaks if working at a desk to stretch and move around." << endl;
    cout << "4. Engage in activities that boost your mood and mental well-being." << endl;
    cout << "5. Prevent eye strain by following the 20-20-20 rule." << endl;
    cout << "6. Boost your fiber intake by eating more whole grains, fruits, and vegetables." << endl;
    cout << "7. Stay active throughout the day, take the stairs, walk or bike whenever possible." << endl;
    cout << "8. Learn relaxation techniques such as deep breathing to manage stress." << endl;
    cout << "9. Use essential oils like lavender to reduce stress and improve sleep." << endl;
    cout << "10. Foster positive thinking and reduce anxiety by focusing on the positives." << endl;
    cout << "11. Eat More Leafy Greens - Incorporate spinach, kale, and other leafy greens to support heart health and digestion." << endl;
    cout << "12. Maintain a Consistent Sleep Schedule - Going to bed and waking up at the same time each day can improve sleep quality." << endl;
    cout << "13. Limit Processed Foods - Reducing intake of processed and sugary foods can help manage weight and lower the risk of chronic diseases." << endl;
    cout << "14. Practice Deep Breathing - Engage in deep breathing exercises to reduce anxiety and promote relaxation." << endl;
    cout << "15. Stay Socially Connected - Engaging in regular social activities can boost mental health and reduce feelings of loneliness." << endl;
    cout << "16. Keep a Food Journal - Tracking your food intake can help you identify and correct unhealthy eating patterns." << endl;
    cout << "17. Reduce Caffeine Intake - Limiting caffeine consumption, especially in the afternoon and evening, can help improve sleep." << endl;
    cout << "18. Wash Your Hands Regularly - Good hand hygiene is one of the best ways to prevent the spread of infections." << endl;
    cout << "19. Do Regular Mental Exercises - Engage in activities like puzzles or learning new skills to keep your brain sharp." << endl;
    cout << "20. Maintain a Healthy Weight - Aim for a healthy body mass index (BMI) through balanced diet and regular exercise." << endl;
    cout << "21. Get Fresh Air - Spending time outdoors, even for just a few minutes each day, can improve mood and boost Vitamin D levels." << endl;
    cout << "22. Practice Good Oral Hygiene - Brushing and flossing your teeth daily helps prevent gum disease and tooth decay." << endl;
    cout << "23. Don't Skip Breakfast - Starting the day with a healthy breakfast can boost energy levels and metabolism." << endl;
    cout << "24. Drink Green Tea - Rich in antioxidants, green tea can help with metabolism and overall health." << endl;
    cout << "25. Limit Alcohol Consumption - Keeping alcohol intake moderate can reduce the risk of liver disease, high blood pressure, and other health issues." << endl;
    cout << "26. Stretch Daily - Stretching can improve flexibility, prevent injury, and reduce muscle tension." << endl;
    cout << "27. Use Sunscreen - Always protect your skin from UV rays to reduce the risk of skin cancer and premature aging." << endl;
    cout << "28. Reduce Stress - Find stress-relief methods such as yoga, meditation, or spending time in nature." << endl;
    cout << "29. Take Time for Hobbies - Engaging in hobbies you enjoy can reduce stress and promote a sense of well-being." << endl;
    cout << "30. Practice Mindful Eating - Pay attention to your hunger cues and eat slowly to improve digestion and prevent overeating." << endl;

    // Add more health tips as needed...
}

struct Modification
{
    string treatment;
    double oldCost;
    double newCost;
};

struct Patient
{
    string name;
    int severity; // Lower values indicate higher severity (e.g., 1 is critical)
    int arrivalOrder; // To break ties based on arrival order

    bool operator<(const Patient& other) const
    {
        if (severity == other.severity)
        {
            return arrivalOrder > other.arrivalOrder;
        }
        return severity > other.severity;
    }
};

class TreatmentCostCalculator
{
private:
    unordered_map<string, double> costTable; // Hash table for treatment costs
    stack<Modification> undoStack;          // Stack for undo operations
    stack<Modification> redoStack;          // Stack for redo operations

public:
    void addOrUpdateCost(const string& treatment, double cost)
    {
        double oldCost = costTable.count(treatment) ? costTable[treatment] : -1;
        costTable[treatment] = cost;

        undoStack.push({treatment, oldCost, cost});
        while (!redoStack.empty()) redoStack.pop();

        cout << "Cost updated for treatment: " << treatment << " ($" << fixed << setprecision(2) << cost << ")\n";
    }

    void removeCost(const string& treatment)
    {
        if (costTable.count(treatment))
            {
            double oldCost = costTable[treatment];
            costTable.erase(treatment);

            undoStack.push({treatment, oldCost, -1});
            while (!redoStack.empty()) redoStack.pop();

            cout << "Treatment removed: " << treatment << "\n";
        }
        else
        {
            cout << "Treatment not found: " << treatment << "\n";
        }
    }

    void undo()
    {
        if (undoStack.empty())
        {
            cout << "Nothing to undo!\n";
            return;
        }

        Modification lastModification = undoStack.top();
        undoStack.pop();

        if (lastModification.oldCost == -1)
        {
            costTable.erase(lastModification.treatment);
        }
        else
        {
            costTable[lastModification.treatment] = lastModification.oldCost;
        }

        redoStack.push(lastModification);

        cout << "Undo performed for treatment: " << lastModification.treatment << "\n";
    }

    void redo()
    {
        if (redoStack.empty())
        {
            cout << "Nothing to redo!\n";
            return;
        }

        Modification lastModification = redoStack.top();
        redoStack.pop();

        if (lastModification.newCost == -1)
        {
            costTable.erase(lastModification.treatment);
        }
        else
        {
            costTable[lastModification.treatment] = lastModification.newCost;
        }

        undoStack.push(lastModification);

        cout << "Redo performed for treatment: " << lastModification.treatment << "\n";
    }

    void displayCosts() const
    {
        if (costTable.empty())
        {
            cout << "No treatments available.\n";
            return;
        }

        cout << "\nTreatment Costs:\n";
        for (const auto& pair : costTable)
        {
            cout << "- " << pair.first << ": $" << fixed << setprecision(2) << pair.second << "\n";
        }
    }
};

class EmergencyTriageSystem
{
private:
    priority_queue<Patient> triageQueue; // Priority queue for managing patients
    int patientCounter; // To track arrival order

public:
    EmergencyTriageSystem() : patientCounter(0) {}

    void addPatient(const string& name, int severity)
    {
        triageQueue.push({name, severity, patientCounter++});
        cout << "Patient added: " << name << " (Severity: " << severity << ")\n";
    }

    void attendPatient()
    {
        if (triageQueue.empty())
        {
            cout << "No patients to attend to.\n";
            return;
        }

        Patient nextPatient = triageQueue.top();
        triageQueue.pop();

        cout << "Attending to patient: " << nextPatient.name << " (Severity: " << nextPatient.severity << ")\n";
    }

    void displayPatients()
    {
        if (triageQueue.empty())
        {
            cout << "No patients in the queue.\n";
            return;
        }

        priority_queue<Patient> tempQueue = triageQueue;
        cout << "\nPatients in the queue (sorted by priority):\n";
        while (!tempQueue.empty())
        {
            Patient patient = tempQueue.top();
            tempQueue.pop();
            cout << "- " << patient.name << " (Severity: " << patient.severity << ")\n";
        }
    }
};
// ---------------------------- Blood and Organ Donation Tracker -----------------------------

// Define Donor structure
struct Donor
{
    string name;
    string bloodType;
    string organType;

    Donor(string n, string b, string o) : name(n), bloodType(b), organType(o) {}
};

// Blood and Organ Donation Tracker class
class BloodOrganDonationTracker
{
private:
    unordered_map<string, vector<Donor>> donorDatabase; // Organ type as key, list of compatible donors as value

public:
    // Preloaded Donors (Expanded Database)
    BloodOrganDonationTracker()
    {
        // Kidney Donors
        donorDatabase["KIDNEY"] =
        {
            Donor("John Doe", "O+", "Kidney"),
            Donor("Charlie Davis", "A-", "Kidney"),
            Donor("Grace Clark", "O-", "Kidney"),
            Donor("Jack Hall", "B+", "Kidney"),
            Donor("Olivia Moore", "AB-", "Kidney"),
            Donor("Samantha Lee", "A+", "Kidney"),
            Donor("David White", "O-", "Kidney"),
            Donor("Barbara Adams", "O+", "Kidney")
        };

        // Liver Donors
        donorDatabase["LIVER"] =
        {
            Donor("Jane Smith", "A+", "Liver"),
            Donor("David Evans", "O-", "Liver"),
            Donor("Isabel Walker", "O+", "Liver"),
            Donor("Kathy Allen", "B+", "Liver"),
            Donor("Michael Green", "AB-", "Liver"),
            Donor("Sophia King", "B-", "Liver")
        };

        // Heart Donors
        donorDatabase["HEART"] =
        {
            Donor("Alice Johnson", "B+", "Heart"),
            Donor("Leo Young", "AB+", "Heart"),
            Donor("Nathan Scott", "O-", "Heart"),
            Donor("Rachel Adams", "B-", "Heart"),
            Donor("Franklin Davis", "A+", "Heart"),
            Donor("Mia Taylor", "O+", "Heart")
        };

        // Lung Donors
        donorDatabase["LUNG"] =
        {
            Donor("Bob Brown", "O-", "Lung"),
            Donor("Frank Harris", "A+", "Lung"),
            Donor("Kathy Allen", "O+", "Lung"),
            Donor("Olivia Scott", "AB+", "Lung"),
            Donor("Carlos Miller", "B+", "Lung")
        };

        // Cornea Donors
        donorDatabase["CORNEA"] =
        {
            Donor("Sarah Thomas", "O+", "Cornea"),
            Donor("Andrew Perez", "A-", "Cornea"),
            Donor("Lucas Carter", "B-", "Cornea"),
            Donor("Ella Wright", "A+", "Cornea"),
            Donor("Ryan Harris", "O-", "Cornea")
        };
    }

    // Method to find compatible donors by both blood type and organ type
    void findCompatibleDonorsByBloodAndOrgan(string bloodType, string organType)
    {
        transform(bloodType.begin(), bloodType.end(), bloodType.begin(), ::toupper);
        transform(organType.begin(), organType.end(), organType.begin(), ::toupper);

        cout << "Searching for donors with blood type: " << bloodType << " and organ type: " << organType << endl;

        auto organIt = donorDatabase.find(organType);
        if (organIt != donorDatabase.end())
            {
            bool found = false;
            for (const auto& donor : organIt->second)
                {
                if (donor.bloodType == bloodType)
                {
                    cout << donor.name << " (Blood Type: " << donor.bloodType << ", Organ: " << donor.organType << ")" << endl;
                    found = true;
                }
            }
            if (!found)
            {
                cout << "No compatible donors found with the given blood type and organ type.\n";
            }
        }
        else
        {
            cout << "No donors found for the given organ type.\n";
        }
    }

    // Method to find compatible donors by organ type
    void findCompatibleDonorsByOrgan(string organType)
    {
        transform(organType.begin(), organType.end(), organType.begin(), ::toupper);
        cout << "Searching for donors with organ type: " << organType << endl;

        auto organIt = donorDatabase.find(organType);
        if (organIt != donorDatabase.end())
            {
            cout << "List of compatible donors for " << organType << ":\n";
            for (const auto& donor : organIt->second)
            {
                cout << donor.name << " (Blood Type: " << donor.bloodType << ", Organ: " << donor.organType << ")" << endl;
            }
        }
        else
        {
            cout << "No donors found for the given organ type.\n";
        }
    }

    // Method to find compatible donors by blood type
    void findCompatibleDonorsByBlood(string bloodType)
    {
        transform(bloodType.begin(), bloodType.end(), bloodType.begin(), ::toupper);
        cout << "Searching for donors with blood type: " << bloodType << endl;

        bool found = false;
        for (const auto& organEntry : donorDatabase)
            {
            for (const auto& donor : organEntry.second)
            {
                if (donor.bloodType == bloodType)
                {
                    cout << donor.name << " (Blood Type: " << donor.bloodType << ", Organ: " << donor.organType << ")" << endl;
                    found = true;
                }
            }
        }
        if (!found)
        {
            cout << "No compatible donors found with the given blood type.\n";
        }
    }

    // Method to add a new donor to the database
    void addNewDonor()
    {
        string name, bloodType, organType;
        cout << "Enter donor name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter donor blood type (e.g., O+, A-, B+): ";
        getline(cin, bloodType);
        cout << "Enter donor organ type (e.g., KIDNEY, LIVER, HEART): ";
        getline(cin, organType);

        // Convert blood type and organ type to uppercase for consistency
        transform(bloodType.begin(), bloodType.end(), bloodType.begin(), ::toupper);
        transform(organType.begin(), organType.end(), organType.begin(), ::toupper);

        // Add the new donor to the database
        donorDatabase[organType].push_back(Donor(name, bloodType, organType));
        cout << "New donor added successfully.\n";
    }

    // Method to display all donors
    void displayAllDonors()
    {
        cout << "Displaying all donors:\n";
        for (const auto& organEntry : donorDatabase)
            {
            cout << "Organ Type: " << organEntry.first << "\n";
            for (const auto& donor : organEntry.second)
            {
                cout << donor.name << " (Blood Type: " << donor.bloodType << ", Organ: " << donor.organType << ")\n";
            }
        }
    }
};
// Equipment Inventory System Code
struct Equipment
{
    string name;
    bool isAvailable;
    int priority;

    Equipment(string n, bool avail, int prio) : name(n), isAvailable(avail), priority(prio) {}

    bool operator<(const Equipment& other) const
    {
        return priority < other.priority;  // Higher priority comes first
    }
};

string toLowerCase(const string& str)
{
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

class EquipmentInventorySystem
{
private:
    vector<Equipment> inventory;
    priority_queue<Equipment> pq;

    void rebuildPriorityQueue()
    {
        // Rebuild the priority queue to reflect the current availability status
        priority_queue<Equipment> newPQ;
        for (const auto& eq : inventory)
            {
            if (eq.isAvailable)
            {
                newPQ.push(eq);
            }
        }
        pq = newPQ;
    }

public:
    void addEquipment(string name, bool isAvailable, int priority)
    {
        Equipment newEquipment(name, isAvailable, priority);
        inventory.push_back(newEquipment);
        if (isAvailable) pq.push(newEquipment);
    }

    void allocateEquipment()
    {
        // Ensure there are available equipment to allocate
        while (!pq.empty() && !pq.top().isAvailable) pq.pop();

        if (pq.empty())
        {
            cout << "No equipment available to allocate.\n";
            return;
        }

        // Allocate the equipment with the highest priority
        Equipment allocated = pq.top();
        pq.pop();

        cout << "Allocating equipment: " << allocated.name << " (Priority: " << allocated.priority << ")\n";

        // Mark the equipment as unavailable
        for (auto& equipment : inventory)
            {
            if (equipment.name == allocated.name)
            {
                equipment.isAvailable = false;
                break;
            }
        }

        rebuildPriorityQueue(); // Rebuild the priority queue after allocation
    }

    void checkAvailability(string name)
    {
        string lowerName = toLowerCase(name);  // Convert input name to lowercase
        auto it = find_if(inventory.begin(), inventory.end(), [&lowerName](const Equipment& eq)
        {
            return toLowerCase(eq.name) == lowerName;  // Convert each equipment name to lowercase and compare
        });

        if (it != inventory.end())
            {
            if (it->isAvailable)
            {
                cout << it->name << " is available.\n";
            }
            else
            {
                cout << it->name << " is currently in use.\n";
            }
        }
        else
        {
            cout << "Equipment " << name << " not found in inventory.\n";
        }
    }

    void displayInventory()
    {
        cout << "\nEquipment Inventory:\n";
        for (const auto& eq : inventory)
        {
            cout << "Name: " << eq.name
                 << ", Availability: " << (eq.isAvailable ? "Available" : "In Use")
                 << ", Priority: " << eq.priority << endl;
        }
    }
};

// Structure to store emergency contact information

struct EmergencyContact
{
    string name;
    string contactNumber;
    string serviceType;  // E.g., Police, Fire, Ambulance, etc.
    double x;  // X coordinate of the service location
    double y;  // Y coordinate of the service location
    double distance;  // Distance from the user's location (calculated later)
};

// Structure to represent an activity with its name, duration, category, and description
struct Activity
{
    string name;
    int duration;  // Duration in minutes
    string category;  // Category of activity (e.g., sightseeing, adventure, culture)
    string description;  // A short description of the activity
    int travelTime;  // Time it takes to travel to this activity from the previous one (in minutes)

    Activity(string n, int d, string c, string desc, int t)
        : name(n), duration(d), category(c), description(desc), travelTime(t) {}
};
// Structure to hold efficiency tips
struct Tip
{
    string title;       // Title of the tip
    string description; // Description of the tip
    vector<string> keywords; // Keywords related to the tip
};

// Structure to store Tourist details
struct Tourist
{
    int id; // Unique identifier for the tourist
    string name; // Name of the tourist
    string locationPreference; // Preferred location for accommodation
    double maxPrice; // Maximum price the tourist is willing to pay
    bool allocated; // Allocation status
    bool reallocated; // Reallocation status
    string reason; // Reason for allocation or non-allocation

    // Constructor to initialize a Tourist
    Tourist(int id, string name, string locationPreference, double maxPrice)
        : id(id), name(name), locationPreference(locationPreference),
          maxPrice(maxPrice), allocated(false), reallocated(false), reason("Not allocated initially") {}
};

// Structure to store Room details
struct Room
{
    int id; // Unique identifier for the room
    string location; // Location of the room
    int capacity; // Total capacity of the room
    int remainingCapacity; // Remaining capacity of the room
    double price; // Price of the room

    // Constructor to initialize a Room
    Room(int id, string location, int capacity, double price)
        : id(id), location(location), capacity(capacity), remainingCapacity(capacity), price(price) {}
};

// Structure to hold information about problems and their solutions
struct Problem
 {
    string problemName;
    string description;
    string solution; // Added for the second part of the code
};


// Shelter structure for cleanliness-based allocation
struct CleanlinessShelter
{
    int id;
    int capacity;
    int occupied;
    int priority; // Lower value means higher priority
    bool isAccessible;
    int cleanliness; // Cleanliness level (0 to 10)
    string name; // Name of the shelter

    CleanlinessShelter(int id, int capacity, int priority, bool isAccessible, int cleanliness, string name)
        : id(id), capacity(capacity), occupied(0), priority(priority), isAccessible(isAccessible), cleanliness(cleanliness), name(name) {}
};

// Tourist structure for cleanliness-based allocation
struct CleanlinessTourist
 {
    int id;
    string name;
    int costPerUnitDistance;
    bool hasSpecialPreference;
    int preferredShelter;
    bool isAllocated;
    int allocatedShelter;
    string reason; // Reason for allocation or reallocation

    CleanlinessTourist(int id, string name, int costPerUnitDistance, bool hasSpecialPreference, int preferredShelter)
        : id(id), name(name), costPerUnitDistance(costPerUnitDistance), hasSpecialPreference(hasSpecialPreference), preferredShelter(preferredShelter),
          isAllocated(false), allocatedShelter(-1) {}
};

// Shelter structure for distance-based allocation
struct DistanceShelter
 {
    int id;
    int capacity;
    int occupied;
    string name; // Name of the shelter

    DistanceShelter(int id, int capacity, string name) : id(id), capacity(capacity), occupied(0), name(name) {}
};

// Tourist structure for distance-based allocation
struct DistanceTourist
{
    int id;
    string name;
    bool isAllocated;        // True if allocated, false otherwise
    int allocatedShelter;    // ID of allocated shelter, -1 if not allocated
    string reason;           // Reason for reallocation or non-allocation

    DistanceTourist(int id, string name) : id(id), name(name), isAllocated(false), allocatedShelter(-1), reason("") {}
};


// Function to calculate distance between two points (Euclidean distance)
double calculateDistance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Function to display the emergency contact list
void displayEmergencyContacts(const vector<EmergencyContact>& contacts)
 {
    cout << "Emergency Services in Mumbai:" << endl;
    for (size_t i = 0; i < contacts.size(); ++i)
    {
        cout << i + 1 << ". " << contacts[i].name << " (" << contacts[i].serviceType << ")" << endl;
        cout << "   Contact Number: " << contacts[i].contactNumber << endl;
        cout << "   Location: (" << contacts[i].x << ", " << contacts[i].y << ")" << endl;
    }
}

// Function to find the nearest emergency contact based on the user's location
EmergencyContact findNearestContact(const vector<EmergencyContact>& contacts, double userX, double userY)
    {
    EmergencyContact nearestContact;
    double minDistance = numeric_limits<double>::max(); // Start with a very large distance

    for (size_t i = 0; i < contacts.size(); ++i)
    {
        // Calculate the distance from the user's location to the emergency contact
        double distance = calculateDistance(userX, userY, contacts[i].x, contacts[i].y);
        if (distance < minDistance)
        {
            minDistance = distance;
            nearestContact = contacts[i];
        }
    }
    nearestContact.distance = minDistance;
    return nearestContact;
}

// Function to get user location input
void getUserLocation(double& userX, double& userY)
{
    cout << "\nPlease enter your location's X coordinate: ";
    cin >> userX;

    cout << "Please enter your location's Y coordinate: ";
    cin >> userY;
}

// Function to handle emergency services selection
void handleServiceSelection(const vector<EmergencyContact>& contacts)
    {
    int serviceChoice;
    double userX, userY;
    cout << "\nEnter the number corresponding to the emergency service you need:" << endl;
    cout << "1. Police\n2. Fire\n3. Ambulance\n4. Hospital\n5. Disaster Control\n";
    cin >> serviceChoice;

    getUserLocation(userX, userY);

    // Filter contacts based on the selected service
    vector<EmergencyContact> filteredContacts;
    for (size_t i = 0; i < contacts.size(); ++i)
        {
        if ((serviceChoice == 1 && contacts[i].serviceType == "Police") ||
            (serviceChoice == 2 && contacts[i].serviceType == "Fire") ||
            (serviceChoice == 3 && contacts[i].serviceType == "Ambulance") ||
            (serviceChoice == 4 && contacts[i].serviceType == "Hospital") ||
            (serviceChoice == 5 && contacts[i].serviceType == "Disaster Control"))
        {
            filteredContacts.push_back(contacts[i]);
        }
    }

    if (filteredContacts.empty())
    {
        cout << "No service found for the selected option!" << endl;
        return;
    }

    // Find nearest emergency contact from the filtered list
    EmergencyContact nearest = findNearestContact(filteredContacts, userX, userY);
    cout << "\nThe nearest " << nearest.serviceType << " service is: " << endl;
    cout << nearest.name << " at location (" << nearest.x << ", " << nearest.y << ")" << endl;
    cout << "Contact Number: " << nearest.contactNumber << endl;
    cout << "Distance from your location: " << nearest.distance << " km" << endl;
}

// Function to handle user input for continuing the program or exiting
void handleUserExit()
    {
    char continueChoice;
    cout << "\nWould you like to search for another emergency service? (y/n): ";
    cin >> continueChoice;

    if (continueChoice == 'y' || continueChoice == 'Y')
    {
        return;
    }
    else
    {
        cout << "Thank you for using the Emergency Contact Finder. Stay safe!" << endl;
        exit(0);
    }
}

// Function to validate user input for coordinates
bool isValidCoordinate(double coord)
{
    if (coord < -180.0 || coord > 180.0)
    {
        cout << "Invalid coordinate! Coordinates must be between -180 and 180 degrees." << endl;
        return false;
    }
    return true;
}

// Function to add a new emergency contact
void addEmergencyContact(vector<EmergencyContact>& contacts)
{
    EmergencyContact newContact;
    cout << "\nEnter the name of the new service: ";
    cin.ignore();
    getline(cin, newContact.name);

    cout << "Enter the contact number: ";
    getline(cin, newContact.contactNumber);

    cout << "Enter the service type (Police, Fire, Ambulance, Hospital, Disaster Control): ";
    getline(cin, newContact.serviceType);

    double x, y;
    cout << "Enter the X coordinate for the service location: ";
    cin >> x;

    while (!isValidCoordinate(x))
        {
        cout << "Please enter a valid X coordinate: ";
        cin >> x;
    }

    cout << "Enter the Y coordinate for the service location: ";
    cin >> y;

    while (!isValidCoordinate(y))
    {
        cout << "Please enter a valid Y coordinate: ";
        cin >> y;
    }

    newContact.x = x;
    newContact.y = y;
    newContact.distance = 0.0; // Distance will be calculated later
    contacts.push_back(newContact);

    cout << "New emergency contact added successfully!" << endl;
}

// Function to remove an emergency contact by index
void removeEmergencyContact(vector<EmergencyContact>& contacts)
{
    int index;
    cout << "\nEnter the number of the service to remove (1 - " << contacts.size() << "): ";
    cin >> index;
    if (index > 0 && index <= contacts.size())
    {
        contacts.erase(contacts.begin() + index - 1);
        cout << "Emergency contact removed successfully!" << endl;
    }
    else
    {
        cout << "Invalid selection! No contact removed." << endl;
    }
}

// Function to display the menu options for emergency services
void displayEmergencyMenu()
{
    cout<<"----------------------------------\n";
    cout << "1. View All Emergency Contacts\n";
    cout << "2. Find Nearest Emergency Service\n";
    cout << "3. Add New Emergency Contact\n";
    cout << "4. Remove Emergency Contact\n";
    cout << "5.Back to main menu" << endl;

}

// Function to handle user input and process the selected option for emergency services
void handleEmergencyMenuSelection(vector<EmergencyContact>& contacts)
{
    int userChoice;
     cout << "\nWelcome to the Mumbai Emergency Contact Finder!" << endl;
    do
    {
    displayEmergencyMenu();
    cout << "Enter your choice: ";
    cin >> userChoice;

    switch (userChoice)
    {
        case 1:
            displayEmergencyContacts(contacts);
            break;
        case 2:
            handleServiceSelection(contacts);
            break;
        case 3:
            addEmergencyContact(contacts);
            break;
        case 4:
            removeEmergencyContact(contacts);
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice! Please enter a valid option." << endl;
    }
}

while(userChoice!=5);
}

// Function to display the list of activities
void displayActivities(const vector<Activity>& activities)
 {
    cout << "\nAvailable Activities:\n";
    for (size_t i = 0; i < activities.size(); ++i)
        {
        cout << i + 1 << ". " << activities[i].name
             << " (Duration: " << activities[i].duration
             << " minutes, Category: " << activities[i].category << ")\n"
             << "   Description: " << activities[i].description << "\n";
    }
}

// Function to display unique categories
set<string> getUniqueCategories(const vector<Activity>& activities)
{
    set<string> categories;
    for (const auto& activity : activities)
        {
        categories.insert(activity.category);
    }
    return categories;
}

// Comparator to sort activities by duration (shortest first)
bool compareDuration(Activity a, Activity b)
{
    return a.duration < b.duration;
}

// Function to plan the itinerary based on available time
void planItinerary(vector<Activity>& activities, int availableTime)
{
    // Sort activities based on duration (Greedy approach)
    sort(activities.begin(), activities.end(), compareDuration);

    cout << "\nOptimized Itinerary:\n";
    int totalTime = 0;
    int totalActivities = 0;
    int currentTime = 0;

    // Iterate over sorted activities and add them if they fit in the available time
    for (size_t i = 0; i < activities.size(); ++i)
    {
        if (currentTime + activities[i].duration + activities[i].travelTime <= availableTime)
            {
            cout << "Activity: " << activities[i].name
                 << " (Duration: " << activities[i].duration << " minutes)\n"
                 << "   Description: " << activities[i].description << "\n";
            currentTime += activities[i].duration + activities[i].travelTime;
            totalTime += activities[i].duration;
            totalActivities++;
        }
        else
        {
            break;  // No more time to add activities
        }
    }

    if (totalActivities == 0)
    {
        cout << "Sorry, there is not enough time to visit any activities.\n";
    }
    else
    {
        cout << "\nTotal time spent: " << currentTime << " minutes\n";
        cout << "Total number of activities: " << totalActivities << "\n";
    }
}

// Function to filter activities based on the category selected by the user
vector<Activity> filterActivitiesByCategory(const vector<Activity>& activities, const string& category)
{
    vector<Activity> filtered;
    for (const auto& activity : activities)
    {
        if (activity.category == category)
            {
            filtered.push_back(activity);
        }
    }

    return filtered;
}

// Function to add a new activity
void addActivity(vector<Activity>& activities)
{
    string name, category, description;
    int duration, travelTime;

    cout << "\nEnter the name of the activity: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, name);
    cout << "Enter the duration (in minutes): ";
    cin >> duration;
    cout << "Enter the category (e.g., sightseeing, adventure, culture): ";
    cin.ignore(); // Clear the input buffer
    getline(cin, category);
    cout << "Enter a short description: ";
    getline(cin, description);
    cout << "Enter travel time to this activity (in minutes): ";
    cin >> travelTime;

    activities.push_back(Activity(name, duration, category, description, travelTime));
    cout << "Activity added successfully!\n";
}

// Function to remove an activity
void removeActivity(vector<Activity>& activities)
   {
    int index;
    displayActivities(activities);
    cout << "Enter the number of the activity you want to remove: ";
    cin >> index;

    if (index > 0 && index <= activities.size())
    {
        activities.erase(activities.begin() + index - 1);
        cout << "Activity removed successfully!\n";
    }
    else
    {
        cout << "Invalid activity number.\n";
    }
}

// Function to display a welcome message
void displayWelcomeMessage()
{
    cout << "\n....Welcome to the Mumbai Tourist Itinerary Planner!...\n";
    cout << "This program helps you plan your itinerary based on available activities.\n";
    cout << "You can add, remove, and filter activities based on categories.\n";
}

// Function to display the menu options for itinerary planning

void displayItineraryMenu()
{
    cout << "\n---Itinerary Menu:----\n";
    cout << "1. Plan Itinerary\n";
    cout << "2. Add Activity\n";
    cout << "3. Remove Activity\n";
    cout << "4. View Activities by Category\n";
    cout << "5. Display Categories\n";
    cout << "6. Main Menu\n";
}

// Function to initialize activities with some default values

void initializeActivities(vector<Activity>& activities)
{
    activities.push_back(Activity("Visit Gateway of India", 120, "sightseeing", "A historical monument overlooking the Arabian Sea.", 30));
    activities.push_back(Activity("Explore Marine Drive", 90, "sightseeing", "A scenic promenade along the coast.", 15));
    activities.push_back(Activity("Enjoy a Bollywood Movie", 180, "entertainment", "Watch a popular Bollywood film in a local theater.", 20));
    activities.push_back(Activity("Visit Chhatrapati Shivaji Maharaj Terminus", 60, "sightseeing", "A UNESCO World Heritage Site and historic railway station.", 10));
    activities.push_back(Activity("Take a Ferry to Elephanta C aves", 240, "adventure", "Explore ancient rock-cut temples on Elephanta Island.", 45));
    activities.push_back(Activity("Shop at Colaba Causeway", 120, "shopping", "A bustling street market with a variety of shops.", 20));
    activities.push_back(Activity("Visit the Prince of Wales Museum", 90, "culture", "Explore art and history exhibits in this renowned museum.", 15));
    activities.push_back(Activity("Stroll through Juhu Beach", 150, "sightseeing", "Relax and enjoy the sunset at this popular beach.", 25));
    activities.push_back(Activity("Experience Local Cuisine", 120, "food", "Taste authentic Mumbai street food at various stalls.", 10));
    activities.push_back(Activity("Visit Siddhivinayak Temple", 60, "culture", "A famous Hindu temple dedicated to Lord Ganesha.", 15));
    activities.push_back(Activity("Explore Sanjay Gandhi National Park", 180, "adventure", "A large national park with wildlife and nature trails.", 30));
    activities.push_back(Activity("Visit Haji Ali Dargah", 90, "culture", "A mosque and tomb located on an islet in the Arabian Sea.", 20));
    activities.push_back(Activity("Take a Walk in Bandra Bandstand", 60, "sightseeing", "A popular promenade with views of the sea and city.", 10));
    activities.push_back(Activity("Visit the Nehru Science Centre", 120, "education", "An interactive science museum with various exhibits.", 15));
    activities.push_back(Activity("Attend a Local Festival", 180, "culture", "Experience the vibrant local festivals celebrated in Mumbai.", 30));
    activities.push_back(Activity("Explore Worli Sea Link", 90, "sightseeing", "A cable-stayed bridge connecting Worli and Bandra.", 15));
}

// Function to handle user input and program flow for itinerary planning
void handleItineraryMenuSelection(vector<Activity>& activities)
{
    int choice;
    do
        {
        displayItineraryMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                {
                int availableTime;
                cout << "Enter available time (in minutes): ";
                cin >> availableTime;
                planItinerary(activities, availableTime);
                break;
            }
            case 2:
                addActivity(activities);
                break;
            case 3:
                removeActivity(activities);
                break;
            case 4:
                {
                string category;
                cout << "\nEnter a category to view activities: ";
                cin >> category;
                vector<Activity> filteredActivities = filterActivitiesByCategory(activities, category);
                displayActivities(filteredActivities);
                break;
            }
            case 5:
                {
                set<string> categories = getUniqueCategories(activities);
                cout << "\nAvailable Categories:\n";
                for (const auto& cat : categories)
                    {
                    cout << "- " << cat << "\n";
                }
                break;
            }
            case 6:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    while (choice != 6);
}


// Function to display the main menu for efficiency tips
void displayMenuTips()
{
    cout << "\n---Main Menu (Efficiency Tips):---" << endl;
    cout << "1. View All Efficiency Tips" << endl;
    cout << "2. View Tips by Category" << endl;
    cout << "3. Add a New Tip" << endl;
    cout << "4. Search Tips by Keyword" << endl;
    cout << "5. View Keywords Related to a Tip" << endl;
    cout << "6. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
}

// Function to display the main menu for room allocation
void displayMenuRooms()
{
    cout << "\n---Main Menu (Room Allocation):---" << endl;
    cout << "1. Display Existing Tourists" << endl;
    cout << "2. Add New Tourist" << endl;
    cout << "3. Display Available Rooms" << endl;
    cout << "4. Allocate Rooms" << endl;
    cout << "5. Show Tourist Allocations" << endl;
    cout << "6. Reallocate Rooms" << endl;
    cout << "7. Show Allocations After Reallocation" << endl;
    cout << "8. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
}

// Function to display all efficiency tips
void viewAllTips(const vector<Tip>& tips)
{
    if (tips.empty())
        {
        cout << "\nNo tips available!" << endl;
        return;
    }
    cout << "\nWays to Make Your Trip More Efficient:" << endl;
    for (size_t i = 0; i < tips.size(); ++i)
    {
        cout << i + 1 << ". " << tips[i].title << ": " << tips[i].description << endl;
    }
}

// Function to view tips by category
void viewTipsByCategory(const vector<Tip>& tips)
{
    if (tips.empty())
    {
        cout << "\nNo tips available!" << endl;
        return;
    }

    cout<< "welcome\n"<<endl;
    cout << "\nSelect a Category:" << endl;
    cout << "1. Transportation" << endl;
    cout << "2. Accommodation" << endl;
    cout << "3. Budgeting" << endl;
    cout << "4. Time Management" << endl;
    cout << "5. Safety and Preparedness" << endl;
    cout << "6. Food and Dining" << endl;
    cout << "7. Packing" << endl;
    cout << "8. Local Culture" << endl;
    cout << "Enter your choice: ";

    int category;
    cin >> category;

    cout << "\nTips in Selected Category:" << endl;

    for (const auto& tip : tips)
        {
        switch (category)
               {
            case 1:
                if (tip.title.find("Transportation") != string::npos)
                {
                    cout << "- " << tip.title << ": " << tip.description << endl;
                }
                break;
            case 2:
                if (tip.title.find("Accommodation") != string::npos)
                {
                    cout << "- " << tip.title << ": " << tip.description << endl;
                }
                break;
            case 3:
                if (tip.title.find("Budgeting") != string::npos)
                {
                    cout << "- " << tip.title << ": " << tip.description << endl;
                }
                break;
            case 4:
                if (tip.title.find("Time Management") != string::npos)
                {
                    cout << "- " << tip.title << ": " << tip.description << endl;
                }
                break;
            case 5:
                if (tip.title.find("Safety") != string::npos || tip.title.find("Preparedness") != string::npos)
                {
                    cout << "- " << tip.title << ": " << tip.description << endl;
                }
                break;
            case 6:
                if (tip.title.find("Food") != string::npos || tip.title.find("Dining") != string::npos)
                {
                    cout << "- " << tip.title << ": " << tip.description << endl;
                }
                break;
            case 7:
                if (tip.title.find("Packing") != string::npos)
                    {
                    cout << "- " << tip.title << ": " << tip.description << endl;
                }
                break;
            case 8:
                if (tip.title.find("Culture") != string::npos)
                    {
                    cout << "- " << tip.title << ": " << tip.description << endl;
                }
                break;
            default:
                cout << "Invalid category! Please try again." << endl;
                return;
        }
    }
}

// Function to add a new tip
void addNewTip(vector<Tip>& tips)
{
    Tip newTip;
    cout << "\nEnter the title of the new tip: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, newTip.title);
    cout << "Enter the description of the new tip: ";
    getline(cin, newTip.description);
    string keyword;
    cout << "Enter keywords related to the tip (separated by commas): ";
    getline(cin, keyword);
    size_t pos = 0;
    while ((pos = keyword.find(',')) != string::npos)
        {
        newTip.keywords.push_back(keyword.substr(0, pos));
        keyword.erase(0, pos + 1);
    }
    newTip.keywords.push_back(keyword); // Add the last keyword

    tips.push_back(newTip);
    cout << "New tip added successfully!" << endl;
}

// Function to search tips by keyword
void searchTipsByKeyword(const vector<Tip>& tips)
{
    if (tips.empty())
        {
        cout << "\nNo tips available!" << endl;
        return;
    }

    string searchKeyword;
    cout << "\nEnter a keyword to search for tips: ";
    cin.ignore();
    getline(cin, searchKeyword);

    cout << "\nTips related to '" << searchKeyword << "':" << endl;
    bool found = false;
    for (const auto& tip : tips)
        {
        for (const auto& keyword : tip.keywords)
        {
            if (keyword.find(searchKeyword) != string::npos)
                {
                cout << "- " << tip.title << ": " << tip.description << endl;
                found = true;
                break; // No need to check other keywords for this tip
            }
        }
    }
    if (!found)
        {
        cout << "No tips found for the keyword '" << searchKeyword << "'." << endl;
    }
}

// Function to view keywords related to a specific tip
void viewKeywordsByTip(const vector<Tip>& tips)
{
    if (tips.empty())
        {
        cout << "\nNo tips available!" << endl;
        return;
    }

    cout << "\nSelect a Tip to View Keywords:" << endl;
    for (size_t i = 0; i < tips.size(); ++i)
        {
        cout << i + 1 << ". " << tips[i].title << endl;
    }

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice < 1 || choice > tips.size())
        {
        cout << "Invalid choice! Please try again." << endl;
        return;
    }

    cout << "\nKeywords for '" << tips[choice - 1].title << "':" << endl;
    for (const auto& keyword : tips[choice - 1].keywords)
        {
        cout << "- " << keyword << endl;
    }
}

// Function to display tourist allocations
void displayAllocations(const vector<Tourist>& tourists)
{
    cout << "\n==== Tourist Allocations ====\n";
    for (const auto& tourist : tourists)
        {
        cout << "Tour ist ID: " << tourist.id
             << ", Name: " << tourist.name
             << ", Allocated: " << (tourist.allocated ? "Yes" : "No")
             << ", Reason: " << tourist.reason << endl;
    }
    cout << "=============================\n";
}

// Function to display room information
void displayRooms(const vector<Room>& rooms)
{
    cout << "\n==== Available Rooms ====\n";
    for (const auto& room : rooms)
        {
        cout << "Room ID: " << room.id
             << ", Location: " << room.location
             << ", Capacity: " << room.capacity
             << ", Remaining Capacity: " << room.remainingCapacity
             << ", Price: " << room.price << endl;
    }
    cout << "=========================\n";
}

// Function to find a suitable room for a tourist
int findSuitableRoom(vector<Room>& rooms, const string& preferredLocation, double maxPrice)
{
    int bestRoomIndex = -1;
    double minPriceDifference = 1e9;  // Large arbitrary value for comparison

    // Iterate through all rooms to find a suitable match
    for (int i = 0; i < rooms.size(); ++i)
    {
        if (rooms[i].remainingCapacity > 0 && rooms[i].price <= maxPrice)
            {
            double priceDifference = maxPrice - rooms[i].price;

            // Prefer rooms with an exact location match first
            if ((rooms[i].location == preferredLocation && priceDifference < minPriceDifference) ||
                (bestRoomIndex == -1 && priceDifference < minPriceDifference))
                {
                minPriceDifference = priceDifference;
                bestRoomIndex = i;
            }
        }
    }

    return bestRoomIndex; // Return the index of the best room found
}

// Function to allocate rooms to tourists
void allocateRooms(vector<Tourist>& tourists, vector<Room>& rooms)
{
    for (auto& tourist : tourists)
    {

        if (!tourist.allocated)
        {
            int roomIndex = findSuitableRoom(rooms, tourist.locationPreference, tourist.maxPrice);
            if (roomIndex != -1)
            {
                tourist.allocated = true; // Mark tourist as allocated
                rooms[roomIndex].remainingCapacity--; // Decrease remaining capacity
                tourist.reason = "Allocated to Room " + to_string(rooms[roomIndex].id);
                cout << "Tourist " << tourist.name << " allocated to Room "
                     << rooms[roomIndex].id << " at " << rooms[roomIndex].location << endl;
            }
            else
            {
                tourist.reason = "No room available within budget";
                cout << "No room found for Tourist " << tourist.name << endl;
            }
        }
    }
}

// Function to reallocate rooms for unallocated tourists
void reallocateRooms(vector<Tourist>& tourists, vector<Room>& rooms)
{
    for (auto& tourist : tourists)
        {
        if (!tourist.allocated)
        {
            cout << "\nReallocating room for Tourist " << tourist.name << "..." << endl;
            int roomIndex = findSuitableRoom(rooms, "", tourist.maxPrice);  // Ignore location preference in reallocation
            if (roomIndex != -1)
                {
                tourist.reallocated = true; // Mark tourist as reallocated
                tourist.allocated = true; // Mark tourist as allocated
                rooms[roomIndex].remainingCapacity--; // Decrease remaining capacity
                tourist.reason = "Reallocated to Room " + to_string(rooms[roomIndex].id);
                cout << "Reallocated Tourist " << tourist.name << " to Room "
                     << rooms[roomIndex].id << " at " << rooms[roomIndex].location << endl;
            }
            else
            {
                tourist.reason = "Reallocation failed: No room available even after adjustment";
                cout << "No room available for Tourist " << tourist.name << " during reallocation." << endl;
            }
        }
    }
}

// Function to input tourist data
void inputTouristData(vector<Tourist>& tourists)
 {
    int n;
    cout << "Enter the number of tourists: ";
    cin >> n;
    for (int i = 0; i < n; ++i)
        {
        int id;
        string name, locationPreference;
        double maxPrice;
        cout << "\nEnter details for Tourist " << i + 1 << ":\n";
        cout << "Enter Tourist ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Preferred Location: ";
        cin >> locationPreference;
        cout << "Enter Maximum Price Tourist is willing to pay: ";
        cin >> maxPrice;
        tourists.emplace_back(id, name, locationPreference, maxPrice);
    }
}

// Function to display existing tourists
void displayExistingTourists(const vector<Tourist>& tourists)
{
    if (tourists.empty())
        {
        cout << "\nNo tourists available!" << endl;
        return;
    }
    cout << "\nExisting Tourists:" << endl;
    for (const auto& tourist : tourists)
    {
        cout << "Tourist ID: " << tourist.id
             << ", Name: " << tourist.name
             << ", Preferred Location: " << tourist.locationPreference
             << ", Max Price: " << tourist.maxPrice << endl;
    }
}


// Function to display the main menu for tourist problems
void displayTouristMenu()
{
    cout << "\n---Tourist Problems Menu---:" << endl;
    cout << "1. View All Problems" << endl;
    cout << "2. Analyze Problems" << endl;
    cout << "3. Ways to Solve Problems" << endl;
    cout << "4. Return to Main Menu" << endl;
    cout << "Enter your choice: ";
}

// Function to display the main menu for shelter-related problems
void displayShelterMenu()
{
    cout << "\n----Shelter-Related Problems Menu:----" << endl;

    cout << "1. View Problems" << endl;
    cout << "2. View Solutions" << endl;
    cout << "3. Analyze Problems" << endl;
    cout << "4. Ways to Solve Problems" << endl;
    cout << "5. Return to Main Menu" << endl;
    cout << "Enter your choice: ";
}

// Function to view all tourist problems
void viewTouristProblems(const vector<Problem>& problems)
 {
    if (problems.empty())
    {

        cout << "\nNo problems recorded!" << endl;
        return;
    }
    cout << "\nList of Tourist Problems:" << endl;
    for (size_t i = 0; i < problems.size(); ++i)
     {
        cout << i + 1 << ". " << problems[i].problemName << ": " << problems[i].description << endl;
    }
}

// Function to analyze tourist problems
void analyzeTouristProblems(const vector<Problem>& problems)
{
    if (problems.empty())
    {
        cout << "\nNo problems to analyze!" << endl;
        return;
    }
    cout << "\nAnalysis of Tourist Problems:" << endl;
    cout << "Total problems recorded: " << problems.size() << endl;

    int transportIssues = 0, accommodationIssues = 0, safetyIssues = 0, others = 0;
    for (const auto& problem : problems)
        {
        if (problem.problemName.find("transport") != string::npos ||
            problem.problemName.find("bus") != string::npos ||
            problem.problemName.find("flight") != string::npos)
        {
            transportIssues++;
        }
        else if (problem.problemName.find("hotel") != string::npos ||
                   problem.problemName.find("accommodation") != string::npos)
        {
            accommodationIssues++;
        }
        else if (problem.problemName.find("safety") != string::npos ||
                   problem.problemName.find("security") != string::npos)
        {
            safetyIssues++;
        }
        else
        {
            others++;
        }
    }

    cout << "Transport-related issues: " << transportIssues << endl;
    cout << "Accommodation-related issues: " << accommodationIssues << endl;
    cout << "Safety-related issues: " << safetyIssues << endl;
    cout << "Other issues: " << others << endl;
}

// Function to view shelter-related problems
void viewShelterProblems(const vector<Problem>& problems)
 {
    if (problems.empty())
   {
        cout << "\nNo problems recorded!" << endl;
        return;
    }
    cout << "\nList of Shelter-Related Problems:" << endl;
    for (size_t i = 0; i < problems.size(); ++i)
    {
        cout << i + 1 << ". " << problems[i].problemName << ": " << problems[i].description << endl;
    }
}

// Function to display solutions for shelter-related problems
void viewShelterSolutions(const vector<Problem>& problems)
    {
    if (problems.empty())
    {
        cout << "\nNo solutions available!" << endl;
        return;
    }
    cout << "\nSolutions to Shelter-Related Problems:" << endl;
    for (size_t i = 0; i < problems.size(); ++i)
    {
        cout << i + 1 << ". " << problems[i].problemName << ": " << problems[i].solution << endl;
    }
}

// Function to analyze shelter-related problems
void analyzeShelterProblems(const vector<Problem>& problems)
   {
    if (problems.empty())
    {
        cout << "\nNo problems to analyze!" << endl;
        return;
    }

    cout << "\nAnalysis of Shelter-Related Problems:" << endl;
    cout << "Total problems recorded: " << problems.size() << endl;

    int availabilityIssues = 0, cleanlinessIssues =  0, safetyIssues = 0, costIssues = 0, others = 0;
    for (const auto& problem : problems)
        {
        if (problem.problemName.find("availability") != string::npos)
        {
            availabilityIssues++;
        }
        else if (problem.problemName.find("cleanliness") != string::npos)
        {
            cleanlinessIssues++;
        }
        else if (problem.problemName.find("safety") != string::npos)
         {
            safetyIssues++;
        }
        else if (problem.problemName.find("cost") != string::npos)
        {
            costIssues++;
        }
        else
        {
            others++;
        }
    }

    cout << "Availability issues: " << availabilityIssues << endl;
    cout << "Cleanliness issues: " << cleanlinessIssues << endl;
    cout << "Safety issues: " << safetyIssues << endl;
    cout << "Cost-related issues: " << costIssues << endl;
    cout << "Other issues: " << others << endl;
}

// Function to display ways to solve problems
void displayWaysToSolveProblems()
{
    cout << "\nWays to Solve Problems:" << endl;

    cout << "1. Contact Local Authorities" << endl;
    cout << "2. Use Mobile Apps for Assistance" << endl;
    cout << "3. Seek Help from Fellow Tourists" << endl;
    cout << "4. Visit Tourist Information Centers" << endl;
    cout << "5. Return to Previous Menu" << endl;
    cout << "Enter your choice: ";
}
// Function to calculate cost for a tourist for a specific shelter based on distance
int calculateCost(int distance, int costPerUnitDistance)
 {
    return distance * costPerUnitDistance;
}

// Function to check if a cleanliness shelter is available (not full and accessible)
bool isCleanlinessShelterAvailable(const CleanlinessShelter& shelter)
 {
    return shelter.occupied < shelter.capacity && shelter.isAccessible;
}

// Function to allocate/reallocate rooms based on cleanliness
void allocateRoomsByCleanliness(vector<CleanlinessTourist>& tourists, vector<CleanlinessShelter>& shelters, vector<vector<int>>& distances)
 {
    for (size_t t = 0; t < tourists.size(); t++)
        {
        int minCost = INT_MAX;
        int bestShelter = -1;
        int bestCleanliness = -1;
        string reallocationReason = "";

        // Check if the tourist has a special shelter preference
        if (tourists[t].hasSpecialPreference)
            {
            int prefShelter = tourists[t].preferredShelter;
            // Check if the preferred shelter is available (not full, accessible)
            if (isCleanlinessShelterAvailable(shelters[prefShelter]))
            {
                int cost = calculateCost(distances[t][prefShelter], tourists[t].costPerUnitDistance);
                int cleanliness = shelters[prefShelter].cleanliness;

                // Consider cleanliness if the cost is equal or better
                if (cost < minCost || (cost == minCost && cleanliness > bestCleanliness))
                    {
                    minCost = cost;
                    bestShelter = prefShelter;
                    bestCleanliness = cleanliness;
                    reallocationReason = "Allocated to the special preference shelter.";
                }
            }
        }

        // If no special preference or no shelter available for preferred one, find the best shelter
        if (bestShelter == -1)
            {
            for (size_t s = 0; s < shelters.size(); s++)
                {
                // First check if the shelter is available (not full, accessible)
                if (isCleanlinessShelterAvailable(shelters[s]))
                {
                    int cost = calculateCost(distances[t][s], tourists[t].costPerUnitDistance);
                    int cleanliness = shelters[s].cleanliness;

                    // Compare based on cost, cleanliness, and priority
                    if (cost < minCost ||
                        (cost == minCost && cleanliness > bestCleanliness) ||
                        (cost == minCost && cleanliness == bestCleanliness && shelters[s].priority < shelters[bestShelter].priority)) {
                        minCost = cost;
                        bestShelter = s;
                        bestCleanliness = cleanliness;
                        reallocationReason = "Allocated to the best available shelter.";
                    }
                }
            }
        }

        // Allocate or reallocate based on the best shelter found
        switch (bestShelter)
        {
            case -1:
                // No shelter available
                tourists[t].reason = "No shelters available for allocation.";
                cout << "No available shelter for tourist " << tourists[t].name << ". Reason: " << tourists[t].reason << endl;
                break;

            default:
                if (!tourists[t].isAllocated)
                    {
                    // First-time allocation
                    shelters[bestShelter].occupied++;
                    tourists[t].isAllocated = true;
                    tourists[t].allocatedShelter = shelters[bestShelter].id;
                    tourists[t].reason = reallocationReason.empty() ? "Initially allocated to the most cost-efficient and clean shelter." : reallocationReason;
                    cout << "Tourist " << tourists[t].name << " allocated to shelter "
                         << shelters[bestShelter].name << " (Cost: " << minCost << ", Cleanliness: " << bestCleanliness << "). Reason: " << tourists[t].reason << endl;
                }
                else if (shelters[bestShelter].id != tourists[t].allocatedShelter)
                {
                    // Reallocate if a better shelter is found
                    int prevShelterIndex = -1;
                    for (size_t s = 0; s < shelters.size(); s++)
                    {
                        if (shelters[s].id == tourists[t].allocatedShelter)
                        {
                            prevShelterIndex = s;
                            break;
                        }
                    }

                    // Free up the previous shelter's capacity
                    if (prevShelterIndex != -1)
                    {
                        shelters[prevShelterIndex].occupied--;
                    }

                    // Assign to the new shelter
                    shelters[bestShelter].occupied++;
                    tourists[t].allocatedShelter = shelters[bestShelter].id;
                    tourists[t].reason = reallocationReason.empty() ? "Reallocated to a more cost-efficient and cleaner shelter." : reallocationReason;
                    cout << "Tourist " << tourists[t].name << " reallocated to shelter "
                         << shelters[bestShelter].name << " (Cost: " << minCost << ", Cleanliness: " << bestCleanliness << "). Reason: " << tourists[t].reason << endl;
                }
                break;
        }
    }
}
// Function to check if a distance shelter is available (not full)
  bool isDistanceShelterAvailable(const DistanceShelter& shelter)
{
    return shelter.occupied < shelter.capacity;
}

// Function to allocate or reallocate rooms to tourists based on distance
void allocateRoomsByDistance(vector<DistanceTourist>& tourists, vector<DistanceShelter>& shelters, vector<vector<int>>& distances)
{
    for (size_t t = 0; t < tourists.size(); t++)

        {
        int minDistance = INT_MAX; // Large value for comparison
        int nearestShelter = -1;

        // Find the nearest shelter with available capacity
        for (size_t s = 0; s < shelters.size(); s++)
            {
            if (isDistanceShelterAvailable(shelters[s]) && distances[t][s] < minDistance)
            {
                minDistance = distances[t][s];
                nearestShelter = s;
            }
        }

        // Check if reallocation is needed
        if (nearestShelter != -1)
            {
            if (!tourists[t].isAllocated)
            {
                // Allocate for the first time
                shelters[nearestShelter].occupied++;
                tourists[t].isAllocated = true;
                tourists[t].allocatedShelter = shelters[nearestShelter].id;
                tourists[t].reason = "Initially allocated to the nearest shelter.";
                cout << "Tourist " << tourists[t].name << " allocated to shelter "
                     << shelters[nearestShelter].name << " (Distance: " << minDistance << ").\n";
            }
            else if (shelters[nearestShelter].id != tourists[t].allocatedShelter)
            {
                // Reallocation if a better shelter is found
                int prevShelterIndex = -1;
                for (size_t s = 0; s < shelters.size(); s++)
                {
                    if (shelters[s].id == tourists[t].allocatedShelter)
                    {

                        prevShelterIndex = s;
                        break;
                    }
                }

                if (prevShelterIndex != -1)
                    {
                    shelters[prevShelterIndex].occupied--;
                }
                shelters[nearestShelter].occupied++;
                tourists[t].allocatedShelter = shelters[nearestShelter].id;
                tourists[t].reason = "Reallocated to a closer shelter with better availability.";
                cout << "Tourist " << tourists[t].name << " reallocated to shelter "
                     << shelters[nearestShelter].name << " (Distance: " << minDistance << ").\n";
            }
        }
        else
        {
            tourists[t].reason = "No shelters available for allocation.";
            cout << "No available shelter for tourist " << tourists[t].name << ".\n";
        }
    }
}

// Function to input cleanliness shelter details
void inputCleanlinessShelters(vector<CleanlinessShelter>& shelters, int numShelters)
{
    for (int i = 0; i < numShelters; i++)
        {
        int id, capacity, priority, cleanliness;
        bool isAccessible;
        string name;
        cout << "Enter shelter " << i + 1 << " details:" << endl;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Capacity: ";
        cin >> capacity;
        cout << "Enter Priority (Lower value = Higher priority): ";
        cin >> priority;
        cout << "Enter Accessibility (1 for Yes, 0 for No): ";
        cin >> isAccessible;
        cout << "Enter Cleanliness level (0-10): ";
        cin >> cleanliness;
        cout << "Enter Shelter Name: ";
        cin >> name;
        shelters.push_back(CleanlinessShelter(id, capacity, priority, isAccessible, cleanliness, name));
    }
}

// Function to input distance shelter details
void inputDistanceShelters(vector<DistanceShelter>& shelters, int numShelters)
 {
    for (int i = 0; i < numShelters; i++)
        {
        int id, capacity;
        string name;
        cout << "Enter shelter " << i + 1 << " details:" << endl;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Capacity: ";
        cin >> capacity;
        cout << "Enter Shelter Name: ";
        cin >> name;
        shelters.push_back(DistanceShelter(id, capacity, name));
    }
}

// Function to input cleanliness tourist details
void inputCleanlinessTourists(vector<CleanlinessTourist>& tourists, int numTourists)
{
    for (int i = 0; i < numTourists; i++)
        {
        int id;
        string name;
        int costPerUnitDistance;
        bool hasSpecialPreference;
        int preferredShelter;
        cout << "Enter tourist " << i + 1 << " details:" << endl;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Cost per unit distance: ";
        cin >> costPerUnitDistance;
        cout << "Enter Special preference (1 for Yes, 0 for No): ";
        cin >> hasSpecialPreference;
        if (hasSpecialPreference) {
            cout << "Enter Preferred Shelter ID: ";
            cin >> preferredShelter;
        }
        else
        {
            preferredShelter = -1; // No special preference
        }
        tourists.push_back(CleanlinessTourist(id, name, costPerUnitDistance, hasSpecialPreference, preferredShelter));
    }
}

// Function to input distance tourist details
void inputDistanceTourists(vector<DistanceTourist>& tourists, int numTourists)
{
    for (int i = 0; i < numTourists; i++)
        {
        int id;
        string name;
        cout << "Enter  tourist " << i + 1 << " details:" << endl;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        tourists.push_back(DistanceTourist(id, name));
    }
}

// Function to input distances between tourists and cleanliness shelters
void inputCleanlinessDistances(vector<vector<int>>& distances, int numTourists, int numShelters)
{
    for (int i = 0; i < numTourists; i++)
        {
        vector<int> touristDistances;
        for (int j = 0; j < numShelters; j++)
        {

            int distance;
            cout << "Enter distance between tourist " << i + 1 << " and shelter  " << j + 1 << " in km: ";
            cin >> distance;
            touristDistances.push_back(distance);
        }
        distances.push_back(touristDistances);
    }
}

// Function to input distances between tourists and distance shelters
void inputDistanceDistances(vector<vector<int>>& distances, int numTourists, int numShelters)
{
    cout<<"please enter the distance in kilometers!!!";
     cout<<endl;
    for (int i = 0; i < numTourists; i++)
        {
        vector<int> touristDistances;
        for (int j = 0; j < numShelters; j++)
        {

            int distance;
            cout << "Enter distance between tourist " << i + 1 << " and shelter  " << j + 1 << "in km: ";
            cin >> distance;
            touristDistances.push_back(distance);
        }
        distances.push_back(touristDistances);
    }
}

// Function to display the current cleanliness allocation status
void displayCleanlinessAllocationStatus(const vector<CleanlinessTourist>& tourists)
{
    cout << "\n--- Tourist Allocation Status ---" << endl;
    for (const auto& tourist : tourists)
        {
        cout << tourist.name << " is allocated to shelter "
             << (tourist.isAllocated ? to_string(tourist.allocatedShelter) : "None")<<endl;
        cout  << ". Reason: " << tourist.reason << endl;
    }
}

// Function to display the current distance allocation status
void displayDistanceAllocationStatus(const vector<DistanceTourist>& tourists)
{
    cout << "\n--- Distance-based Tourist Allocation Status ---" << endl;
    for (const auto& tourist : tourists)
        {
        cout << "Tourist " << tourist.name << " is allocated to shelter "
             << (tourist.isAllocated ? to_string(tourist.allocatedShelter) : "None")<<endl;
        cout   << ". Reason: " << tourist.reason << endl;
    }
}

// Function to display cleanliness shelters information
void displayCleanlinessSheltersStatus(const vector<CleanlinessShelter>& shelters)
{
    cout << "\n--- Cleanliness-based Shelter Information ---" << endl;
    for (const auto& shelter : shelters)
        {
        cout << "Shelter ID: " << shelter.id<<endl;
        cout << "Name: " << shelter.name<<endl;
        cout << " Capacity: " << shelter.capacity<<endl;
        cout << " Occupied: " << shelter.occupied <<endl;
        cout << " Cleanliness: " << shelter.cleanliness<<endl;
        cout  << " Accessible: " << (shelter.isAccessible ? "Yes" : "No") << endl;
    }
}

// Function to display distance shelters information
void displayDistanceSheltersStatus(const vector<DistanceShelter>& shelters)
{
    cout << "\n--- Distance Shelter Information ---" << endl;
    for (const auto& shelter : shelters) {
        cout  << "Shelter ID: " << shelter.id<<endl;
        cout  << " Name: " << shelter.name<<endl;
        cout  << "Capacity: " << shelter.capacity<<endl;
        cout  << "Occupied: " << shelter.occupied <<endl;
    }
}
// Function to input distance shelter details
void inputDistanceShelters(vector<DistanceShelter>& shelters)
{
    int id, capacity;
    string name;
    cout << "Enter distance shelter details:" << endl;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Capacity: ";
    cin >> capacity;
    cout << "Enter Shelter Name: ";
    cin >> name;
    shelters.push_back(DistanceShelter(id, capacity, name));
}
// Function to input tourist details
void inputDistanceTourists(vector<DistanceTourist>& tourists)
{
    int id;
    string name;
    cout << "Enter tourist details:" << endl;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin >> name;
    tourists.push_back(DistanceTourist(id, name));
}

// Function to input shelter details
void inputCleanlinessShelters(vector<CleanlinessShelter>& shelters)
{
    int id, capacity, priority, cleanliness;
    bool isAccessible;
    string name;
    cout << "Enter shelter details:" << endl;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Capacity: ";
    cin >> capacity;
    cout << "Enter Priority (Lower value = Higher priority): ";
    cin >> priority;
    cout << "Enter Accessibility (1 for Yes, 0 for No): ";
    cin >> isAccessible;
    cout << "Enter Cleanliness level (0-10): ";
    cin >> cleanliness;
    cout << "Enter Shelter Name: ";
    cin >> name;
    shelters.push_back(CleanlinessShelter(id, capacity, priority, isAccessible, cleanliness, name));
}

// Function to input cleanliness tourist details

void inputCleanlinessTourists(vector<CleanlinessTourist>& tourists)
{
    int id;
    string name;
    int costPerUnitDistance;
    bool hasSpecialPreference;
    int preferredShelter;
    cout << "Enter tourist details:" << endl;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Cost per unit distance: ";
    cin >> costPerUnitDistance;
    cout << "Enter Special preference (1 for Yes, 0 for No): ";
    cin >> hasSpecialPreference;
    if (hasSpecialPreference)
        {
        cout << "Enter Preferred Shelter ID: ";
        cin >> preferredShelter;
    }
    else
    {
        preferredShelter = -1; // No special preference
    }
    tourists.push_back(CleanlinessTourist(id, name, costPerUnitDistance, hasSpecialPreference, preferredShelter));
}
class CSVHandler
{
private:
    std::string filename;

public:
    CSVHandler(const std::string &file) : filename(file) {}

    // Function to read data from the CSV file and store it in a vector
    std::vector<std::pair<std::string, double>> readData()
    {
        std::vector<std::pair<std::string, double>> data;
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cout << "Error opening file: " << filename << std::endl;
            return data;
        }

        std::string line, category;
        double price;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::getline(ss, category, ',');
            ss >> price;
            data.push_back(std::make_pair(category, price));
        }

        file.close();
        return data;
    }

    // Function to write data to the CSV file
    void writeData(const std::vector<std::pair<std::string, double>> &data)
    {
        std::ofstream file(filename);

        if (!file.is_open())
        {
            std::cout << "Error opening file: " << filename << std::endl;
            return;
        }

        for (const auto &item : data)
        {
            file << item.first << "," << item.second << std::endl;
        }

        file.close();
        std::cout << "Data written to the file successfully.\n";
    }
};
class Admin;

class Authentication
{
public:
    // static bool isAdmin()
    // {
    //     // std::string choice;
    //     std::auto choice;
    //     std::cout << "Do you want to login as"<<endl;
    //     std::cout << "1. admin"<<endl;
    //     std::cout << "2. user"<<endl;
    //     std::cin >> choice;
    //     if (choice=="admin" or choice == 1)
    //     {
    //         return True;
    //     }
    //     else if (choice=="user" or choice == 2)
    //     {
    //        return False;
    //     }
    //     else{
    //           std::cout<<"pick valid choice"<<endl;
    //     }
    // }

static bool isAdmin()
{
    std::string choice;
    while (true)
    {
        std::cout << "Do you want to login as" << std::endl;
        std::cout << "1. admin" << std::endl;
        std::cout << "2. user" << std::endl;
        std::cin >> choice;
         std::cin.ignore(1000, '\n');

for (char &c : choice)
        {
            c = std::tolower(c);
        }

        if (choice == "admin" || choice == "1")
        {
            return true;
        }
        else if (choice == "user" || choice == "2")
        {
            return false;
        }
        else
        {
            std::cout << "Please type out a valid choice (admin or user).\n";
        }
    }
}

    static bool authenticateAdmin(Admin &admin);
};

class UserBase
{
protected:
    void viewAllCategoriesWithPrices()
    {
         CSVHandler csvHandler("categories.csv");
            std::vector<std::pair<std::string, double>> categories = csvHandler.readData();

            if (categories.empty()) {
                std::cout << "No categories found.\n";
            } else {
                std::cout << "----- All Categories with Prices -----\n";
                for (const auto& item : categories) {
                    std::cout << item.first << ": " << item.second << " Rs/kg\n";
                }
                std::cout << "-------------------------------------\n";
            }
    }

public:
    virtual void greet() const = 0;
    virtual void userMenu() = 0;
};

class Admin : public UserBase

{
private:
    std::string username;
    std::string password;
    void showMenu()
    {
        std::cout << "----------- Admin Menu -----------\n"
                  << "1. Change Password\n"
                  << "2. Add Waste Category\n"
                  << "3. Remove Waste Category\n"
                  << "4. Change Price of Category\n"
                  << "5. View All Categories with Prices\n"
                  << "6. View all Transactions\n"
                  << "7. search Category\n"
                  << "8. view Categories Sorted By Price\n"
                  << "9. View Total Revenue\n"
                  << "10. View Users\n"
                  << "11. View User Transaction History\n"
                  << "12. Add New Category\n"
                  << "13. Update Category Price\n"
                  << "14. Delete Category\n"
                  << "15. Register New User\n"
                  << "16. track Waste Generation By Area\n"
                  << "17. allocate Resources\n"
                  << "18. generate Waste Disposal Report\n"
                  << "19. assign Tasks To Workers\n"
                  << "20. monitor Sustainable Waste Practices\n"
                  << "21. promote Zero Waste Initiatives\n"
                  << "22. track Recycling Efforts\n"
                  << "23. set Up Educational Programs\n"
                  << "24. optimize Waste Collection Routes\n"
                  << "25. analyze Waste Generation Patterns\n"
                  << "26. trackWasteManagementStats\n"
                  << "27. track Waste Generation By Date\n"
                  << "28. find Shortest Waste Collection Route"
                  << "29. Quit\n"
                  << "----------------------------------\n";
    }

    // Function to handle the admin menu
    void handleMenu()
    {
        int choice;
        while (true)
        {
            showMenu();
            std::string input;
            std::cout << "Enter your choice: ";
            std::cin >> input;

            // Check if input is an integer
            std::istringstream iss(input);
            if (!(iss >> choice))
            {
                std::cout << "Invalid input. Please enter a valid integer choice.\n";
                std::cin.clear();                                                   // Clear error flags from cin
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters in the input buffer
                continue;                                                           // Continue to next iteration of the loop
            }

            switch (choice)
            {
            case 1:
                changePassword();
                break;
            case 2:
                addCategory();

                break;
            case 3:
                removeCategory();

                break;
            case 4:
                changePrice();
                break;
            case 5:
                viewAllCategoriesWithPrices();
                break;
            case 6:
                viewAllTransactions();
                break;
            case 7:
                searchCategory();
                break;
            case 8:
                viewCategoriesSortedByPrice();
                break;
            case 9:
                viewTotalRevenue();
                break;
            case 10:
                viewUsers();
                break;
            case 11:
                viewUserTransactionHistory();
                break;
            case 12:
                addNewCategory();
                break;
            case 13:
                updateCategoryPrice();
                break;
            case 14:
                deleteCategory();
                break;
            case 15:
                registerUser();
                break;
            case 16:
                trackWasteGenerationByArea();
                break;
            case 17:
                allocateResources();
                break;
            case 18:
                generateWasteDisposalReport();
                break;


            case 19:
                assignTasksToWorkers();
                break;
            case 20:
                monitorSustainableWastePractices();
                break;
            case 21:
                promoteZeroWasteInitiatives();
                break;
            case 22:
                trackRecyclingEfforts();
                break;
            case 23:
                setUpEducationalPrograms();
                break;
            case 24:
                optimizeWasteCollectionRoutes();
                break;
            case 25:
                analyzeWasteGenerationPatterns();
                break;
            case 26:
                trackWasteManagementStats();
                break;
            case 27:
                trackWasteGenerationByDate();
                break;
            case 28:
                {
                    // Get the start and destination areas from the user
                    int startArea, destinationArea;
                    std::cout << "Enter the starting area (0 to 4): ";
                    std::cin >> startArea;
                    std::cout << "Enter the destination area (0 to 4): ";
                    std::cin >> destinationArea;

                    // Call the function to find the shortest waste collection route
                findShortestWasteCollectionRoute(startArea, destinationArea);
                }
                break;
            case 29:
                std::cout << "Exiting Admin Menu.\n";
                return;


            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }

     void viewAllTransactions()
     {
            std::string filename = "transactions.csv";
            std::ifstream inputFile(filename);
            if (!inputFile)
            {
                std::cout << "Error opening file for reading transactions.\n";
                return;
            }

            std::string line;
            std::cout << "----- All Transactions -----\n";
            while (std::getline(inputFile, line)) {
                std::cout << line << '\n';
            }
            std::cout << "-----------------------------\n";

            inputFile.close();
        }

   std::pair<std::string, std::string> readAdminInfo()
    {
        std::ifstream file("adminfile.csv");
        if (!file.is_open())
        {
            std::cout << "Error opening admin file.\n";
            return std::make_pair("", "");
        }

        // Assuming the format of the file is: username,password
        std::string line;
        if (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::getline(iss, username, ',');
            std::getline(iss, password, ',');
        }

        file.close();
        return std::make_pair(username, password);
    }

//   Function to write admin information to the file
    void writeAdminInfo()
    {
        std::ofstream file("adminfile.csv");
        if (!file.is_open())
        {
            std::cout << "Error opening admin file.\n";
            return;
        }

        file << username << "," << password << std::endl;

        file.close();
    }

void changePassword()
{
    readAdminInfo(); // Read admin information from the file

    std::string currentPassword, newPassword, confirmPassword;
    std::cout << "Enter current password: ";
    std::cin >> currentPassword;

    if (currentPassword != password)
    {
        std::cout << "Incorrect current password. Password not changed.\n";
        return;
    }

    std::cout << "Enter new password: ";
    std::cin >> newPassword;

    std::cout << "Confirm new password: ";
    std::cin >> confirmPassword;

    if (newPassword != confirmPassword)
    {
        std::cout << "New password and confirmation do not match. Password not changed.\n";
        return;
    }

    password = newPassword;
    writeAdminInfo(); // Update the new password in the file
    std::cout << "Password changed successfully.\n";
}

    void addCategory()
    {
        viewAllCategoriesWithPrices();
        std::string category;
        double price;

        std::cout << "Enter the new category: ";
        std::cin.ignore(); // Ignore any previous newline character in the input buffer
        std::getline(std::cin, category);

        std::cout << "Enter the price (in Rs/kg): ";
        std::cin >> price;

        std::pair<std::string, double> newCategory(category, price);

        CSVHandler csvHandler("categories.csv");
        std::vector<std::pair<std::string, double>> categories = csvHandler.readData();

        bool categoryExists = false;
        for (const auto &item : categories)
        {
            if (item.first == category)
            {
                categoryExists = true;
                break;
            }
        }

        if (categoryExists)
        {
            std::cout << "Category already exists. Please try adding a different category.\n";
        }
        else
        {
            categories.push_back(newCategory);
            csvHandler.writeData(categories);
            std::cout << "Category added successfully.\n";
        }
    }

    void removeCategory()
    {
        viewAllCategoriesWithPrices();
        std::string categoryToRemove;
        std::cout << "Enter the category to remove: ";
        std::cin.ignore(); // Ignore any previous newline character in the input buffer
        std::getline(std::cin, categoryToRemove);

        CSVHandler csvHandler("categories.csv");
        std::vector<std::pair<std::string, double>> categories = csvHandler.readData();

        auto it = std::remove_if(categories.begin(), categories.end(), [&](const auto &item)
                                 { return item.first == categoryToRemove; });

        if (it != categories.end())
        {
            categories.erase(it, categories.end());
            csvHandler.writeData(categories);
            std::cout << "Category removed successfully.\n";
        }
        else
        {
            std::cout << "Category not found.\n";
        }
    }

    void changePrice()
    {

        viewAllCategoriesWithPrices();
        std::string categoryToChange;
        double newPrice;

        std::cout << "Enter the category to change the price: ";
        std::cin.ignore(); // Ignore any previous newline character in the input buffer
        std::getline(std::cin, categoryToChange);

        std::cout << "Enter the new price (in Rs/kg): ";
        std::cin >> newPrice;

        CSVHandler csvHandler("categories.csv");
        std::vector<std::pair<std::string, double>> categories = csvHandler.readData();

        bool categoryExists = false;
        for (auto &item : categories)
        {
            if (item.first == categoryToChange)
            {
                item.second = newPrice;
                categoryExists = true;
                break;
            }
        }

        if (categoryExists)
        {
            csvHandler.writeData(categories);
            std::cout << "Price for category updated successfully.\n";
        }
        else
        {
            std::cout << "Category not found. Unable to update the price.\n";
        }
    }

    //   void viewAllCategoriesWithPrices() {
    //         CSVHandler csvHandler("categories.csv");
    //         std::vector<std::pair<std::string, double>> categories = csvHandler.readData();

    //         if (categories.empty()) {
    //             std::cout << "No categories found.\n";
    //         } else {
    //             std::cout << "----- All Categories with Prices -----\n";
    //             for (const auto& item : categories) {
    //                 std::cout << item.first << ": " << item.second << " Rs/kg\n";
    //             }
    //             std::cout << "-------------------------------------\n";
    //         }
    //     }
    void searchCategory()
    {
    std::string searchTerm;
    std::cout << "Enter category name to search: ";
    std::cin.ignore();  // Clear any leftover input from previous operations
    std::getline(std::cin, searchTerm);

    CSVHandler csvHandler("categories.csv");
    std::vector<std::pair<std::string, double>> categories = csvHandler.readData();

    bool found = false;
    for (const auto& item : categories)
        {
        if (item.first.find(searchTerm) != std::string::npos)
        {
            std::cout << "Found: " << item.first << " - " << item.second << " Rs/kg\n";
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "No matching categories found.\n";
    }
    }
    void viewCategoriesSortedByPrice()
    {
    CSVHandler csvHandler("categories.csv");
    std::vector<std::pair<std::string, double>> categories = csvHandler.readData();

    // Sorting categories by price
    std::sort(categories.begin(), categories.end(), [](const auto& a, const auto& b)
    {
        return a.second < b.second;  // Ascending order
    });

    std::cout << "----- Sorted Categories by Price -----\n";
    for (const auto& item : categories) {
        std::cout << item.first << ": " << item.second << " Rs/kg\n";
    }
    std::cout << "-------------------------------------\n";
    }
    void viewTotalRevenue()
    {
    std::ifstream inputFile("transactions.csv");
    if (!inputFile)
    {
        std::cout << "Error opening file for reading transactions.\n";
        return;
    }

    double totalRevenue = 0.0;
    std::string line;
    while (std::getline(inputFile, line))
    {
        // Assuming the last column of each line is the price
        size_t lastComma = line.rfind(',');
        if (lastComma != std::string::npos)
        {
            double price = std::stod(line.substr(lastComma + 1));
            totalRevenue += price;
        }
    }

    inputFile.close();
    std::cout << "Total Revenue: " << totalRevenue << " Rs\n";
 }
 void viewUsers()
 {
    std::ifstream userFile("users.csv");
    if (!userFile)
    {
        std::cout << "Error opening file for reading users.\n";
        return;
    }

    std::string line;
    std::cout << "----- All Users -----\n";
    while (std::getline(userFile, line))
    {
        std::cout << line << '\n';  // Assuming each line contains user info
    }
    std::cout << "---------------------\n";
    userFile.close();
 }
 void viewUserTransactionHistory()
 {
    std::string username;
    std::cout << "Enter the username to view their transaction history: ";
    std::cin.ignore();
    std::getline(std::cin, username);

    std::ifstream inputFile("transactions.csv");
    if (!inputFile)
    {
        std::cout << "Error opening file for reading transactions.\n";
        return;
    }

    bool found = false;
    std::string line;
    while (std::getline(inputFile, line))
    {
        if (line.find(username) != std::string::npos)
        {
            std::cout << line << '\n';  // Display the transaction if username matches
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "No transactions found for the user: " << username << '\n';
    }

    inputFile.close();
 }
 void addNewCategory()
 {
    std::string categoryName;
    double categoryPrice;

    std::cout << "Enter category name: ";
    std::cin.ignore();
    std::getline(std::cin, categoryName);

    std::cout << "Enter category price (Rs per kg): ";
    std::cin >> categoryPrice;

    // Append the new category to the CSV file
    std::ofstream outputFile("categories.csv", std::ios::app);
    if (outputFile)
    {
        outputFile << categoryName << "," << categoryPrice << "\n";
        std::cout << "New category added successfully.\n";
    }
    else
    {
        std::cout << "Error adding category.\n";
    }
 }
 void updateCategoryPrice()
 {
    std::string categoryName;
    double newPrice;

    std::cout << "Enter the category name to update price: ";
    std::cin.ignore();
    std::getline(std::cin, categoryName);

    std::cout << "Enter the new price for " << categoryName << ": ";
    std::cin >> newPrice;

    // Reading the file and updating the price
    std::ifstream inputFile("categories.csv");
    std::ofstream tempFile("temp.csv");
    std::string line;
    bool updated = false;

    while (std::getline(inputFile, line))
    {
        size_t commaPos = line.find(',');
        std::string currentCategory = line.substr(0, commaPos);
        if (currentCategory == categoryName)
        {
            line = categoryName + "," + std::to_string(newPrice);  // Update price
            updated = true;
        }
        tempFile << line << "\n";
    }

    inputFile.close();
    tempFile.close();

    // Replace old file with the updated one
    std::remove("categories.csv");
    std::rename("temp.csv", "categories.csv");

    if (updated)
    {
        std::cout << "Category price updated successfully.\n";
    }
    else
    {
        std::cout << "Category not found.\n";
    }
 }

 void deleteCategory()
 {
    std::string categoryName;

    std::cout << "Enter the category name to delete: ";
    std::cin.ignore();
    std::getline(std::cin, categoryName);

    // Reading the file and deleting the category
    std::ifstream inputFile("categories.csv");
    std::ofstream tempFile("temp.csv");
    std::string line;
    bool deleted = false;

    while (std::getline(inputFile, line))
    {
        size_t commaPos = line.find(',');
        std::string currentCategory = line.substr(0, commaPos);
        if (currentCategory != categoryName)
        {
            tempFile << line << "\n";  // Write non-deleted categories to temp file
        } else
        {
            deleted = true;
        }
    }

    inputFile.close();
    tempFile.close();

    // Replace old file with the updated one
    std::remove("categories.csv");
    std::rename("temp.csv", "categories.csv");

    if (deleted)
    {
        std::cout << "Category deleted successfully.\n";
    }
    else
    {
        std::cout << "Category not found.\n";
    }
 }

 void registerUser()
 {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin.ignore();
    std::getline(std::cin, username);

    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    // Add the new user to the users file
    std::ofstream outputFile("users.csv", std::ios::app);
    if (outputFile)
    {
        outputFile << username << "," << password << "\n";
        std::cout << "User registered successfully.\n";
    } else
    {
        std::cout << "Error registering user.\n";
    }
}

void trackWasteGenerationByArea()
{
    std::cout << "Tracking Waste Generation by Area...\n";
    int area;
    std::cout << "Enter the area number (1-10) to track waste generation: ";
    std::cin >> area;

    if(area < 1 || area > 10)
    {
        std::cout << "Invalid area number. Please enter a valid number between 1 and 10.\n";
        return;
    }

    // Simulate tracking with random data based on area
    std::cout << "Waste generation report for Area " << area << ":\n";
    double wasteGenerated = area * 50 + (rand() % 100); // Simulating waste generation
    std::cout << "Total waste generated: " << wasteGenerated << " kg\n";
    double wasteRecycled = wasteGenerated * 0.6; // 60% recycling rate
    double wasteDisposed = wasteGenerated - wasteRecycled;

    std::cout << "Total waste recycled: " << wasteRecycled << " kg\n";
    std::cout << "Total waste disposed of: " << wasteDisposed << " kg\n";
    std::cout << "End of Report.\n";
}

void allocateResources()
{
    int area;
    std::cout << "Enter Area Number (1-10) to allocate resources: ";
    std::cin >> area;

    if(area < 1 || area > 10)
    {
        std::cout << "Invalid area number. Please enter a valid number between 1 and 10.\n";
        return;
    }

    std::cout << "Allocating resources to Area " << area << ".\n";
    // Simulate resource allocation with a random allocation
    int wasteBins = area * 2 + (rand() % 5); // Simulated bin allocation
    int trucks = area + (rand() % 2); // Simulated truck allocation
    std::cout << "Waste Bins allocated: " << wasteBins << "\n";
    std::cout << "Trucks allocated: " << trucks << "\n";
    std::cout << "Resources successfully allocated.\n";
}

 void generateWasteDisposalReport()
 {
    std::cout << "Generating Detailed Waste Disposal Report...\n";
    int year;
    std::cout << "Enter the year for the report (e.g., 2023): ";
    std::cin >> year;

    if(year < 2000 || year > 2100)
    {
        std::cout << "Invalid year. Please enter a valid year between 2000 and 2100.\n";
        return;
    }

    // Simulate the report generation
    std::cout << "Waste Disposal Report for Year " << year << ":\n";
    double totalWasteCollected = (rand() % 5000) + 10000; // Simulating total waste collected
    double totalWasteRecycled = totalWasteCollected * 0.5; // 50% recycled
    double totalWasteDisposed = totalWasteCollected - totalWasteRecycled;

    std::cout << "Total Waste Collected: " << totalWasteCollected << " kg\n";
    std::cout << "Total Waste Recycled: " << totalWasteRecycled << " kg\n";
    std::cout << "Total Waste Disposed: " << totalWasteDisposed << " kg\n";
    std::cout << "Report generated successfully.\n";
}

void assignTasksToWorkers()
{
    int workerId;
    std::cout << "Enter Worker ID to assign tasks: ";
    std::cin >> workerId;

    if(workerId <= 0)
    {
        std::cout << "Invalid Worker ID. Please enter a valid ID.\n";
        return;
    }

    std::cout << "Assigning tasks to Worker " << workerId << "...\n";
    // Simulate task allocation with random task assignments
    std::string task = (rand() % 2 == 0) ? "Collecting Waste" : "Monitoring Recycling Centers";
    std::cout << "Worker " << workerId << " is assigned the task: " << task << ".\n";
    std::cout << "Task successfully assigned.\n";
 }

 void monitorSustainableWastePractices()
 {
    std::cout << "Monitoring sustainable waste practices in the city...\n";
    std::cout << "Fetching data from waste management systems...\n";
    std::cout << "Please wait while we analyze the statistics.\n";

    // Simulating some calculations and gathering data
    double recyclingRate = 45.0;
    double organicWasteDiverted = 30.0;
    int wasteSegregationPrograms = 10;

    // Logic to display sustainable practices
    std::cout << "\nSustainable Waste Practices Report:\n";
    std::cout << "------------------------------------\n";
    std::cout << "1. Percentage of waste being recycled: " << recyclingRate << "%\n";
    std::cout << "2. Percentage of organic waste diverted from landfills: " << organicWasteDiverted << "%\n";
    std::cout << "3. Number of waste segregation programs in place: " << wasteSegregationPrograms << "\n";

    // Simulating additional recommendations
    std::cout << "\nRecommendations for improvement:\n";
    std::cout << "1. Increase the number of waste segregation programs.\n";
    std::cout << "2. Provide more incentives for residents to separate waste.\n";
    std::cout << "3. Expand recycling programs, particularly for e-waste.\n";
}

 void promoteZeroWasteInitiatives()
 {
    std::cout << "Promoting zero waste initiatives...\n";
    std::cout << "Working on the following action points:\n";

    // Expanded program actions
    std::cout << "1. Expanding composting programs across the city.\n";
    std::cout << "2. Reducing plastic waste by setting up additional recycling points.\n";
    std::cout << "3. Partnering with local businesses to encourage sustainable packaging.\n";
    std::cout << "4. Educating citizens about reducing food waste through campaigns.\n";

    std::cout << "\nAction Plan for the Year:\n";
    std::cout << "--------------------------------\n";
    std::cout << "1. Launch a citywide campaign to reduce plastic bag usage by 50%.\n";
    std::cout << "2. Set up 100 composting bins in public spaces and community gardens.\n";
    std::cout << "3. Offer free workshops on sustainable practices for local businesses.\n";

    // Simulate tracking the progress of initiatives
    std::cout << "\nCurrent Progress:\n";
    std::cout << "--------------------------------\n";
    std::cout << "1. Plastic reduction: 20% decrease in usage since the last quarter.\n";
    std::cout << "2. Composting bins installed: 45 of 100.\n";
    std::cout << "3. Educational campaigns reaching 30% of the population.\n";
}

void trackRecyclingEfforts()
{
    std::cout << "Tracking recycling efforts in the city...\n";
    std::cout << "Fetching the latest recycling data...\n";

    // Simulated data for demonstration
    int totalRecycledMaterials = 500;
    double recyclingRate = 50.0;
    int recyclingBins = 200;
    int wasteDivertedFromLandfill = 1000;  // in tons

    std::cout << "\nRecycling Statistics Report:\n";
    std::cout << "------------------------------------\n";
    std::cout << "1. Total recycled materials: " << totalRecycledMaterials << " tons\n";
    std::cout << "2. Percentage of waste diverted from landfill: " << recyclingRate << "%\n";
    std::cout << "3. Total number of recycling bins installed: " << recyclingBins << "\n";
    std::cout << "4. Total waste diverted from landfill (in tons): " << wasteDivertedFromLandfill << " tons\n";

    std::cout << "\nRecommendations for improvement:\n";
    std::cout << "------------------------------------\n";
    std::cout << "1. Increase the number of recycling bins by 30% in high-density areas.\n";
    std::cout << "2. Promote recycling in schools and colleges through awareness campaigns.\n";
    std::cout << "3. Increase the number of recycling centers for electronic waste.\n";
}

 void setUpEducationalPrograms()
 {
    std::cout << "Setting up educational programs on sustainable waste management...\n";
    std::cout << "We are focusing on the following programs:\n";

    // Simulate setup of educational programs
    std::cout << "1. School workshops to educate students on recycling and composting.\n";
    std::cout << "2. Community outreach programs to inform citizens about reducing waste.\n";
    std::cout << "3. Online awareness campaigns targeting all age groups.\n";

    std::cout << "\nProgram Schedule:\n";
    std::cout << "------------------------\n";
    std::cout << "1. Recycling Awareness Workshop on January 15th at City Hall.\n";
    std::cout << "2. Composting Workshop on January 20th at the Community Center.\n";
    std::cout << "3. Online Seminar on Waste Management on February 5th.\n";

    std::cout << "\nTracking Program Implementation...\n";
    std::cout << "------------------------------------\n";
    std::cout << "1. Workshop attendees so far: 500 people.\n";
    std::cout << "2. Total online participants in webinars: 1500 people.\n";
    std::cout << "3. Program feedback rating: 4.5/5\n";
}

 void optimizeWasteCollectionRoutes()
 {
    std::cout << "Optimizing waste collection routes for efficient pickup...\n";
    std::cout << "Analyzing waste generation data by area...\n";

    // Simulated waste generation data by area
    double wasteGeneratedByArea[] = {500, 1500, 800, 1200, 900}; // in kg
    std::string areas[] = {"Sector 1", "Sector 2", "Sector 3", "Sector 4", "Sector 5"};

    // Optimization logic (simple, based on waste amount)
    std::cout << "\nWaste Collection Route Optimization:\n";
    std::cout << "--------------------------------------------\n";
    for (int i = 0; i < 5; i++)
    {
        if (wasteGeneratedByArea[i] > 1000)
        {
            std::cout << "Priority area: " << areas[i] << " with waste generation of " << wasteGeneratedByArea[i] << " kg.\n";
            std::cout << "Optimized collection route: Use larger vehicles with higher capacity.\n";
        }
    else
        {
            std::cout << "Standard collection route for area: " << areas[i] << " with waste generation of " << wasteGeneratedByArea[i] << " kg.\n";
            std::cout << "Optimized collection route: Use smaller vehicles.\n";
        }
    }

    std::cout << "\nRoutes have been optimized based on the data. The waste collection system is now more efficient.\n";
}

 void analyzeWasteGenerationPatterns()
 {
    std::cout << "Analyzing waste generation patterns in the city...\n";
    std::cout << "Fetching data from all sectors...\n";

    // Simulating the data collection process
    double industrialWaste = 2500.0; // in tons
    double residentialWaste = 1500.0; // in tons
    double commercialWaste = 800.0;  // in tons

    std::cout << "\nWaste Generation Breakdown:\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "1. Industrial Waste: " << industrialWaste << " tons\n";
    std::cout << "2. Residential Waste: " << residentialWaste << " tons\n";
    std::cout << "3. Commercial Waste: " << commercialWaste << " tons\n";

    // Analyzing trends and suggesting actions
    std::cout << "\nAnalysis:\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "1. The highest waste generation comes from industries, suggesting the need for stricter waste management policies in industrial zones.\n";
    std::cout << "2. Residential waste generation is significantly high, indicating a need for better waste segregation and recycling campaigns.\n";
    std::cout << "3. Commercial sectors can be encouraged to reduce waste through incentives and more waste diversion programs.\n";
}

 void trackWasteManagementStats()
 {
    std::cout << "Track City-Wide Waste Management Statistics\n";
    std::cout << "-----------------------------------------\n";

    std::cout << "Please choose the type of statistics you would like to view:\n";
    std::cout << "1. Total waste generated in the city\n";
    std::cout << "2. Waste recycled in the city\n";
    std::cout << "3. Waste composted in the city\n";
    std::cout << "4. Waste sent to landfill\n";
    std::cout << "5. Waste reduction progress over the last 6 months\n";
    std::cout << "6. User participation in waste management programs\n";

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    while (choice < 1 || choice > 6)
    {
        std::cout << "Invalid input. Please choose a valid option between 1 and 6: ";
        std::cin >> choice;
    }

    switch (choice)
    {
        case 1:
            std::cout << "Displaying total waste generated this year:\n";
            // Fetch and display total waste generated in the city
            break;
        case 2:
            std::cout << "Displaying total waste recycled this year:\n";
            // Fetch and display total waste recycled in the city
            break;
        case 3:
            std::cout << "Displaying total waste composted this year:\n";
            // Fetch and display total waste composted in the city
            break;
        case 4:
            std::cout << "Displaying total waste sent to landfill this year:\n";
            // Fetch and display total waste sent to landfill in the city
            break;
        case 5:
            std::cout << "Displaying waste reduction progress for the last 6 months:\n";
            // Fetch and display trends and progress
            break;
        case 6:
            std::cout << "Displaying user participation in waste management programs:\n";
            // Fetch and display user participation data
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
    }

    std::cout << "Would you like to view another statistic? (y/n): ";
    char response;
    std::cin >> response;
    if (response == 'y' || response == 'Y')
    {
        trackWasteManagementStats();
    } else
    {
        std::cout << "Returning to main menu...\n";
    }
}

 void trackWasteGenerationByDate()
 {
    std::string date;
    std::cout << "Enter the date (YYYY-MM-DD) to track waste generation: ";
    std::cin >> date;

    // Validate date format (basic validation)
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
    {
        std::cout << "Invalid date format! Please use YYYY-MM-DD format.\n";
        return;
    }

    // Example logic for querying data from a database or records
    // This can be extended to fetch data from an actual database, CSV file, or other sources.

    // Sample records based on date
    std::map<std::string, std::pair<int, int>> wasteData =
    {
        {"2024-12-01", {150, 120}}, // Example: 150 kg wet waste, 120 kg dry waste
        {"2024-12-02", {180, 140}},
        {"2024-12-03", {160, 130}},
    };

    if (wasteData.find(date) == wasteData.end())
    {
        std::cout << "No waste data found for the entered date.\n";
        return;
    }

    // Fetch the wet and dry waste data for the given date
    int wetWaste = wasteData[date].first;
    int dryWaste = wasteData[date].second;

    // Calculate total waste
    int totalWaste = wetWaste + dryWaste;

    // Display results
    std::cout << "Waste generation data for " << date << ":\n";
    std::cout << "------------------------------------\n";
    std::cout << "Wet waste generated: " << wetWaste << " kg\n";
    std::cout << "Dry waste generated: " << dryWaste << " kg\n";
    std::cout << "Total waste generated: " << totalWaste << " kg\n";

    // Optionally, you can add more information, like comparison with previous days or trends
    std::cout << "\nWaste generation trend:\n";
    std::cout << "--------------------------------\n";

    // Compare with the previous day
    if (wasteData.find(date) != wasteData.begin())
    {
        auto prevDayIt = std::prev(wasteData.lower_bound(date));
        int prevWetWaste = prevDayIt->second.first;
        int prevDryWaste = prevDayIt->second.second;

        std::cout << "Comparing with the previous day (" << prevDayIt->first << "):\n";
        std::cout << "Wet waste difference: " << wetWaste - prevWetWaste << " kg\n";
        std::cout << "Dry waste difference: " << dryWaste - prevDryWaste << " kg\n";
        std::cout << "Total waste difference: " << totalWaste - (prevWetWaste + prevDryWaste) << " kg\n";
    }
    else
    {
        std::cout << "No data available for the previous day for comparison.\n";
    }

    // Provide suggestions based on the amount of waste generated
    std::cout << "\nWaste reduction suggestions:\n";
    if (wetWaste > 150)
    {
        std::cout << "- Consider composting wet waste to reduce landfill contributions.\n";
    }
    if (dryWaste > 100)
    {
        std::cout << "- Increase recycling efforts for dry waste items such as plastics and paper.\n";
    }
    if (totalWaste > 300)
    {
        std::cout << "- Consider enhancing waste segregation and setting up more recycling bins.\n";
    }
}

 void findShortestWasteCollectionRoute(int start, int destination)
 {
    // Define the graph (adjacency matrix) inside the function
    std::vector<std::vector<int>> graph =
    {
        {0, 10, 0, 30, 0},  // Area 0 to 1 (10 units), Area 0 to 3 (30 units)
        {10, 0, 50, 0, 0},   // Area 1 to 0 (10 units), Area 1 to 2 (50 units)
        {0, 50, 0, 20, 10},  // Area 2 to 1 (50 units), Area 2 to 3 (20 units), Area 2 to 4 (10 units)
        {30, 0, 20, 0, 60},  // Area 3 to 0 (30 units), Area 3 to 2 (20 units), Area 3 to 4 (60 units)
        {0, 0, 10, 60, 0}    // Area 4 to 2 (10 units), Area 4 to 3 (60 units)
    };

    int V = graph.size();  // Number of areas (vertices)

    std::vector<int> dist(V, INT_MAX);  // Distance array to store the shortest distances from the start area
    std::vector<bool> visited(V, false); // Visited array to keep track of which areas have been processed
    dist[start] = 0;  // Distance from the start to itself is 0

    // Dijkstra's Algorithm
    for (int i = 0; i < V - 1; ++i)
        {
        // Find the unvisited area with the minimum distance
        int min = INT_MAX, u = -1;
        for (int j = 0; j < V; ++j)
        {
            if (!visited[j] && dist[j] <= min)
            {
                min = dist[j];
                u = j;
            }
        }

        // Mark the selected area as visited
        visited[u] = true;

        // Update the distances of adjacent areas
        for (int v = 0; v < V; ++v)
            {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Display the shortest path distance
    if (dist[destination] == INT_MAX)
    {
        std::cout << "No path exists from the start area to the destination area.\n";
    } else
    {
        std::cout << "The shortest waste collection route from area " << start << " to area " << destination
                  << " is: " << dist[destination] << " units.\n";
    }
}


public:
    // Admin(const std::string& u, const std::string& p) : UserBase(), username(u), password(p) {}
    void greet() const override
    {
        std::cout << "Hi, Admin!" << std::endl;
    }
    void userMenu() override
    {
        if (Authentication::authenticateAdmin(*this))
        {
            std::cout << "Hi, Admin! You are now logged in.\n";
            handleMenu();
        }
        else
        {
            std::cout << "Invalid username or password for admin.\n";
        }
    }

      Admin() : UserBase()
    {
       std::pair<std::string, std::string> adminCredentials = readAdminInfo();
        username = adminCredentials.first;
        password = adminCredentials.second;
    }
    void adminMenu()
    {
        if (Authentication::authenticateAdmin(*this))
        {
            std::cout << "Hi, Admin! You are now logged in.\n";
            handleMenu();
        }
        else
        {
            std::cout << "Invalid username or password for admin.\n";
        }
    }

    friend class Authentication;

    bool authenticate(const std::string &u, const std::string &p) const
    {
        try
        {
            if(u!=username || p!= password)
            {
                throw 0;
            }
        }
        catch(int x)
        {
            std::cout<<"wrong input, try again"<<std::endl<<std::endl;
            return false;
        }
        return true;
    }
};

bool Authentication::authenticateAdmin(Admin &admin)
{
    bool auth=false;
    while(!auth)
    {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    auth = admin.authenticate(username, password);
    }
    return auth;
}

class User : public UserBase
{
private:
    struct CartItem
    {
        std::string category;
        double weight;
        double price;
    };

    std::vector<CartItem> cart;

    void addToCart()
    {
        viewAllCategoriesWithPrices();
        std::string categoryToAdd;
        double weight;

        std::cout << "Enter the category to add to the cart: ";
        std::cin.ignore(); // Ignore any previous newline character in the input buffer
        std::getline(std::cin, categoryToAdd);

        std::cout << "Enter the weight (in kg): ";
        std::cin >> weight;

        CSVHandler csvHandler("categories.csv");
        std::vector<std::pair<std::string, double>> categories = csvHandler.readData();

        auto it = std::find_if(categories.begin(), categories.end(), [&](const auto &item)
                               { return item.first == categoryToAdd; });

        if (it != categories.end())
        {
            double price = it->second * weight;
            cart.push_back({categoryToAdd, weight, price});
            std::cout << "Category added to the cart successfully.\n";
        }
        else
        {
            std::cout << "Category not found. Unable to add to the cart.\n";
        }
    }

    void removeFromCart()
    {
        viewCart();
        if (cart.empty())
        {
            std::cout << "Cart is empty.\n";
            return;
        }

        std::string categoryToRemove;
        std::cout << "Enter the category to remove from the cart: ";
        std::cin.ignore(); // Ignore any previous newline character in the input buffer
        std::getline(std::cin, categoryToRemove);

        auto it = std::remove_if(cart.begin(), cart.end(), [&](const auto &item)
                                 { return item.category == categoryToRemove; });

        if (it != cart.end())
        {
            cart.erase(it, cart.end());
            std::cout << "Category removed from the cart successfully.\n";
        }
        else
        {
            std::cout << "Category not found in the cart.\n";
        }
    }

    void checkout()
    {
        if (cart.empty())
        {
            std::cout << "Cart is empty. Nothing to checkout.\n";
            return;
        }

        std::string filename = "transactions.csv";
        std::ofstream outputFile(filename, std::ios::app);
        if (!outputFile)
        {
            std::cout << "Error opening file for writing transactions.\n";
            return;
        }

        std::string userName;
        std::cout << "Enter your name: ";
        std::cin.ignore(); // Ignore any previous newline character in the input buffer
        std::getline(std::cin, userName);

        double totalAmount = 0.0;
        std::time_t currentTime = std::time(nullptr);
        std::string timestamp = std::asctime(std::localtime(&currentTime));

        outputFile << "Transaction Time, User Name, Category, Weight (kg), Price (Rs)\n";
        for (const auto &item : cart)
        {
            outputFile << timestamp << ", " << userName << ", " << item.category << ", " << item.weight << ", " << item.price << "\n";
            totalAmount += item.price;
        }

        outputFile << "Total Amount, , , ," << totalAmount << "\n";

        outputFile.close();

        // Empty the cart after successful checkout
        cart.clear();

        std::cout << "Checkout successful .\n";
    }

    void viewCart()
    {
        if (cart.empty())
        {
            std::cout << "Cart is empty.\n";
        }
        else
        {
            double totalPrice = 0.0;
            std::cout << "----- Cart -----\n";
            for (const auto &item : cart)
            {
                std::cout << item.category << ": " << item.weight << " kg - " << item.price << " Rs\n";
                totalPrice += item.price;
            }
            std::cout << "----------------\n";
            std::cout << "Total Price: " << totalPrice << " Rs\n";
        }
    }

    void totalPrice()
    {
        if (cart.empty())
        {
            std::cout << "Price = 0 as cart is empty\n";
        }
        else
        {
            double totalPrice = 0.0;
            for (const auto &item : cart)
            {
                totalPrice += item.price;
            }
            std::cout << "----------------\n";
            std::cout << "Total Price: " << totalPrice << " Rs\n";
        }
    }
    void checkoutConfirmation()
    {
    if (cart.empty())
    {
        std::cout << "Cart is empty. Nothing to checkout.\n";
        return;
    }

    double totalAmount = 0.0;
    std::cout << "----- Checkout Confirmation -----\n";
    for (const auto &item : cart)
    {
        std::cout << item.category << ": " << item.weight << " kg - " << item.price << " Rs\n";
        totalAmount += item.price;
    }

    std::cout << "-----------------------------\n";
    std::cout << "Total Amount: " << totalAmount << " Rs\n";
    std::cout << "Do you want to proceed with checkout? (yes/no): ";
    std::string choice;
    std::cin >> choice;

    if (choice == "yes")
    {
        checkout();  // Call the original checkout function
    }
    else
    {
        std::cout << "Checkout canceled.\n";
    }
 }

 void findNearestWasteBin(double userLat, double userLon)
{
    // Sample waste bins data (latitude, longitude)
    std::vector<std::pair<double, double>> wasteBins =
    {
        {12.9716, 77.5946}, // Example: Bin 1 (Bangalore)
        {13.0827, 80.2707}, // Example: Bin 2 (Chennai)
        {19.0760, 72.8777}  // Example: Bin 3 (Mumbai)
    };

    double minDistance = std::numeric_limits<double>::max();
    int nearestBin = -1;
    for (size_t i = 0; i < wasteBins.size(); ++i)
    {
        double distance = calculateDistance(userLat, userLon, wasteBins[i].first, wasteBins[i].second);
        if (distance < minDistance)
        {
            minDistance = distance;
            nearestBin = i;
        }
    }

    if (nearestBin != -1)
    {
        std::cout << "Nearest waste bin is located at latitude: "
                  << wasteBins[nearestBin].first << ", longitude: "
                  << wasteBins[nearestBin].second << "\n";
    }
    else
    {
        std::cout << "No waste bins available in the database.\n";
    }
}

// Helper function to calculate distance between two latitude and longitude points (in kilometers)
double calculateDistance(double lat1, double lon1, double lat2, double lon2)
{
    const double PI = 3.14159265358979323846;
    const double R = 6371; // Earth radius in kilometers

    double dLat = (lat2 - lat1) * PI / 180.0;
    double dLon = (lon2 - lon1) * PI / 180.0;

    lat1 = lat1 * PI / 180.0;
    lat2 = lat2 * PI / 180.0;

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::sin(dLon / 2) * std::sin(dLon / 2) * std::cos(lat1) * std::cos(lat2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return R * c; // Distance in kilometers
}

void findNearestDumpingArea(double userLat, double userLon)
{
    // Sample dumping areas data (latitude, longitude)
    std::vector<std::pair<double, double>> dumpingAreas =
    {
        {12.9716, 77.5946}, // Example: Area 1 (Bangalore)
        {13.0827, 80.2707}, // Example: Area 2 (Chennai)
        {19.0760, 72.8777}  // Example: Area 3 (Mumbai)
    };

    double minDistance = std::numeric_limits<double>::max();
    int nearestArea = -1;
    for (size_t i = 0; i < dumpingAreas.size(); ++i)
    {
        double distance = calculateDistance(userLat, userLon, dumpingAreas[i].first, dumpingAreas[i].second);
        if (distance < minDistance)
        {
            minDistance = distance;
            nearestArea = i;
        }
    }

    if (nearestArea != -1)
    {
        std::cout << "Nearest waste dumping area is located at latitude: "
                  << dumpingAreas[nearestArea].first << ", longitude: "
                  << dumpingAreas[nearestArea].second << "\n";
    }
    else
    {
        std::cout << "No waste dumping areas available in the database.\n";
    }
}

 void reportIllegalDumping()
 {
    std::string location, details;
    std::cout << "Enter the location of illegal dumping: ";
    std::cin.ignore();
    std::getline(std::cin, location);
    std::cout << "Enter any additional details (optional): ";
    std::getline(std::cin, details);

    std::cout << "Thank you for reporting the illegal dumping at " << location << ".\n";
    std::cout << "Details: " << details << "\n";
    std::cout << "Your report will be reviewed and action will be taken accordingly.\n";
 }

 void requestAdditionalWasteBins()
 {
    std::string area;
    std::cout << "Enter the area name where you want additional waste bins: ";
    std::cin.ignore();
    std::getline(std::cin, area);

    std::cout << "Requesting additional waste bins for " << area << "...\n";
    std::cout << "Your request has been successfully submitted and will be processed.\n";
 }

 void participateInRecyclingProgram()
 {
    std::cout << "You are about to join the city's Recycling Program.\n";
    std::cout << "Benefits include: discounts on waste services, recycling rewards, and environmental contributions.\n";
    std::cout << "Please enter your address for verification: ";
    std::string address;
    std::cin.ignore();
    std::getline(std::cin, address);

    std::cout << "You have successfully joined the recycling program. Welcome, " << address << "!\n";
}

 void trackPersonalWaste()
 {
    double wasteDisposed, wasteRecycled;
    std::cout << "Enter the amount of waste you disposed of (in kg): ";
    std::cin >> wasteDisposed;
    std::cout << "Enter the amount of waste you recycled (in kg): ";
    std::cin >> wasteRecycled;

    if(wasteDisposed < 0 || wasteRecycled < 0)
    {
        std::cout << "Invalid input! Waste disposed and recycled values must be non-negative.\n";
        return;
    }

    double totalWaste = wasteDisposed + wasteRecycled;
    std::cout << "Tracking Personal Waste:\n";
    std::cout << "Waste Disposed: " << wasteDisposed << " kg\n";
    std::cout << "Waste Recycled: " << wasteRecycled << " kg\n";
    std::cout << "Total Waste: " << totalWaste << " kg\n";
    std::cout << "Thank you for managing your waste responsibly!\n";
}

void getSustainableWasteManagementTips()
{
    std::cout << "Here are some detailed tips for sustainable waste management:\n";
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "1. Reduce, Reuse, Recycle.\n";
    std::cout << "   - Reduce your consumption by buying fewer disposable items.\n";
    std::cout << "   - Reuse products whenever possible, like glass jars, plastic containers, etc.\n";
    std::cout << "   - Recycle paper, plastic, and glass properly at designated centers.\n";
    std::cout << "2. Avoid plastic bags and switch to reusable ones.\n";
    std::cout << "   - Carry your own cloth or jute bags when you go shopping.\n";
    std::cout << "   - Many stores offer discounts for using reusable bags.\n";
    std::cout << "3. Compost organic waste to reduce landfill waste.\n";
    std::cout << "   - You can compost kitchen waste like vegetable peels, fruit scraps, etc.\n";
    std::cout << "   - Set up a small composting bin in your backyard or community garden.\n";
    std::cout << "4. Buy products with minimal packaging.\n";
    std::cout << "   - Choose products with minimal or biodegradable packaging to reduce waste.\n";
    std::cout << "5. Avoid electronic waste and recycle old electronics properly.\n";
    std::cout << "   - Instead of discarding old electronics, recycle them at authorized centers.\n";
    std::cout << "   - Many e-waste centers also refurbish devices for reuse.\n";

    std::cout << "\nBy following these simple tips, you can make a significant impact on waste management in your community.\n";
}

 void reportImproperWasteDisposal()
 {
    std::string location;
    std::cout << "Enter the location of improper waste disposal (e.g., street name, landmark): ";
    std::cin.ignore();  // To clear any leftover newline characters
    std::getline(std::cin, location);

    // Logic to store and report the location
    std::cout << "\nThank you for reporting. The location of improper waste disposal has been recorded.\n";
    std::cout << "Reported location: " << location << "\n";

    // Simulate sending a report to the waste management department
    std::cout << "\nSending report to the local waste management department...\n";
    std::cout << "Report successfully sent.\n";
}

 void findRecyclingCentersNearby()
 {
    std::cout << "Finding nearby recycling centers...\n";
    std::cout << "Please enter your current location (latitude, longitude): ";
    double latitude, longitude;
    std::cin >> latitude >> longitude;

    // Simulated list of nearby recycling centers with their locations
    double recyclingCenterLocations[5][2] = {{12.9716, 77.5946}, {12.9353, 77.6247}, {12.9670, 77.6104}, {12.9536, 77.6094}, {12.9380, 77.6240}};
    std::string centerNames[5] = {"Recycling Center A", "Recycling Center B", "Recycling Center C", "Recycling Center D", "Recycling Center E"};

    // Display nearby centers
    std::cout << "\nNearby Recycling Centers:\n";
    for (int i = 0; i < 5; i++) {
        std::cout << centerNames[i] << " located at (" << recyclingCenterLocations[i][0] << ", " << recyclingCenterLocations[i][1] << ")\n";
    }

    std::cout << "\nYou can visit any of these centers to drop off your recyclables.\n";
}

 void rateWasteManagementService()
 {
    std::cout << "Welcome to the Waste Management Feedback System.\n";
    std::cout << "Please rate your experience with the city's waste management services on a scale of 1 to 5.\n";
    std::cout << "1: Poor, 2: Fair, 3: Good, 4: Very Good, 5: Excellent\n";
    int rating;
    std::cin >> rating;

    // Validate input
    if (rating >= 1 && rating <= 5)
        {
        std::cout << "Thank you for your rating: " << rating << "/5\n";

        // Detailed feedback
        std::cout << "Please share any specific comments, suggestions, or concerns you may have regarding the waste management system:\n";
        std::string feedback;
        std::cin.ignore();  // Clear input buffer
        std::getline(std::cin, feedback);

        std::cout << "You wrote: " << feedback << "\n";
        std::cout << "Your feedback has been submitted successfully. We will review your suggestions and work on improving the service.\n";
    }
    else
    {
        std::cout << "Invalid rating. Please provide a rating between 1 and 5.\n";
    }
}

void requestMoreRecyclingBins()
{
    std::cout << "Request More Recycling Bins for Your Area\n";
    std::cout << "-------------------------------------------\n";
    std::cout << "Please provide the name of your area or locality: ";
    std::string areaName;
    std::cin.ignore();
    std::getline(std::cin, areaName);

    std::cout << "Enter the number of bins you need for recycling purposes: ";
    int numberOfBins;
    std::cin >> numberOfBins;

    std::cout << "You have requested " << numberOfBins << " recycling bins for the area: " << areaName << ".\n";
    std::cout << "Thank you for helping to improve recycling infrastructure in your community. We will process your request.\n";
}

void learnWasteSegregationTips()
{
    std::cout << "Waste Segregation Tips for a Greener Home\n";
    std::cout << "--------------------------------------------\n";

    std::cout << "1. Wet Waste: This includes food scraps, vegetable peels, and other organic waste. This can be composted at home.\n";
    std::cout << "   - Tip: Use a separate container in your kitchen to collect wet waste for composting.\n";

    std::cout << "2. Dry Waste: Includes recyclable items like paper, cardboard, plastics, glass bottles, and metals.\n";
    std::cout << "   - Tip: Clean the recyclables before putting them in the bin to avoid contamination.\n";

    std::cout << "3. Hazardous Waste: Items like batteries, paint, electronic waste, and medical waste should be kept separate.\n";
    std::cout << "   - Tip: Find out the local disposal centers for hazardous waste in your city.\n";

    std::cout << "4. E-Waste: Old phones, chargers, computers, and televisions should be sent to e-waste recycling centers.\n";
    std::cout << "   - Tip: Many electronic stores have take-back programs for old electronics.\n";

    std::cout << "By following these guidelines, you can effectively segregate your waste, making it easier to recycle or compost.\n";
}

 void createPersonalWasteManagementPlan()
 {
    std::cout << "Welcome to your personalized waste management planner!\n";
    std::cout << "------------------------------------------\n";
    std::cout << "Step 1: Set Your Waste Reduction Goals\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "How much waste do you want to reduce in the next 6 months? (Enter in kg): ";
    double wasteReductionGoal;
    std::cin >> wasteReductionGoal;

    while (wasteReductionGoal <= 0)
    {
        std::cout << "Please enter a valid positive number for your waste reduction goal.\n";
        std::cin >> wasteReductionGoal;
    }

    std::cout << "Your goal is to reduce " << wasteReductionGoal << " kg of waste in the next 6 months.\n";
    std::cout << "Great! Let's move to the next step.\n";

    std::cout << "-----------------------------------------\n";
    std::cout << "Step 2: Choose Waste Reduction Strategies\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "Please select strategies to reduce your waste (You can select multiple by entering numbers separated by spaces): \n";
    std::cout << "1. Reduce single-use plastic (e.g., water bottles, straws)\n";
    std::cout << "2. Start composting kitchen waste\n";
    std::cout << "3. Recycle more (plastic, glass, paper)\n";
    std::cout << "4. Donate unwanted items (clothes, electronics)\n";
    std::cout << "5. Reduce food waste (plan meals, avoid overbuying)\n";
    std::cout << "6. Buy in bulk to reduce packaging waste\n";

    std::vector<int> strategies;
    int strategy;
    std::cout << "Enter your selected strategies (separate numbers by space): ";

    while (std::cin >> strategy)
        {
        if (strategy < 1 || strategy > 6)
        {
            std::cout << "Please enter a valid number between 1 and 6.\n";
        }
    else
        {
            strategies.push_back(strategy);
        }
        if (std::cin.get() == '\n') break;
    }

    if (strategies.empty())
    {
        std::cout << "You need to select at least one strategy. Let's try again.\n";
        return;
    }

    std::cout << "-----------------------------------------\n";
    std::cout << "Step 3: Set Weekly Action Points\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "For each strategy you selected, create a weekly action plan. Example: If you selected \"Reduce food waste\", set an action to plan your meals every Sunday evening.\n";

    std::map<int, std::string> strategyMap =
    {
        {1, "Reduce single-use plastic"},
        {2, "Start composting kitchen waste"},
        {3, "Recycle more"},
        {4, "Donate unwanted items"},
        {5, "Reduce food waste"},
        {6, "Buy in bulk"}
    };

    for (int s : strategies)
    {
        std::cout << "Action plan for " << strategyMap[s] << ": ";
        std::string actionPoint;
        std::cin.ignore();
        std::getline(std::cin, actionPoint);
        std::cout << "You set the following action: " << actionPoint << "\n";
    }

    std::cout << "-----------------------------------------\n";
    std::cout << "Step 4: Track Your Progress\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "You can now track your progress weekly. For each strategy, log how much waste you reduced and how effectively you followed through with your actions.\n";
    std::cout << "You can also adjust your goals every month based on your progress.\n";
    std::cout << "This will keep you motivated and focused on your waste reduction journey!\n";
}

 void trackWasteGenerationAndReduction()
 {
    std::cout << "Track Your Waste Generation and Reduction\n";
    std::cout << "----------------------------------------\n";

    double generatedWaste, recycledWaste, compostedWaste;
    std::cout << "Enter the total waste you generated this week (in kg): ";
    std::cin >> generatedWaste;

    while (generatedWaste < 0)
    {
        std::cout << "Please enter a valid positive number for waste generated.\n";
        std::cin >> generatedWaste;
    }

    std::cout << "Enter the total waste you recycled this week (in kg): ";
    std::cin >> recycledWaste;

    while (recycledWaste < 0)
    {
        std::cout << "Please enter a valid positive number for recycled waste.\n";
        std::cin >> recycledWaste;
    }

    std::cout << "Enter the total waste you composted this week (in kg): ";
    std::cin >> compostedWaste;

    while (compostedWaste < 0)
    {
        std::cout << "Please enter a valid positive number for composted waste.\n";
        std::cin >> compostedWaste;
    }

    double totalWasteReduced = recycledWaste + compostedWaste;
    double wasteToLandfill = generatedWaste - totalWasteReduced;

    std::cout << "You generated a total of " << generatedWaste << " kg of waste this week.\n";
    std::cout << "You recycled " << recycledWaste << " kg and composted " << compostedWaste << " kg.\n";
    std::cout << "Total waste reduced: " << totalWasteReduced << " kg\n";
    std::cout << "Waste that went to the landfill: " << wasteToLandfill << " kg\n";

    if (wasteToLandfill > 0)
    {
        std::cout << "You can reduce your landfill waste further by increasing your recycling and composting efforts.\n";
        std::cout << "Try setting more specific goals for next week. For instance, aim to reduce plastic waste further by choosing reusable products.\n";
        std::cout << "Would you like tips on reducing your waste further? (y/n): ";
        char response;
        std::cin >> response;
        if (response == 'y' || response == 'Y')
        {
            std::cout << "Here are some tips:\n";
            std::cout << "- Avoid single-use plastic items like plastic bottles, bags, and straws.\n";
            std::cout << "- Plan meals ahead to avoid food waste.\n";
            std::cout << "- Buy in bulk to reduce packaging waste.\n";
            std::cout << "- Start a compost bin for your kitchen scraps.\n";
        }
    }
    else
    {
        std::cout << "Great job! You've managed to reduce all your waste this week. Keep it up!\n";
    }

    std::cout << "You can review your progress weekly or monthly to set new goals and further reduce your impact.\n";
}

 void participateInWasteReductionChallenges()
 {
    std::cout << "Participate in Waste Reduction Challenges\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Join a weekly challenge to reduce waste in your community!\n";
    std::cout << "Here are the available challenges for this month:\n";
    std::cout << "1. Plastic-Free Week: Avoid single-use plastics for an entire week.\n";
    std::cout << "2. Zero Waste Challenge: Aim to generate zero waste for the entire week.\n";
    std::cout << "3. Recycling Marathon: Collect and recycle as much as possible.\n";
    std::cout << "4. Composting Challenge: Compost all your kitchen waste for a week.\n";
    std::cout << "5. Sustainable Shopping Challenge: Shop for sustainable, eco-friendly products only for the week.\n";
    std::cout << "6. Paper Reduction Week: Reduce paper usage by switching to digital alternatives.\n";
    std::cout << "7. E-Waste Collection Drive: Collect and recycle your electronic waste for a week.\n";

    std::cout << "Please choose a challenge by entering its number (1-7): ";
    int choice;
    std::cin >> choice;

    while (choice < 1 || choice > 7)
    {
        std::cout << "Invalid choice. Please select a number between 1 and 7.\n";
        std::cin >> choice;
    }

    std::cout << "You have joined the challenge number " << choice << "!\n";
    std::cout << "Here are the details of your chosen challenge:\n";

    switch (choice)
    {
        case 1:
            std::cout << "You have joined the Plastic-Free Week challenge! Avoid single-use plastics.\n";
            break;
        case 2:
            std::cout << "You have joined the Zero Waste Challenge! Aim for zero waste for a week.\n";
            break;
        case 3:
            std::cout << "You have joined the Recycling Marathon! Collect and recycle as much as possible.\n";
            break;
        case 4:
            std::cout << "You have joined the Composting Challenge! Compost your kitchen waste.\n";
            break;
        case 5:
            std::cout << "You have joined the Sustainable Shopping Challenge! Shop sustainably.\n";
            break;
        case 6:
            std::cout << "You have joined the Paper Reduction Week challenge! Reduce paper usage.\n";
            break;
        case 7:
            std::cout << "You have joined the E-Waste Collection Drive! Collect and recycle e-waste.\n";
            break;
    }

    std::cout << "Track your progress and make sure to take a photo or note each day for your challenge.\n";
    std::cout << "Would you like to share your progress online? (y/n): ";
    char response;
    std::cin >> response;

    if (response == 'y' || response == 'Y')
    {
        std::cout << "You can share your progress with your social media or local community groups to inspire others!\n";
    }
    else
    {
        std::cout << "No worries! You can still track your progress privately.\n";
    }
}


public:
    User() {}
    void greet() const override
    {
        std::cout << "Hi, User!" << std::endl;
    }
    void userMenu()
    {
        int choice;
        while (true)
        {
            std::cout << "----------- User Menu -----------\n"
                      << "1. View All Categories with Prices\n"
                      << "2. Add Items to Cart\n"
                      << "3. Remove Items from Cart\n"
                      << "4. View Cart\n"
                      << "5. Total Price\n"
                      << "6. Checkout\n"
                      << "7. Checkout confi\n"
                      << "8. find Nearest Waste Bin\n"
                      << "9. find Nearest Dumping Area\n"
                      << "10. report Illegal Dumping\n"
                      << "11. request Additional WasteBin\n"
                      << "12. participate In Recycling Program\n"
                      << "13. track Personal Waste\n"
                      << "14. get Sustainable Waste Management Tips\n"
                      << "15. report Improper Waste Disposal\n"
                      << "16. find Recycling Centers Nearby\n"
                      << "17. rate WasteManagement Service\n"
                      << "18. request More Recycling Bins\n"
                      << "19. learn Waste Segregation Tips\n"
                      << "20. create Personal Waste Management Plan\n"
                      << "21. track Waste Generation And Reduction\n"
                      << "22. participate In Waste Reduction Challenges\n"
                      << "10. Quit\n"
                      << "----------------------------------\n";

            std::string input;
            std::cout << "Enter your choice: ";
            std::cin >> input;

            // Check if input is an integer
            std::istringstream iss(input);
            if (!(iss >> choice))
            {
                std::cout << "Invalid input. Please enter a valid integer choice.\n";
                std::cin.clear();                                                   // Clear error flags from cin
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters in the input buffer
                continue;                                                           // Continue to next iteration of the loop
            }

            switch (choice)
            {
            case 1:
                viewAllCategoriesWithPrices();
                break;
            case 2:
                addToCart();
                break;
            case 3:
                removeFromCart();
                break;
            case 4:
                viewCart();
                break;
            case 5:
                totalPrice();
                break;
            case 6:
                checkout();
                break;
            case 7:
                checkoutConfirmation();
                break;
            case 8:
                double userLat, userLon;
                std::cout << "Enter your current latitude: ";
                std::cin >> userLat;
                std::cout << "Enter your current longitude: ";
                std::cin >> userLon;
                findNearestWasteBin(userLat, userLon);
                break;
            case 9:
                std::cout << "Enter your current latitude: ";
                std::cin >> userLat;
                std::cout << "Enter your current longitude: ";
                std::cin >> userLon;
                findNearestDumpingArea(userLat, userLon);
                break;
            case 10:
                reportIllegalDumping();
                break;
            case 11:
                requestAdditionalWasteBins();
                break;
            case 12:
                participateInRecyclingProgram();
                break;
            case 13:
                trackPersonalWaste();
                break;
            case 14:
                getSustainableWasteManagementTips();
                break;
            case 15:
                reportImproperWasteDisposal();
                break;
            case 16:
                findRecyclingCentersNearby();
                break;
            case 17:
                rateWasteManagementService();
                break;

            case 18:
                requestMoreRecyclingBins();
                break;
            case 19:
                learnWasteSegregationTips();
                break;

            case 20:
                createPersonalWasteManagementPlan();
                break;

            case 21:
                trackWasteGenerationAndReduction();
                break;

            case 22:
                participateInWasteReductionChallenges();
                break;


            case 23:
                std::cout << "Exiting User Menu.\n";
                return;

            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

//SUSHIL

class Station
{
public:
    void displayFeedbackSummary();
    string name;
    unordered_map<string, int> connections; // Station name and distance

    Station(string name) : name(name) {}

    void addConnection(const string &station, int distance)
    {
        // Check if the connection already exists
        if (connections.find(station) != connections.end())
        {
            // If the connection exists, update the distance
            connections[station] = distance;
            cout << "Updated the distance to " << station << " from " << name << " to " << distance << " km.\n";
        }
        else
        {
            // If the connection does not exist, add a new connection
            connections[station] = distance;
            cout << "Added a new connection from " << name << " to " << station << " with a distance of " << distance << " km.\n";
        }
    }

    void displayConnections()
    {
        cout << "Connections from " << name << ":\n";
        for (const auto &conn : connections)
        {
            cout << "To " << conn.first << " - " << conn.second << " km\n";
        }
    }
};


class Train
{
public:
    string name;
    vector<string> route;
    int capacity;
    string trainClass;             // Sleeper, AC, Local, etc.
    map<string, int> reservations; // Station and number of reserved seats
    vector<pair<string, string>> bookingLog; // To keep track of booking details

    Train(string name, const vector<string> &route, int capacity, const string &trainClass)
        : name(name), route(route), capacity(capacity), trainClass(trainClass) {}

    void reserveSeat(const string &station)
    {
        if (reservations[station] < capacity)
        {
            reservations[station]++;
            bookingLog.push_back({name, station});
            cout << "Seat reserved successfully on " << name << " for station " << station << ".\n";
            cout << "Current reservations at " << station << ": " << reservations[station] << "/" << capacity << "\n";
        }
        else
        {
            cout << "No seats available on " << name << " for station " << station << ".\n";
        }
    }

    void cancelReservation(const string &station)
    {
        if (reservations[station] > 0)
        {
            reservations[station]--;
            cout << "Reservation cancelled successfully on " << name << " for station " << station << ".\n";
            cout << "Current reservations at " << station << ": " << reservations[station] << "/" << capacity << "\n";
        }
        else
        {
            cout << "No reservations to cancel on " << name << " for station " << station << ".\n";
        }
    }

    void modifyReservation(const string &oldStation, const string &newStation)
    {
        if (reservations[oldStation] > 0)
        {
            if (reservations[newStation] < capacity)
            {
                reservations[oldStation]--;
                reservations[newStation]++;
                cout << "Reservation modified successfully from " << oldStation << " to " << newStation << " on " << name << ".\n";
                cout << "Current reservations at " << oldStation << ": " << reservations[oldStation] << "/" << capacity << "\n";
                cout << "Current reservations at " << newStation << ": " << reservations[newStation] << "/" << capacity << "\n";
            }
            else
            {
                cout << "No seats available on " << name << " for station " << newStation << ".\n";
            }
        }
        else
        {
            cout << "No reservations to modify on " << name << " for station " << oldStation << ".\n";
        }
    }

    void displayRoute()
    {
        // Display the train name and class
        cout << "Train: " << name << " (Class: " << trainClass << ")\n";

        // Display the route of the train
        cout << "Route: ";
        for (const auto &station : route)
        {
            cout << station << (station == route.back() ? "\n" : " -> ");
        }

        // Display the total number of stations in the route
        cout << "Total number of stations: " << route.size() << "\n";

        // Display the capacity of the train
        cout << "Train capacity: " << capacity << " seats\n";

        // Display the current reservation status at each station
        cout << "Reservation status:\n";
        for (const auto &station : route)
        {
            cout << "Station: " << station << ", Seats reserved: " << reservations[station] << "/" << capacity << "\n";
        }

        // Display the booking log for this train
        cout << "Booking log:\n";
        for (const auto &booking : bookingLog)
        {
            if (booking.first == name)
            {
                cout << "Station: " << booking.second << "\n";
            }
        }

        // Display a separator for better readability
        cout << "-----------------------------------\n";
    }
    void refundSeat(const string &userName)
    {
        for (auto it = bookingLog.begin(); it != bookingLog.end(); ++it)
        {
            if (it->first == name && it->second == userName)
            {
                reservations[userName]--;
                bookingLog.erase(it);
                cout << "Refund processed successfully for " << userName << " on " << name << ".\n";
                cout << "Current reservations at " << userName << ": " << reservations[userName] << "/" << capacity << "\n";
                return;
            }
        }
        cout << "No reservation found for " << userName << " on " << name << ".\n";
    }

    void displayReservations()
    {
        cout << "Reservations for train " << name << " (" << trainClass << "):\n";
        for (const auto &res : reservations)
        {
            cout << "Station: " << res.first << ", Seats reserved: " << res.second << "/" << capacity << "\n";
        }
    }

};



class TransportSystem
{
private:
    unordered_map<string, Station *> stations;
    unordered_map<string, bool> overcrowdedStations;
    vector<Train> trains;
    vector<pair<string, string>> bookingLog; // To keep track of booking details

    struct Feedback
    {
        std::string userName;
        std::string trainName;
        int rating;
        std::string comments;
    };

    std::vector<Feedback> feedbacks;
public:
    void displayStationList();
    void displayTrainList();
    void displayBookingLog();
    void displayOvercrowdedStations();
    void displayFeedbackSummary();
    void updateTrainSchedule();


    // Helper function for Dijkstra's algorithm
    vector<string> findShortestPath(const string &start, const string &end)
    {
        unordered_map<string, int> distances;
        unordered_map<string, string> previous;
        for (auto &station : stations)
        {
            distances[station.first] = numeric_limits<int>::max();
        }
        distances[start] = 0;

        auto compare = [&distances](const string &a, const string &b)
        {
            return distances[a] > distances[b];
        };

        priority_queue<string, vector<string>, decltype(compare)> pq(compare);
        pq.push(start);

        while (!pq.empty())
        {
            string current = pq.top();
            pq.pop();

            for (auto &conn : stations[current]->connections)
            {
                if (overcrowdedStations[conn.first])
                    continue; // Skip overcrowded stations

                int newDist = distances[current] + conn.second;
                if (newDist < distances[conn.first])
                {
                    distances[conn.first] = newDist;
                    previous[conn.first] = current;
                    pq.push(conn.first);
                }
            }
        }

        vector<string> path;
        string current = end;
        while (current != start)
        {
            path.push_back(current);
            current = previous[current];
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return path;
    }

    vector<vector<string>> findAlternativeRoutes(const string &start, const string &end, int maxAlternatives = 3)
    {
        vector<vector<string>> alternativeRoutes;
        unordered_map<string, int> distances;
        unordered_map<string, string> previous;
        for (auto &station : stations)
        {
            distances[station.first] = numeric_limits<int>::max();
        }
        distances[start] = 0;

        auto compare = [&distances](const string &a, const string &b)
        {
            return distances[a] > distances[b];
        };
        priority_queue<string, vector<string>, decltype(compare)> pq(compare);
        pq.push(start);

        std::function<void(string, vector<string>)> backtrack = [&](string current, vector<string> path)
        {
            if (current == start)
            {
                path.push_back(start);
                reverse(path.begin(), path.end());
                alternativeRoutes.push_back(path);
                return;
            }
            path.push_back(current);
            for (auto &prev : previous)
            {
                if (prev.second == current)
                {
                    backtrack(prev.first, path);
                }
            }
        };

        while (!pq.empty())
        {
            string current = pq.top();
            pq.pop();

            for (auto &conn : stations[current]->connections)
            {
                if (overcrowdedStations[conn.first])
                    continue; // Skip overcrowded stations

                int newDist = distances[current] + conn.second;
                if (newDist < distances[conn.first])
                {
                    distances[conn.first] = newDist;
                    previous[conn.first] = current;
                    pq.push(conn.first);
                }
            }
        }

        backtrack(end, {});

        // Limit the number of alternative routes
        if (alternativeRoutes.size() > maxAlternatives)
        {
            alternativeRoutes.resize(maxAlternatives);
        }

        return alternativeRoutes;
    }

public:
    TransportSystem() : stations(), overcrowdedStations(), trains(), bookingLog() {}

    void addStation(const string &name)
    {
        stations[name] = new Station(name);
        overcrowdedStations[name] = false;
    }

    void addConnection(const string &from, const string &to, int distance)
    {
        stations[from]->addConnection(to, distance);
        stations[to]->addConnection(from, distance);
    }

    void addTrain(const string &name, const vector<string> &route, int capacity, const string &trainClass)
    {
        trains.emplace_back(name, route, capacity, trainClass);
    }

    void reserveTrainSeat(const string &trainName, const string &station)
    {
        for (auto &train : trains)
        {
            if (train.name == trainName)
            {
                train.reserveSeat(station);
                return;
            }
        }
        cout << "Train " << trainName << " not found.\n";
    }



    void requestTrain(const string &from, const string &to, const string &trainClass)
    {
        cout << "Requesting a new " << trainClass << " train from " << from << " to " << to << ".\n";
        cout << "Your request has been noted. We will work on adding this route soon.\n";
    }
        // Function to request a refund
    void requestRefund(const std::string& trainName, const std::string& userName)
    {
        for (auto& train : trains)
            {
            if (train.name == trainName)
            {
                train.refundSeat(userName);
                return;
            }
        }
        std::cout << "Train " << trainName << " not found.\n";
    }

        // Function to reschedule a booking
    void rescheduleBooking(const std::string& oldTrainName, const std::string& newTrainName, const std::string& oldStation)
    {
        for (auto& train : trains)
            {
            if (train.name == oldTrainName)
            {
                if (train.reservations[oldStation] > 0)
                {
                    train.cancelReservation(oldStation);
                    reserveTrainSeat(newTrainName, oldStation);
                }
                return;
            }
        }
        std::cout << "Train " << oldTrainName << " not found.\n";
    }

    void displayTrains()
    {
        cout << "Displaying all trains and their routes:\n";
        for (auto &train : trains)
        {
            train.displayRoute();
            cout << "-----------------------------------\n";
        }
    }

    void updateTrainSchedule(const string &trainName, const vector<pair<string, int>> &stationDelays) {
    for (auto &train : trains)
        {
        if (train.name == trainName)
        {
            cout << "Updating schedule for train: " << trainName << "\n";
            for (const auto &delay : stationDelays)
            {
                cout << "Station: " << delay.first << ", Delay: " << delay.second << " minutes\n";
                // Assuming some internal mechanism to update timings
            }
            cout << "Schedule updated successfully.\n";
            return;
        }
    }
    cout << "Train " << trainName << " not found.\n";
 }
   void trackTrainLocationAndSpeed(const string &trainName)
   {
    bool trainFound = false;

    for (const auto &train : trains)
        {
        if (train.name == trainName)
        {
            trainFound = true;
            cout << "Tracking train: " << trainName << ".\n";
            cout << "Current Location: " << "Approaching Andheri\n"; // Placeholder
            cout << "Current Speed: " << "80 km/h\n";               // Placeholder
            cout << "Next Station: " << "Borivali\n";               // Placeholder
            break;
        }
    }

    if (!trainFound)
    {
        cout << "Train " << trainName << " not found.\n";
    }
}

 void bookAdvancedVIPLounge(const string &station, const string &loungeType, int hours, int numPeople)
 {
    double ratePerHour = (loungeType == "Premium") ? 100 : 50;
    double totalCost = ratePerHour * hours * numPeople;

    cout << "VIP lounge (" << loungeType << ") at " << station
         << " booked for " << hours << " hours for " << numPeople
         << " people. Total cost: Rs. " << totalCost << ".\n";
 }

 void notifyTrainArrivalWithETA(const string &trainName, const string &station, int etaMinutes)
 {
    bool trainFound = false;

    for (const auto &train : trains)
    {
        if (train.name == trainName && find(train.route.begin(), train.route.end(), station) != train.route.end())
        {
            trainFound = true;
            cout << "Notification: Train " << trainName << " is approaching " << station
                 << ". ETA: " << etaMinutes << " minutes.\n";
            break;
        }
    }

    if (!trainFound)
    {
        cout << "No such train or station found.\n";
    }
 }

 void calculateRouteDistance(const string &trainName)
 {
    bool trainFound = false;

    for (const auto &train : trains)
        {
        if (train.name == trainName)
        {
            trainFound = true;
            int totalDistance = 0;
            cout << "Calculating total distance for train: " << trainName << "\n";
            cout << "Route Details:\n";

            for (size_t i = 0; i < train.route.size() - 1; ++i)
                {
                const string &currentStation = train.route[i];
                const string &nextStation = train.route[i + 1];

                if (stations[currentStation]->connections.find(nextStation) != stations[currentStation]->connections.end())
                {
                    int distance = stations[currentStation]->connections.at(nextStation);
                    totalDistance += distance;
                    cout << "From " << currentStation << " to " << nextStation << ": " << distance << " km\n";
                }
                else
                {
                    cout << "Warning: No direct connection between " << currentStation << " and " << nextStation << "!\n";
                }
            }

            cout << "Total distance for train " << trainName << ": " << totalDistance << " km.\n";
            cout << "-----------------------------------\n";
            return;
        }
    }

    if (!trainFound)
    {
        cout << "Train " << trainName << " not found.\n";
    }
}
   void adjustDynamicFare(const string &trainName, double multiplier)
   {
    if (multiplier <= 0)
    {
        cout << "Error: Multiplier must be greater than 0.\n";
        return;
    }

    for (auto &train : trains)
        {
        if (train.name == trainName)
        {
            cout << "Adjusting fares for train: " << trainName << " (Multiplier: " << multiplier << ")\n";

            cout << "Reservation Status Before Adjustment:\n";
            for (const auto &res : train.reservations)
            {
                cout << "Station: " << res.first << ", Seats Reserved: " << res.second << "\n";
            }

            // Apply fare multiplier
            for (auto &res : train.reservations)
            {
                res.second = static_cast<int>(res.second * multiplier);
            }

            cout << "Reservation Status After Adjustment:\n";
            for (const auto &res : train.reservations)
            {
                cout << "Station: " << res.first << ", Adjusted Reserved Seats: " << res.second << "\n";
            }
            cout << "Fares adjusted successfully.\n";
            return;
        }
    }

    cout << "Train " << trainName << " not found.\n";
}
  void searchTrainByStation(const string &station)
  {
    cout << "Searching for trains passing through: " << station << "\n";
    bool trainsFound = false;

    for (const auto &train : trains)
        {
        if (find(train.route.begin(), train.route.end(), station) != train.route.end())
        {
            trainsFound = true;
            cout << "Train: " << train.name << " (" << train.trainClass << ")\n";
            cout << "Stops:\n";

            for (size_t i = 0; i < train.route.size(); ++i)
                {
                cout << train.route[i];
                if (train.route[i] == station)
                {
                    cout << " (You are here)";
                }
                if (i != train.route.size() - 1)
                {
                    cout << " -> ";
                }
            }
            cout << "\n-----------------------------------\n";
        }
    }

    if (!trainsFound)
    {
        cout << "No trains pass through the station " << station << ".\n";
    }
}

 void displayFeedbackStatistics()
 {
    unordered_map<string, pair<int, int>> feedbackSummary; // trainName -> (totalRating, count)
    string bestTrain, worstTrain;
    double bestRating = 0, worstRating = 5;

    for (const auto &feedback : feedbacks)
    {
        feedbackSummary[feedback.trainName].first += feedback.rating;
        feedbackSummary[feedback.trainName].second++;
    }

    cout << "Feedback Statistics:\n";
    for (const auto &entry : feedbackSummary)
        {
        double avgRating = static_cast<double>(entry.second.first) / entry.second.second;
        cout << "Train: " << entry.first << ", Average Rating: " << avgRating
             << " (" << entry.second.second << " feedbacks)\n";

        // Track best and worst trains
        if (avgRating > bestRating)
        {
            bestRating = avgRating;
            bestTrain = entry.first;
        }
        if (avgRating < worstRating)
        {
            worstRating = avgRating;
            worstTrain = entry.first;
        }
    }

    cout << "\nBest-rated Train: " << bestTrain << " (Rating: " << bestRating << ")\n";
    cout << "Worst-rated Train: " << worstTrain << " (Rating: " << worstRating << ")\n";
    cout << "-----------------------------------\n";
}

  void displayTrainStopDurations(const string &trainName)
  {
    bool trainFound = false;

    for (const auto &train : trains)
        {
        if (train.name == trainName)
        {
            trainFound = true;
            int totalStopTime = 0;
            cout << "Stop durations for train " << trainName << ":\n";

            for (const auto &station : train.route)
            {
                int stopDuration = 5 + rand() % 6; // Random stop duration (5-10 minutes)
                cout << "Station: " << station << ", Stop Duration: " << stopDuration << " minutes\n";
                totalStopTime += stopDuration;
            }

            cout << "Total stop time for train " << trainName << ": " << totalStopTime << " minutes.\n";
            cout << "-----------------------------------\n";
            return;
        }
    }

    if (!trainFound)
    {
        cout << "Train " << trainName << " not found.\n";
    }
}

 void predictTrainArrival(const string &trainName, const string &station)
 {
    for (const auto &train : trains)
        {
        if (train.name == trainName)
        {
            int accumulatedDelay = 0;
            bool stationFound = false;

            cout << "Predicting arrival time for train " << trainName << " at station " << station << ":\n";
            for (const auto &stop : train.route)
                {
                accumulatedDelay += rand() % 5; // Simulate random delays
                if (stop == station)
                {
                    stationFound = true;
                    cout << "Predicted arrival time at " << station << ": +" << accumulatedDelay << " minutes delay.\n";
                    break;
                }
            }

            if (!stationFound)
            {
                cout << "Station " << station << " is not part of train " << trainName << "'s route.\n";
            }
            return;
        }
    }

    cout << "Train " << trainName << " not found.\n";
}

 void generateTrainTicket(const string &trainName, const string &passengerName, const string &startStation, const string &endStation)
 {
    for (const auto &train : trains)
        {
        if (train.name == trainName)
        {
            cout << "\n----------- TRAIN TICKET -----------\n";
            cout << "Passenger Name: " << passengerName << "\n";
            cout << "Train: " << trainName << " (" << train.trainClass << ")\n";
            cout << "From: " << startStation << "\n";
            cout << "To: " << endStation << "\n";
            cout << "Seat: Reserved\n";
            cout << "------------------------------------\n";
            return;
        }
    }

    cout << "Train " << trainName << " not found.\n";
}

 void viewActiveTrains()
 {
    cout << "Active Trains:\n";
    for (const auto &train : trains)
        {
        cout << "Train: " << train.name << " (" << train.trainClass << ")\n";
        cout << "Current Route: ";
        for (const auto &station : train.route)
        {
            cout << station << " ";
        }
        cout << "\n------------------------------------\n";
    }
}
 void addNewStation(const string &stationName)
 {
    if (stations.find(stationName) == stations.end())
    {
        stations[stationName] = new Station(stationName);
        overcrowdedStations[stationName] = false;
        cout << "Station " << stationName << " added successfully.\n";
    }
    else
    {
        cout << "Station " << stationName << " already exists.\n";
    }
}

 void removeStation(const string &stationName)
 {
    if (stations.find(stationName) != stations.end())
        {
        delete stations[stationName];
        stations.erase(stationName);
        overcrowdedStations.erase(stationName);

        // Update all train routes
        for (auto &train : trains)
        {
            train.route.erase(remove(train.route.begin(), train.route.end(), stationName), train.route.end());
        }

        cout << "Station " << stationName << " removed successfully.\n";
    }
    else
    {
        cout << "Station " << stationName << " does not exist.\n";
    }
}

 void calculateTrainRevenue(const string &trainName)
 {
    double farePerSeat = 50; // Example fare
    for (const auto &train : trains)
        {
        if (train.name == trainName)
        {
            int totalSeatsReserved = 0;
            for (const auto &res : train.reservations)
            {
                totalSeatsReserved += res.second;
            }
            double revenue = totalSeatsReserved * farePerSeat;
            cout << "Total revenue for train " << trainName << ": Rs. " << revenue << "\n";
            return;
        }
    }
    cout << "Train " << trainName << " not found.\n";
}


    void generatePlatformTicket()
    {
        // Get current time
        std::time_t now = std::time(nullptr);      // Get current time as time_t
        std::tm *localTime = std::localtime(&now); // Convert to local time (std::tm)

        // Manually construct the date and time string
        std::string date = std::to_string(localTime->tm_year + 1900) + "-" +
                           std::to_string(localTime->tm_mon + 1) + "-" +
                           std::to_string(localTime->tm_mday);

        std::string time = (localTime->tm_hour < 10 ? "0" : "") + std::to_string(localTime->tm_hour) + ":" +
                           (localTime->tm_min < 10 ? "0" : "") + std::to_string(localTime->tm_min) + ":" +
                           (localTime->tm_sec < 10 ? "0" : "") + std::to_string(localTime->tm_sec);

        // Fare (example)
        double fare = 10.50; // Replace with actual fare logic if needed

        // Display ticket details
        std::cout << "----------- PLATFORM TICKET -----------" << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << "Time: " << time << std::endl;
        std::cout << "Fare: $" << fare << std::endl;
        std::cout << "---------------------------------------" << std::endl;
    }

    void bookDormitory()
    {
        // Get current time
        std::time_t now = std::time(nullptr);      // Get current time as time_t
        std::tm *localTime = std::localtime(&now); // Convert to local time (std::tm)

        // Manually construct the date and time string
        std::string date = std::to_string(localTime->tm_year + 1900) + "-" +
                           std::to_string(localTime->tm_mon + 1) + "-" +
                           std::to_string(localTime->tm_mday);

        std::string time = (localTime->tm_hour < 10 ? "0" : "") + std::to_string(localTime->tm_hour) + ":" +
                           (localTime->tm_min < 10 ? "0" : "") + std::to_string(localTime->tm_min) + ":" +
                           (localTime->tm_sec < 10 ? "0" : "") + std::to_string(localTime->tm_sec);

        // Booking details
        int ticketNumber;
        double pricePerDay;
        int noOfDays;
        bool isAC;

        std::cout << "Enter Ticket Number: ";
        std::cin >> ticketNumber;

        std::cout << "Enter Price Per Day: ";
        std::cin >> pricePerDay;

        std::cout << "Enter Number of Days to Book: ";
        std::cin >> noOfDays;

        std::cout << "Enter 1 for AC, 0 for Non-AC: ";
        std::cin >> isAC;

        // Calculate total price
        double totalPrice = pricePerDay * noOfDays;

        // Display booking confirmation
        std::cout << "\n----------- DORMITORY BOOKING DETAILS -----------" << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << "Time: " << time << std::endl;
        std::cout << "Ticket Number: " << ticketNumber << std::endl;
        std::cout << "Number of Days Booked: " << noOfDays << std::endl;
        std::cout << "Room Type: " << (isAC ? "AC" : "Non-AC") << std::endl;
        std::cout << "Total Price: $" << totalPrice << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
        }

        void markOvercrowded(const string &station)
        {
        overcrowdedStations[station] = true;
        }

        void unmarkOvercrowded(const string &station)
        {
        overcrowdedStations[station] = false;
        }

        void findRoute(const string &start, const string &end)
        {
        if (overcrowdedStations[start] || overcrowdedStations[end])
        {
            cout << "Either the start or end station is overcrowded. Please try alternative routes or modes of transport.\n";
            suggestAlternatives();
            return;
        }

        // Find the shortest path using Dijkstra's algorithm
        vector<string> path = findShortestPath(start, end);
        cout << "Shortest route from " << start << " to " << end << ":\n";
        for (const auto &station : path)
        {
            cout << station << (station == end ? "\n" : " -> ");
        }
        }

        void findNearestStation(const string &current)
        {
        int minDistance = numeric_limits<int>::max();
        string nearestStation;
        for (auto &conn : stations[current]->connections)
        {
            // Find the nearest station that is not overcrowded
            if (conn.second < minDistance && !overcrowdedStations[conn.first])
            {
            minDistance = conn.second;
            nearestStation = conn.first;
            }
        }
        cout << "Nearest station to " << current << " is " << nearestStation << " at a distance of " << minDistance << " km.\n";
        }

        void calculateFare(const string &start, const string &end)
        {
        // Find the shortest path to calculate the total distance
        vector<string> path = findShortestPath(start, end);
        int totalDistance = 0;
        for (size_t i = 0; i < path.size() - 1; ++i)
        {
            totalDistance += stations[path[i]]->connections[path[i + 1]];
        }

        // Calculate fare based on train class and route
        double farePerKm = 2.0; // Default fare per km
        for (const auto &train : trains)
        {
            if (find(train.route.begin(), train.route.end(), start) != train.route.end() &&
            find(train.route.begin(), train.route.end(), end) != train.route.end())
            {
            if (train.trainClass == "AC")
            {
            farePerKm = 3.0;
            }
            else if (train.trainClass == "Sleeper")
            {
            farePerKm = 2.5;
            }
            else if (train.trainClass == "Local")
            {
            farePerKm = 1.5;
            }
            break;
            }
        }

        double totalFare = totalDistance * farePerKm;
        cout << "Total fare from " << start << " to " << end << " is Rs. " << totalFare << " (" << farePerKm << " Rs. per km).\n";
        }

        void suggestAlternatives()
        {
        // Suggest alternative modes of transport
        cout << "Alternative modes of transport: \n";
        cout << "1. Auto-rickshaws\n2. Taxis\n3. Bus services\n4. Metro (if available)\n5. Rental bikes or scooters\n";
        }
        void displayReservations()
        {
        // Display reservations for all trains
        for (auto &train : trains)
        {
            train.displayReservations();
        }
        }

        void displayBookings()
        {
        cout << "Booking Log:\n";
        for (const auto &booking : bookingLog)
        {
            cout << "Train: " << booking.first << ", Station: " << booking.second << "\n";
        }
    }

    ~TransportSystem()
    {
        for (auto &station : stations)
        {
            delete station.second;
        }
    }
        // Function to collect feedback from users
    void collectFeedback()
    {
        std::string trainName;
        int rating;
        std::string comments;
        std::string userName;

        // Ask for the user's name
        std::cout << "Enter your name: ";
        std::cin.ignore(); // To clear the newline character from the input buffer
        std::getline(std::cin, userName);

        // Ask for the train name
        std::cout << "Enter the name of the train you traveled on: ";
        std::getline(std::cin, trainName);

        // Ask for the rating
        std::cout << "Rate your experience on a scale of 1 to 5: ";
        std::cin >> rating;

        while (rating < 1 || rating > 5)
        {
            std::cout << "Invalid rating. Please enter a rating between 1 and 5: ";
            std::cin >> rating;
        }

        // Ask for additional comments
        std::cout << "Please provide any additional comments or feedback: ";
        std::cin.ignore(); // To clear the newline character from the input buffer
        std::getline(std::cin, comments);

        // Store the feedback
        feedbacks.push_back({userName, trainName, rating, comments});

        std::cout << "Thank you for your feedback!\n";
    }

    // Function to display all feedback
    void displayFeedback()
    {
        std::cout << "\nFeedback Summary:\n";
        for (const auto& feedback : feedbacks)
        {
            std::cout << "User: " << feedback.userName << "\n";
            std::cout << "Train: " << feedback.trainName << "\n";
            std::cout << "Rating: " << feedback.rating << "\n";
            std::cout << "Comments: " << feedback.comments << "\n";
            std::cout << "-----------------------------------\n";
        }
    }

};


// Function to display a greeting message to the user
void displayGreeting()
{
    cout << "\n===========================================\n";
    cout << "Welcome to the Mumbai Transport System!\n";
    cout << "===========================================\n\n";
}

// Function to display a farewell message to the user
void displayFarewell()
{
    cout << "\n===========================================\n";
    cout << "Thank you for using the Mumbai Transport System.\nHave a great day!\n";
    cout << "===========================================\n\n";
}

// Function to display guidelines for railway travel
void displayGuidelines()
{
    vector<string> guidelines =
    {
        "Plan Ahead:",
        "1. Book tickets in advance, especially during peak seasons.",
        "2. Check train schedules and routes carefully.",
        "3. Consider travel time and make allowances for potential delays.",
        "",
        "At the Station:",
        "1. Arrive at the station with ample time to board your train.",
        "2. Keep your ticket and identification readily available for inspection.",
        "3. Be mindful of your belongings and surroundings.",
        "4. Use designated waiting areas and follow station rules.",
        "",
        "On the Train:",
        "1. Find your assigned seat and ensure it's clean and comfortable.",
        "2. Keep your luggage secure and out of the aisle.",
        "3. Be considerate of other passengers by keeping noise levels down.",
        "4. Avoid littering and dispose of waste properly.",
        "",
        "During Travel:",
        "1. Stay hydrated and eat light snacks.",
        "2. Take breaks to stretch and walk around.",
        "3. Enjoy the scenery and relax.",
        "4. Be aware of your surroundings and report any suspicious activity.",
        "",
        "At Your Destination:",
        "1. Collect your luggage promptly upon arrival.",
        "2. Follow exit signs and navigate the station safely.",
        "3. Use local transportation or pre-arranged pick-up services.",
        "",
        "Important Notes:",
        "1. Always follow safety instructions from railway staff.",
        "2. Keep valuable items close to you and avoid displaying them openly.",
        "3. Be cautious of strangers and avoid engaging in conversations with them unnecessarily.",
        "4. If you experience any problems, contact railway authorities or local police."};

    cout << "Railway Travel Guidelines:\n\n";
    for (const string &line : guidelines)
    {
        cout << line << endl;
    }
}

// Function to display emergency contact numbers
void displayEmergencyContacts()
{
    vector<pair<string, string>> emergencyContacts =
    {
        {"Railway Helpline", "139"},
        {"Police Emergency", "112"},
        {"Ambulance", "102"},
        {"Fire Service", "101"},
        {"Women�s Helpline", "1091"},
        {"Child Helpline", "1098"},
        {"Senior Citizen Helpline", "14567"},
        {"Anti-Trafficking Helpline", "155260"},
        {"Disaster Management Helpline", "108"},
        {"Railway Vigilance", "155210"},
        {"Lost and Found (Railways)", "182"}};

    cout << "Emergency Numbers and Contacts:\n\n";
    for (const auto &contact : emergencyContacts)
    {
        cout << contact.first << ": " << contact.second << endl;
    }
}

void adminMenu(TransportSystem &system)
{
    int choice;
    string stationName, fromStation, toStation, trainName, trainClass;
    vector<string> route;
    int distance, capacity;
    string inputStation;

    do
    {
        cout<<"welcome\n";
        cout << "\n===========================================\n";
        cout << "Admin Menu\n";
        cout << "===========================================\n";
        cout << "1. Add new station\n";
        cout << "2. Add new connection\n";
        cout << "3. Add new train\n";
        cout << "4. Return to main menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the name of the new station: ";
            cin >> stationName;
            system.addStation(stationName);
            cout << "Station " << stationName << " added successfully.\n";
            break;
        case 2:
            cout << "Enter the starting station: ";
            cin >> fromStation;
            cout << "Enter the destination station: ";
            cin >> toStation;
            cout << "Enter the distance between the stations: ";
            cin >> distance;
            system.addConnection(fromStation, toStation, distance);
            cout << "Connection added successfully between " << fromStation << " and " << toStation << ".\n";
            break;
        case 3:
            cout << "Enter the name of the train: ";
            cin >> trainName;
            cout << "Enter the train class (e.g., Sleeper, AC, Local): ";
            cin >> trainClass;
            cout << "Enter the capacity of the train: ";
            cin >> capacity;
            cout << "Enter the route of the train (type 'done' to finish): ";
            route.clear();
            while (true)
            {
                cin >> inputStation;
                if (inputStation == "done")
                    break;
                route.push_back(inputStation);
            }
            system.addTrain(trainName, route, capacity, trainClass);
            cout << "Train " << trainName << " added successfully.\n";
            break;
        case 4:
            cout << "Returning to main menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}



// Function to display the main menu and handle user operations
void menu(TransportSystem &system)
{
{
    int choice;
    string start, end, station, trainName, trainClass;

    do
    {
        cout << "\nMumbai Transport System\n";
        cout << "\n===========================================\n";
        cout << "Mumbai Transport System - Main Menu\n";
        cout << "===========================================\n";
        cout << "1. Find shortest route\n";
        cout << "2. Find nearest station\n";
        cout << "3. Calculate fare\n";
        cout << "4. Mark station as overcrowded\n";
        cout << "5. Unmark station as overcrowded\n";
        cout << "6. Suggest alternative transport\n";
        cout << "7. Display trains and routes\n";
        cout << "8. Reserve train seat\n";
        cout << "9. Generate platform ticket\n";
        cout << "10. Book dormitory\n";
        cout << "11. Request new train\n";
        cout << "12. Exit\n";
        cout << "13.Guidlines of the Railway\n";
        cout << "14.Emergency contacts\n";
        cout << "15.Admin menu\n";
        cout << "16. Collect and display feedback\n";
        cout << "17. update Train Schedule\n";
        cout << "18. track Train Location And Spee\n";
        cout << "19. book Advanced VIP Lounge\n";
        cout << "20. notify Train Arrival With ETA\n";
        cout << "21. calculate Route Distance\n";
        cout << "22. adjust Dynamic Fare\n";
        cout << "23. search Train By Station\n";
        cout << "24. display Feedback Statistics\n";
        cout << "25. display Train Stop Durations\n";
        cout << "26. predict Train  Arrival\n";
        cout << "27. generate Train Ticket\n";
        cout << "28. view Active Trains\n";
        cout << "29. add New Station\n";
        cout << "30. remove Station\n";
        cout << "31. calculate Train Revenue\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter starting station: ";
            cin >> start;
            cout << "Enter destination station: ";
            cin >> end;
            system.findRoute(start, end);
            break;
        case 2:
            cout << "Enter current station: ";
            cin >> station;
            system.findNearestStation(station);
            break;
        case 3:
            cout << "Enter starting station: ";
            cin >> start;
            cout << "Enter destination station: ";
            cin >> end;
            system.calculateFare(start, end);
            break;
        case 4:
            cout << "Enter station to mark as overcrowded: ";
            cin >> station;
            system.markOvercrowded(station);
            break;
        case 5:
            cout << "Enter station to unmark as overcrowded: ";
            cin >> station;
            system.unmarkOvercrowded(station);
            break;
        case 6:
            system.suggestAlternatives();
            break;
        case 7:
            system.displayTrains();
            break;
        case 8:
            cout << "Enter train name: ";
            cin >> trainName;
            cout << "Enter station: ";
            cin >> station;
            system.reserveTrainSeat(trainName, station);
            break;
        case 9:
            system.generatePlatformTicket();
            break;
        case 10:
            system.bookDormitory();
            break;
        case 11:
            cout << "Enter starting station: ";
            cin >> start;
            cout << "Enter destination station: ";
            cin >> end;
            cout << "Enter train class (e.g., Sleeper, AC, Local): ";
            cin >> trainClass;
            system.requestTrain(start, end, trainClass);
            break;
        case 12:
            cout << "Exiting system. Thank you!\n";
            displayFarewell();
            break;
        case 13:
            displayGuidelines();
            break;
        case 14:
            displayEmergencyContacts();
            break;
        case 15:
            adminMenu(system);
        case 16:
            system.collectFeedback();
            system.displayFeedback();
            break;
        case 17:
           {
            string trainName;
            int numStations; // Declare numStations here to avoid errors

            cout << "Enter train name to update schedule: ";
            cin >> trainName;

            cout << "Enter number of stations to update: ";
            cin >> numStations;

            vector<pair<string, int>> stationDelays;
            for (int i = 0; i < numStations; ++i) {
                string station;
                int delay;
                cout << "Enter station name and delay in minutes: ";
                cin >> station >> delay;
                stationDelays.push_back({station, delay});
            }

            system.updateTrainSchedule(trainName, stationDelays);
        }
            break;
        case 18:
            {
                string trainName;

                cout << "Enter train name to track: ";
                cin >> trainName;

                system.trackTrainLocationAndSpeed(trainName);
            }
            break;
        case 19:
            {
                string station, loungeType;
                int hours, numPeople;

                cout << "Enter station: ";
                cin >> station;
                cout << "Enter lounge type (Standard/Premium): ";
                cin >> loungeType;
                cout << "Enter number of hours: ";
                cin >> hours;
                cout << "Enter number of people: ";
                cin >> numPeople;

                system.bookAdvancedVIPLounge(station, loungeType, hours, numPeople);
            }
            break;
        case 20:
            {
                string trainName, station;
                int etaMinutes;

                cout << "Enter train name: ";
                cin >> trainName;
                cout << "Enter station name: ";
                cin >> station;
                cout << "Enter ETA in minutes: ";
                cin >> etaMinutes;

                system.notifyTrainArrivalWithETA(trainName, station, etaMinutes);
            }
            break;
        case 21:
            {
                string trainName;
                cout << "Enter train name: ";
                cin >> trainName;
                system.calculateRouteDistance(trainName);
            }
            break;
        case 22:
            {
                string trainName;
                double multiplier;
                cout << "Enter train name: ";
                cin >> trainName;
                cout << "Enter fare multiplier (e.g., 1.2 for 20% increase): ";
                cin >> multiplier;
                system.adjustDynamicFare(trainName, multiplier);
            }
            break;
        case 23:
            {
                string station;
                cout << "Enter station name: ";
                cin >> station;
                system.searchTrainByStation(station);
            }
            break;
        case 24:
            system.displayFeedbackStatistics();
            break;
        case 25:
            {
                string trainName;
                cout << "Enter train name: ";
                cin >> trainName;
                system.displayTrainStopDurations(trainName);
            }
            break;
        case 26:
            {
                string trainName, station;
                cout << "Enter train name: ";
                cin >> trainName;
                cout << "Enter station name: ";
                cin >> station;
                system.predictTrainArrival(trainName, station);
            }
            break;
        case 27:
            {
                string trainName, passengerName, startStation, endStation;
                cout << "Enter train name: ";
                cin >> trainName;
                cout << "Enter passenger name: ";
                cin >> passengerName;
                cout << "Enter starting station: ";
                cin >> startStation;
                cout << "Enter destination station: ";
                cin >> endStation;
                system.generateTrainTicket(trainName, passengerName, startStation, endStation);
            }
            break;
        case 28:
            system.viewActiveTrains();
            break;
        case 29:
            {
                string stationName;
                cout << "Enter new station name: ";
                cin >> stationName;
                system.addNewStation(stationName);
            }
            break;
        case 30:
            {
                string stationName;
                cout << "Enter station name to remove: ";
                cin >> stationName;
                system.removeStation(stationName);
            }
            break;
        case 31:
            {
                string trainName;
                cout << "Enter train name: ";
                cin >> trainName;
                system.calculateTrainRevenue(trainName);
            }
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 16);
}
}



// Main program to interact with the user
int main()
{
    BedAvailabilityTracker bedTracker;
    TreatmentSystem treatmentSystem;
    AppointmentScheduler appointmentScheduler;
    Graph cityGraph(20);
    HealthcareSystem healthcareSystem;
    HealthInformationTrie trie;
    initializeDatabase(trie);
    TreatmentCostCalculator calculator;
    EmergencyTriageSystem triageSystem;
    BloodOrganDonationTracker donationTracker;
    EquipmentInventorySystem equipmentSystem;


    // Add some equipment
    equipmentSystem.addEquipment("X-ray Machine", true, 5);  // Available
    equipmentSystem.addEquipment("MRI Machine", true, 8);  // Available
    equipmentSystem.addEquipment("Ventilator", false, 10);  // Not available
    equipmentSystem.addEquipment("Ultrasound", true, 4);  // Available
    equipmentSystem.addEquipment("ECG Machine", true, 6);  // Available
    equipmentSystem.addEquipment("CT Scanner", true, 9);  // Available
    equipmentSystem.addEquipment("Defibrillator", true, 3);  // Available
    equipmentSystem.addEquipment("Blood Pressure Monitor", true, 2);  // Available
    equipmentSystem.addEquipment("Anesthesia Machine", true, 7);  // Available
    equipmentSystem.addEquipment("Oxygen Concentrator", false, 6);  // Not available
    equipmentSystem.addEquipment("Infusion Pump", true, 4);  // Available
    equipmentSystem.addEquipment("Surgical Robot", true, 10);  // Available
    equipmentSystem.addEquipment("Patient Monitoring System", true, 5);  // Available

    // Initialize healthcare data
    healthcareSystem.initializeData(cityGraph);
    vector<EmergencyContact> contacts =
    {
        {"Mumbai Police", "100", "Police", 18.9750, 72.8258, 0.0},
        {"Mumbai Fire Brigade", "101", "Fire", 18.9893, 72.8204, 0.0},
        {"Mumbai Ambulance", "102", "Ambulance", 18.9476, 72.8243, 0.0},
        {"BMC Disaster Control", "1916", "Disaster Control", 18.9777, 72.8230, 0.0},
        {"Mumbai Hospital", "108", "Hospital", 18.9765, 72.8240, 0.0}
    };

    vector<Activity> activities;
    initializeActivities(activities); // Initialize with default activities
    vector<Tip> tips =
    {
        {"Transportation: Use Public Transit", "Save money and reduce stress by using local public transportation systems.", {"public transit", "transportation", "money saving"}},
        {"Accommodation: Book in Advance", "Secure better deals and avoid last-minute hassles by booking accommodations early.", {"accommodation", "booking", "advance"}},
        {"Budgeting: Set a Daily Limit", "Keep your spending in check by setting a daily budget for your trip.", {"budgeting", "daily limit", "spending"}},
        {"Time Management: Create an Itinerary", "Plan your days in advance to make the most of your time.", {"itinerary", "time management", "planning"}},
        {"Safety: Keep Copies of Important Documents", "Make copies of your passport and other important documents in case of loss.", {"safety", "documents", "copies"}},
        {"Food: Try Local Cuisine", "Experience the culture by trying local dishes and specialties.", {"food", "local cuisine", "dining"}},
        {"Packing: Pack Light", "Bring only what you need to make traveling easier.", {"packing", "light packing", "travel tips"}},
        {"Culture: Learn Basic Local Phrases", "Enhance your experience by learning a few phrases in the local language.", {"culture", "language", "phrases"}},
    };

    vector<Tourist> tourists =
    {
        {1, "Alice", "Colaba", 5000},
        {2, "Bob", "Bandra", 4000},
        {3, "Charlie", "Andheri", 3000},
        {4, "David", "Powai", 6000},
        {5, "Eve", "Juhu", 7000},
        {6, "Frank", "Marine Drive", 8000},
        {7, "Grace", "Dadar", 3500},
        {8, "Heidi", "Lower Parel", 4500},
        {9, "Ivan", "Versova", 3000},
        {10, "Judy", "Malad", 5500},
    };

    vector<Room> rooms =
    {
        {101, "Colaba", 2, 5000},
        {102, "Bandra", 3, 4000},
        {103, "Andheri", 2, 3000},
        {104, "Powai", 4, 6000},
        {105, "Juhu", 3, 7000},
        {106, "Marine Drive", 2, 8000},
        {107, "Dadar", 3, 3500},
        {108, "Lower Parel", 2, 4500},
        {109, "Versova", 2, 3000},
        {110, "Malad", 4, 5500},
    };
    // Predefined tourist problems
    vector<Problem> touristProblems =
    {
        {"Transport Delay", "Flight delayed by 4 hours due to weather conditions.", ""},
        {"Accommodation Issue", "Hotel room was not clean upon arrival.", ""},
        {"Safety Concern", "Pickpocketing reported near tourist attraction.", ""},
        {"Lost Luggage", "Tourist lost their luggage during transit.", ""},
        {"Language Barrier", "Difficulty in communicating with locals.", ""},
        {"Traffic Jam", "Severe traffic congestion during peak hours.", ""},
        {"Public Transport Strike", "Local transport services halted due to strike.", ""},
        {"Overcrowded Attractions", "Popular tourist spots are overcrowded.", ""},
        {"High Prices", "Prices of food and services are too high.", ""},
        {"Cultural Misunderstanding", "Miscommunication due to cultural differences.", ""}
    };

    // Predefined shelter-related problems and solutions

    vector<Problem> shelterProblems =
    {
        {"Availability Issue", "No shelters available during peak tourist season.",
         "Plan and book shelters in advance to avoid availability issues."},
        {"Cleanliness Problem", "Shelters are not maintained properly.",
         "Choose shelters with good reviews and ratings for cleanliness."},
        {"Safety Concern", "Shelter located in unsafe or poorly lit areas.",
         "Research and select shelters in safer neighborhoods."},
        {"Cost Issue", "Shelters are too expensive for tourists on a budget.",
         "Look for budget-friendly accommodations or use price comparison platforms."},
        {"Overcrowding", "Shelters are overcrowded during holidays.",
         "Visit during off-peak seasons to avoid overcrowding."},
        {"Noise Pollution", "Shelters are located near noisy areas.",
         "Choose shelters in quieter neighborhoods."},
        {"Lack of Amenities", "Shelters lack basic amenities like Wi-Fi.",
         "Check for amenities before booking."},
        {"Unfriendly Staff", "Staff at shelters are unhelpful.",
         "Read reviews to find friendly accommodations."},
        {"Transportation Access", "Difficult to access public transport from shelters.",
         "Choose shelters near public transport hubs."},
        {"Limited Food Options", "Few food options available near shelters.",
         "Research nearby restaurants before booking."}
    };

    vector<CleanlinessShelter> cleanlinessShelters;
    vector<CleanlinessTourist> cleanlinessTourists;
    vector<vector<int>> cleanlinessDistances;

    vector<DistanceShelter> distanceShelters;
    vector<DistanceTourist> distanceTourists;
    vector<vector<int>> distanceDistances;

    // Predefined shelters and tourists
    cleanlinessShelters.push_back(CleanlinessShelter(1, 10, 1, true, 8, "Hotel residency park,mumbai"));
    cleanlinessShelters.push_back(CleanlinessShelter(2, 5, 2, true, 9, "Sahara star"));
    distanceShelters.push_back(DistanceShelter(1, 15, "Hotel grand Heritage"));
    distanceShelters.push_back(DistanceShelter(2, 10, "FabHotel Admiral"));

    cleanlinessTourists.push_back(CleanlinessTourist(1, "Alice", 5, true, 1));
    cleanlinessTourists.push_back(CleanlinessTourist(2, "Bob", 3, false, -1));
    distanceTourists.push_back(DistanceTourist(1, "Charlie"));
    distanceTourists.push_back(DistanceTourist(2, "Diana"));


    //sushil
   TransportSystem system;

    // Adding stations based on the map (example subset)
    system.addStation("Mumbai_CST");
    system.addStation("Dadar");
    system.addStation("Thane");
    system.addStation("Kurla");
    system.addStation("Andheri");
    system.addStation("Borivali");
    system.addStation("Virar");
    system.addStation("Panvel");
    system.addStation("Vashi");
    system.addStation("Kalyan");
    system.addStation("Vasai_Road");
    system.addStation("Churchgate");
    system.addStation("Goregaon");
    system.addStation("Mira_Road");
    system.addStation("Bhayander");
    system.addStation("Badlapur");
    system.addStation("Titwala");
    system.addStation("Kasara");
    system.addStation("Karjat");
    system.addStation("Khopoli");
    system.addStation("Roha");
    system.addStation("Nagothane");
    system.addStation("Kasu");
    system.addStation("Pen");
    system.addStation("Hamrapur");
    system.addStation("Apta");
    system.addStation("Rasayani");
    system.addStation("Palasari");
    system.addStation("Kelavali");
    system.addStation("Lowjee");
    system.addStation("Dolavli");
    system.addStation("Shelu");
    system.addStation("Vangani");
    system.addStation("Neral");
    system.addStation("Vasind");
    system.addStation("Atgaon");
    system.addStation("Shahad");
    system.addStation("Ambivli");
    system.addStation("Ulhasnagar");
    system.addStation("Vithalwadi");
    system.addStation("Ambernath");
    system.addStation("Khandeshwar");
    system.addStation("Kharghar");
    system.addStation("Belapur");
    system.addStation("Seawood");
    system.addStation("Sanpada");
    system.addStation("Tilak_Nagar");
    system.addStation("Chembur");
    system.addStation("Govandi");
    system.addStation("Ghatkopar");
    system.addStation("Vikhroli");
    system.addStation("Bhandup");
    system.addStation("Mulund");
    system.addStation("Nahur");
    system.addStation("Kalwa");
    system.addStation("Mumbra");
    system.addStation("Diva");
    system.addStation("Lower_Parel");
    system.addStation("Mahalaxmi");
    system.addStation("Sandhurst_Road");
    system.addStation("Reay_Road");
    system.addStation("Sewri");
    system.addStation("GTB_Nagar");
    system.addStation("Chunabhatti");
    system.addStation("Wadala");
    system.addStation("Matunga_Road");
    system.addStation("Santacruz");
    system.addStation("Vile_Parle");
    system.addStation("Jogeshwari");
    system.addStation("Malad");
    system.addStation("Kandivali");
    system.addStation("Dahisar");

    // Adding connections
    system.addConnection("Mumbai_CST", "Dadar", 10);
    system.addConnection("Dadar", "Thane", 15);
    system.addConnection("Dadar", "Kurla", 5);
    system.addConnection("Kurla", "Thane", 8);
    system.addConnection("Dadar", "Andheri", 12);
    system.addConnection("Andheri", "Borivali", 10);
    system.addConnection("Borivali", "Virar", 20);
    system.addConnection("Thane", "Kalyan", 15);
    system.addConnection("Thane", "Vashi", 12);
    system.addConnection("Vashi", "Panvel", 10);
    system.addConnection("Virar", "Vasai_Road", 5);
    system.addConnection("Churchgate", "Dadar", 12);
    system.addConnection("Goregaon", "Andheri", 5);
    system.addConnection("Bhayander", "Mira_Road", 7);
    system.addConnection("Kalyan", "Badlapur", 10);
    system.addConnection("Badlapur", "Titwala", 8);
    system.addConnection("Thane", "Titwala", 12);
    system.addConnection("Kalyan", "Kasara", 20);
    system.addConnection("Kalyan", "Karjat", 25);
    system.addConnection("Karjat", "Khopoli", 15);
    system.addConnection("Khopoli", "Roha", 30);


    // Adding trains
    system.addTrain("Express1", {"Mumbai_CST", "Dadar", "Thane", "Kalyan"}, 100, "AC");
    system.addTrain("Local1", {"Mumbai_CST", "Kurla", "Thane", "Vashi", "Panvel"}, 150, "Local");
    system.addTrain("WesternFast", {"Churchgate", "Dadar", "Andheri", "Borivali", "Virar"}, 200, "Regular");
    system.addTrain("HarbourSpecial", {"Mumbai_CST", "Kurla", "Vashi", "Panvel"}, 120, "Local");
    system.addTrain("CentralLocal", {"Mumbai_CST", "Dadar", "Thane", "Kalyan"}, 180, "Sleeper");
    system.addTrain("KasaraExpress", {"Mumbai_CST", "Thane", "Kalyan", "Kasara"}, 150, "AC");
    system.addTrain("KhopoliFast", {"Mumbai_CST", "Thane", "Kalyan", "Karjat", "Khopoli"}, 100, "Sleeper");




int ch;

cout<< "                                                                                                            \n";
cout << "                   'WELCOME TO CITY SYNC'                    \n";
cout<<"-------- A COMPREHENSIVE APPROACH TO URBAN LIVING -------\n";
cout << "Connecting you with the Healthcare service ,Tourism management ,Waste management and Transport optimization";
cout <<"\n                          \n";

do
{

cout<<"\n-------MAIN MENU------\n";
cout<<"                                        \n";
cout<<"1.HEALTHCARE SERVICE:\n";
cout<<"2.TOURIST MANAGEMENT:\n";
cout<<"3.WASTE MANAGEMENT :\n";
cout<<"4.TRANSPORT OPTIMIZATION:\n";
cout<<"5.EXIT\n";
cout<<"enter your choice : \n";
cin>>ch;
switch(ch)
{


case 1 :
    int choice;
    do
        {
        cout << "\n=========================\n";
        cout << "\n......WELCOME TO THE HEALTH CARE SERVICE.....\n";
        cout << "\n                                             \n";
        cout << "Main Menu\n";
        cout << "=========================\n";
        cout << "1. Bed Availability Tracker\n";
        cout << "2. Treatment Affordability Calculator\n";
        cout << "3. Appointment Scheduler\n";
        cout << "4. Search Nearest Specialist\n";
        cout << "5. Emergency Triage System\n";
        cout << "6. Treatment Cost Calculator\n";
        cout << "7. Health Education\n";
        cout << "8. Blood and Organ Donation Tracker\n";
        cout << "9. Equipment Handling\n";
        cout << "10.Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {

            case 1:
                {
                int bedChoice;
                do {
                    cout << "\nBed Availability Tracker Menu:\n";
                    cout << "1. Show current bed status\n";
                    cout << "2. Update bed status\n";
                    cout << "3. Back to main menu\n";
                    cout << "Enter your choice: ";
                    cin >> bedChoice;

                    if (bedChoice == 1)
                    {
                        bedTracker.showBedStatus();
                    }
                    else if (bedChoice == 2)
                    {
                        int idx, status;
                        cout << "Enter the bed index (0-based) to update its status: ";
                        cin >> idx;
                        cout << "Enter the new status for bed " << idx << " (0 for vacant, 1 for occupied): ";
                        cin >> status;
                        bedTracker.updateBedStatus(idx, status);
                    }
                }
                while (bedChoice != 3);
                break;
            }

            case 2:
                treatmentSystem.solveAffordability();
                break;

            case 3:
                {
                int appointmentChoice;
                do
                    {
                    cout << "\nAppointment Scheduler Menu:\n";
                    cout << "1. Book an Appointment\n";
                    cout << "2. Modify an Appointment\n";
                    cout << "3. Cancel an Appointment\n";
                    cout << "4. Display Appointments\n";
                    cout << "5. Display Available Time Slots\n";
                    cout << "6. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> appointmentChoice;

                    switch (appointmentChoice)
                    {
                        case 1:
                            appointmentScheduler.bookAppointment();
                            break;
                        case 2:
                            appointmentScheduler.modifyAppointment();
                            break;
                        case 3:
                            appointmentScheduler.cancelAppointment();
                            break;
                        case 4:
                            appointmentScheduler.displayAppointments();
                            break;
                        case 5:
                            appointmentScheduler.displayAvailableSlots();
                            break;
                        case 6:
                            cout << "Returning to Main Menu.\n";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                    }
                }
                while (appointmentChoice != 6);
                break;
            }

            case 4:
            {
                healthcareSystem.searchNearestSpecialist(cityGraph);
                break;
            }

            case 5:
                { // Emergency Triage System
                int triageChoice;
                do
                    {
                    cout << "\n--- Emergency Triage System ---\n";
                    cout << "1. Add Patient\n";
                    cout << "2. Attend to Patient\n";
                    cout << "3. Display Patients\n";
                    cout << "4. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> triageChoice;

                    switch (triageChoice)
                    {
                        case 1:
                        {
                            string name;
                            int severity;
                            cout << "Enter patient name: ";
                            cin.ignore();
                            getline(cin, name);
                            cout << "Enter severity (1 = Critical, higher numbers = Less severe): ";
                            cin >> severity;
                            triageSystem.addPatient(name, severity);
                            break;
                        }
                        case 2:
                            triageSystem.attendPatient();
                            break;
                        case 3:
                            triageSystem.displayPatients();
                            break;
                        case 4:
                            cout << "Returning to Main Menu.\n";
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                    }
                }
                while (triageChoice != 4);
                break;
            }

            case 6:
                { // Treatment Cost Calculator
                int calculatorChoice;
                do
                    {
                    cout << "\n--- Treatment Cost Calculator ---\n";
                    cout << "1. Add/Update Treatment Cost\n";
                    cout << "2. Remove Treatment\n";
                    cout << "3. Undo Last Operation\n";
                    cout << "4. Redo Last Operation\n";
                    cout << "5. Display All Costs\n";
                    cout << "6. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> calculatorChoice;

                    switch (calculatorChoice)
                    {
                        case 1:
                        {
                            string treatment;
                            double cost;
                            cout << "Enter treatment name: ";
                            cin.ignore();
                            getline(cin, treatment);
                            cout << "Enter cost: ";
                            cin >> cost;
                            calculator.addOrUpdateCost(treatment, cost);
                            break;
                        }
                        case 2:
                        {
                            string treatment;
                            cout << "Enter treatment name to remove: ";
                            cin.ignore();
                            getline(cin, treatment);
                            calculator.removeCost(treatment);
                            break;
                        }
                        case 3:
                            calculator.undo();
                            break;
                        case 4:
                            calculator.redo();
                            break;
                        case 5:
                            calculator.displayCosts();
                            break;
                        case 6:
                            cout << "Returning to Main Menu.\n";
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                    }
                }
                while (calculatorChoice != 6);
                break;
            }

            case 7:
                { // Health Education
                int healthChoice;
                do
                    {
                    cout << "\n--- Health Education ---\n";
                    cout << "1. Search for a Topic\n";
                    cout << "2. Display All Topics\n";
                    cout << "3. Health Tips\n";
                    cout << "4. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> healthChoice;

                    switch (healthChoice)
                    {
                        case 1:
                        {
                            string topic;
                            cout << "Enter topic to search: ";
                            cin.ignore(); // To clear the newline from the input buffer
                            getline(cin, topic);
                            trie.search(topic); // Call search function
                            break;
                        }
                        case 2:
                            trie.displayAllTopics(); // Show all topics
                            break;
                        case 3:
                            displayHealthTips(); // Display health tips
                            break;
                        case 4:
                            cout << "Returning to Main Menu.\n";
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                    }
                }
                while (healthChoice != 4);
                break;
            }
             case 8:
                while (true)
                    {
                    int donationChoice;
                    cout << "\nBlood and Organ Donation Tracker Menu:\n";
                    cout << "1. Find Compatible Donors by Organ Type\n";
                    cout << "2. Find Compatible Donors by Blood Type\n";
                    cout << "3. Find Compatible Donors by Both Blood and Organ Type\n";
                    cout << "4. Add New Donor\n";
                    cout << "5. Display All Donors\n";
                    cout << "6. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> donationChoice;

                    switch (donationChoice)
                    {
                        case 1:
                        {
                            string organType;
                            cout << "Enter organ type (e.g., KIDNEY, LIVER, HEART): ";
                            cin >> organType;
                            donationTracker.findCompatibleDonorsByOrgan(organType);
                            break;
                        }
                        case 2:
                        {
                            string bloodType;
                            cout << "Enter blood type (e.g., O+, A-, etc.): ";
                            cin >> bloodType;
                            donationTracker.findCompatibleDonorsByBlood(bloodType);
                            break;
                        }
                        case 3:
                        {
                            string bloodType, organType;
                            cout << "Enter blood type (e.g., O+, A-, etc.): ";
                            cin >> bloodType;
                            cout << "Enter organ type (e.g., KIDNEY, LIVER, HEART): ";
                            cin >> organType;
                            donationTracker.findCompatibleDonorsByBloodAndOrgan(bloodType, organType);
                            break;
                        }
                        case 4:
                            donationTracker.addNewDonor();
                            break;
                        case 5:
                            donationTracker.displayAllDonors();
                            break;
                        case 6:
                            break;
                        default:
                            cout << "Invalid option! Please try again.\n";
                    }

                    if (donationChoice == 6)
                    {
                        break;  // Exit the donation tracker and go back to the main menu
                    }
                }
                break;

                 case 9:
                     {
                bool continueEquipment = true;
                while (continueEquipment)
                {
                    cout << "\nEquipment Management\n";
                    cout << "1. Allocate Equipment\n";
                    cout << "2. Check Equipment Availability\n";
                    cout << "3. Display All Equipment\n";
                    cout << "4. Return to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                        case 1:
                            equipmentSystem.allocateEquipment();
                            break;
                        case 2:
                        {
                            string equipmentName;
                            cout << "Enter equipment name to check availability: ";
                            cin.ignore();  // Ignore any trailing newline
                            getline(cin, equipmentName);
                            equipmentSystem.checkAvailability(equipmentName);
                            break;
                        }
                        case 3:
                            equipmentSystem.displayInventory();
                            break;
                        case 4:
                            continueEquipment = false;
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                }
                break;
            }
                case 10:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    while (choice != 10);
    break;


case 2:

    int mainChoice;

    cout<<"\n.........................................................................\n";
    cout<<"\n------------------WELCOME TO TOURIST MANAGEMENT SYSTEM!!!-------------\n";
    cout<<"\n..........................................................................\n";
    cout<<"                                                                              \n";
    do
        {
        cout << "\n==== Main Menu ====\n";
        cout << "1.Efficient Trip Tips\n";
        cout << "2.Room Allocation based on Price\n";
        cout << "3.Emergency Contact Finder\n";
        cout << "4. Itinerary Time Management\n";
        cout << "5. Tourist Problems" << endl;
        cout << "6. Shelter-Related Problems" << endl;
        cout << "7. Cleanliness-based allocation" << endl;
        cout << "8. Distance-based allocation" << endl;
        cout << "9. Back to Main Menu\n";
        cout << "====================\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice)
        {

        case 1:
                {
                int choice;
                do
                    {
                    displayMenuTips();
                    cin >> choice;

                    switch (choice)
                    {
                        case 1:
                            viewAllTips(tips);
                            break;
                        case 2:
                            viewTipsByCategory(tips);
                            break;
                        case 3:
                            addNewTip(tips);
                            break;
                        case 4:
                            searchTipsByKeyword(tips);
                            break;
                        case 5:
                            viewKeywordsByTip(tips);
                            break;
                        case 6:
                            break; // Back to main menu
                        default:
                            cout << "Invalid choice! Please try again." << endl;
                    }

                }

                while (choice != 6);
                break;
            }
        case 2:
                {
                int choice;
                bool exitMenu = false;

                while (! exitMenu)
                    {
                    displayMenuRooms();
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {

                        case 1:
                            displayExistingTourists(tourists);
                            break;

                        case 2:
                            inputTouristData(tourists);
                            break;

                        case 3:
                            displayRooms(rooms);
                            break;

                        case 4:
                            allocateRooms(tourists, rooms);
                            break;

                        case 5:
                            displayAllocations(tourists);
                            break;

                        case 6:
                            reallocateRooms(tourists, rooms);
                            break;

                        case 7:
                            displayAllocations(tourists);
                            break;

                        case 8:
                            exitMenu = true;
                            break;

                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                }

                break;
            }

        case 3:
                handleEmergencyMenuSelection(contacts);
                break;

        case 4:
                handleItineraryMenuSelection(activities);
                break;

        case 5:
                {
                int touristChoice;
                do
                    {
                    displayTouristMenu();
                    cin >> touristChoice;

                    switch (touristChoice)
                    {
                        case 1:
                            viewTouristProblems(touristProblems);
                            break;
                        case 2:
                            analyzeTouristProblems(touristProblems);
                            break;
                        case 3:
                            {
                            int solveChoice;
                            displayWaysToSolveProblems();
                            cin >> solveChoice;
                            switch (solveChoice)
                            {

                                case 1:
                                    cout << "Contact local authorities for assistance." << endl;
                                    break;

                                case 2:
                                    cout << "Use mobile apps like Google Maps or local transport apps for real-time updates." << endl;
                                    break;

                                case 3:
                                    cout << "Seek help from fellow tourists or locals." << endl;
                                    break;

                                case 4:
                                    cout << "Visit tourist information centers for guidance." << endl;
                                    break;

                                case 5:
                                    cout << "Returning to Tourist Problems Menu..." << endl;
                                    break;

                                default:
                                    cout << "Invalid choice! Please try again." << endl;
                            }
                            break;
                        }
                        case 4:
                            cout << "Returning to Main Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice! Please try again." << endl;
                    }
                }

                while (touristChoice != 4);
                break;
            }
    case 6:
                {
                int shelterChoice;
                do
                    {
                    displayShelterMenu();
                    cin >> shelterChoice;

                    switch (shelterChoice)
                    {

                        case 1:
                            viewShelterProblems(shelterProblems);
                            break;

                        case 2:
                            viewShelterSolutions(shelterProblems);
                            break;

                        case 3:
                            analyzeShelterProblems(shelterProblems);
                            break;

                        case 4:
                            {
                            int solveChoice;
                            displayWaysToSolveProblems();
                            cin >> solveChoice;

                            switch (solveChoice)
                            {
                                case 1:
                                    cout << "Contact local authorities for assistance." << endl;
                                    break;

                                case 2:
                                    cout << "Use mobile apps for finding nearby shelters." << endl;
                                    break;
                                case 3:
                                    cout << "Seek help from fellow travelers." << endl;
                                    break;

                                case 4:
                                    cout << "Visit local tourist information centers." << endl;
                                    break;

                                case 5:
                                    cout << "Returning to Shelter-Related Problems Menu..." << endl;
                                    break;

                                default:
                                    cout << "Invalid choice! Please try again." << endl;
                            }
                            break;
                        }
                        case 5:
                            cout << "Returning to Main Menu..." << endl;
                            break;

                        default:
                            cout << "Invalid choice! Please try again." << endl;
                    }

                }

                while (shelterChoice != 5);
                break;
            }
      case 7:
             {
                int cleanlinessChoice;
                do
                    {
                    cout << "\n--- Cleanliness-Based Allocation Menu ---" << endl;

                    cout << "1. Add New Tourist" << endl; // New option
                    cout << "2. Add New Shelter" << endl; // New option
                    cout << "3. Display existing shelters and tourists in mumbai" << endl;
                    cout << "4. Input Distances in KM" << endl;
                    cout << "5. Allocate Rooms by considering Cleanliness of the rooms" << endl;
                    cout << "6. Display room Allocation Status " << endl;
                    cout << "7. Back to Main Menu" << endl;

                    cout << "Enter choice: ";
                    cin >> cleanlinessChoice;

                    switch (cleanlinessChoice)
                    {

                      case 1:
                         inputCleanlinessTourists(cleanlinessTourists);
                         break;

                      case 2:
                         inputCleanlinessShelters(cleanlinessShelters);
                         break;

                      case 3: displayCleanlinessSheltersStatus(cleanlinessShelters);

                                displayCleanlinessAllocationStatus(cleanlinessTourists);
                              break;

                        case 4:
                            inputCleanlinessDistances(cleanlinessDistances, cleanlinessTourists.size(), cleanlinessShelters.size());
                            break;

                        case 5:

                            allocateRoomsByCleanliness(cleanlinessTourists, cleanlinessShelters, cleanlinessDistances);

                            displayCleanlinessAllocationStatus(cleanlinessTourists);

                            displayCleanlinessSheltersStatus(cleanlinessShelters);

                            break;

                        case 6:
                            displayCleanlinessAllocationStatus(cleanlinessTourists);
                            break;

                        case 7:
                            break;

                        default:
                            cout << "Invalid choice! Please try again." << endl;
                            break;

                    }

                }

                while (cleanlinessChoice !=7 );

                break;
            }

    case 8:

        {
                int distanceChoice;

                do
                    {

                    cout << "\n---Distance-Based Allocation Menu ---" << endl;

                    cout << "1. Add New Tourist" << endl; // New option
                    cout << "2. Add New Shelter" << endl; // New option
                    cout << "3. Display existing shelters and tourists in mumbai" << endl;
                    cout << "4. Input Distances in kilometers" << endl;
                    cout << "5. Allocate Rooms by considering Distance" << endl;
                    cout << "6. Display Allocation Status" << endl;
                    cout << "7. Back to Main Menu" << endl;
                    cout << "Enter choice: ";
                    cin >> distanceChoice;

                    switch (distanceChoice)
                    {

                        case 1:
                               inputDistanceTourists(distanceTourists);
                                break;

                       case 2:
                               inputDistanceShelters(distanceShelters);
                               break;

                        case 3:
                                displayDistanceSheltersStatus(distanceShelters);

                                displayDistanceAllocationStatus(distanceTourists);
                                break;

                        case 4:
                            inputDistanceDistances(distanceDistances, distanceTourists.size(), distanceShelters.size());
                            break;

                        case 5:
                            allocateRoomsByDistance(distanceTourists, distanceShelters, distanceDistances);

                            displayDistanceAllocationStatus(distanceTourists);

                            displayDistanceSheltersStatus(distanceShelters);

                            break;

                        case 6:
                            displayDistanceAllocationStatus(distanceTourists);
                            break;

                        case 7:
                            break;

                        default:
                            cout << "Invalid choice! Please try again." << endl;
                            break;
                    }

                }
                while (distanceChoice != 7);

                break;
            }

        case 9:
                break;

            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }

    }

    while (mainChoice !=9);
    break;
case 3:
    {
               // Admin admin("a", "b");
            //  std::pair<std::string, std::string> adminCredentials = Authentication::readAdminInfo();
            // Admin admin(adminCredentials.first, adminCredentials.second);
            Admin admin;
            bool isAdmin = Authentication::isAdmin();
            if (isAdmin)
            {
                admin.greet();
                admin.userMenu();
            }
            else
            {
                User user;
                user.greet();
                user.userMenu();

            }

          }
        break;

case 4: menu(system);
       break;

default: cout<<"\n enter valid choice\n";
         break;
}
}
while(ch!=4);

 return 0;
}
