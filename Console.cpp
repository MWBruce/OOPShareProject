#include "Console.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

using namespace std;

Console::Console() {
  Logged_In_Status = 1;  // 1 means the user is logged on, 0 means they are not
  Welcome_Message();     // call welcome message function
}

void Console::Welcome_Message() {
  system("Clear");  // Clears terminal
  cout << " .----------------.  .----------------.  .----------------.  "
          ".----------------.  .----------------.  .----------------.  "
          ".----------------.  "
       << endl;
  cout << "| .--------------. || .--------------. || .--------------. || "
          ".--------------. || .--------------. || .--------------. || "
          ".--------------. | "
       << endl;
  cout << "| | _____  _____ | || |  _________   | || |   _____      | || |     "
          "______   | || |     ____     | || | ____    ____ | || |  _________  "
          " | | "
       << endl;
  cout << "| ||_   _||_   _|| || | |_   ___  |  | || |  |_   _|     | || |   "
          ".' ___  |  | || |   .'    `.   | || ||_   \\  /   _|| || | |_   ___ "
          " |  | | "
       << endl;
  cout << "| |  | | /\\ | |  | || |   | |_  \\_|  | || |    | |       | || |  "
          "/ .'   \\_|  | || |  /  .--.  \\  | || |  |   \\/   |  | || |   | "
          "|_  \\_|  | | "
       << endl;
  cout << "| |  | |/  \\| |  | || |   |  _|  _   | || |    | |   _   | || |  | "
          "|         | || |  | |    | |  | || |  | |\\  /| |  | || |   |  _|  "
          "_   | |  "
       << endl;
  cout << "| |  |   /\\   |  | || |  _| |___/ |  | || |   _| |__/ |  | || |  "
          "\\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\/_| |_ | || |  _| "
          "|___/ |  | | "
       << endl;
  cout << "| |  |__/  \\__|  | || | |_________|  | || |  |________|  | || |   "
          "`._____.'  | || |   `.____.'   | || ||_____||_____|| || | "
          "|_________|  | | "
       << endl;
  cout << "| |              | || |              | || |              | || |     "
          "         | || |              | || |              | || |             "
          " | |  "
       << endl;
  cout << "| '--------------' || '--------------' || '--------------' || "
          "'--------------' || '--------------' || '--------------' || "
          "'--------------' |  "
       << endl;
  cout << " '----------------'  '----------------'  '----------------'  "
          "'----------------'  '----------------'  '----------------'  "
          "'----------------'   "
       << endl
       << endl;  // Output welcome message
  this_thread::sleep_for(chrono::seconds(2));
  system("Clear");  // Clears terminal
  cout << "Loading." << endl;
  this_thread::sleep_for(chrono::seconds(1));
  system("Clear");  // Clears terminal
  cout << "Loading.." << endl;
  this_thread::sleep_for(chrono::seconds(1));
  system("Clear");  // Clears terminal
  cout << "Loading..." << endl;
  this_thread::sleep_for(chrono::seconds(1));
  system("Clear");                                   // Clears terminal
  string Confirmation = "";                          // Initialises confirmation
  cout << "Do you already have an account? (Y/N) ";  // Requests input from user
                                                     // clarrifying if user has
                                                     // an existing account
  cin >> Confirmation;
  while (Confirmation != "Y" && Confirmation != "y" && Confirmation != "n" &&
         Confirmation != "N")  // Confirms valid entry from user.
  {
    cout << "You entered an invalid input! Do you already have an account? "
            "(Y/N) ";     // Requests input from user clarrifying if user has an
                          // existing account
    cin >> Confirmation;  // Takes inputs from user
  }
  if (Confirmation == "Y" || Confirmation == "y") {
    Existing_User = 1;  // They are a user
  } else {
    Existing_User = 0;  // They are not a user
  }
}

int Console::Get_Existing_User() {
  return Existing_User;  // return Existing_User;
}

int Console::Login() {  // intialise ID and Password
  string Given_ID;
  string Given_Password;
  cout << "Please provide your ID: ";
  cin >> Given_ID;  // Takes input from user for ID
  cout << "Please provide your Password: ";
  cin >> Given_Password;              // Takes input from user for password
  ifstream AccountsList;              // File object
  AccountsList.open("Accounts.csv");  // Open Accounts csv
  if (!AccountsList.is_open()) {
    cout << "File Failed To Open" << endl;  // failed to open
    Log_Out();                              // Call logout function
  }
  string Temp_ID;  // intialise temp variables
  string Temp_Password;
  string Temp_Type;
  string Line;
  while (getline(
      AccountsList,
      Line))  // while loop that keeps looping until ID and Password are given
  {
    stringstream ss(Line);
    getline(ss, Temp_ID, ',');
    getline(ss, Temp_Password, ',');
    getline(ss, Temp_Type, ',');
    if (Temp_ID == Given_ID && Temp_Password == Given_Password) {
      if (Temp_Type == "B")  // User is a Broker
      {
        User_Type = 0;
      } else if (Temp_Type == "I")  // User is an Individual
      {
        User_Type = 1;
      } else if (Temp_Type == "P")  // User is a partnership
      {
        User_Type = 2;
      } else if (Temp_Type == "T")  // User is a trust
      {
        User_Type = 3;
      } else if (Temp_Type == "C")  // User is a company
      {
        User_Type = 4;
      }

      AccountsList.close();   // Call close
      return stoi(Given_ID);  // stoi converts given ID to an int
    }
  }
  AccountsList.close();  // call close function
  Log_Out();             // call logout function
  return -1;
}

int Console::Create_Account() {
  string Account_Type;  // intialise account type as a string
  int Account_Number;   // intialise account number as an int
  system("Clear");      // clear terminal
  cout << "What type of user are you?" << endl;
  cout << "1 - Broker" << endl;
  cout << "2 - Investor" << endl;
  cin >> Account_Type;  // Takes input from user
  while (Account_Type != "1" &&
         Account_Type != "2")  // Input must be 1 or 2, or will be asked again
  {
    cout << "You Entered an invalid input! Please Try Again!" << endl;
    cout << "What type of user are you? ";
    cout << "1 - Broker" << endl;
    cout << "2 - Investor" << endl;
    cin >> Account_Type;  // take input from user about user type
  }
  if (Account_Type == "1")  // input 1 creates a broker user
  {
    Account_Number =
        Create_Broker();  // Account number equals the create Broker call.
    this->User_Type = 0;
  } else {
    string Investor_Type;  // Intialise investor type string
    system("Clear");       // clear terminal
    cout << "Please select the number associated with the entity type you are: "
         << endl;  // Output options
    cout << "1 - Individual" << endl;
    cout << "2 - Partnership" << endl;
    cout << "3 - Trust" << endl;
    cout << "4 - Company" << endl;
    cin >> Investor_Type;  // Takes input from user
    while (Investor_Type != "1" && Investor_Type != "2" &&
           Investor_Type != "3" &&
           Investor_Type != "4")  // If input is not 1,2,3,4 repeat Question
    {
      system("Clear");  // clear terminal
      cout << "You selected an option that wasnt in the avaliable options! "
              "Please try again! "
           << endl;
      cout << "Please select the number associated with the entity type you "
              "are: "
           << endl;  // output options
      cout << "1 - Individual" << endl;
      cout << "2 - Partnership" << endl;
      cout << "3 - Trust" << endl;
      cout << "4 - Company" << endl;
      cin >> Investor_Type;  // Takes input from user
    }
    if (Investor_Type == "1") {
      User_Type = 1;
      Account_Number =
          Create_Individual();  // input 1 calls the create individual function
    } else if (Investor_Type == "2") {
      User_Type = 2;
      Account_Number = Create_Partnership();  // input 2 calls the create
                                              // partnership function
    } else if (Investor_Type == "3") {
      User_Type = 3;
      Account_Number =
          Create_Trust();  // input 3 calls the create trust function
    } else if (Investor_Type == "4") {
      User_Type = 4;
      Account_Number =
          Create_Company();  // input 4 calls the create company function
    }
  }
  return Account_Number;
}

void Console::Log_Out() {
  Logged_In_Status = 0;  // log out status is 0.
}

bool Console::Logged_In() {
  if (Logged_In_Status == 1) {
    return true;  // 1 means the user is logged in
  }
  return false;  // else they are logged out
}

void Console::Bye_Message()  // Outputs BYE
{
  system("Clear");  // Clears terminal
  cout << ".----------------.  .----------------.  .----------------." << endl;
  cout << "| .--------------. || .--------------. || .--------------. |"
       << endl;
  cout << "| |   ______     | || |  ____  ____  | || |  _________   | |"
       << endl;
  cout << "| |  |_   _ \\    | || | |_  _||_  _| | || | |_   ___  |  | |"
       << endl;
  cout << "| |    | |_) |   | || |   \\ \\  / /   | || |   | |_  \\_|  | |"
       << endl;
  cout << "| |    |  __'.   | || |    \\ \\/ /    | || |   |  _|  _   | |"
       << endl;
  cout << "| |   _| |__) |  | || |    _|  |_    | || |  _| |___/ |  | |"
       << endl;
  cout << "| |  |_______/   | || |   |______|   | || | |_________|  | |"
       << endl;
  cout << "| |              | || |              | || |              | |"
       << endl;
  cout << "| '--------------' || '--------------' || '--------------' |"
       << endl;
  cout << "'----------------'  '----------------'  '----------------'  "
       << endl;
}

int Console::Create_Broker() {
  int Given_ID;               // intialises ID for broker as an int
  string Given_Password;      // Intialises password as a string
  int Commission;             // Initialses commission as an int
  string Recommendations[3];  // Broker gives 3 recommendations
  int Client_Count;           // client count initialised as an int
  // int Client_ID[3];
  Given_ID = Get_ID();  // given ID from the the get ID function
  cout << "Please provide password: ";
  cin >> Given_Password;  // Take input from broker
  cout << "Please provide your default fee (in dollars): ";
  cin >> Commission;  // Take commission from broker
  while (cin.fail()) {
    cout << "You entered an invalid value, Please provide your default fee (in "
            "dollars): ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> Commission;  // Broker inputs the amount of clients he would like
  }
  for (int i = 0; i < 3; i++)  // Loops from 0 to 3 for recommendations
  {
    cout << "Please provide your stock recommendation number " << i + 1 << ": ";
    cin >> Recommendations[i];  // Input current iteration of recommendation
  }
  cout << "Whats the maximum amount of clients you would like to have: ";
  cin >> Client_Count;  // Broker inputs the amount of clients he would like
  while (Client_Count < 0 || cin.fail()) {
    cout << "You entered an amount less than 0 or a string! Whats the maximum "
            "amount of "
            "clients you would like to have: ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> Client_Count;  // Broker inputs the amount of clients he would like
  }
  int Client_ID[Client_Count];  // Client ID has the size of client count
  for (int j = 0; j < Client_Count; j++)  // loop from 0 to client count
  {
    cout << "Please provide the ID of client number " << j + 1
         << " (Or 0 if you dont have enough clients for quota of 3): ";
    cin >> Client_ID[j];  // input client ID
    while (!Duplicate_ID(Client_ID[j]) && Client_ID[j] != 0 || cin.fail()) {
      cout << "You entered a non-existant ID!" << endl;
      cout << "Please try again and enter the ID of client number " << j + 1
           << " (Or 0 if you dont have enough clients for quota of 3): ";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> Client_ID[j];  // input client ID
    }
  }
  fstream Accounts;                             // File object
  Accounts.open("Accounts.csv", fstream::app);  // open accounts.csv
  Accounts
      << Given_ID << "," << Given_Password << ","
      << "B"
      << "," << Commission << "," << Recommendations[0] << ","
      << Recommendations[1] << "," << Recommendations[2] << ","
      << Client_Count;  // display ID,Password,Type,Commission,Recommendations
                        // and client count.
  for (int i = 0; i < Client_Count; i++)  // Loop from 0 to client count
  {
    Accounts << "," << Client_ID[i];  // displays clients
  }
  Accounts << ",,,\n";
  Accounts.close();  // call close function
  return Given_ID;   // return ID
}

int Console::Create_Individual() {
  system("Clear");
  int Given_ID;                  // intialise ID for individual as int
  string Given_Password;         // intialise password as string
  string Individual_First_Name;  // intialise first name as string
  string Individual_Last_Name;   // intialise last name as string
  Given_ID = Get_ID();           // Call Get ID function
  cout << "Please provide password: ";
  cin >> Given_Password;  // Takes password input from user
  cout << "Please provide your first name as you would like it to appear on "
          "your portfolio statement: ";
  cin.clear();
  cin.ignore(256, '\n');
  getline(cin, Individual_First_Name);
  cout << "Please provide your last name as you would like it to appear on "
          "your portfolio statement: ";
  getline(cin, Individual_Last_Name);           // Takes input of last name
  fstream Accounts;                             // File object
  Accounts.open("Accounts.csv", fstream::app);  // Open Accounts.csv
  Accounts << Given_ID << "," << Given_Password << ","
           << "I"
           << "," << Individual_First_Name << "," << Individual_Last_Name
           << ",,,\n";  // display individual details in accounts file
  Accounts.close();
  return Given_ID;  // return ID
}
int Console::Create_Partnership() {
  system("Clear");        // Clear terminal
  int Given_ID;           // Cntialise as int
  string Given_Password;  // Intialise as string
  int Partner_Number;     // Intialise as int
  Given_ID = Get_ID();    // Call get ID
  cout << "Please provide password: ";
  cin >> Given_Password;  // Take password input
  cout << "How many partners are there? ";
  cin >> Partner_Number;
  while (cin.fail() || Partner_Number < 1)  // Confirming valid input
  {
    cout << "Invalid Input! How many partners are there? ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> Partner_Number;
  }

  // take number of partners input
  string Partners_First_Names[Partner_Number];  // intialises partners first
                                                // name with number attached
  string Partners_Last_Names[Partner_Number];   // intialises partners last name
                                                // with number attached
  cin.clear();
  cin.ignore(256, '\n');
  for (int i = 0; i < Partner_Number; i++)      // Loop through all the partners
  {
    cout << "Please provide the first name for partner number " << i + 1
         << " as you would like it to appear on your portfolio statement: ";
    getline(cin, Partners_First_Names[i]);
    cout << "Please provide the last name for partner number " << i + 1
         << " as you would like it to appear on your portfolio statement: ";
    getline(cin, Partners_Last_Names[i]);
  }
  fstream Accounts;                             // file object
  Accounts.open("Accounts.csv", fstream::app);  // open accounts csv
  Accounts << Given_ID << "," << Given_Password << ","
           << "P"
           << "," << Partner_Number;  // Display details for partners
  for (int i = 0; i < Partner_Number;
       i++)  // Loop through partners and display their names
  {
    Accounts << "," << Partners_First_Names[i] << "," << Partners_Last_Names[i];
  }
  Accounts << ",,,\n";
  Accounts.close();
  return Given_ID;
}

int Console::Create_Trust() {
  system("Clear");         // Clears terminal
  int Given_ID;            // Intialise ID as int
  string Given_Password;   // Intialise password as string
  int Trustee_Number;      // Intialise amount of trustees as int
  int Beneficiary_Number;  // Intialise amount of beneficiaries as int
  Given_ID = Get_ID();     // call get ID
  cout << "Please provide password: ";
  cin >> Given_Password;  // Takes input for password
  cout << "How many beneficiaries are there? ";
  cin >> Beneficiary_Number;  // Takes input for Beneficiary number
  while (cin.fail() || Beneficiary_Number < 1)  // Confirming valid input
  {
    cout << "Invalid Input! How many Beneficiaries are there? ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> Beneficiary_Number;
  }
  string
      Beneficiary_First_Names[Beneficiary_Number];  // String for names with the
                                                    // size being the amount of
                                                    // beneficiaries there are
  string
      Beneficiary_Last_Names[Beneficiary_Number];  // String for names with the
                                                   // size being the amount of
                                                   // beneficiaries there are
  cin.clear();
  cin.ignore(256, '\n');
  for (int i = 0; i < Beneficiary_Number;
       i++) {  // loop through from 0 to the amount of beneficiaries
    cout << "Please provide the first name for beneificary number " << i + 1
         << " as you would like it to appear on your portfolio statement: ";
    getline(cin, Beneficiary_First_Names[i]);
    cout << "Please provide the last name for beneificary number " << i + 1
         << " as you would like it to appear on your portfolio statement: ";
    getline(cin, Beneficiary_Last_Names[i]);
  }
  cout << "How many trustees are there? ";
  cin >> Trustee_Number;  // Take input for the amount of trustees
  while (cin.fail() || Trustee_Number < 1)  // Confirming valid input
  {
    cout << "Invalid Input! How many Trustees are there? ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> Trustee_Number;
  }
  string Trustee_First_Names[Beneficiary_Number];  // String for names with the
                                                   // size being the amount of
                                                   // trustees there are
  string Trustee_Last_Names[Beneficiary_Number];   // String for names with the
                                                   // size being the amount of
                                                   // trustees there are
  cin.clear();
  cin.ignore(256, '\n');
  for (int i = 0; i < Trustee_Number;
       i++)  // loop through from 0 to size of trustees number
  {
    cout << "Please provide the first name for trustee number " << i + 1
         << " as you would like it to appear on your portfolio statement: ";
    getline(cin, Trustee_First_Names[i]);
    cout << "Please provide the last name for trustee number " << i + 1
         << " as you would like it to appear on your portfolio statement: ";
    getline(cin, Trustee_Last_Names[i]);
  }
  fstream Accounts;                             // file object
  Accounts.open("Accounts.csv", fstream::app);  // open accounts csv
  Accounts << Given_ID << "," << Given_Password << ","
           << "T"
           << "," << Beneficiary_Number;        // display details
  for (int i = 0; i < Beneficiary_Number; i++)  // Loop through beneficiaries
  {
    Accounts << "," << Beneficiary_First_Names[i] << ","
             << Beneficiary_Last_Names[i];  // Display beneficiaries names
  }
  Accounts << ", " << Trustee_Number;  // display details
  for (int i = 0; i < Trustee_Number; i++) {
    Accounts << "," << Trustee_First_Names[i] << ","
             << Trustee_Last_Names[i];  // displays trustees names in accounts
  }
  Accounts << ",,,\n";
  Accounts.close();  // call close function

  return Given_ID;
}

int Console::Create_Company() {
  system("Clear");         // clear terminal
  int Given_ID;            // Intialises ID as int
  string Given_Password;   // Intialises Password as string
  int Director_Number;     // Intialse Director number
  string Registered_Name;  // Intialises registered name
  Given_ID = Get_ID();     // call Get_ID
  cout << "Please provide password: ";
  cin >> Given_Password;  // User inputs password
  cout << "Please enter your registered name: ";
  cin.ignore(1000, '\n');
  getline(cin, Registered_Name);  // input registered name
  cout << "How many directors are there? ";
  cin >> Director_Number;  // User inputs how many directors there are
  while (cin.fail() || Director_Number < 1)  // Confirming valid input
  {
    cout << "Invalid Input! How many Directors are there? ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> Director_Number;
  }
  string Director_First_Names[Director_Number];  // string for directors names,
                                                 // Size = amount of directors
  string Director_Last_Names[Director_Number];   // string for directors names,
                                                 // Size = amount of directors
  cout << "Please provide the first name for director number " << 1
       << " as you would like it to appear on your portfolio statement: ";
  cin.clear();
  cin.ignore(256, '\n');
  getline(cin, Director_First_Names[0]);  // input director name for current
                                          // iteration
  cout << "Please provide the last name for director number " << 1
       << " as you would like it to appear on your portfolio statement: ";
  getline(cin,
          Director_Last_Names[0]);  // input director name for current iteration
  for (int i = 1; i < Director_Number; i++)  // Loop Through directors
  {
    cout << "Please provide the first name for director number " << i + 1
         << " as you would like it to appear on your portfolio statement: ";
    getline(cin, Director_First_Names[i]);  // input director name for current
                                            // iteration
    cout << "Please provide the last name for director number " << i + 1
         << " as you would like it to appear on your portfolio statement: ";
    getline(
        cin,
        Director_Last_Names[i]);  // input director name for current iteration
  }
  fstream Accounts;                             // file object
  Accounts.open("Accounts.csv", fstream::app);  // Open accounts csv
  Accounts << Given_ID << "," << Given_Password << ","
           << "C"
           << "," << Registered_Name << ","
           << Director_Number;               // display details
  for (int i = 0; i < Director_Number; i++)  // Loop through directors
  {
    Accounts << "," << Director_First_Names[i] << ","
             << Director_Last_Names[i];  // Display names of directors
  }
  Accounts << ",,,\n";
  Accounts.close();

  return Given_ID;
}

void Console::Loading() {
  this_thread::sleep_for(chrono::seconds(2));  // Displays for 2 seconds
  system("Clear");                             // Clears terminal
  cout << "Loading." << endl;
  this_thread::sleep_for(chrono::seconds(1));  // Displays for 1 second
  system("Clear");                             // Clears terminal
  cout << "Loading.." << endl;
  this_thread::sleep_for(chrono::seconds(1));  // Displays for 1 second
  system("Clear");                             // Clears terminal
  cout << "Loading..." << endl;
  this_thread::sleep_for(chrono::seconds(1));  // Displays for 1 second
  system("Clear");                             // Clears terminal
}

int Console::Get_ID() {
  int ID;
  cout << "Please provide your desired ID (Integers Only): ";
  cin >> ID;  // Takes input of a ID, has to be a number
  while (ID <= 0 || cin.fail()) {
    cout << "You entered an invalid number! Please provide your desired ID "
            "(Integers Only): ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> ID;  // Takes input of a ID, has to be a number
  }
  while (Duplicate_ID(ID) ||
         cin.fail())  // While the user inputs a duplicate ID, keep looping.
  {
    cout << "You entered an already Existing ID: Please provide your desired "
            "ID (Integers Only): ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> ID;  // Takes input from user
  }
  return ID;
}

int Console::Get_User_Type() {
  return User_Type;  // Return User type
}

bool Console::Duplicate_ID(int ID) {
  ifstream Accounts;              // File object
  Accounts.open("Accounts.csv");  // Open accounts.csv
  string line;
  int Temp_ID;  // intialise temp id
  string myID;  // intialise ID
  while (getline(Accounts, line)) {
    stringstream ss(line);
    getline(ss, myID, ',');
    Temp_ID = stoi(myID);
    if (Temp_ID == ID) {
      return true;  // While the ID is a duplicate ID return true
    }
  }
  Accounts.close();
  return false;  // otherwise accounts close and return false
}

Console::~Console(){};