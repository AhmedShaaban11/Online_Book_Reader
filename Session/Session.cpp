//
// Created by ahmed on 2/7/2023.
//

#include "Session.h"
#include "../Namespaces/gpm.h"

Session::Session(const string &line, const string &del) {
  vector<string> entries = gpm::LineToWords(line, del);
  user_id_ = std::stoi(entries[0]);
  book_title_ = entries[1];
  last_page_ = std::stoi(entries[2]);
}

Session::Session(int user_id, const string &book_title, int last_page)
    : user_id_{user_id}, book_title_{book_title}, last_page_{last_page} {

}

bool Session::Open(const string &path) {
  string full_path = path;
  if (path.back() != '/') { full_path += '/'; }
  full_path += book_title_ += ".txt";
  ifstream fin(full_path);
  if (fin.fail()) {
    cout << "Error! Cannot open " << book_title_ << " file.\n";
    return false;
  }
  string line;
  while (getline(cin, line)) { lines_.push_back(line); }
  fin.close();
  return true;
}

void Session::Close() {
  lines_.clear();
}

void Session::Show() const {
  int cur_line = 30 * last_page_;
  for (int i = cur_line; i < cur_line + 30; ++i) {
    if (i >= (int) lines_.size()) { return; }
    cout << lines_[i] << "\n";
  }
}

void Session::NxtPage() {
  if ((last_page_ + 1) * 30 < (int) lines_.size()) {
    ++last_page_;
  }
}

void Session::PrvPage() {
  if (last_page_ > 0) { --last_page_; }
}

int Session::GetUserId() const {
  return user_id_;
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

string Session::ToString(const string &del) {
  return gpm::ToString(del, std::to_string(user_id_),
                       book_title_, std::to_string(last_page_));
}
