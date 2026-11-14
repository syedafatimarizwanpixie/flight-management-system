#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int CalculatePriorityScore(string status, int delayMinutes)
{

    if (status == "Scheduled" || status == "scheduled")
    {
        return 100 + delayMinutes;
    }
    else if (status == "Delayed" || status == "delayed")
    {
        return 200 + delayMinutes;
    }
    else if (status == "Emergency" || status == "emergency")
    {
        return 300 + delayMinutes;
    }
    else
    {
        cout << "Invalid status!" << endl;
        return -1; // Return -1 to indicate an error
    }
}

struct Flight
{
    int flightID;
    string Source;
    string Destination;
    string Airline;
    string departureTime;
    string arrivalTime;
    string flightDuration;
    int ticketPrice;
    string Status;
    int delayMinutes;
    int PriorityScore;
    //bool hasSpecialNeeds;

    Flight() {}
    Flight(int id, string src, string dest, string air, string dep, string arr, string dur, int price, string status, int delay)
    {
        flightID = id;
        Source = src;
        Destination = dest;
        Airline = air;
        departureTime = dep;
        arrivalTime = arr;
        flightDuration = dur;
        ticketPrice = price;
        if ((status == "Scheduled" || status == "scheduled") && delay > 0)
        {
            status = "Delayed";
        }
        Status = status;
        delayMinutes = delay;
        PriorityScore = CalculatePriorityScore(status, delay);
    }
};

// A[1] to A[n] contain the emergency scores.
// Index 0 is intentionally not used.
class MaxHeap
{

public:
    
    void Heapify(Flight A[], int i, int heapSize);

    void BuildHeap(Flight A[], int n, int &heapSize);
    void HeapSort(Flight A[], int n);
    int HeapMaximum(Flight A[]);
    Flight HeapExtractMaximum(Flight A[], int &heapsize);
    void HeapIncreasePriority(Flight A[], int i, int flightID, string status, int delMin, int &PriorityScore);
    void MaxHeapInsert(Flight A[], int flightID, string source, string destination, string airline, string depTime, string arrTime, string dur, int price, string status, int delMin, int &heapsize);
    void DisplayHeap(Flight A[], int heapsize);
    int FindFlightIndex(Flight A[], int heapsize, int flightID);
    bool hasHigherPriority(const Flight& a, const Flight& b);
    void HeapifyUp(Flight A[], int i);
    bool IsValidHeap(Flight A[], int heapsize);
    void ShowHeapArray(Flight A[], int heapsize);
};

bool MaxHeap::hasHigherPriority(const Flight& a, const Flight& b)
{
    if (a.PriorityScore != b.PriorityScore)
        return a.PriorityScore > b.PriorityScore;

    else if (a.departureTime != b.departureTime)
        return a.departureTime < b.departureTime;

    else
        return a.flightID < b.flightID;
}

void MaxHeap::Heapify(Flight A[], int i, int heapSize)
{
    // TODO 1: Find the left child and right child of index i.
    int Left = 2 * i;
    int Right = (2 * i) + 1;

    // TODO 2: Assume the current node i is the largest.
    int Largest = i;

    // TODO 3: If the left child exists and is greater than A[i],
    //         update the index of the largest value.
    if (Left <= heapSize && hasHigherPriority(A[Left], A[Largest]))
    {
        Largest = Left;
    }

    // TODO 4: If the right child exists and is greater than
    //         the value at the current largest index,
    //         update the index of the largest value.
    if (Right <= heapSize && hasHigherPriority(A[Right], A[Largest]))
    {
        Largest = Right;
    }

    // TODO 5: If the largest index is not i:
    //         a) Exchange A[i] and A[largest].
    //         b) Call Heapify() again for the affected subtree.
    if (Largest != i)
    {
        Flight temp = A[i];
        A[i] = A[Largest];
        A[Largest] = temp;

        Heapify(A, Largest, heapSize);
    }
}

void MaxHeap::BuildHeap(Flight A[], int n, int &heapSize)
{
    // TODO 6: Set heapSize equal to n.
    heapSize = n;

    // TODO 7: Start i from n/2 and move backwards to 1.
    //         Call Heapify(A, i, heapSize) for each i.
    for (int i = n / 2; i >= 1; i--)
    {
        Heapify(A, i, heapSize);
    }
}

void MaxHeap::HeapSort(Flight A[], int n)
{
    int heapSize;

    // TODO 8: Call BuildHeap().
    BuildHeap(A, n, heapSize);

    // TODO 9: Run a loop from i = n down to 2.
    //         a) Exchange A[1] and A[i].
    //         b) Decrease heapSize by 1.
    //         c) Call Heapify(A, 1, heapSize).
    for (int i = n; i >= 2; i--)
    {
        Flight temp = A[1];
        A[1] = A[i];
        A[i] = temp;

        heapSize--;

        Heapify(A, 1, heapSize);
    }
}

int MaxHeap::HeapMaximum(Flight A[])
{
    // TODO 11: Return the maximum value in the heap.
    return A[1].PriorityScore;
}

Flight MaxHeap::HeapExtractMaximum(Flight A[], int &heapsize)
{
    if (heapsize < 1)
    {
        cout << "No Flight available for takeoff!" << endl;
        return Flight();
    }
    else
    {
        Flight max = A[1];
        A[1] = A[heapsize];
        heapsize--;
        Heapify(A, 1, heapsize);
        return max;
    }
}

void MaxHeap::HeapIncreasePriority(Flight A[], int i, int flightID, string status, int delMin, int &PriorityScore)
{
    PriorityScore = CalculatePriorityScore(status, delMin);

    int Parent = i / 2;

    A[i].PriorityScore = PriorityScore;
    while (i > 1 && hasHigherPriority(A[i], A[Parent]))
    {
        Flight temp = A[i];
        A[i] = A[Parent];
        A[Parent] = temp;

        i = Parent;
        Parent = i / 2;
    }
}
// same as the fucntion above but only No priority score bcs its changing the correct one that i already calculated!!!!!
void MaxHeap::HeapifyUp(Flight A[], int i)
{
    int Parent = i / 2;

    while (i > 1 && hasHigherPriority(A[i], A[Parent]))
    {
        Flight temp = A[i];
        A[i] = A[Parent];
        A[Parent] = temp;
        i = Parent;
        Parent = i / 2;
    }
}
// int id, string src, string dest, string air, float dep, float arr, float dur, int price, string status, int delay
void MaxHeap::MaxHeapInsert(Flight A[], int flightID, string source, string destination, string airline, string depTime, string arrTime, string dur, int price, string status, int delMin, int &heapsize)
{
    heapsize++;
    A[heapsize] = Flight(flightID, source, destination, airline, depTime, arrTime, dur, price, status, delMin);
    // HeapIncreasePriority(A, heapsize, flightID, status, delMin, PriorityScore);
    HeapifyUp(A, heapsize);
}

void MaxHeap::DisplayHeap(Flight A[], int heapsize)
{
    if (heapsize == 0)
    {
        cout << "Runway is empty!" << endl;
    }
    else
    {
        int size = heapsize;
        Flight B[101];
        for (int i = 1; i <= heapsize; i++)
        {
            B[i] = A[i];
        }
        cout << "======Registered Flights====== \n";

        for (int i = 1; size > 0; i++)
        {

            Flight flight = HeapExtractMaximum(B, size);
            cout << "Flight " << i << ":" << endl;
            cout << "Flight ID:         " << flight.flightID << endl;
            cout << "Source:            " << flight.Source << endl;
            cout << "Destination:       " << flight.Destination << endl;
            cout << "Airline:           " << flight.Airline << endl;
            cout << "Departure Time:    " << flight.departureTime << endl;
            cout << "Arrival Time:      " << flight.arrivalTime << endl;
            cout << "Flight Duration:   " << flight.flightDuration << endl;
            cout << "Ticket Price:      " << flight.ticketPrice << endl;
            cout << "Status:            " << flight.Status << endl;
            cout << "Delay Minutes:     " << flight.delayMinutes << endl;
            cout << "Priority Score:    " << flight.PriorityScore << endl;
            cout << endl;
        }

        cout << endl;
    }
}

void loadRecords(Flight A[], int &heapSize)
{
    ifstream in("priority_flights.txt");
    if (!in)
    {
        cout << "No saved file found. Starting with an empty queue.\n";
        return;
    }

    heapSize = 0;
    string id, src, dest, air, dep, arr, dur, price, stat, delay, score;

    while (heapSize < 100 && getline(in, id, ','))
    {
        getline(in, src, ',');
        getline(in, dest, ',');
        getline(in, air, ',');
        getline(in, dep, ',');
        getline(in, arr, ',');
        getline(in, dur, ',');
        getline(in, price, ',');
        getline(in, stat, ',');
        getline(in, delay, ',');
        getline(in, score);

        heapSize++;
        A[heapSize] = Flight(stoi(id), src, dest, air, dep, arr,
                             dur, stoi(price), stat, stoi(delay));
    }
    in.close();
}

void saveRecords(Flight A[], int heapSize)
{
    ofstream out("priority_flights.txt");
    if (!out)
    {
        cout << "Error opening file for saving.\n";
        return;
    }

    for (int i = 1; i <= heapSize; i++)
    {
        out << A[i].flightID << ","
            << A[i].Source << ","
            << A[i].Destination << ","
            << A[i].Airline << ","
            << A[i].departureTime << ","
            << A[i].arrivalTime << ","
            << A[i].flightDuration << ","
            << A[i].ticketPrice << ","
            << A[i].Status << ","
            << A[i].delayMinutes << ","
            << A[i].PriorityScore << "\n";
    }

    out.close();
}

int MaxHeap::FindFlightIndex(Flight A[], int heapsize, int flightID)
{
    for (int i = 1; i <= heapsize; i++)
    {
        if (A[i].flightID == flightID)
        {
            return i;
        }
    }
    return 0;
}


bool MaxHeap::IsValidHeap(Flight A[], int heapsize)
{
    for (int i = 2; i <= heapsize; i++)
    {
        // A[i/2] is the parent of A[i]
        if (hasHigherPriority(A[i], A[i / 2]))
            return false;      // comparing 
    }
    return true;
}

void MaxHeap::ShowHeapArray(Flight A[], int heapsize)
{
    cout << "\n======Raw heap array======\n" << endl;
    for (int i = 1; i <= heapsize; i++)
    {
        cout << "A[" << i << "] = Flight " << A[i].flightID << "  \nPriority Score: " << A[i].PriorityScore << " " << endl;
    }
    cout << "Heap property valid: " << (IsValidHeap(A, heapsize) ? "yep :)" : "no :(") << endl;
}

int main()
{
    MaxHeap heap;

    int flightId;
    string source;
    string destination;
    string airline;
    string depTime;
    string arrTime;
    int tPrice;
    string status;
    int delMin;
    int prioritySc = 0;
    string flightDur;
    // string specialNeeds;
    // bool hasSpecialNeeds;
    Flight A[101];
    int n = 0;
    int heapSize = 0;
    int choice, key, index;

    loadRecords(A, heapSize);
    heap.BuildHeap(A, heapSize, heapSize);

    do
    {
        cout << "\n\n===== RUNWAY COMMAND =====" << endl;
        cout << "1. Register Flight" << endl;
        cout << "2. View Next Flight" << endl;
        cout << "3. Clear Flight for Takeoff" << endl;
        cout << "4. Declare Emergency" << endl;
        cout << "5. Report Flight Delay" << endl;
        cout << "6. Display Departure Board" << endl;
        cout << "0. Exit" << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {

        case 1:
            if (heapSize >= 100)
            {
                cout << "Runway is full!" << endl;
            }
            else
            {
                cout << "Enter Flight ID: ";
                cin >> flightId;

                int check = heap.FindFlightIndex(A, heapSize, flightId);
                if (check != 0)
                {
                    cout << "Flight ID already exists!" << endl;
                    break;
                }

                cout << "Enter Source: ";
                cin >> source;
                cout << "Enter Destination: ";
                cin >> destination;
                cout << "Enter Airline: ";
                cin >> airline;

                cout << "Enter Departure Time(HH:MM): ";
                cin >> depTime;
                if(depTime.length() != 5)
                {
                    cout<< "Please Enter Departure Time in Correct Format(HH:MM)!" <<endl;
                    break;
                }

                cout << "Enter Arrival Time(HH:MM): ";
                cin >> arrTime;
                if(arrTime.length() != 5)
                {
                    cout<< "Please Enter Arrival Time in Correct Format(HH:MM)!" <<endl;
                    break;
                }

                cout << "Enter Ticket Price: ";
                cin >> tPrice;
                cout << "Enter Flight Duration: ";
                cin >> flightDur;
                cout << "Enter Status (Scheduled/Delayed): ";
                cin >> status;
                    if (status != "Scheduled" && status != "scheduled" && status != "Delayed" && status != "delayed")
                    {
                        cout << "Invalid Status!" << endl;
                        break;
                    }
                    else if (status == "Delayed" || status == "delayed")
                    {
                        cout << "Enter Delay Minutes: ";
                        cin >> delMin;
                        if (delMin < 1 || delMin > 99)
                        {
                            cout << "Invalid Delay Minutes(1-99 only)!" << endl;
                            break;
                        }
                    }
                    else
                    {
                        delMin = 0;
                    }

                    // Calculate Flight Duration

                    heap.MaxHeapInsert(A, flightId, source, destination, airline, depTime, arrTime, flightDur, tPrice, status, delMin, heapSize);
                    n = heapSize;

                    cout << "New flight inserted!" << endl;

                    cout << "Priority Score of New Flight " << flightId << " :" << CalculatePriorityScore(status, delMin) <<endl;
            }

            break;

        case 2:
            if (heapSize == 0)
            {
                cout << "No Registered Flights yet!" << endl;
            }
            else
            {
                cout << "Highest Priority Flight ID: " << A[1].flightID << endl;
                cout << "Priority Score: " << heap.HeapMaximum(A) << endl;
                cout << "Source: " << A[1].Source << endl;
                cout << "Destination: " << A[1].Destination << endl;
                cout << "Status: " << A[1].Status << endl;
            }

            break;

        case 3:

            if (heapSize == 0)
            {
                cout << "No Registered Flights yet!" << endl;
            }
            else
            {
                Flight flight = heap.HeapExtractMaximum(A, heapSize);
                cout << "Clear for Takeoff: " << endl;
                cout << "Flight ID:         " << flight.flightID << endl;
                cout << "Priority Score:    " << flight.PriorityScore << endl;
                cout << "Source:            " << flight.Source << endl;
                cout << "Destination:       " << flight.Destination << endl;
                cout << "Airline:           " << flight.Airline << endl;
                cout << "Departure Time:    " << flight.departureTime << endl;
                cout << "Arrival Time:      " << flight.arrivalTime << endl;
                cout << "Flight Duration:   " << flight.flightDuration << endl;
                cout << "Ticket Price:      " << flight.ticketPrice << endl;
                cout << "Status:            " << flight.Status << endl;
                cout << "Delay Minutes:     " << flight.delayMinutes << endl;

                n = heapSize;
            }

            break;

        case 4:

            cout << "Enter Flight ID: ";
            cin >> flightId;

            index = heap.FindFlightIndex(A, heapSize, flightId);

            if (index == 0)
            {
                cout << "Flight Not Found!" << endl;
            }
            else
            {
                if (A[index].Status == "Emergency" || A[index].Status == "emergency")
                {
                    cout << "Flight already has Emergency status!" << endl;
                    break;
                }
                else
                {
                    A[index].Status = "Emergency";
                    A[index].PriorityScore = CalculatePriorityScore(A[index].Status, A[index].delayMinutes);
                    heap.HeapifyUp(A, index);

                    cout << "Flight ID " << flightId << " has been declared as an Emergency Flight!" << endl;
                }
            }

            break;

        case 5:

            if (heapSize == 0)
            {
                cout << "No such Registered Flight yet!" << endl;
            }
            else
            {
                cout << "Enter Flight ID: ";
                cin >> flightId;
                cout << "Enter delay minutes: ";
                cin >> delMin;

                index = heap.FindFlightIndex(A, heapSize, flightId);

                if (index == 0)
                {
                    cout << "Flight not Found!" << endl;
                }
                else
                {
                    if (delMin < 1 || delMin > 99)
                    {
                        cout << "Invalid delay minutes!(1-99)" << endl;
                    }
                    else
                    {
                        A[index].delayMinutes = A[index].delayMinutes + delMin;

                        if (A[index].delayMinutes > 99)
                        {
                            A[index].delayMinutes = 99;
                            cout << "Delay Minutes Capped" <<endl;
                        }

                        if (A[index].Status == "Delayed" || A[index].Status == "delayed")
                        {
                            A[index].Status = "Delayed";
                        }
                        else if (A[index].Status == "Emergency" || A[index].Status == "emergency")
                        {
                            A[index].Status = "Emergency";
                        }
                        else
                        {
                            A[index].Status = "Delayed";
                        }

                        A[index].PriorityScore = CalculatePriorityScore(A[index].Status, A[index].delayMinutes);
                        heap.HeapifyUp(A, index);

                        cout << "Flight ID " << flightId << " has been delayed by " << delMin << " minutes!" << endl;
                    }
                }
            }
            break;

        case 6:
            if (heapSize == 0)
            {
                cout << "No Flights yet!" << endl;
            }
            else
            {

                heap.DisplayHeap(A, heapSize);

                cout << endl;
            }
            break;

        case 7:
            if(heapSize == 0)
            {
                cout << "Heap is Empty!" <<endl;
            }
            else
            {
                heap.ShowHeapArray(A, heapSize);
            }
            break;

        case 0:
            cout << "Exiting program..." << endl;
            saveRecords(A, heapSize);
            break;

        default:
            cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
