#include "User.h"

#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

string User::Get_Account_Type() {
  return Account_Type;  // return the account type of the user.
}
void User::Set_Account_Type() {
  Account_Type = "N/A";              // set account type
  ifstream Information;              // file object
  Information.open("Accounts.csv");  // open accounts csv

  if (!Information.is_open()) {
    cout << "File wasnt found and openned "
         << endl;  // If statement determined file can not be opened
  }
  string Temp_Account_Number;   // intialise string temp account number
  int Int_Temp_Account_Number;  // intialise int temp number
  string Temp_Password;         // intialise temp password
  string Temp_Account_Type;     // intialise temp account type
  string line;
  while (getline(Information, line)) {
    stringstream ss(line);
    getline(ss, Temp_Account_Number, ',');
    getline(ss, Temp_Password, ',');
    getline(ss, Temp_Account_Type, ',');
    Int_Temp_Account_Number = stoi(
        Temp_Account_Number);  // set int temp account number to string temp
                               // account number and convert using stoi.
    if (Int_Temp_Account_Number ==
        this->Account_Number)  // if the temp number is equal to the actual
                               // account number...
    {
      Account_Type = Temp_Account_Type;  //...Then the account type is equal to
                                         // the temp type.
      break;
    }
  }
  Information.close();  // close information
}