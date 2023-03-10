//
// Created by ahmed on 2/7/2023.
//

#include "Session.h"
#include "../Namespaces/gpm.h"

Session::Session(const string &line, const string &del) : lines_in_page_{15} {
  vector<string> entries = gpm::LineToWords(line, del);
  username_ = entries[0];
  book_title_ = entries[1];
  last_page_ = std::stoi(entries[2]);
}

Session::Session(string username, const string &book_title, int last_page)
    : username_{username}, book_title_{book_title}, last_page_{last_page},
    lines_in_page_{15} {

}

bool Session::Open(const string &path) {
  ifstream fin(path);
  if (fin.fail()) {
    cout << "Error! Cannot open " << book_title_ << " file.\n";
    return false;
  }
  string line;
  while (getline(fin, line)) { lines_.push_back(line); }
  fin.close();
  return true;
}

void Session::Close() {
  lines_.clear();
}

void Session::Show() const {
  int cur_line = lines_in_page_ * last_page_;
  for (int i = cur_line; i < cur_line + lines_in_page_; ++i) {
    if (i >= (int) lines_.size()) { return; }
    cout << lines_[i] << "\n";
  }
}

void Session::NxtPage() {
  if ((last_page_ + 1) * lines_in_page_ < (int) lines_.size()) {
    ++last_page_;
  }
}

void Session::PrvPage() {
  if (last_page_ > 0) { --last_page_; }
}

void Session::JumpToPage() {
  int pages = (int) lines_.size() / lines_in_page_;
  int c = gpm::InputInt("Enter the page number:", 0, pages);
  last_page_ = c;
}

string Session::GetUsername() const {
  return username_;
}

string Session::GetBookTitle() const {
  return book_title_;
}

void Session::Print() const {
  cout << "Session:\n";
  gpm::PrintSeparator('-', 15);
  cout << "Book: " << book_title_ << "\n";
  cout << "Last Page: " << last_page_ << "\n";
}

string Session::ToString(const string &del) const {
  return gpm::ToString(del, username_, book_title_,
                       std::to_string(last_page_));
}
