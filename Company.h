#ifndef COMPANY_H
#define COMPANY_H
#include <iostream>
#include <string>

#include "Investor.h"
#include "User.h"

class Company : public Investor {
 private:
  std::string Registered_Name;
  int Number_Of_Directors;
  std::string *Director_First_Name;
  std::string *Director_Last_Name;

 public:
  Company();                   // Default constructor
  Company(int ID);             // Constructor
  void Get_Company_Details();  // Sets company name and director details
  void Company_Display_Results_Test();  // Test for Displaying Results
  void Set_Director_Count();            // Sets Director count
  void Set_Names();                     // Sets Director names
  void Print();                         // Overloading inherited function
  ~Company();                           // Destructor
};

#endif