#ifndef CONSOLE_H
#define CONSOLE_H

class Console {
 protected:
  int User_Type;
  int Existing_User;
  int Logged_In_Status;

 public:
  Console();                  // Constructor
  void Welcome_Message();     // Displayes Welcome Message for User
  int Get_Existing_User();    // Returns Existing user status
  int Login();                // Logs User in
  int Create_Account();       // Creates Account from user
  void Log_Out();             // Logs User Out
  bool Logged_In();           // Bool function which is true when logged in
  void Bye_Message();         // Displays bye message
  int Create_Broker();        // Creates Broker Account
  int Create_Individual();    // Creates Individual Account
  int Create_Partnership();   // Creates Partnership Account
  int Create_Trust();         // Creates Trust Account
  int Create_Company();       // Creates Company Account
  void Loading();             // Outputs Loading Message
  int Get_ID();               // Gets ID from user and validates it
  int Get_User_Type();        // Returns user type
  bool Duplicate_ID(int ID);  // Checks if duplicate ID has been given
  ~Console(); // Destructor
};

#endif