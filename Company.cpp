#include "Company.h"

#include <stdlib.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "Broker.h"
#include "Investor.h"
#include "Portfolio.h"
#include "User.h"

using namespace std;

Company::Company() {
  Director_First_Name = new string[1];  // Allocate memory
  Director_First_Name[0] = "N/A";       // Set Director name = NA
  Director_Last_Name = new string[1];   // Allocate memory
  Director_Last_Name[0] = "N/A";        // Set Director name = NA
  Registered_Name = "N/A";              // Set Registered name = NA
  Balance = 0;                          // Intialise balance to 0
  Account_Number = 0;                   // Intialise Account Number to 0
  Account_Type = "N/A";                 // Intialise type to N/A
  Current_Year = 2014;                  // Set current year to 2014
  Number_Of_Directors = 1;              // Set number of directors to 1
  Investors_Portfolio = new Portfolio;  // allocate memory
  Broker_ID = 0;                        // Sets no broker
}

Company::Company(int ID) {
  Account_Number = ID;                  // Account number = ID
  Get_Company_Details();                // Call function
  Account_Type = "C";                   // Account type is a Company
  Current_Year = 2014;                  // Set current year to 0
  Investors_Portfolio = new Portfolio;  // Allocate memory
  Logged_In = 1;                        // log in status is 1
  Display_Options();                    // Display options 1-9
  Broker_ID = 0;                        // Sets no broker
}

void Company::Get_Company_Details() {
  Set_Director_Count();  // Amount of directors
  Set_Names();           // Names of directors
}

void Company::Company_Display_Results_Test() {
  cout << "Company name is: " << Registered_Name << endl;  // Output Company
                                                           // name
  for (int i = 0; i < Number_Of_Directors; i++)  // Loop through directors
  {
    cout << "First name: " << Director_First_Name[i]
         << " Last name: " << Director_Last_Name[i]
         << endl;  // Outputs directors names
  }
  cout << Number_Of_Directors << endl;  // Output number of directors
}

void Company::Set_Director_Count() {
  ifstream Information;              // File object
  Information.open("Accounts.csv");  // Open Accounts csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;  // Unable to open csv
  }
  string Temp_ID;              // Set temp id
  int Int_Temp_ID;             // Set int temp ID
  string Temp_Nothing;         // Set temp nothing
  string Temp_Director_Count;  // Set temp Director count
  string line;                 // String line
  while (getline(Information, line)) {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Director_Count, ',');
    if (Int_Temp_ID ==
        Account_Number)  // If Temp Id is equal to account number then..
    {
      Number_Of_Directors = stoi(
          Temp_Director_Count);  //...THe number of directors is equal to the
                                 // temp director count. Stoi converts to int
      Information.close();
      break;
    }
  }
  Information.close();
}

void Company::Set_Names() {
  ifstream Information;              // File object
  Information.open("Accounts.csv");  // Open accounts csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;  // Unable to open file
  }
  string Temp_ID;          // Intialise temp ID
  int Int_Temp_ID;         // Intialise temp ID
  string Temp_Nothing;     // Intialise Nothing
  string Temp_Name;        // Intialise temp Name
  string Temp_First_Name;  // Intialise First name
  string Temp_Last_Name;   // Intialise Last name
  string line;             // Intialise line
  Director_First_Name = new string[Number_Of_Directors];  // Allocate memory
  Director_Last_Name = new string[Number_Of_Directors];   // Allocate memory
  while (getline(Information,
                 line))  // While loop until Temp ID is equal to account number
  {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Name, ',');
    getline(ss, Temp_Nothing, ',');
    if (Int_Temp_ID == Account_Number) {
      Registered_Name = Temp_Name;  // Registered name is equal to temp name
      for (int i = 0; i < Number_Of_Directors; i++)  // loop through directors
      {
        getline(ss, Temp_First_Name, ',');
        getline(ss, Temp_Last_Name, ',');
        Director_First_Name[i] =
            Temp_First_Name;  // Set first name to temp first name
        Director_Last_Name[i] =
            Temp_Last_Name;  // Set last name to temp last name
      }
      Information.close();
      break;
    }
  }
  Information.close();
}

void Company::Print() {
  Investor::Print();           // Print constructor
  ofstream Printed_Portfolio;  // PrintedPortfolio obj
  Printed_Portfolio.open(
      "Company Portfolio Report.csv");  // open Company Portfolio csv
  int Share_Count =
      Investors_Portfolio->Get_Share_Count();  // get share count from portfolio
  Printed_Portfolio << "Report for Company Investors" << endl;
  Printed_Portfolio << "Company Name: " << Registered_Name << endl;
  for (int i = 0; i < Number_Of_Directors; i++)  // Loop through directors
  {
    Printed_Portfolio << "Director Number: " << i + 1
                      << endl;  // Display director number
    Printed_Portfolio << "\t First Name: " << Director_First_Name[i]
                      << endl;  // Display director name
    Printed_Portfolio << "\t Last Name: " << Director_Last_Name[i]
                      << endl;  // Display director name
  }
  for (int i = 0; i < Share_Count; i++)  // loop through shares
  {
    int Temp_Units =
        Investors_Portfolio->Units(i);  // Set temp units to portfolio units
    int Temp_Current_Price = Investors_Portfolio->Current_Price(
        i);  // Set temp current price to portfolio current price
    int Temp_Previous_Price = Investors_Portfolio->Previous_Price(
        i);  // Set temp previous price to portfolio previous price
    string Temp_Name = Investors_Portfolio->Name(
        i);  // Set temp name to current name from portfolio
    Printed_Portfolio << "Share Number " << i + 1 << " - " << Temp_Name
                      << endl;  // print share number
    Printed_Portfolio << "\t Units: " << Temp_Units << endl;  // Print units
    Printed_Portfolio << "\t Current Price: $" << Temp_Current_Price
                      << endl;  // Prints current prices
    Printed_Portfolio << "\t Previous Price: $" << Temp_Previous_Price
                      << endl;  // Prints previous price
    Printed_Portfolio << "\t 12 Month Price Change: $"
                      << (Temp_Current_Price - Temp_Previous_Price) * Temp_Units
                      << endl;  // prints 12 month change
  }
  Printed_Portfolio << "Your Bank Balance is furthermore: $"
                    << Investors_Portfolio->Get_Cash()
                    << endl;  // print balance
  Printed_Portfolio.close();
  cout << "Please find your report called \"Company Portfolio Report\" "
       << endl;  // Find it in company portfolio csv
  this_thread::sleep_for(chrono::seconds(2));  // display for two seconds
}
// Free up memory
Company::~Company() {
  delete[] Director_First_Name;
  delete[] Director_Last_Name;
  delete Investors_Portfolio;
}