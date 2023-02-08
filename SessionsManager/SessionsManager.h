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
  bool IsSessionFound(const string &title, const string &username) const;
 public:
  explicit SessionsManager(const string &path);
  bool Update();
  bool Save() const;
  void Clear();
  Session*& AccessSession() const;
  bool AddSession();
};


#endif //ONLINE_BOOK_READER_SESSIONSMANAGER_H
