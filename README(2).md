Flight Management System

A C++ program that manages departures with a Max-Heap priority queue for Runway Command.

Phase 2: Runway Command

Features
- Register a flight and reject duplicate Flight IDs
- View the next flight to depart without removing it
- Clear the highest-priority flight for takeoff
- Declare an emergency for a flight
- Report a flight delay
- Display the departure board in priority order
- Save to and load from priority_flights.txt
- Priority Score = Base Score + Delay Minutes (Emergency 300, Delayed 200, Scheduled 100)

How to Run
1. Open the main.cpp file inside the runway folder in Visual Studio.
2. Build and run the program.
3. Use the menu to choose an option.

File Format
One flight per line in priority_flights.txt:
201,Lahore,Karachi,PIA,09:30,11:15,1.75,18000,Scheduled,0,100

-Syeda Fatima Rizwan (F25BSCS107)