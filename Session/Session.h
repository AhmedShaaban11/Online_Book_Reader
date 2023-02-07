//
// Created by ahmed on 2/7/2023.
//

#ifndef ONLINE_BOOK_READER_SESSION_H
#define ONLINE_BOOK_READER_SESSION_H

#include <string>
#include <vector>
#include "../Book/Book.h"

using std::string;
using std::vector;

class Session {
 private:
  int user_id_;
  string book_title_;
  int last_page_;
  vector<string> lines_;
 public:
  explicit Session(const string &line, const string &del = ",");
  Session(int user_id, const string &book_title, int last_page);
  bool Open(const string &path);
  void Close();
  void Show() const;
  void NxtPage();
  void PrvPage();
  int GetUserId() const;
  string GetBookTitle() const;
  void Print() const;
  string ToString(const string &del = ",");
};


#endif //ONLINE_BOOK_READER_SESSION_H
