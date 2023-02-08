//
// Created by ahmed on 2/7/2023.
//

#include <fstream>
#include "SessionsManager.h"
#include "../Session/Session.h"
#include "../Namespaces/gpm.h"

using std::ifstream;
using std::ofstream;

SessionsManager::SessionsManager(const string &path) : path_{gpm::CorrectPath(path)} {
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

auto SessionsManager::IsSessionFound(const string &title, const string &username) {
  auto begin = sessions_.find(username)->second.begin();
  auto end = sessions_.find(username)->second.end();
  auto it = begin;
  for (; it != end; ++it) {
    if (it->GetBookTitle() == title) { return it; }
  }
  return end;
}

Session* SessionsManager::AccessSession(const string &username) {
  string title = gpm::InputString("Enter the book title:");
  Update();
  auto end = sessions_.find(username)->second.end();
  auto it = IsSessionFound(title, username);
  if (it == end) {
    cout << "Error! Session for " << title << " not found.\n";
    return nullptr;
  }
  return &*it;
}

void SessionsManager::AddSession(const string &username) {
  string title = gpm::InputString("Enter the book title:");
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
