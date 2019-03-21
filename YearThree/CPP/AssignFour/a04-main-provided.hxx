// Copyright (c) Paul Preney 2019. All Rights Reserved.
// For use by students in the University of Windsor's 2019W COMP3400 course.

#ifndef a04_main_provided_hxx_
#define a04_main_provided_hxx_

#include <string>
#include <vector>
#include <ostream>
#include <iostream>

#include "a04-provided.hxx"

// function prototype for write_csv_row()...
std::ostream& write_csv_row(
  std::ostream& os, 
  std::vector<std::string> const& v
);

//
// main() is not normally defined in a header file but it is in this
// assignment.
//
int main()
{
  using namespace std;
  while (cin)
  {
    auto result = read_csv_row(cin);
    write_csv_row(cout, result.first);
    if (result.second)
    {
      cerr << "A partial field was read in. Field=" << *result.second << '\n';
      return 1;
    }
  }
}

#endif // #ifndef a04_main_provided_hxx_
