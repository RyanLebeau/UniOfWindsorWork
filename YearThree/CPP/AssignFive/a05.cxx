#include <map>
#include <set>
#include <string>

#include "a05-provided.hxx"

auto inverse(std::map<std::string,std::size_t> const& m) ->
  std::map<std::size_t,std::set<std::string>>
{
  // Write the code necessary to compute the inverse of 
  // m and return the result here.
  using namespace std;
  map<size_t,set<string>> retval;
  for(auto kv:m){
	  auto result = retval.insert(make_pair(kv.second, set<string>{}));
	  result.first->second.insert(kv.first);
  }
  return {retval};
}