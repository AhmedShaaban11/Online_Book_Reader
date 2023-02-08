//
// Created by ahmed on 2/7/2023.
//

#ifndef ONLINE_BOOK_READER_APP_H
#define ONLINE_BOOK_READER_APP_H

#include <string>
#include <vector>
#include "../Session/Session.h"
#include "../UsersManager/UsersManager.h"
#include "../BooksManager/BooksManager.h"
#include "../SessionsManager/SessionsManager.h"

using std::string;
using std::vector;

class App {
 private:
  User *usr_;
  vector<Session>::iterator sess_;
  UsersManager users_;
  BooksManager books_;
  SessionsManager sessions_;
  vector<string> sign_menu_;
  vector<string> admin_menu_;
  vector<string> customer_menu_;
  void PrintSignMenu() const;
  void PrintAdminMenu() const;
  void PrintCustomerMenu() const;
  bool RunSign();
  bool RunAdmin();
  bool RunCustomer();
  void LogOut();
 public:
  App(const string &users_path, const string &books_path,
      const string &books_dir, const string &sessions_path);
  bool Run();
};


#endif //ONLINE_BOOK_READER_APP_H
