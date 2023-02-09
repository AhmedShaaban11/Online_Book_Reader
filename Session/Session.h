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
  string username_;
  string book_title_;
  int last_page_;
  int lines_in_page_;
  vector<string> lines_;
 public:
  explicit Session(const string &line, const string &del = ",");
  Session(string username, const string &book_title, int last_page = 0);
  bool Open(const string &path);
  void Close();
  void Show() const;
  void NxtPage();
  void PrvPage();
  string GetUsername() const;
  string GetBookTitle() const;
  void Print() const;
  string ToString(const string &del = ",") const;
};


#endif //ONLINE_BOOK_READER_SESSION_H
