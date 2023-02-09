//
// Created by ahmed on 2/7/2023.
//

#include <fstream>
#include "SessionsManager.h"
#include "../Session/Session.h"
#include "../Namespaces/gpm.h"

using std::ifstream;
using std::ofstream;

SessionsManager::SessionsManager(const string &path) : path_{path} {
  Update();
}

bool SessionsManager::Update() {
  ifstream fin(path_);
  if (fin.fail()) {
    cout << "Error! cannot open the file " << path_ << "\n";
    return false;
  }
  Clear();
  string line;
  while (getline(fin, line)) {
    Session sess(line);
    sessions_["j"].push_back(sess);
  }
  fin.close();
  return true;
}

bool SessionsManager::Save() const {
  ofstream fout(path_, std::ios::out);
  if (fout.fail()) {
    cout << "Error! cannot open the file " << path_ << "\n";
    return false;
  }
  for (auto &p : sessions_) {
    for (auto &sess : p.second) {
      fout << sess.ToString() << "\n";
    }
  }
  fout.close();
  return true;
}

void SessionsManager::Clear() {
  sessions_.clear();
}

int SessionsManager::IsSessionFound(const string &title, const string &username) {
  if (sessions_.find(username) == sessions_.end()) { return -1; }
  vector<Session> &sessions = sessions_.find(username)->second;
  for (int i = 0; i < (int) sessions.size(); ++i) {
    if (sessions[i].GetBookTitle() == title) { return i; }
  }
  return -1;
}

Session* SessionsManager::AccessSession(const string &title, const string &username) {
  Update();
  int idx = IsSessionFound(title, username);
  if (idx == -1) {
    AddSession(title, username);
    return &sessions_[username].back();
  }
  return &sessions_[username][idx];
}

void SessionsManager::AddSession(const string &title, const string &username) {
  Update();
  Session sess(username, title, 0);
  sessions_[username].push_back(sess);
  Save();
}

void SessionsManager::PrintHistory(const string &username) const {
  if (sessions_.find(username) == sessions_.end()) { return; }
  cout << "History of Sessions:\n";
  gpm::PrintSeparator('-', 15);
  for (auto &sess : sessions_.find(username)->second) {
    sess.Print();
  }
}
