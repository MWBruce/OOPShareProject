#include <math.h>
#include <stdlib.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "Broker.h"
#include "Company.h"
#include "Console.h"
#include "Individual.h"
#include "Investor.h"
#include "Partnership.h"
#include "Portfolio.h"
#include "Share.h"
#include "Trust.h"
#include "User.h"

using namespace std;

int main() {
  Console UserConsole;                       // Create console object
  int Account_ID;                            // intialise account id
  if (UserConsole.Get_Existing_User() == 1)  // Opens program to user
  {
    Account_ID = UserConsole.Login();  // login function
    if (Account_ID == -1) {
      cout << "Login Failed! This Software Will Now Close!"
           << endl;           // login fails as -1 is an invalid input
      UserConsole.Loading();  // display loading
    } else {
      cout << "User ID Number: " << Account_ID << " Succesfully Logged In. "
           << endl;           // Successful login as ID matched the csv file
      UserConsole.Loading();  // display loading
    }
  } else {
    Account_ID = UserConsole.Create_Account();  // Create Account function
    cout << "User ID Number " << Account_ID
         << " Succesfully Created And Logged In! "
         << endl;           // Output, registration was successful
    UserConsole.Loading();  // display loading
  }

  if (UserConsole.Logged_In()) {
    system("Clear");  // Clear system
    if (UserConsole.Get_User_Type() == 1 || UserConsole.Get_User_Type() == 2 ||
        UserConsole.Get_User_Type() == 3 || UserConsole.Get_User_Type() == 4) {
      cout << "You Will Begin In The Financial Year 2014" << endl;
      this_thread::sleep_for(chrono::seconds(2));
    }
    if (UserConsole.Get_User_Type() == 0)  // 0 means the user is a broker
    {
      Broker U1(Account_ID);
    } else if (UserConsole.Get_User_Type() ==
               1)  // if input is 1, then the investor is an individual
    {
      Individual U1(Account_ID);
    } else if (UserConsole.Get_User_Type() ==
               2)  // if input is 2, then the investor is a partnership
    {
      Partnership U1(Account_ID);
    } else if (UserConsole.Get_User_Type() ==
               3)  // if input is 3, then the investor is a trust
    {
      Trust U1(Account_ID);
    } else if (UserConsole.Get_User_Type() ==
               4)  // if input is 4, then the investor is a company
    {
      Company U1(Account_ID);
    } else {
      UserConsole.Log_Out();  // else logout
    }
  }

  UserConsole.Bye_Message();  // Display BYE message
  return 0;
}