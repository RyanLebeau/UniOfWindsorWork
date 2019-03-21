// Copyright (c) Paul Preney 2019. All Rights Reserved.
// For use by students in the University of Windsor's 2019W COMP3400 course.

#ifndef a04_provided_hxx_
#define a04_provided_hxx_

#include <string>
#include <istream>
#include <sstream>
#include <cctype>
#include <optional>
#include <utility>
#include <vector>

//
// ignore_whitespace_except_end_of_line(std::istream& is)
// function
//
// This function ignores all whitespace characters on is except the end-of-line
// characters. This function considers the end-of-line characters to be
// either a CR (i.e., '\r') or LF (i.e., '\n').
//
std::istream& ignore_whitespace_except_end_of_line(std::istream& is);

//
// std::string read_csv_field(std::istream& is)
// function
//
// This function will read in the next CSV field (i.e., "column") in to an
// instance of std::string. If the stream is bad or failed then the string
// returned was an improperly delimited field, i.e., it represents a
// partially read field.
//
std::string read_csv_field(std::istream& is);

//
// std::ostream& write_csv_field(std::ostream& os, std::string const& f)
// function
//
// This function will output f as a CSV-formatted field (column)
// appropriately enclosed in quotation marks if the content of f
// requires such.
//
std::ostream& write_csv_field(std::ostream& os, std::string const& f);

//
// auto read_csv_row(std::istream& is) ->
//   std::pair< std::vector<std::string>, std::optional<std::string> >
// function
//
// This function will read in the next CSV row in to a std::vector of
// std::string returned in the .first member of std::pair.
// If the last CSV field was not properly delimited (i.e., it was partially
// read in) then that partially read in field is returned in the .second
// member of std::pair.
//
auto read_csv_row(std::istream& is) ->
  std::pair<
    std::vector<std::string>,
    std::optional<std::string>
  >
;

#endif // #ifndef a04_provided_hxx_
