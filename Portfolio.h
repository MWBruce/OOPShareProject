#ifndef PORTFOLIO_H
#define PORTFOLIO_H
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "Share.h"

class Portfolio {
 private:
  int Share_Count;
  int Current_Year;
  Share *User_Shares;
  double Cash;

 public:
  Portfolio();            // Default Constructor
  int Get_Share_Count();  // Returns Share_Count
  void Buy_Share(std::string Ticker, int Current_Year,
                 int Units);  // Buys stock
  void Sell_Share(std::string Ticker, int Current_Year,
                  int Units);  // Sell Stock
  bool Reached_Share_Max();    // Returns true if stock can be added as maximum
                               // amount of shares hasnt been reached
  void Display_Portfolio();    // Displays Portfolio
  void Increase_Current_Year();              // Increases current year by 1;
  void Decrease_Current_Year();              // Decreases current year by 1;
  bool Reached_Year_Upper_Bound();           // Returns false if in year 2022>
  bool Reached_Year_Lower_Bound();           // Returns false if in year 2014<
  int Get_Year();                            // Returns year
  int Find_Stock_Index(std::string Ticker);  // Finds index of stock in
                                             // portfolio
  int Units(int Share_Number);  // Returns Units Of Shares In User Shares at the
                                // element requested
  int Current_Price(int Share_Number);   // Returns Price Of Shares In User
                                         // Shares at the element requested
  int Previous_Price(int Share_Number);  // Returns Price Of Shares In User
                                         // Shares at the element requested
  std::string Name(int Share_Number);    // Returns name of Share in User Shares
                                         // at element requested
  double Get_Cash();                     // Returns cash balance
  ~Portfolio();                          // Need tp fix destructor error
};

#endif