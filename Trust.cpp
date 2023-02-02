#include "Trust.h"

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

Trust::Trust() {
  Bene_First_Name =
      new string[1];           // Allocate memory for Beneficiaries first name
  Bene_First_Name[0] = "N/A";  // Set Beneficiaries first name
  Bene_Last_Name = new string[1];      // Allocate memory for Beneficiaries last
                                       // name
  Bene_Last_Name[0] = "N/A";           // Set Beneficiaries last name
  Trustee_First_Name = new string[1];  // Allocate memory for Trustees first
                                       // name
  Trustee_First_Name[0] = "N/A";       // Set Trustees first name
  Trustee_Last_Name = new string[1];   // Allocate memory for Trustees last name
  Trustee_Last_Name[0] = "N/A";        // set Trustees last name
  Balance = 0;                         // Set balance to 0
  Account_Number = 0;                  // Set Account number to 0
  Account_Type = "N/A";                // Set Account type
  Current_Year = 2014;                 // Set Current year to 2014
  Number_Of_Trustee = 1;               // Set number of Trustees
  Number_Of_Bene = 1;                  // Set number of Beneficiaries
  Investors_Portfolio = new Portfolio;
  Broker_ID = 0;  // Setting no broker
}

Trust::Trust(int ID) {
  Account_Number = ID;  // Set account number = to ID
  Get_Trust_Details();  // Call Get trust details function
  Account_Type = "T";   // Set Account type
  Current_Year = 2014;  // Set Current year to 2014
  Investors_Portfolio = new Portfolio;
  Logged_In = 1;
  Broker_ID = 0;      // Setting no broker
  Display_Options();  // call display options function
}
// This Function will set the names involved in the trust and also get the
// number of beneficiaries involved.
void Trust::Get_Trust_Details() {
  Set_Bene_Count();
  Set_Names();
}
void Trust::Print_Trust_Portfolio()  //////////////////////////////////////////
{}
// For loop that will loop through each Beneficiary and display their first and
// last name
void Trust::Trust_Display_Results_Test() {
  for (int i = 0; i < Number_Of_Bene; i++) {
    cout << "First name: " << Bene_First_Name[i]
         << " Last name: " << Bene_Last_Name[i] << endl;
  }
  // For loop that will loop through each Trustee and display their first and
  // last name
  for (int i = 0; i < Number_Of_Trustee; i++) {
    cout << "First name: " << Trustee_First_Name[i]
         << " Last name: " << Trustee_Last_Name[i] << endl;
  }
  // This will Display the number of Beneficiaries and Trustees
  cout << "Bene count: " << Number_Of_Bene << endl;
  cout << "Trustee count: " << Number_Of_Trustee << endl;
}

void Trust::Set_Bene_Count() {
  ifstream Information;
  Information.open("Accounts.csv");  // Account csv file that will be opened

  if (!Information.is_open()) {  // Display if file was not found
    cout << "File wasnt found and opened " << endl;
  }
  // Set variables
  string Temp_ID;
  int Int_Temp_ID;
  string Temp_Nothing;
  string Temp_Bene_Count;
  string line;
  // While loop that will keep looping until temp id is received
  while (getline(Information, line)) {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Bene_Count, ',');
    // If temp ID is equal to Account Number, convert the Beneficiary count
    // using stoi and set number of beneficiaries variable equal to it
    if (Int_Temp_ID == Account_Number) {
      Number_Of_Bene = stoi(Temp_Bene_Count);
      Information.close();
      break;
    }
  }
  Information.close();
}

void Trust::Set_Names() {
  ifstream Information;
  Information.open("Accounts.csv");  // Account csv file that will be opened

  if (!Information.is_open()) {
    cout << "File wasnt found and openned "
         << endl;  // Display if file was not found
  }
  // Set Variables and Allocate memory
  string Temp_ID;
  int Int_Temp_ID;
  string Temp_Nothing;
  string line;
  string Temp_Trustee_Count;
  string Bene_Temp_First_Name;
  string Bene_Temp_Last_Name;
  string Trustee_Temp_First_Name;
  string Trustee_Temp_Last_Name;
  Bene_First_Name = new string[Number_Of_Bene];
  Bene_Last_Name = new string[Number_Of_Bene];
  Trustee_First_Name = new string[Number_Of_Bene];
  Trustee_Last_Name = new string[Number_Of_Bene];
  // While loop that will keep looping until temp id is received
  while (getline(Information, line)) {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    // If statement to confirm Temp ID found
    if (Int_Temp_ID == Account_Number) {
      // For loop that will loop through all the names until the number of
      // beneficiaries is reached
      for (int i = 0; i < Number_Of_Bene; i++) {
        // Set beneficiaries names
        getline(ss, Bene_Temp_First_Name, ',');
        getline(ss, Bene_Temp_Last_Name, ',');
        Bene_First_Name[i] = Bene_Temp_First_Name;
        Bene_Last_Name[i] = Bene_Temp_Last_Name;
      }
      // Convert number of trustees to a int using stoi and set it.
      getline(ss, Temp_Trustee_Count, ',');
      this->Number_Of_Trustee = stoi(Temp_Trustee_Count);
      // For loop from 0 to the number of trustees
      for (int i = 0; i < Number_Of_Trustee; i++) {
        // Set the trustees first names and last names
        getline(ss, Trustee_Temp_First_Name, ',');
        getline(ss, Trustee_Temp_Last_Name, ',');
        Trustee_First_Name[i] = Trustee_Temp_First_Name;
        Trustee_Last_Name[i] = Trustee_Temp_Last_Name;
      }
      Information.close();
      break;
    }
  }
  Information.close();
}

void Trust::Print() {
  // Call print constructor
  Investor::Print();
  ofstream Printed_Portfolio;
  // Open portfolio, get share count and display the portfolio
  Printed_Portfolio.open("Trust Portfolio Report.csv");
  int Share_Count = Investors_Portfolio->Get_Share_Count();
  Printed_Portfolio << "Report for Trust Investors" << endl;
  // For loop from 0 to the number of trustees that will print their names
  for (int i = 0; i < Number_Of_Trustee; i++) {
    Printed_Portfolio << "Trustee Number: " << i + 1 << endl;
    Printed_Portfolio << "\t First Name: " << Trustee_First_Name[i] << endl;
    Printed_Portfolio << "\t Last Name: " << Trustee_Last_Name[i] << endl;
  }
  // For loop from 0 to the number of Beneficiaries that will print their names
  for (int i = 0; i < Number_Of_Bene; i++) {
    Printed_Portfolio << "Beneificary Number: " << i + 1 << endl;
    Printed_Portfolio << "\t First Name: " << Bene_First_Name[i] << endl;
    Printed_Portfolio << "\t Last Name: " << Bene_Last_Name[i] << endl;
  }
  // For loop that will loop from 0 to the amount of shares.
  for (int i = 0; i < Share_Count; i++) {
    // Get the units, current price, previous price and name
    int Temp_Units = Investors_Portfolio->Units(i);
    int Temp_Current_Price = Investors_Portfolio->Current_Price(i);
    int Temp_Previous_Price = Investors_Portfolio->Previous_Price(i);
    string Temp_Name = Investors_Portfolio->Name(i);
    // Print the share number, units, current price, previous price and 12 month
    // price change.
    Printed_Portfolio << "Share Number " << i + 1 << " - " << Temp_Name << endl;
    Printed_Portfolio << "\t Units: " << Temp_Units << endl;
    Printed_Portfolio << "\t Current Price: $" << Temp_Current_Price << endl;
    Printed_Portfolio << "\t Previous Price: $" << Temp_Previous_Price << endl;
    Printed_Portfolio << "\t 12 Month Price Change: $"
                      << (Temp_Current_Price - Temp_Previous_Price) * Temp_Units
                      << endl;
  }
  // Print current balance
  Printed_Portfolio << "Your Bank Balance is furthermore: $"
                    << Investors_Portfolio->Get_Cash() << endl;
  Printed_Portfolio.close();
  cout << "Please find your report called \"Trust Portfolio Report\" "
       << endl;  // Directing the user to Trust Portfolio Report.csv
  this_thread::sleep_for(chrono::seconds(2));
}

// Destructor to free up memory
Trust::~Trust() {
  delete[] Bene_First_Name;
  delete[] Bene_Last_Name;
  delete[] Trustee_First_Name;
  delete[] Trustee_Last_Name;
  delete Investors_Portfolio;
}