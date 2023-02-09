#include <iostream>
#include "App/App.h"
#include "Namespaces/gpm.h"

const char KUsersPath[] = "UsersManager/users_data.csv";
const char KBooksPath[] = "BooksManager/books_data.csv";
const char KBooksDir[] = "BooksManager/books/.run";
const char KSessionsPath[] = "SessionsManager/sessions_data.csv";

int main() {
  App app(KUsersPath, KBooksPath, KBooksDir, KSessionsPath);
  while (app.Run()) {
    gpm::PrintSeparator('=', 30);
  }
  return 0;
}
