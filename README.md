### Flight Management System

A C++ program that stores flight records in a Binary Search Tree (Phase 1) and manages departures with a Max-Heap priority queue (Phase 2). The BST is the main flight database, and the Max-Heap is the departure queue/runway command.

### Phase 1: BST Flight Database

A program that stores flight records in a Binary Search Tree, ordered by unique Flight ID.

### Features
- Add, search, and delete flights by Flight ID
- Display all flights in ascending Flight ID order
- Calculate flight duration and ETA, and mark each flight On-Time, Early, or Delayed
- Save to and load from flights.txt
- Surprise feature: My surprise feature is that when a flight is being entered into the database, the system asks them whether there is a person with disabilities and/or special needs on the flight, so that the flight personnel can be informed.

### How to Run
1. Open DSA Project - FMS - Module 1.cpp in Visual Studio.
2. Build and run the program.
3. Use the menu to choose an option.

### File Format
One flight per line in flights.txt:

101,Lahore,Karachi,PIA,09:30,11:15,1:45/1.75,18000,Scheduled

## Phase 2: Runway Command

A departure control system that uses an array-based Max-Heap so the highest-priority flight is always next for takeoff.

### Features
- Register a flight and reject duplicate Flight IDs
- View the next flight to depart without removing it
- Clear the highest-priority flight for takeoff
- Declare an emergency for a flight
- Report a flight delay
- Display the departure board in priority order
- Save to and load from priority_flights.txt
- Priority Score = Base Score + Delay Minutes (Emergency 300, Delayed 200, Scheduled 100)

### How to Run
1. Open [your Module 2 file name].cpp in Visual Studio.
2. Build and run the program.
3. Use the menu to choose an option.

### File Format
One flight per line in priority_flights.txt:

203,Islamabad,Lahore,SereneAir,10:15,11:15,1.00,12000,Delayed,20,220
204,Lahore,Skardu,PIA,11:00,12:15,1.25,24000,Scheduled,0,100
