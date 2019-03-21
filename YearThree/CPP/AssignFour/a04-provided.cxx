// Copyright (c) Paul Preney 2019. All Rights Reserved.
// For use by students in the University of Windsor's 2019W COMP3400 course.

#include "a04-provided.hxx"

std::istream& ignore_whitespace_except_end_of_line(std::istream& is)
{
  for (
    // read the next character without consuming it...
    auto ch = is.peek();

    // loop condition...
    ch != std::istream::traits_type::eof()
      && ch != '\r'
      && ch != '\n'
      && std::isspace(ch)
    ;

    // read in next char...
    ch = is.peek()
  )
  {
    is.get(); // consume the character...
  }
  return is;
}

std::string read_csv_field(std::istream& is)
{
  auto ch = is.peek();
  std::ostringstream buffer;

  // First character is either a quotation mark or not.
  // Use lambda so quote_ch can be const...
  std::optional<decltype(ch)> const quote_ch =
    [ch]() -> std::optional<decltype(ch)>
    {
      if (ch == '"' || ch == '\'')
        return ch;
      else
        return std::nullopt;
    }()
  ;
  if (quote_ch.has_value())
  {
    is.get(); ch = is.peek(); // consume quote and peek
  }

  bool end_of_field = false;
  for (; ch != std::istream::traits_type::eof(); ch = is.peek())
  {
    if (quote_ch && ch == *quote_ch)
    {
      // handle escaped quotes and quote delimeter...
      is.get(); ch = is.peek(); // consume and peek
      if (ch == *quote_ch)
      {
        buffer.put(*quote_ch); // place escaped quotation mark into buffer
        is.get(); ch = is.peek(); // consume and peek
      }
      else
      {
        // this is not an escaped quotation mark so it is the end of the
        // CSV field...
        end_of_field = true;
        break;
      }
    }
    else if (!quote_ch && (ch == ',' || ch == '\r' || ch == '\n'))
    {
      // encountered comma or end-of-line, it is the end of this
      // CSV field...
      end_of_field = true;
      break;
    }
    else
    {
      buffer.put(ch); // place ch into buffer
      is.get(); // consume the character
    }
  }

  if (!end_of_field)
    is.setstate(std::ios::failbit);
  return buffer.str();
}

std::ostream& write_csv_field(std::ostream& os, std::string const& f)
{
  std::optional<char> const quote_ch =
    [&f]() -> std::optional<char>
    {
      bool quote_req = false;

      // scan field for non-printable chars, whitespace, ", or '...
      for (auto i=begin(f), iEnd=end(f); i != iEnd && !quote_req; ++i)
        quote_req |= !isprint(*i) || isspace(*i) 
          || (*i == '"') || (*i == '\'') || (*i == ',');

      if (quote_req)
        return '"';
      else
        return std::nullopt;
    }()
  ;

  if (quote_ch)
    os.put(*quote_ch);

  for (auto const& ch : f)
  {
    if (quote_ch && *quote_ch == ch)
      os.put(ch);
    os.put(ch);
  }

  if (quote_ch)
    os.put(*quote_ch);

  return os;
}

auto read_csv_row(std::istream& is) ->
  std::pair<
    std::vector<std::string>,
    std::optional<std::string>
  >
{
  std::vector<std::string> row;
  std::optional<std::string> partial_field;

  while (is)
  {
    // NOTE: Initial whitespace is not ignored. The first character
    //       should either be a quotation mark or the start of the field
    //       data. If the first character is not a quotation mark then
    //       the field is delimited by a comma.

    // read the next field...
    std::string field = read_csv_field(is);

    if (is)
      // append the field to row...
      row.push_back(std::move(field));
    else if (is.eof())
    {
      // append the field to row...
      row.push_back(std::move(field));
      break;
    }
    else
    {
      // stream is bad or failed...
      if (!field.empty())
        partial_field = field; // partial read occurred
      break;
    }

    // NOTE: Trailing field whitespace is not ignored here.

    // handle comma or end-of-line...
    auto ch = is.peek();
    if (ch == std::istream::traits_type::eof())
      break; // eof (or error) encountered, we're done reading in row
    else if (ch == ',')
      is.get(); // comma encountered, consume comma, possibly more fields
    else if (ch == '\r')
    {
      is.get(); ch = is.peek(); // consume CR and peek
      if (ch == '\n')
        is.get(); // consume LF
      else
        is.setstate(std::ios::failbit); // LF does not exist
      break; // end of row, terminate loop
    }
    else if (ch == '\n')
    {
      is.get(); // consume LF
      break; // end of row, terminate loop
    }
    else
    {
      is.setstate(std::ios::failbit); // invalid character, fail
      break;
    }
  }

  return { std::move(row), std::move(partial_field) };
}
