#ifndef a05_provided_hxx_
#define a05_provided_hxx_

#include <map>
#include <set>
#include <string>
#include <fstream>
#include <cstddef>
#include <iostream>

// function prototype for inverse()...
auto inverse(std::map<std::string,std::size_t> const& m) ->
  std::map<std::size_t,std::set<std::string>>;

//
// main() is not normally defined in a header file but is
// in this assignment.
//
int main()
{
  using namespace std;
  map<string,size_t> word_freqhist;

  ifstream in("hamlet-words.dat");
  for (string word; in >> word; )
  {
#if 0
    // Demonstrate building the frequency histogram
    // using operator[]()...
    ++word_freqhist[word];
#else
    // Demonstrate building the frequency histogram
    // using insert()...
    auto result = word_freqhist.insert(
      make_pair(
        word, 
        // create a default-constructed value...
        // i.e., here the std::size_t rvalue will be zero
        map<string,size_t>::mapped_type{}
      )
    );

    //
    // result's type is pair<iterator,bool> thus:
    //  1) result.first is the iterator returned
    //  2) result.second is true iff the element was added
    //
    // Since the iterator returned will either point to the
    // newly inserted entry OR the previously inserted
    // entry, result.second does not need to be checked
    // here.
    //
    ++result.first->second;
#endif
  }

  for (auto const& datum : inverse(word_freqhist))
  {
    cout << datum.first;
    for (auto const& v : datum.second)
      cout << ' ' << v;
    cout << '\n';
  }
}

#endif // #ifndef a05_provided_hxx_
