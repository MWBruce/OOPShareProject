#include "Individual.h"

#include <stdlib.h>
#include <string.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include "Broker.h"
#include "Investor.h"
#include "Portfolio.h"
#include "User.h"

using namespace std;

Individual::Individual() {
  First_Name = "N/A";                   // Intialise first name
  Last_Name = "N/A";                    // Intialise last name
  Balance = 0;                          // Intialise balance to 0
  Account_Number = 0;                   // Set account number to 0
  Account_Type = "N/A";                 // Set account type
  Current_Year = 2014;                  // Set current year 2014
  Investors_Portfolio = new Portfolio;  // Allocate memory
  Broker_ID = 0;                        // Sets no broker
}

Individual::Individual(int ID) {
  Account_Number = ID;                  // Set Account number equal to ID
  Get_Individual_Details();             // call individual details function
  Account_Type = "I";                   // set to I
  Current_Year = 2014;                  // Set current year to 2014
  Investors_Portfolio = new Portfolio;  // allocate memory
  Logged_In = 1;                        // Log in status to 1
  Broker_ID = 0;                        // Sets no broker
  Display_Options();                    // Display Options 1-9
}

void Individual::Get_Individual_Details() {
  ifstream Information;
  Information.open("Accounts.csv");  // Open Accounts.csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;  // File unable to be
                                                      // opened
  }
  string Temp_ID;  // intialise temp variables
  int Int_Temp_ID;
  string Temp_Nothing;
  string Temp_First_Name;
  string Temp_Last_Name;
  string line;
  while (getline(
      Information,
      line))  // while loop, loop until Temp ID is matched with account number
  {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_First_Name, ',');
    getline(ss, Temp_Last_Name, ',');
    if (Int_Temp_ID == Account_Number) {
      First_Name = Temp_First_Name;  // Set First name
      Last_Name = Temp_Last_Name;    // Set last name
      break;
    }
  }
  Information.close();
}

void Individual::Print() {
  Investor::Print();           // Print constructor
  ofstream Printed_Portfolio;  // file object
  Printed_Portfolio.open(
      "Individual Portfolio Report.csv");  // open Individual portfolio csv
  int Share_Count =
      Investors_Portfolio->Get_Share_Count();  // Intialise share count
  Printed_Portfolio << "Report for Individual Investors" << endl;
  Printed_Portfolio << "First Name: " << First_Name
                    << endl;  // display first name
  Printed_Portfolio << "Last Name: " << Last_Name << endl;  // display last name
  for (int i = 0; i < Share_Count; i++)  // Loop from 0 to share count
  {
    int Temp_Units =
        Investors_Portfolio->Units(i);  // Set temp units to investors units
    int Temp_Current_Price = Investors_Portfolio->Current_Price(
        i);  // Set temp current price to investors current price
    int Temp_Previous_Price = Investors_Portfolio->Previous_Price(
        i);  // Set temp previous price to investors previous price
    string Temp_Name =
        Investors_Portfolio->Name(i);  // Set temp name to investors name
    Printed_Portfolio << "Share Number " << i + 1 << " - " << Temp_Name
                      << endl;  // Display share number
    Printed_Portfolio << "\t Units: " << Temp_Units << endl;  // Display units
    Printed_Portfolio << "\t Current Price: $" << Temp_Current_Price
                      << endl;  // Display current price
    Printed_Portfolio << "\t Previous Price: $" << Temp_Previous_Price
                      << endl;  // Display Previous Price
    Printed_Portfolio << "\t 12 Month Price Change: $"
                      << (Temp_Current_Price - Temp_Previous_Price) * Temp_Units
                      << endl;  // Display 12 month change
  }
  Printed_Portfolio << "Your Bank Balance is furthermore: $"
                    << Investors_Portfolio->Get_Cash()
                    << endl;  // Display balance
  Printed_Portfolio.close();  // close portfolio
  cout << "Please find your report called \"Individual Portfolio Report\" "
       << endl;  // Tells user to go to individual portfolio report csv
  this_thread::sleep_for(chrono::seconds(2));  // sleep for 2 seconds
}

void Individual::Individual_Display_Results_Test() {
  cout << "Name: " << First_Name << " " << Last_Name << " balance: " << Balance
       << endl;  // Display results
}
// Deconstructor
Individual::~Individual() { delete Investors_Portfolio; }