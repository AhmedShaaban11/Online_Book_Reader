//
// Created by ahmed on 2/7/2023.
//

#include <iostream>
#include "Book.h"
#include "../Namespaces/gpm.h"

using std::cout;

Book::Book(const string &title) : title_{title} {

}

string Book::GetTitle() const {
  return title_;
}

void Book::Print() const {
  cout << "Title: " << title_ << "\n";
}

string Book::ToString(const string &del) const {
  return gpm::ToString(del, title_);
}
