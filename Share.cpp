#include "Share.h"

#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Share::Share() {
  Ticker = "CBA";         // Set ticker
  Name = "CBA";           // Set name
  Current_Year = 2014;    // Set current year
  Current_Price = 0;      // Set current price
  Units = 0;              // Set units
  Prices = Get_Prices();  // Set price to get prices function
  Value = 0;              // Set value
  Cost_Base = 0;          // Set cost base
}

Share::Share(string Ticker, int Current_Year) {
  this->Ticker = Ticker;
  int Continue = 1;
  // While loop will keep looping until a valid ticker is entered eg. ANZ or
  // user has elected to stop the function "Stop."
  while (!Check_Valid_Ticker(Ticker, Current_Year) && Continue == 1) {
    cout << "Please re enter the ticker as the company information wasnt found "
            "(Or enter \"Stop\" to stop searching): ";
    cin >> Ticker;
    this->Ticker = Ticker;
    if (Ticker == "Stop") {
      Continue = 0;
    }
    Name = "N/A";
  }
  // Set Prices and Current Year
  Prices = Get_Prices();
  this->Current_Year = Current_Year;
  Name = Find_Name(Current_Year);
  Value = 0;
  Cost_Base = 0;
  Units = 0;
  Current_Price = Get_Current_Price();
}

Share::Share(std::string Ticker, int Current_Year, int Units) {
  this->Ticker = Ticker;
  // While loop will keep looping until a valid ticker is entered eg. ANZ
  while (!Check_Valid_Ticker(Ticker, Current_Year)) {
    cout << "Please re enter the ticker as the company information wasnt "
            "found: ";
    cin >> Ticker;
    this->Ticker = Ticker;
  }
  // Set Prices, current year, name and current price
  Prices = Get_Prices();
  this->Current_Year = Current_Year;
  Name = Find_Name(Current_Year);
  Current_Price = Get_Current_Price();
  // Set units
  this->Units = Units;
  Value = Get_Current_Price() *
          Units;  // The value is the current price multiplied by the units
  Cost_Base =
      Get_Current_Price() *
      Units;  // The cost base is the current price multiplied by the units
  Current_Price = Get_Current_Price();  // get current price
}
// Functions that will return their respective variables.
string Share::Get_Ticker() { return Ticker; }

string Share::Get_Name() { return Name; }

int Share::Get_Current_Year() { return Current_Year; }

double Share::Get_Current_Price() { return Get_Price(Current_Year); }

int Share::Get_Units() { return Units; }
// function that will remove units once sold. Units will now equal units minus
// sold units.
void Share::Sell_Units(int Sold_Units) { Units = Units - Sold_Units; }
// bool function that will check if the ticker is valid. eg. AUWQ is not valid
bool Share::Check_Valid_Ticker(std::string Ticker, int Current_Year) {
  // open yearly csv such as 2017.csv
  string i_string = to_string(Current_Year);
  string FileToBeOpened = i_string + ".csv";

  ifstream Information;
  Information.open(FileToBeOpened);
  // Return false if file can not be opened
  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;
    return false;
  }
  string Temp_Ticker;
  string line;
  // while loop that will keep looping until ticker is found
  while (getline(Information, line)) {
    stringstream ss(line);
    getline(ss, Temp_Ticker, ',');
    // If ticker and temp ticker are equal return true
    if (Temp_Ticker == Ticker) {
      return true;
      break;
    }
  }
  Information.close();
  return false;
}

double Share::Get_Price(int Year) {
  // initialise price variable
  double Price = 0;
  // open yearly file eg. 2017.csv
  string i_string = to_string(Year);
  string FileToBeOpened = i_string + ".csv";

  ifstream Information;
  Information.open(FileToBeOpened);
  // If the file can not be open, display that it was not found.
  if (!Information.is_open()) {
    cout << "File wasnt found and openned " << endl;
  }
  // Set variables
  string Temp_Ticker;
  string Temp_Price;
  double Another_Temp_Price;
  string Temp_Name;
  string line;
  // While the ticker has not been founc, keep looping
  while (getline(Information, line)) {
    stringstream ss(line);
    getline(ss, Temp_Ticker, ',');
    getline(ss, Temp_Name, ',');
    getline(ss, Temp_Price, ',');

    if (Temp_Ticker == Get_Ticker()) {
      // convert float to string and assign to price variable
      Price = stod(Temp_Price);
      break;
    }
  }
  Information.close();
  return Price;
}
// Current year increased variable. eg. 2014+1 = 2015.
void Share::Set_Current_Year(int Increase) {
  Current_Year = Current_Year + Increase;
}

double *Share::Get_Prices() {
  double *Prices = new double[9];  // Allocate memory for prices pointer
  // For loop that will return the prices from 2014 to 2023.
  for (int i = 2014; i < 2023; i++) {
    Prices[i - 2014] = Get_Price(i);
  }
  return Prices;
}

std::string Share::Find_Name(int Year) {
  string Name = "Not Found";  // set Name
  if (Year != 2020)  // if year not equal to 2020, open csv of that year.
  {
    string i_string = to_string(Year);
    string FileToBeOpened = i_string + ".csv";

    ifstream Information;
    Information.open(FileToBeOpened);
    // if file is not opened, display that it was not
    if (!Information.is_open()) {
      cout << "File wasnt found and openned " << endl;
    }
    // Set variables
    string Temp_Ticker;
    string Temp_Price;
    string Temp_Name;
    string line;
    // While loop that will keep looping until ticker is found
    while (getline(Information, line)) {
      stringstream ss(line);
      getline(ss, Temp_Ticker, ',');
      getline(ss, Temp_Name, ',');
      getline(ss, Temp_Price, ',');
      if (Temp_Ticker == Ticker) {
        Name = Temp_Name;  // Set name
        break;
      }
    }
    Information.close();
    return Name;  // Return name
  } else {
    ifstream Information;
    Information.open("ASX_Companies.csv");  // Open asx companies csv

    if (!Information.is_open()) {
      cout << "File wasnt found and openned "
           << endl;  // Display if file not found
    }
    // Set variables
    string Temp_Ticker;
    string Temp_Price;
    string Temp_Name;
    string line;
    // While loop that will keep looping until ticker is found
    while (getline(Information, line)) {
      stringstream ss(line);
      getline(ss, Temp_Ticker, ',');
      getline(ss, Temp_Name, ',');
      getline(ss, Temp_Price, ',');
      if (Temp_Ticker == Ticker) {
        Name = Temp_Name;  // Set Name to temp name
        break;
      }
    }
    Information.close();
    return Name;  // Return name
  }
  return Name;
}

void Share::Increase_Units(int Units) {
  this->Units += Units;  // Set units
  Cost_Base +=
      Units *
      Get_Current_Price();  // Cost base = Units multiplied by current price
}
// Free up memory
Share::~Share() { delete Prices; }