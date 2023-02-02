#ifndef TRUST_H
#define TRUST_H
#include <iostream>
#include <string>

#include "Investor.h"
#include "User.h"

class Trust : public Investor {
 private:
  std::string *Bene_First_Name;
  std::string *Bene_Last_Name;
  int Number_Of_Bene;
  std::string *Trustee_First_Name;
  std::string *Trustee_Last_Name;
  int Number_Of_Trustee;

 public:
  Trust();                       // Default Constructor
  Trust(int ID);                 // Constructor
  void Get_Trust_Details();      // Sets trust beneficiary and trustee details
  void Print_Trust_Portfolio();  // Creates a csv of portfolio personalised for
                                 // trusts
  void Trust_Display_Results_Test();  // Test for Displaying Results
  void Set_Bene_Count();              // Sets Beneficiary count
  void Set_Names();                   // Sets Beneficiary and Trustee Names
  void Print();                       // Overloading inherited function
  ~Trust();                           // Destructor
};

#endif
