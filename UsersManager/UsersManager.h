//
// Created by ahmed on 2/7/2023.
//

#ifndef ONLINE_BOOK_READER_USERSMANAGER_H
#define ONLINE_BOOK_READER_USERSMANAGER_H

#include <string>
#include <map>
#include <set>

using std::string;
using std::map;
using std::set;

class User;

class UsersManager {
 private:
  string path_;
  map<string, User> users_;
  set<string> emails_;
  bool IsUserFound(const string &username) const;
  bool IsEmailFound(const string &email) const;
  bool IsPasswordCorrect(const string &pass, const string &username) const;
 public:
  explicit UsersManager(const string &path);
  bool Update();
  bool Save() const;
  void Clear();
  User* AccessUser();
  bool AddUser();
};


#endif //ONLINE_BOOK_READER_USERSMANAGER_H
