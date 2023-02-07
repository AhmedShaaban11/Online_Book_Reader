//
// Created by ahmed on 2/7/2023.
//

#include "User.h"
#include "../Namespaces/gpm.h"

User::User(const string &line, const string &del) {
  vector<string> entries = gpm::LineToWords(line, del);
  username_ = entries[0];
  email_ = entries[1];
  password_ = entries[2];
  is_admin_ = (bool) std::stoi(entries[3]);
}

User::User(const string &username, const string &email,
           const string &pass, bool is_admin)
           : username_{username}, email_{email},
           password_{pass}, is_admin_{is_admin} {

}

string User::GetUsername() const {
  return username_;
}

string User::GetEmail() const {
  return email_;
}

string User::GetPassword() const {
  return password_;
}

bool User::IsAdmin() const {
  return is_admin_;
}

void User::Print() const {
  cout << "Profile:\n";
  gpm::PrintSeparator('-', 15);
  cout << "Username: " << username_ << "\n";
  cout << "Email: " << email_ << "\n";
  cout << (is_admin_ ? "Admin" : "Customer") << " User\n";
}

string User::ToString(const string &del) const {
  return gpm::ToString(del, username_, email_, password_, std::to_string(is_admin_));
}
