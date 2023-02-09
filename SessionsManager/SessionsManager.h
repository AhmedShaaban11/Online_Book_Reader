//
// Created by ahmed on 2/7/2023.
//

#ifndef ONLINE_BOOK_READER_SESSIONSMANAGER_H
#define ONLINE_BOOK_READER_SESSIONSMANAGER_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class Session;

class SessionsManager {
 private:
  string path_;
  map<string, vector<Session>> sessions_;
  int IsSessionFound(const string &title, const string &username);
  void AddSession(const string &title, const string &username);
 public:
  explicit SessionsManager(const string &path);
  bool Update();
  bool Save() const;
  void Clear();
  Session* AccessSession(const string &title, const string &username);
  void PrintHistory(const string &username) const;
};


#endif //ONLINE_BOOK_READER_SESSIONSMANAGER_H
