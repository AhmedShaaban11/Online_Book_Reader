//
// Created by ahmed on 2/7/2023.
//

#ifndef ONLINE_BOOK_READER_USER_H
#define ONLINE_BOOK_READER_USER_H

#include <string>

using std::string;

class User {
 private:
  string username_;
  string email_;
  string password_;
  bool is_admin_;
 public:
  explicit User(const string &line, const string &del = ",");
  User(const string &username, const string &email,
       const string &pass, bool is_admin);
  string GetUsername() const;
  string GetEmail() const;
  string GetPassword() const;
  bool IsAdmin() const;
  void Print() const;
  string ToString(const string &del = ",") const;
};


#endif //ONLINE_BOOK_READER_USER_H
