#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "Investor.h"
#include "User.h"

class Individual : public Investor {
 private:
  std::string First_Name;
  std::string Last_Name;

 public:
  Individual();                   // Default constructor
  Individual(int ID);             // Constructor
  void Get_Individual_Details();  // Sets user First Name and Last Name Per
                                  // Accounts.csv
  void Individual_Display_Results_Test();  // Test for Displaying Results
  void Print();                            // Overloading inherited function
  ~Individual();                           // Destructor
};

#endif