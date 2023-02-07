//
// Created by ahmed on 2/7/2023.
//

#ifndef ONLINE_BOOK_READER_BOOKSMANAGER_H
#define ONLINE_BOOK_READER_BOOKSMANAGER_H

#include <string>
#include <map>

using std::string;
using std::map;

class Book;

class BooksManager {
 private:
  string path_;
  map<string, Book> books_;
  bool IsBookFound(const string &title) const;
 public:
  explicit BooksManager(const string &path);
  bool Update();
  bool Save() const;
  void Clear();
  string AccessBook() const;
  bool AddBook();
};


#endif //ONLINE_BOOK_READER_BOOKSMANAGER_H
