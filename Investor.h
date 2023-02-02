#ifndef INVESTOR_H
#define INVESTOR_H
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "Broker.h"
#include "Portfolio.h"
#include "Share.h"
#include "User.h"

class Investor : public User {
 protected:
  Portfolio *Investors_Portfolio;
  double Balance;
  int Broker_ID;

 public:
  void Display_Options();  // Display Options for User to interact with and
                           // returns a number indicating the option
  bool Check_Balace(int Transaction);  // Confirms user can afford transaction
  void Get_Recommendations();          // Prints out brokers recommendations
  void Change_Balance(
      int Transaction);      // Changes user balance according to amount given
  void Display_Portfolio();  // Displays Users Portfolio on screen
  void Buy();                // Buys Stock
  void Sell();               // Sells Stock
  void Go_To_Next_Financial_Year();  // Increases current year by one
  bool Broker_ID_Confirmation(
      int ID);  // Returns true if the account linked with user input is broker
  void Set_Broker(int ID);  // Sets broker ID per given;
  void Remove_Broker();     // Removes Broker
  double Get_Balance();     // Returns Balance
  virtual void Print();     // Prints portfolio to csv
};

#endif