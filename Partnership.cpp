#include "Partnership.h"

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

Partnership::Partnership() {
  First_Name = new string[1];  // Allocate memory for first name
  First_Name[0] = "N/A";       // Set first name
  Last_Name = new string[1];   // Allocate memory for last name
  Last_Name[0] = "N/A";        // Set last name
  Balance = 0;                 // Set balance to 0
  Account_Number = 0;          // Set account number to 0
  Account_Type = "N/A";        // Set account type
  Current_Year = 2014;         // Set current year to 2014
  Number_Of_Partners = 1;      // Set number of partners
  Broker_ID = 0;               // Sets no broker
  Investors_Portfolio =
      new Portfolio;  // Allocate memory for investors portfolio
}

Partnership::Partnership(int ID) {
  Account_Number = ID;        // Set Account number to ID
  Get_Partnership_Details();  // Call function
  Account_Type = "P";         // Set account type
  Current_Year = 2014;        // Set current year to 2014
  Investors_Portfolio =
      new Portfolio;  // Allocate memory for investors portfolio
  Logged_In = 1;      // User is now logged in
  Broker_ID = 0;      // Sets no broker
  Display_Options();
}

void Partnership::Get_Partnership_Details() {
  Set_Partners_Count();  // Set partners count
  Set_Partners_Names();  // Set partners names
}

void Partnership::Partnersip_Display_Results_Test() {
  for (int i = 0; i < Number_Of_Partners;
       i++)  // For loop from 0  to the number of partners
  {
    cout << "First name: " << First_Name[i] << " Last name: " << Last_Name[i]
         << endl;  // Output names of partners
  }
  cout << Number_Of_Partners << endl;  // Output number of partners
}

void Partnership::Set_Partners_Count() {
  ifstream Information;
  Information.open("Accounts.csv");  // Open Accounts.csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;  // Unable to open file
  }
  // Set temp variables
  string Temp_ID;
  int Int_Temp_ID;
  string Temp_Nothing;
  string Temp_Partner_Count;
  string line;
  while (getline(Information, line))  // While loop to find ID
  {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);  // convert Temp ID to int
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Partner_Count, ',');
    if (Int_Temp_ID == Account_Number)  // if ID is equal to account number set
                                        // number of partners
    {
      Number_Of_Partners =
          stoi(Temp_Partner_Count);  // Convert number of partners to int
      Information.close();
      break;
    }
  }
  Information.close();
}

void Partnership::Set_Partners_Names() {
  ifstream Information;
  Information.open("Accounts.csv");  // Open accounts.csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;  // file was unable to open
  }
  // set variables
  string Temp_ID;
  int Int_Temp_ID;
  string Temp_Nothing;
  string line;
  string Temp_First_Name;
  string Temp_Last_Name;
  First_Name = new string[Number_Of_Partners];  // Allocate memory for partners
                                                // first names
  Last_Name = new string[Number_Of_Partners];   // Allocate memory for partners
                                                // last names
  while (getline(Information, line))  // while loop to find Temporary ID
  {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    if (Int_Temp_ID ==
        Account_Number)  // If Temp ID equals the account number, set names.
    {
      for (int i = 0; i < Number_Of_Partners;
           i++)  // Loop through all the partners
      {
        getline(ss, Temp_First_Name, ',');
        getline(ss, Temp_Last_Name, ',');
        First_Name[i] = Temp_First_Name;  // Set first name
        Last_Name[i] = Temp_Last_Name;    // Set last name
      }
      Information.close();
      break;
    }
  }
  Information.close();
}

void Partnership::Print() {
  Investor::Print();  // Print constructor
  ofstream Printed_Portfolio;
  Printed_Portfolio.open(
      "Partnership Portfolio Report.csv");  // Open Partnership portfolio csv
  int Share_Count = Investors_Portfolio->Get_Share_Count();  // Get share count
  Printed_Portfolio << "Report for Partnership Investors" << endl;
  for (int i = 0; i < Number_Of_Partners;
       i++)  // For loop that will loop through the number of partners
  {
    Printed_Portfolio << "Partner Number: " << i + 1
                      << endl;  // Print partner number
    Printed_Portfolio << "\t First Name: " << First_Name[i]
                      << endl;  // Print first name
    Printed_Portfolio << "\t Last Name: " << Last_Name[i]
                      << endl;  // Print last name
  }
  for (int i = 0; i < Share_Count;
       i++)  // For loop will loop iterate all the shares
  {
    int Temp_Units = Investors_Portfolio->Units(i);  // Set temp units
    int Temp_Current_Price =
        Investors_Portfolio->Current_Price(i);  // Set temp current price
    int Temp_Previous_Price =
        Investors_Portfolio->Previous_Price(i);       // Set temp previous price
    string Temp_Name = Investors_Portfolio->Name(i);  // Set temp name
    Printed_Portfolio << "Share Number " << i + 1 << " - " << Temp_Name
                      << endl;  // Print share number
    Printed_Portfolio << "\t Units: " << Temp_Units << endl;  // Print units
    Printed_Portfolio << "\t Current Price: $" << Temp_Current_Price
                      << endl;  // Print current price
    Printed_Portfolio << "\t Previous Price: $" << Temp_Previous_Price
                      << endl;  // Print previous price
    Printed_Portfolio << "\t 12 Month Price Change: $"
                      << (Temp_Current_Price - Temp_Previous_Price) * Temp_Units
                      << endl;  // Print 12 month chanve
  }
  Printed_Portfolio << "Your Bank Balance is furthermore: $"
                    << Investors_Portfolio->Get_Cash()
                    << endl;  // Print balance
  Printed_Portfolio.close();
  cout << "Please find your report called \"Partnership Portfolio Report\" "
       << endl;  // Advises user where to find report
  this_thread::sleep_for(chrono::seconds(2));  // Display for 2 seconds
}
// Free up memory
Partnership::~Partnership() {
  delete[] First_Name;
  delete[] Last_Name;
  delete Investors_Portfolio;
}