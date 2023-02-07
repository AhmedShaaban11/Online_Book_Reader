//
// Created by ahmed on 2/7/2023.
//

#ifndef ONLINE_BOOK_READER_BOOK_H
#define ONLINE_BOOK_READER_BOOK_H

#include <string>

using std::string;

class Book {
 private:
  string title_;
 public:
  explicit Book(const string &title);
  string GetTitle() const;
  void Print() const;
  string ToString(const string &del = ",") const;
};


#endif //ONLINE_BOOK_READER_BOOK_H
