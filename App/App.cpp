//
// Created by ahmed on 2/7/2023.
//

#include <iostream>
#include "App.h"
#include "../Namespaces/gpm.h"
#include "../User/User.h"

using std::cout;

App::App(const string &users_path, const string &books_path,
         const string &books_dir, const string &sessions_path)
         : usr_{nullptr}, sess_{NULL},users_{users_path},
         books_{books_path, books_dir}, sessions_{sessions_path} {
  sign_menu_.emplace_back("SignUp");
  sign_menu_.emplace_back("LogIn");
  sign_menu_.emplace_back("Exit");
  customer_menu_.emplace_back("Read");
  customer_menu_.emplace_back("History");
  customer_menu_.emplace_back("List of Books");
  customer_menu_.emplace_back("LogOut");
  admin_menu_.emplace_back("Add Book");
  admin_menu_.emplace_back("LogOut");
}

void App::PrintSignMenu() const {
  for (int i = 0; i < (int) sign_menu_.size(); ++i) {
    cout << i << " - " << sign_menu_[i] << "\n";
  }
}

void App::PrintAdminMenu() const {
  for (int i = 0; i < (int) admin_menu_.size(); ++i) {
    cout << i << " - " << admin_menu_[i] << "\n";
  }
}

void App::PrintCustomerMenu() const {
  for (int i = 0; i < (int) customer_menu_.size(); ++i) {
    cout << i << " - " << customer_menu_[i] << "\n";
  }
}

bool App::RunSign() {
  PrintSignMenu();
  int c = gpm::InputInt("Enter a number", 0, (int) sign_menu_.size() - 1);
  if (c == 0) {
    users_.AddUser();
  } else if (c == 1) {
    usr_ = users_.AccessUser();
  } else {
    return false;
  }
}

bool App::Run() {
  if (!usr_) {
    return RunSign();
  } else if (usr_->IsAdmin()) {
    return RunAdmin();
  } else {
    return RunCustomer();
  }
}
