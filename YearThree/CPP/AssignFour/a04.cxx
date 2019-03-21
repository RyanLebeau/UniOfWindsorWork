#include <string>
#include <vector>
#include <ostream>

#include "a04-provided.hxx"
#include "a04-main-provided.hxx"

std::ostream& write_csv_row(
  std::ostream& os, 
  std::vector<std::string> const& v
)
{
  // Write the code necessary to output v as a
  // CSV (comma-separated value) row using the
  // functions provided in a04-provided.hxx here.
  int lenV=v.size();
  for(auto x:v){
	  write_csv_field(os,x);
	  lenV--;
	  if(lenV>0)
		os.put(',');
  }
  os.put('\n');
  return os;
}

