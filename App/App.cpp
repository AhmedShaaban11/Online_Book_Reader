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
         : books_dir_{books_dir}, usr_{nullptr}, sess_{nullptr},
         users_{users_path}, books_{books_path, books_dir},
         sessions_{sessions_path} {
  sign_menu_.emplace_back("SignUp");
  sign_menu_.emplace_back("LogIn");
  sign_menu_.emplace_back("Exit");
  customer_menu_.emplace_back("Read");
  customer_menu_.emplace_back("History");
  customer_menu_.emplace_back("List of Books");
  customer_menu_.emplace_back("LogOut");
  admin_menu_.emplace_back("Add Book");
  admin_menu_.emplace_back("LogOut");
  session_menu_.emplace_back("Print Current Page");
  session_menu_.emplace_back("Go To The Next Page");
  session_menu_.emplace_back("Go To The Previous Page");
  session_menu_.emplace_back("End");
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

void App::PrintSessionMenu() const {
  for (int i = 0; i < (int) session_menu_.size(); ++i) {
    cout << i << " - " << session_menu_[i] << "\n";
  }
}

void App::LogOut() {
  usr_ = nullptr;
  sess_ = nullptr;
}

bool App::RunSign() {
  PrintSignMenu();
  gpm::PrintSeparator('-', 15);
  int c = gpm::InputInt("Enter a number", 0, (int) sign_menu_.size() - 1);
  if (c == 0) {
    users_.AddUser();
  } else if (c == 1) {
    usr_ = users_.AccessUser();
  } else {
    return false;
  }
  return true;
}

bool App::RunAdmin() {
  PrintAdminMenu();
  gpm::PrintSeparator('-', 15);
  int c = gpm::InputInt("Enter a number:", 0, (int) admin_menu_.size() - 1);
  if (c == 0) {
    books_.AddBook();
  } else {
    LogOut();
  }
  return true;
}

bool App::RunCustomer() {
  PrintCustomerMenu();
  gpm::PrintSeparator('-', 15);
  int c = gpm::InputInt("Enter a number:", 0, (int) customer_menu_.size() - 1);
  if (c == 0) {
    string title = books_.AccessBook();
    if (title.empty()) { return true; }
    sess_ = sessions_.AccessSession(title, usr_->GetUsername());
    sess_->Open(books_dir_);
  } else if (c == 1) {
    sessions_.PrintHistory(usr_->GetUsername());
  } else if (c == 2) {
    books_.PrintBooks();
  } else {
    LogOut();
  }
  return true;
}

bool App::RunSession() {
  PrintSessionMenu();
  gpm::PrintSeparator('-', 15);
  int c = gpm::InputInt("Enter a number:", 0, (int) session_menu_.size() - 1);
  if (c == 0) {
    sess_->Show();
  } else if (c == 1) {
    sess_->NxtPage();
  } else if (c == 2) {
    sess_->PrvPage();
  } else {
    sess_->Close();
    sess_ = nullptr;
  }
  return true;
}

bool App::Run() {
  if (!usr_) {
    return RunSign();
  } else if (usr_->IsAdmin()) {
    return RunAdmin();
  } else if (!sess_){
    return RunCustomer();
  } else {
    return RunSession();
  }
}
