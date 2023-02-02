#include "Investor.h"

#include <stdlib.h>
#include <string.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include "User.h"

using namespace std;

void Investor::Display_Options()  // Display options
{
  while (Logged_In == 1)  // login in status is set to 1, 0 is offline
  {
    {
      system("Clear");  // clear system
      string Option;    // intialise option
      // Output the Options for the user
      cout << "Please select the number correlating to the function you wish "
              "to utilise: "
           << endl;
      cout << "1 - Advance A Year" << endl;
      cout << "2 - View Yearly Change Statement (Only For 2015 Onwards) "
           << endl;
      cout << "3 - Print CSV File of Portfolio (Only for 2015 Onwards) "
           << endl;
      cout << "4 - Research Stock" << endl;
      cout << "5 - Add Broker" << endl;
      cout << "6 - Remove Broker" << endl;
      cout << "7 - Get Recommendations" << endl;
      cout << "8 - Buy Stocks" << endl;
      cout << "9 - Sell Stocks " << endl;
      cout << "0 - Log Out" << endl;
      cin >> Option;  // Takes input from user
      while (Option != "0" && Option != "1" && Option != "2" && Option != "3" &&
             Option != "4" && Option != "5" && Option != "6" && Option != "7" &&
             Option != "8" && Option != "9") {
        system("Clear");
        cin.clear();
        cin.ignore(256, '\n');
        cout << "You didnt use a valid number! Please try again! "
             << endl;  // While the User does not input a valid number, show
                       // this message
        this_thread::sleep_for(chrono::seconds(1));  // display for 1 second
        system("Clear");                             // clear terminal
        // Ouput options for the user
        cout << "Please select the number correlating to the function you wish "
                "to utilise: "
             << endl;
        cout << "1 - Advance A Year" << endl;
        cout << "2 - View Yearly Change Statement (Only For 2015 Onwards) "
             << endl;
        cout << "3 - Print CSV File of Portfolio (Only for 2015 Onwards) "
             << endl;
        cout << "4 - Research Stock" << endl;
        cout << "5 - Add Broker" << endl;
        cout << "6 - Remove Broker" << endl;
        cout << "7 - Get Recommendations" << endl;
        cout << "8 - Buy Stocks" << endl;
        cout << "9 - Sell Stocks " << endl;
        cout << "0 - Log Out" << endl;
        cin >> Option;  // Takes input from user
      }
      if (Option == "0")  // If input is 0, logout.
      {
        Logged_In = 0;
      } else if (Option == "1")  // if input is 1, increment year by 1.
      {
        system("Clear");
        Investors_Portfolio->Increase_Current_Year();
      } else if (Option == "2") {
        if (Current_Year ==
            Investors_Portfolio
                ->Get_Year())  // if input is 2, print yearly statement
        {
          system("Clear");
          cout << "Sorry this option isn't avaliable when you are in the 2014 "
                  "Financial Year! "
               << endl;  // if year is 2014, this is unavaliable.
          this_thread::sleep_for(chrono::seconds(2));  // sleep for 2 seconds
          system("Clear");                             // clear
        } else {
          Display_Portfolio();  // else if it is not 2014, display portfolio
        }

      } else if (Option == "3")  // If input is 3, print portfolio
      {
        if (Current_Year == Investors_Portfolio->Get_Year()) {
          system("Clear");
          cout << "Sorry this option isn't avaliable when you are in the 2014 "
                  "Financial Year! "
               << endl;  // if year is 2014, this is unavaliable.
          this_thread::sleep_for(chrono::seconds(2));  // display for 2 seconds
          system("Clear");                             // clear terminal
        } else {
          Print();  // if its not 2014, print portfolio
        }
      }

      else if (Option == "4")  // If input is 4 then..
      {
        system("Clear");      //...clear terminal
        string Given_Ticker;  // Intialise string
        cout << "Please provide the Ticker of the stock you would like the "
                "current price of: ";                  // Output message
        cin >> Given_Ticker;                           // Take input from user
        Share Temp_Share(Given_Ticker, Current_Year);  // Temp share object
        if (Temp_Share.Get_Name() !=
            "N/A")  // If ticker corresponds to actual ticker
        {
          cout << "Stock Name: " << Temp_Share.Get_Name()
               << endl;  // Show stock name
          cout << "Current price: "
               << Temp_Share.Get_Price(Investors_Portfolio->Get_Year())
               << endl;  // Show current price
          cout << "Press enter to return to main page" << endl;
          cin.ignore();
          cin.get();  // This allows user to press enter to return
        }
      } else if (Option == "5")  // Input 5 will clear terminal
      {
        int Temp_ID;
        system("Clear");
        cout << "What is the ID of the broker whos recommendations you would "
                "like to see? ";  // It will then display this message
        cin >> Temp_ID;           // take input of ID
        while (!Broker_ID_Confirmation(Temp_ID) &&
               Temp_ID != -1)  // Keep looping until a valid ID is entered
        {
          system("Clear");                         // clear terminal
          cout << "Invalid ID Entered! " << endl;  // Invalid ID
          cout << "What is the ID of the broker whos recommendations you would "
                  "like to see? (Or enter -1 to stop trying to add broker): ";
          cin.clear();
          cin.ignore(256, '\n');
          cin >> Temp_ID;  // take input of ID
        }
        if (Broker_ID_Confirmation(
                Temp_ID))  // if ID correlated with a broker then display that
                           // the broker was set.
        {
          system("Clear");
          Set_Broker(Temp_ID);
          cout << "Broker Set!!!" << endl;
          this_thread::sleep_for(chrono::seconds(1));  // display for 1 second
        }
      } else if (Option ==
                 "6")  // If input is 6, clear terminal and remove broker
      {
        system("Clear");
        Remove_Broker();
      } else if (Option == "7")  // If input is 7, get recommendations
      {
        if (Broker_ID == 0) {
          system("Clear");
          cout << "You dont have a broker set!!" << endl;
          this_thread::sleep_for(chrono::seconds(1));
        } else {
          Get_Recommendations();
        }
      } else if (Option ==
                 "8")  // if input is 8, clear terminal and execute buy function
      {
        system("Clear");
        Buy();
      } else if (Option == "9")  // if input is 9, clear terminal and execute
                                 // sell function
      {
        system("Clear");
        Sell();
      }
    }
  }
}

void Investor::Get_Recommendations() {
  ifstream Information;
  Information.open("Accounts.csv");  // open accounts.csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;  // unable to open file
  }
  // intialise variables
  string Temp_Recommendation[3] = {"N/A"};  // 3 Recommendations from broker
  string Temp_ID;
  int Int_Temp_ID;
  string Temp_Nothing;
  string line;
  string Temp_First_Name;
  string Temp_Type;
  while (
      getline(Information, line))  // While loop to match temp ID to broker ID
  {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Type, ',');
    getline(ss, Temp_Nothing, ',');
    if (Int_Temp_ID == Broker_ID) {
      Information.close();
      getline(ss, Temp_Recommendation[0], ',');  // display recommendation
      getline(ss, Temp_Recommendation[1], ',');  // display recommendation
      getline(ss, Temp_Recommendation[2], ',');  // display recommendation
      break;
    }
  }
  Information.close();
  system("Clear");  // clear terminal
  cout << "Your brokers recommendations are as follows:" << endl;
  for (int i = 0; i < 3; i++)  // for loop for the 3 recommendations
  {
    cout << Temp_Recommendation[i]
         << endl;  // Output recommendation in current iteration
  }
  cout << "Press enter to return to main page" << endl;
  cin.ignore();
  cin.get();  // This function allows user to press enter to return to main page
}

bool Investor::Check_Balace(int Transaction) {
  if (Transaction > Balance)  // If transaction is greater than the balance
                              // return true, else return false
  {
    return true;
  }
  return false;
}

void Investor::Change_Balance(int Transaction) {
  Balance = Balance + Transaction;  // Balance = Balance + Transaction;
}

void Investor::Display_Portfolio() {
  Investors_Portfolio->Display_Portfolio();  // display portfolio
}

void Investor::Buy() {
  string Temp_Ticker;  // intialise variable
  int Temp_Units;      // intialse Units
  cout << "Whats the ticker of the stock you wish to buy? (Case Sensitive) ";
  cin >> Temp_Ticker;  // Take input of ticker from user
  cout << "How many units would you like to buy? ";
  cin >> Temp_Units;  // Take input of units from user
  while (Temp_Units < 1 || cin.fail()) {
    cout << "Invalid Unit amount! How many units would you like to buy? ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> Temp_Units;  // Take input of units from user
  }
  Share Temp_Share;  // create temporary share object
  if (Temp_Share.Check_Valid_Ticker(
          Temp_Ticker, Current_Year))  // Checking if ticker is valid
  {
    Investors_Portfolio->Buy_Share(Temp_Ticker, Current_Year,
                                   Temp_Units);  // add share to portfolio
  } else {
    cout << "That was an invalid ticker!"
         << endl;  // else it was an invalid ticker
    this_thread::sleep_for(chrono::seconds(1));  // display for 1 second
  }
}

void Investor::Sell() {
  string Temp_Ticker;  // set variables
  int Temp_Units;
  cout << "Whats the ticker of the stock you wish to Sell? (Case Sensitive) ";
  cin >> Temp_Ticker;  // Take ticker input from user
  cout << "How many units would you like to Sell? ";
  cin >> Temp_Units;  // Take units input from user
  while (Temp_Units < 1 || cin.fail()) {
    cout << "Invalid Unit amount! How many units would you like to sell? ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> Temp_Units;  // Take input of units from user
  }
  Investors_Portfolio->Sell_Share(
      Temp_Ticker, Current_Year,
      Temp_Units);  // Sell Share, remove from portfolio
}

bool Investor::Broker_ID_Confirmation(int ID) {
  ifstream Information;
  Information.open("Accounts.csv");  // open Accounts.csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;  // unable to open file
  }
  string Temp_ID;  // intialise variables
  int Int_Temp_ID;
  string Temp_Nothing;
  string line;
  string Temp_First_Name;
  string Temp_Type;
  while (getline(Information, line)) {
    stringstream ss(line);
    getline(ss, Temp_ID, ',');
    Int_Temp_ID = stoi(Temp_ID);
    getline(ss, Temp_Nothing, ',');
    getline(ss, Temp_Type, ',');
    if (Int_Temp_ID == ID &&
        Temp_Type == "B")  // If temp ID = ID and Type = B, then this confirms
                           // this is the broker
    {
      Information.close();
      return true;  // return true
      break;
    }
  }
  Information.close();
  return false;  // else it is not the broker
}

void Investor::Go_To_Next_Financial_Year() {
  Current_Year++;  // iterate current year
}
// Set ID to broker ID
void Investor::Set_Broker(int ID) { Broker_ID = ID; }

void Investor::Remove_Broker() {
  cout << "Broker Removed!!!" << endl;
  this_thread::sleep_for(chrono::seconds(2));  // display for 2 seconds
  Broker_ID = 0;  // Set broker ID to 0 to remove the broker
}
// return balance to the get balance function
double Investor::Get_Balance() { return Balance; }
// print report
void Investor::Print() {
  system("Clear");
  cout << "Your report has been printed to your file. " << endl;
  this_thread::sleep_for(chrono::seconds(2));
}