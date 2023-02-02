#ifndef PARTNERSHIP_H
#define PARTNERSHIP_H
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "Investor.h"
#include "User.h"

class Partnership : public Investor {
 private:
  std::string *First_Name;
  std::string *Last_Name;
  int Number_Of_Partners;

 public:
  Partnership();                   // Default Constructor
  Partnership(int ID);             // Constructor
  void Get_Partnership_Details();  // Sets partners First Name and Last Name Per
                                   // Accounts.csv
  void Partnersip_Display_Results_Test();  // Test for Displaying Results
  void Set_Partners_Count();               // Sets Partner count
  void Set_Partners_Names();               // Sets Partners First Names
  void Print();                            // Overloading inherited function
  ~Partnership();                          // Destructor
};

#endif