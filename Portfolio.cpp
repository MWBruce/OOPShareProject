#include "Portfolio.h"

#include <stdlib.h>
#include <string.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "Share.h"

using namespace std;

Portfolio::Portfolio() {
  User_Shares = new Share[20];  // Allocate memory for user shares
  Share_Count = 0;              // initialise share count
  Current_Year = 2014;          // initialise current year
  cout << "How much cash would you like to start with? ";  // Output message to
                                                           // user
  cin >> Cash;  // User will input how much money they want to use
  // While the input is less than zero print this message.
  while (Cash <= 0 || cin.fail()) {
    cout << "You entered a invalid balance! What would "
            "you like your starting "
            "balance to be? ";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> Cash;
  }
}
// Return Share count
int Portfolio::Get_Share_Count() { return Share_Count; }

void Portfolio::Buy_Share(std::string Ticker, int Current_Year, int Units) {
  // If the max shares have not been reached, set temp share.
  if (!Reached_Share_Max()) {
    Share Temp_Share(Ticker, Current_Year);
    // This if statement will check if user has enough money
    if (Cash > (Temp_Share.Get_Price(Current_Year) * Units)) {
      // Set variable to the ticker
      int Index_For_Stock = Find_Stock_Index(Ticker);
      // If statement checking that the index for stock is equal to share count
      if (Index_For_Stock == Share_Count) {
        User_Shares[Share_Count] =
            Share(Ticker, Current_Year, Units);  // Add share to user shares.
        cout << "You have bought " << User_Shares[Share_Count].Get_Name()
             << endl;  // Display the share the user bought
        this_thread::sleep_for(chrono::seconds(2));  // Display for 2 seconds
        Cash = Cash - (User_Shares[Share_Count].Get_Price(Current_Year) *
                       Units);  // User Balance = Balance minus (Current price
                                // multiplied by units).
        Share_Count++;          // iterate share ocunt
      } else {
        int Temp_Units =
            User_Shares[Index_For_Stock].Get_Units();  // Set units for stock
        User_Shares[Index_For_Stock] =
            Share(Ticker, Current_Year,
                  Units + Temp_Units);  // Add share to user shares
        Cash = Cash - (User_Shares[Index_For_Stock].Get_Price(Current_Year) *
                       Units);  // User Balance = Balance minus (Current price
                                // multiplied by units).
        cout << "You have bought " << User_Shares[Index_For_Stock].Get_Name()
             << endl;  // Display message of the bought share
        this_thread::sleep_for(chrono::seconds(2));  // display for 2 seconds
      }
    } else {
      // else statement that is executed when the user does not have enough
      // money
      cout << "You dont have enough money to buy this! " << endl;
      this_thread::sleep_for(chrono::seconds(1));  // display for 1 second
    }
  } else {
    // else statement that is executed when the user when maximum shares is
    // reached
    cout << "You have reached the maximum amount of shares!!" << endl;
    this_thread::sleep_for(chrono::seconds(1));  // display for 1 second
  }
}

void Portfolio::Sell_Share(std::string Ticker, int Current_Year, int Units) {
  int Stock_Found = 0;  // intialise stock is found
  for (int i = 0; i < Share_Count;
       i++)  // for loop that will loop from 0 to the share count
  {
    if (User_Shares[i].Get_Ticker() == Ticker) {
      if (User_Shares[i].Get_Units() <
          Units)  // if statement that will be executed when the user does not
                  // have enough units to sell
      {
        cout << "You dont have enough units to sell!! " << endl;
        this_thread::sleep_for(chrono::seconds(1));  // display for 1 second
        Stock_Found = 1;                             // stock found now equals 1
      } else {
        // Display when user sold share
        cout << "You sold " << User_Shares[i].Get_Name() << endl;
        this_thread::sleep_for(chrono::seconds(2));  // Display for 2 seconds
        Cash = Cash + (User_Shares[i].Get_Price(Current_Year) *
                       Units);  // Balance = Balance + (Current price*Units)
        User_Shares[i].Sell_Units(Units);  // Execute sell units command
        Stock_Found = 1;                   // stock found now equals 1
      }
    }
  }
  // if stock found is equal to zero, then the stock is not owned by the user
  if (Stock_Found == 0) {
    cout << "You dont own this stock or you entered the ticker incorrectly!"
         << endl;
    this_thread::sleep_for(chrono::seconds(1));  // display for 1 second
  }
}

bool Portfolio::Reached_Share_Max() {
  if (Share_Count > 20)  // if share count is greater than 20, then the share
                         // limit has been reached
  {
    return true;
  } else {
    return false;  // else the share limit has not been reached
  }
  return false;
}

void Portfolio::Display_Portfolio() {
  system("Clear");  // Function that will clear the system
  cout << "Your Portfolio is as Follows, Please Note Figures Have Been Rounded "
          "For Ease"
       << endl;  // output message
  string temp;
  // This for loop will loop from 0 to the share count and output the share
  // names and variables.
  for (int i = 0; i < Share_Count; i++) {
    int Temp_Units = User_Shares[i].Get_Units();  // Get units
    int Temp_Current_Price =
        User_Shares[i].Get_Price(Current_Year);  // Get current price
    int Temp_Previous_Price =
        User_Shares[i].Get_Price(Current_Year - 1);  // Get previous price
    cout << i + 1 << " - Name: " << User_Shares[i].Get_Name() << endl;
    cout << "\t Current Stock Price: $"
         << User_Shares[i].Get_Price(Current_Year) << endl;
    cout << "\t Last Years Stock Price: $"
         << User_Shares[i].Get_Price(Current_Year - 1) << endl;
    cout << "\t Units Held: " << User_Shares[i].Get_Units() << endl;
    cout << "\t Current Market Value: $" << Temp_Units * Temp_Current_Price
         << endl;
    cout << "\t 12 Month Stock Change: $"
         << (Temp_Units * Temp_Current_Price) -
                (Temp_Units * Temp_Previous_Price)
         << endl;  // Calculate and output the 12 month price change
  }
  cout << "Your Bank Balance is furthermore: $" << Cash
       << endl;  // output Balance
  cout << "Press enter to return to main page" << endl;
  cin.ignore();
  cin.get();  // This allows user to press Enter to return to main page
}

void Portfolio::Increase_Current_Year() {
  if (Reached_Year_Upper_Bound()) {
    Current_Year++;  // Iterate current year
    for (int i = 0; i < Share_Count;
         i++)  // for loop that will loop from 0 to the share count
    {
      User_Shares[i].Set_Current_Year(
          Current_Year);  // Set user shares to new current year
    }
    cout << "You have advanced forward into year " << Current_Year
         << endl;                                // Output
    this_thread::sleep_for(chrono::seconds(3));  // Display for 3 seconds
  } else {
    cout << "You cant advance any further you have reached the upper limit!"
         << endl;  // If reached 2023, display this
    this_thread::sleep_for(chrono::seconds(1));  // display for 1 second
  }
}

void Portfolio::Decrease_Current_Year() {
  if (Reached_Year_Lower_Bound()) {
    Current_Year--;  // Decrement a year
    cout << "You have advanced backward into year " << Current_Year
         << endl;  // Output
    // for loop that will loop from 0 to the share count
    for (int i = 0; i < Share_Count; i++) {
      User_Shares[i].Set_Current_Year(
          Current_Year);  // Set user shares to the new current year
    }
  } else {
    cout << "You cant advance any further into the past you have reached the "
            "lower limit!"
         << endl;  // Can not got further back than 2014
  }
}

bool Portfolio::Reached_Year_Upper_Bound() {
  if (Current_Year >= 2022) {
    return false;  // if current year is greater than or equal to 2022, return
                   // false
  }
  return true;  // else return true
}

bool Portfolio::Reached_Year_Lower_Bound() {
  if (Current_Year <= 2014) {
    return false;  // If current year is above 2014, return false
  }
  return true;  // else return true
}

int Portfolio::Find_Stock_Index(std::string Ticker) {
  int Index = Share_Count;  // Intialise index
  // for loop that will loop from 0 to the share count
  for (int i = 0; i < Share_Count; i++) {
    if (User_Shares[i].Get_Ticker() == Ticker) {
      Index = i;  // If user shares(i) equals the ticker, the index equals i.
    }
  }
  return Index;
}

// Return Share Variables to respective functions.
int Portfolio::Get_Year() { return Current_Year; }

int Portfolio::Units(int Share_Number) {
  return User_Shares[Share_Number].Get_Units();
}

int Portfolio::Current_Price(int Share_Number) {
  return User_Shares[Share_Number].Get_Price(Current_Year);
}
int Portfolio::Previous_Price(int Share_Number) {
  return User_Shares[Share_Number].Get_Price(Current_Year - 1);
}

std::string Portfolio::Name(int Share_Number) {
  return User_Shares[Share_Number].Get_Name();
}

double Portfolio::Get_Cash() { return Cash; }
// Free up memory
Portfolio::~Portfolio() {}