#ifndef BROKER_H
#define BROKER_H
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "User.h"

class Broker : public User {
 private:
  int *Clients_ID;
  int Client_Count;
  int Commission;
  std::string *Recommendations;

 public:
  Broker();                // Default constructor
  Broker(int ID);          // Constructor
  void Get_Information();  // Function that gets details from accounts csv file
  void Set_Commission();   // Sets broker commission per csv file
  void Change_Commission(
      int Given_Commission);   // Sets broker commission to given
                               // amount////////////////////////////////////////
  int Get_Commission();        // Returns commission
  void Set_Recommendations();  // Allows broker to modify recommendations
  void Set_Clients_Count();    // Sets Brokers clients count
  void Set_Clients();          // Sets Brokers clients
  void
  Broker_Display_Results_Test();  // Displays features to assist int testing
  std::string *Get_Recommendations();  // Returns array of recommendations
  void Display_Options();              // Displays options
  void Print_Clients();                // Displays clients
  bool Check_Remove_Choice(
      int Choice);  // Returns True if broker has client by given int
  bool Check_Add_Choice(int Choice);  // Returns True if client with ID exists
  void Replace_ID(int Remove_ID, int Replace_ID);  // Swaps given ID's
  void Swap_Clients();  // Allows user to swap clients
  void Print_To_CSV();  // Prints clients to csv file
  ~Broker();            // Destructor
};

#endif