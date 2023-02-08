//
// Created by ahmed on 2/7/2023.
//

#include <fstream>
#include "UsersManager.h"
#include "../Namespaces/gpm.h"
#include "../User/User.h"

using std::ifstream;
using std::ofstream;

UsersManager::UsersManager(const string &path) : path_{gpm::CorrectPath(path)} {
  Update();
}

bool UsersManager::Update() {
  ifstream fin(path_);
  if (fin.fail()) {
    cout << "Error! Cannot open " << path_ << " file.\n";
    return false;
  }
  Clear();
  string line;
  while (std::getline(fin, line)) {
    User usr(line);
    users_.insert({usr.GetUsername(), usr});
    emails_.insert(usr.GetEmail());
  }
  fin.close();
  return true;
}

bool UsersManager::Save() const {
  ofstream fout(path_, std::ios::out);
  if (fout.fail()) {
    cout << "Error! Cannot open " << path_ << " file.\n";
    return false;
  }
  for (const auto &p : users_) {
    fout << p.second.ToString() << "\n";
  }
  fout.close();
  return true;
}

void UsersManager::Clear() {
  users_.clear();
  emails_.clear();
}

bool UsersManager::IsUserFound(const string &username) const {
  return users_.find(username) != users_.end();
}

bool UsersManager::IsEmailFound(const string &email) const {
  return emails_.find(email) != emails_.end();
}

bool UsersManager::IsPasswordCorrect(const string &pass,
                                     const string &username) const {
  return pass == users_.find(username)->second.GetPassword();
}

User* UsersManager::AccessUser() {
  string username = gpm::InputString("Enter Username:");
  string pass = gpm::InputString("Enter Password:");
  if (!IsUserFound(username)) {
    cout << "Error! User " << username << " isn't found.\n";
    return nullptr;
  }
  if (!IsPasswordCorrect(pass, username)) {
    cout << "Error! Password isn't correct.\n";
    return nullptr;
  }
  return &users_.find(username)->second;
}

bool UsersManager::AddUser() {
  string username = gpm::InputString("Enter the Username:");
  string email = gpm::InputString("Enter the Email:");
  string pass = gpm::InputString("Enter the Password:");
  bool is_admin = gpm::YesOrNoQn("Admin user?");
  if (IsUserFound(username)) {
    cout << "Error! Username " << username << " used before.\n";
    return false;
  }
  if (IsEmailFound(email)) {
    cout << "Error! Email " << email << " used before.\n";
    return false;
  }
  Update();
  User usr(username, email, pass, is_admin);
  users_.insert({username, usr});
  Save();
  return true;
}
