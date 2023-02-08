//
// Created by ahmed on 2/7/2023.
//

#include <fstream>
#include <sstream>
#include "BooksManager.h"
#include "../Namespaces/gpm.h"
#include "../Book/Book.h"

using std::ifstream;
using std::ofstream;
using std::stringstream;

BooksManager::BooksManager(const string &path, const string &books_path)
    : path_{gpm::CorrectPath(path)}, books_path_{books_path} {
  Update();
}

bool BooksManager::Update() {
  ifstream fin(path_);
  if (fin.fail()) {
    cout << "Error! Cannot open " << path_ << " file.\n";
    return false;
  }
  Clear();
  string line;
  while (getline(fin, line)) {
    Book book(line);
    books_.insert({book.GetTitle(), book});
  }
  fin.close();
  return true;
}

bool BooksManager::Save() const {
  ofstream fout(path_, std::ios::out);
  if (fout.fail()) {
    cout << "Error! Cannot open " << path_ << " file.\n";
    return false;
  }
  for (const auto &p : books_) {
    fout << p.second.ToString() << "\n";
  }
  fout.close();
  return true;
}

void BooksManager::Clear() {
  books_.clear();
}

bool BooksManager::IsBookFound(const string &title) const {
  return books_.find(title) != books_.end();
}

string BooksManager::AccessBook() const {
  string title = gpm::InputString("Enter the title:");
  if (!IsBookFound(title)) {
    cout << "Error! Book " << title << " isn't found.\n";
    return "";
  }
  return title;
}

bool BooksManager::AddBook() {
  string title = gpm::InputString("Enter the title:");
  string src_path = gpm::InputString("Enter the full path of the book:");
  ifstream fin(src_path);
  if (fin.fail()) {
    cout << "Error! Cannot open " << path_ << " file.\n";
    return false;
  }
  // Copying the file into dst
  string dst_path = books_path_;
  if (dst_path.back() != '/') { dst_path += "/"; }
  dst_path += title += ".txt";
  ofstream fout(dst_path, std::ios::out);
  if (fout.fail()) {
    cout << "Error! Cannot open " << dst_path << " file.\n";
    return false;
  }
  fout << fin.rdbuf();
  fin.close();
  fout.close();
  // Adding the book
  Update();
  Book book(title);
  books_.insert({title, book});
  Save();
  return true;
}

void BooksManager::PrintBooks() const {
  cout << "List of Books:\n";
  gpm::PrintSeparator('-', 15);
  for (auto &p : books_) {
    cout << p.first << "\n";
  }
}