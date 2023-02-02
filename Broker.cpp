#include "Broker.h"

#include <stdlib.h>
#include <string.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include "Company.h"
#include "Individual.h"
#include "Investor.h"
#include "Partnership.h"
#include "Trust.h"
#include "User.h"

using namespace std;

Broker::Broker() {
  Clients_ID = new int[1];          // allocate memory for clients ID
  Clients_ID[0] = 0;                // set Id equal to 0
  Account_Type = "B";               // sent account type to broker
  Account_Number = 0;               // set account number equal to 0
  Client_Count = 1;                 // set client count
  Commission = 0;                   // set commission
  Recommendations = new string[1];  // allocate memory for recommendations
  Recommendations[0] = "N/A";       // set recommendations
}

Broker::Broker(int ID) {
  Account_Number = ID;  // set account number to ID
  Account_Type = "B";   // set to broker type
  Get_Information();    // call get information
  Logged_In = 1;        // log in status equal to 1
  Display_Options();    // call display options
}

void Broker::Get_Information() {
  Set_Commission();  // Call the following functions, these are the functions
                     // the brokers use
  Set_Recommendations();
  Set_Clients_Count();
  Set_Clients();
}

void Broker::Set_Commission() {
  ifstream Information;              // file object
  Information.open("Accounts.csv");  // open accounts csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned "
         << endl;  // If statement checking if file can be opened, display this
                   // if it cant be
  }
  string Temp_ID;          // intialise temp variables
  int Int_Temp_ID;         // intialise temp variables
  string Temp_Nothing;     // intialise temp variables
  string Temp_Commission;  // intialise temp variables
  string line;             // intialise temp variables
  while (getline(Information, line)) {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Commission, ',');
    if (Int_Temp_ID ==
        Account_Number)  // if the temp Id is equal to the account number...
    {
      Commission =
          stoi(Temp_Commission);  // then set the commission to the temp
                                  // commission and convert to a int using stoi.
      Information.close();        // close object
      break;
    }
  }
  Information.close();  // close object
}

void Broker::Change_Commission(int Given_Commission) {
  this->Commission = Given_Commission;  // Change commission to new commission
}

int Broker::Get_Commission() {
  return Commission;  // Return broker commission
}

void Broker::Set_Recommendations() {
  ifstream Information;              // file object
  Information.open("Accounts.csv");  // Open accounts csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;  // file cannot be opened
  }
  string Temp_ID;                   // set temp variables
  int Int_Temp_ID;                  // set temp variables
  string Temp_Nothing;              // set temp variables
  string Temp_Recommendation;       // set temp variables
  Recommendations = new string[3];  // allocate memory for recommendations
  string line;                      // set temp variables
  while (getline(Information, line)) {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    if (Int_Temp_ID ==
        Account_Number)  // if the temp Id is equal to the account number...
    {
      for (int i = 0; i < 3;
           i++)  //...Create a for loop, loop through all the recommendations.
      {
        getline(ss, Temp_Recommendation, ',');
        Recommendations[i] = Temp_Recommendation;  // set the recommendations to
                                                   // the temp recommendations.
      }
      Information.close();
      break;
    }
  }
  Information.close();
}

void Broker::Set_Clients_Count() {
  ifstream Information;              // file object
  Information.open("Accounts.csv");  // open accounts csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;  // file can not be opened
  }
  string Temp_ID;            // set temp variables
  int Int_Temp_ID;           // set temp variables
  string Temp_Client_Count;  // set temp variables
  string Temp_Nothing;       // set temp variables
  string line;               // set temp variables
  while (getline(Information, line)) {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    if (Int_Temp_ID ==
        Account_Number)  // if temp id is equal to the account number...
    {
      for (int i = 0; i < 3;
           i++)  //...then create a for loop that loops through all the clients
      {
        getline(ss, Temp_Nothing, ',');
      }
      getline(ss, Temp_Client_Count, ',');
      Client_Count =
          stoi(Temp_Client_Count);  // Client count becomes the temp client
                                    // count. Converted from string to int with
                                    // the use of stoi
      Information.close();
      break;
    }
  }
  Information.close();
}

void Broker::Set_Clients() {
  ifstream Information;              // file object.
  Information.open("Accounts.csv");  // open accounts csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;  // file can not be opened.
  }
  string Temp_ID;                      // declare temp variables
  int Int_Temp_ID;                     // declare temp variables
  string Temp_Client_ID;               // declare temp variables
  Clients_ID = new int[Client_Count];  // allocate memory for client ID
  string Temp_Nothing;                 // declare temp variables
  string line;
  while (getline(Information, line)) {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Nothing, ',');
    if (Int_Temp_ID == Account_Number)  // If the Temp ID is equal to the
                                        // account number then...
    {
      for (int i = 0; i < 3; i++) {
        getline(ss, Temp_Nothing, ',');
      }
      getline(ss, Temp_Nothing, ',');
      for (int i = 0; i < Client_Count;
           i++)  // create a for loop that loops through the clients
      {
        getline(ss, Temp_Client_ID, ',');
        Clients_ID[i] =
            stoi(Temp_Client_ID);  // The client ID now equals the temp client
                                   // ID. COnverted from string to int via stoi
      }
      Information.close();
      break;
    }
  }
  Information.close();
}

void Broker::Broker_Display_Results_Test() {
  cout << "Commission: " << Commission
       << endl;  // display the commission the broker will take
  for (int i = 0; i < 3;
       i++)  // create a for loop that will loop through the recommendations
  {
    cout << Recommendations[i] << endl;  // display the recommendations
  }
  for (int i = 0; i < Client_Count; i++)  // loop through the clients
  {
    cout << Clients_ID[i] << endl;  // display the clients
  }
}

std::string *Broker::Get_Recommendations() {
  return Recommendations;  // point at the broker, return its recommendations
}

void Broker::Display_Options() {
  while (Logged_In == 1)  // while the user is logged in
  {
    system("Clear");  // clear terminal
    string Option;    // create option string
    cout << "Please select the number correlating to the function you wish to "
            "utilise: "
         << endl;
    cout << "1 - View Clients" << endl;     // display option
    cout << "2 - Replace Client " << endl;  // display option
    cout << "3 - Print Clients" << endl;    // display option
    cout << "0 - Log Out" << endl;          // display option
    cin >> Option;                          // take input of option
    while (Option != "0" && Option != "1" && Option != "2" && Option != "3") {
      system("Clear");  // while the valid is input, clear terminal and ask
                        // again
      cout << "You didnt use a valid number! Please try again! "
           << endl;                                // ask for valid output
      this_thread::sleep_for(chrono::seconds(1));  // display for 1 second
      system("Clear");                             // clear terminal
      cout << "Please select the number correlating to the function you wish "
              "to utilise: "
           << endl;
      cout << "1 - View Clients" << endl;     // display option
      cout << "2 - Replace Client " << endl;  // display option
      cout << "3 - Print Clients" << endl;    // display option
      cout << "0 - Log Out" << endl;          // display option
      cin >> Option;                          // take input
    }
    if (Option == "0") {
      system("Clear");  // clear terminal
      Logged_In = 0;    // logout user
    } else if (Option == "1") {
      system("Clear");  // clear terminal
      Print_Clients();  // call print clients
    } else if (Option == "2") {
      system("Clear");  // clear terminal
      Swap_Clients();   // call swap clients

    } else if (Option == "3") {
      system("Clear");  // clear terminal
      Print_To_CSV();   // print csv
    }
  }
}

void Broker::Print_Clients() {
  for (int i = 0; i < Client_Count; i++)  // loop through clients
  {
    if (Clients_ID[i] != 0) {
      int Temp_ID_To_Search =
          Clients_ID[i];  // temp id is equal to clients ID at current iteration
      ifstream Information;              // file object
      Information.open("Accounts.csv");  // open accounts csv

      if (!Information.is_open()) {
        cout << "File wasnt found and openned " << endl;  // can not open file
      }
      string Temp_Recommendation[3] = {
          "N/A"};                 // create string array of recommendations
      string Temp_ID;             // create temp variable
      int Int_Temp_ID;            // create temp variable
      string Temp_Nothing;        // create temp variable
      string line;                // create temp variable
      string Temp_First_Name;     // create temp variable
      string Temp_Type;           // create temp variable
      string Temp_Partner_Count;  // create temp variable
      string Temp_Bene_Count;     // create temp variable
      string Temp_Trustee_Count;  // create temp variable
      string Temp_Dir_Count;      // create temp variable
      while (getline(Information,
                     line))  // while loop, keeps looping until ID is mathched
      {
        stringstream ss(line);
        getline(ss, Temp_ID, ',');
        Int_Temp_ID = stoi(Temp_ID);
        getline(ss, Temp_Nothing, ',');
        getline(ss, Temp_Type, ',');
        if (Int_Temp_ID == Temp_ID_To_Search)  // if temp ID is equal to Temp ID
                                               // to search continute to type
        {
          if (Temp_Type ==
              "B")  // if temp type is broker then output the following:
          {
            cout << "Client Number: " << i + 1
                 << endl;  // display client number
            cout << "Client ID: " << Temp_ID_To_Search
                 << endl;  // display client ID
            cout << "\t You have a broker saved in as a client and thus this "
                    "information cant be displayed"
                 << endl;
            this_thread::sleep_for(
                chrono::seconds(1));    // disappear after 1 second
          } else if (Temp_Type == "I")  // if an investor output the following
          {
            cout << "Client Number: " << i + 1 << endl;  // client number
            cout << "Client ID: " << Temp_ID_To_Search << endl;  // client ID
            cout << "\t Client Type: Invdividual" << endl;       // client type
            cout << "\t Client ID: " << Int_Temp_ID << endl;     // client ID
            getline(ss, Temp_Nothing, ',');
            cout << "\t First Name: " << Temp_Nothing
                 << endl;  // display first name
            getline(ss, Temp_Nothing, ',');
            cout << "\t Last Name: " << Temp_Nothing << endl;  // display last
                                                               // name
          } else if (Temp_Type == "P")                         // partnership
          {
            cout << "Client Number: " << i + 1
                 << endl;  // display client number
            cout << "Client ID: " << Temp_ID_To_Search
                 << endl;                                   // display client ID
            cout << "\t Client Type: Partnership" << endl;  // client type
            cout << "\t Client ID: " << Int_Temp_ID
                 << endl;  // display client ID
            getline(ss, Temp_Partner_Count, ',');
            for (int j = 0; j < stoi(Temp_Partner_Count);
                 j++)  // loop through partners, convert string to int using
                       // stoi
            {
              cout << "\t Partner Number: " << j + 1
                   << endl;  // display partner number
              getline(ss, Temp_Nothing, ',');
              cout << "\t\t First Name: " << Temp_Nothing
                   << endl;  // display first name
              getline(ss, Temp_Nothing, ',');
              cout << "\t\t Last Name: " << Temp_Nothing
                   << endl;  // display last name
            }
          } else if (Temp_Type == "T")  // trust
          {
            cout << "Client Number: " << i + 1 << endl;  // client number
            cout << "Client ID: " << Temp_ID_To_Search
                 << endl;                             // display client ID
            cout << "\t Client Type: Trust" << endl;  // type
            cout << "\t Client ID: " << Int_Temp_ID
                 << endl;  // display client ID
            getline(ss, Temp_Bene_Count, ',');
            for (int j = 0; j < stoi(Temp_Bene_Count);
                 j++)  // loop through beneficiaries
            {
              cout << "\t Beneficiary Number: " << j + 1
                   << endl;  // display beneficiary number
              getline(ss, Temp_Nothing, ',');
              cout << "\t\t First Name: " << Temp_Nothing
                   << endl;  // display first name
              getline(ss, Temp_Nothing, ',');
              cout << "\t\t Last Name: " << Temp_Nothing
                   << endl;  // display last name
            }
            getline(ss, Temp_Trustee_Count, ',');
            for (int j = 0; j < stoi(Temp_Trustee_Count);
                 j++)  // loop through trustees
            {
              cout << "Trustee Number: " << j + 1
                   << endl;  // display trustee number
              getline(ss, Temp_Nothing, ',');
              cout << "\t\t First Name: " << Temp_Nothing
                   << endl;  // display first name
              getline(ss, Temp_Nothing, ',');
              cout << "\t\t Last Name: " << Temp_Nothing
                   << endl;  // display last name
            }
          } else if (Temp_Type == "C")  // company
          {
            cout << "Client Number: " << i + 1
                 << endl;  // display client number
            cout << "Client ID: " << Temp_ID_To_Search
                 << endl;  // display client id
            cout << "\t Client Type: Company" << endl;
            cout << "\t Client ID: " << Int_Temp_ID
                 << endl;  // display client id
            getline(ss, Temp_Nothing, ',');
            cout << "\t Company Name: " << Temp_Nothing
                 << endl;  // display company name
            getline(ss, Temp_Dir_Count, ',');
            for (int j = 0; j < stoi(Temp_Dir_Count);
                 j++)  // loop through the directors
            {
              cout << "\t Director Number: " << j + 1
                   << endl;  // display director number
              getline(ss, Temp_Nothing, ',');
              cout << "\t\t First Name: " << Temp_Nothing
                   << endl;  // display first name
              getline(ss, Temp_Nothing, ',');
              cout << "\t\t Last Name: " << Temp_Nothing
                   << endl;  // display last name
            }
          }
          Information.close();
          break;
        }
      }
      Information.close();
    }
  }
  cout << "Press enter to return to main page" << endl;
  cin.ignore();
  cin.get();  // this allows for users to press enter to return
}

bool Broker::Check_Remove_Choice(int Choice) {
  for (int i = 0; i < Client_Count; i++)  // loop through clients
  {
    if (Clients_ID[i] == Choice)  // if client ID equals the choice, return true
    {
      return true;
    }
  }
  return false;
}

bool Broker::Check_Add_Choice(int Choice) {
  ifstream Information;              // file object
  Information.open("Accounts.csv");  // open accounts csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;  // file can not open
  }
  string Temp_ID;  // create temp variable
  string line;     // create temp variable
  while (getline(Information, line)) {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    if (Choice ==
        stoi(Temp_ID))  // if choice is equal to the temp ID return true.
    {
      Information.close();
      return true;  // return true
    }
  }
  Information.close();
  return false;  // return false
}

void Broker::Replace_ID(int Remove_ID, int Replace_ID) {
  for (int i = 0; i < Client_Count; i++)  // loop through clients
  {
    if (Clients_ID[i] == Remove_ID)  // if clients equal to remove ID
    {
      Clients_ID[i] = Replace_ID;  // client ID is equal to the replacement
      cout << "You Replaced That Client" << endl;  // output for 1 second
      this_thread::sleep_for(chrono::seconds(1));
    }
  }
}

void Broker::Swap_Clients() {
  int Remove_Client;  // create variable of client being removed
  int Add_Client;     // create variable of client being added
  cout << "Which client would you like to remove: ";
  cin >> Remove_Client;  // take input if the client being removed
  while (cin.fail()) {
    cout << "An Error Occured! Which client would you like to remove: ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> Remove_Client;
  }
  if (Check_Remove_Choice(
          Remove_Client))  // if statement to check if the removed client and
                           // choice are the same
  {
    cout << "What client would you like to add: ";
    cin >> Add_Client;  // take input of the client beinf added
    while (cin.fail()) {
      cout << "An Error Occured! Which client would you like to add: ";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> Add_Client;
    }
    if (Check_Add_Choice(Add_Client))  // add client to spot
    {
      if (!Check_Remove_Choice(Add_Client))  // if not the same choice
      {
        Replace_ID(Remove_Client, Add_Client);  // swap the id of the removed
                                                // client ID and added client
        cout << "These clients have been swapped! "
             << endl;  // display for a second
        this_thread::sleep_for(chrono::seconds(1));
      } else {
        cout << "You already have this client! "
             << endl;  // display for 1 second
        this_thread::sleep_for(chrono::seconds(1));
      }
    } else {
      cout << "This client doesn't exist! Returning to main menu! "
           << endl;  // display for 1 second
      this_thread::sleep_for(chrono::seconds(1));
    }
  } else {
    cout << "You dont have this client! Returning to main menu! "
         << endl;  // display for 1 second
    this_thread::sleep_for(chrono::seconds(1));
  }
}

void Broker::Print_To_CSV() {
  cout << "Your report has been printed" << endl;  // display text
  cout << "Please find it under the name \"Broker Client Report\""
       << endl;                                     // displayed in csv
  this_thread::sleep_for(chrono::seconds(2));       // display for 2 seconds
  ofstream Printed_Client;                          // file object
  Printed_Client.open("Broker Client Report.csv");  // open broker client report
  Printed_Client << "Report for Brokers" << endl;
  for (int i = 0; i < Client_Count; i++)  // loop through clients
  {
    if (Clients_ID[i] != 0) {
      Printed_Client << "Client Number: " << i + 1 << endl;  // print client
                                                             // number
      ifstream Information;                                  // file object
      Information.open("Accounts.csv");  // open accounts csv
      string Temp_ID;                    // create temp variable
      int Int_Temp_ID;                   // create temp variable
      string Temp_Nothing;               // create temp variable
      string Temp_Partner_Count;         // create temp variable
      string Temp_Bene_Count;            // create temp variable
      string Temp_Trustee_Count;         // create temp variable
      string Temp_Dir_Count;             // create temp variable
      string Account_Types;              // create variable
      string line;                       // create variable
      while (getline(Information, line)) {
        stringstream ss(line);
        getline(ss, Temp_ID, ',');
        Int_Temp_ID = stoi(Temp_ID);  // int temp ID is equal to the string temp
                                      // id. Convert using stoi.
        if (Int_Temp_ID ==
            Clients_ID[i])  // if temp ID is equal to the clients ID and...
        {
          getline(ss, Temp_Nothing, ',');
          getline(ss, Account_Types, ',');
          if (Account_Types == "B")  //...the account is a broker then print the
                                     // ID and following message
          {
            Printed_Client << "\t ID: " << Int_Temp_ID << endl;  // print ID
            Printed_Client << "\t This is a broker and as such no information "
                              "can be displayed"
                           << endl;
          } else if (Account_Types == "I")  // Investor
          {
            Printed_Client << "\t Investor Type: Individual"
                           << endl;  // display type
            Printed_Client << "\t Investor ID: " << Int_Temp_ID
                           << endl;  // display ID
            getline(ss, Temp_Nothing, ',');
            Printed_Client << "\t\t First Name: " << Temp_Nothing
                           << endl;  // display first name
            getline(ss, Temp_Nothing, ',');
            Printed_Client << "\t\t Last Name: " << Temp_Nothing
                           << endl;         // display last name
          } else if (Account_Types == "P")  // Partnership
          {
            Printed_Client << "\t Investor Type: Partnership"
                           << endl;  // display type
            Printed_Client << "\t Investor ID: " << Int_Temp_ID
                           << endl;  // display investor ID
            getline(ss, Temp_Partner_Count, ',');
            for (int i = 0; i < stoi(Temp_Partner_Count);
                 i++)  // loop through partners
            {
              Printed_Client << "\t\t Partner Number: " << i + 1
                             << endl;  // display partner number
              getline(ss, Temp_Nothing, ',');
              Printed_Client << "\t\t\t First Name: " << Temp_Nothing
                             << endl;  // display first name
              getline(ss, Temp_Nothing, ',');
              Printed_Client << "\t\t\t Last Name: " << Temp_Nothing
                             << endl;  // display last name
            }
          } else if (Account_Types == "T")  // trust
          {
            Printed_Client << "\t Investor Type: Trust"
                           << endl;  // display type
            Printed_Client << "\t Investor ID: " << Int_Temp_ID
                           << endl;  // display ID
            getline(ss, Temp_Trustee_Count, ',');
            for (int i = 0; i < stoi(Temp_Trustee_Count);
                 i++)  // loop through trustees
            {
              Printed_Client << "\t\t Trustee Number: " << i + 1
                             << endl;  // display trustees number
              getline(ss, Temp_Nothing, ',');
              Printed_Client << "\t\t\t First Name: " << Temp_Nothing
                             << endl;  // display first name
              getline(ss, Temp_Nothing, ',');
              Printed_Client << "\t\t\t Last Name: " << Temp_Nothing
                             << endl;  // display last name
            }
            getline(ss, Temp_Bene_Count, ',');
            for (int i = 0; i < stoi(Temp_Bene_Count);
                 i++)  // loop through beneficiaries
            {
              Printed_Client << "\t\t Beneficiary Number: " << i + 1
                             << endl;  // display beneficiary number
              getline(ss, Temp_Nothing, ',');
              Printed_Client << "\t\t\t First Name: " << Temp_Nothing
                             << endl;  // display first name
              getline(ss, Temp_Nothing, ',');
              Printed_Client << "\t\t\t Last Name: " << Temp_Nothing
                             << endl;  // display last name
            }
          } else if (Account_Types == "C")  // company
          {
            Printed_Client << "\t Investor Type: Company" << endl;  // display
                                                                    // type
            Printed_Client << "\t Investor ID: " << Int_Temp_ID
                           << endl;  // display ID
            getline(ss, Temp_Nothing, ',');
            Printed_Client << "\t Company Name: " << Temp_Nothing
                           << endl;  // display company name
            getline(ss, Temp_Dir_Count, ',');
            for (int i = 0; i < stoi(Temp_Dir_Count);
                 i++)  // loop through directors
            {
              Printed_Client << "\t\t Director Number: " << i + 1
                             << endl;  // display director number
              getline(ss, Temp_Nothing, ',');
              Printed_Client << "\t\t\t First Name: " << Temp_Nothing
                             << endl;  // display first name
              getline(ss, Temp_Nothing, ',');
              Printed_Client << "\t\t\t Last Name: " << Temp_Nothing
                             << endl;  // display last name
            }
          }
        }
      }
      Information.close();
    }
  }
  Printed_Client.close();
}

Broker::~Broker()  // free up memory
{
  delete[] Recommendations;
  delete[] Clients_ID;
}