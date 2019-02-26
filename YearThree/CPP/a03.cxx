/*
Ryan Lebeau
26/01/2019
Assignment Three
COMP 3400
*/

#include <regex> // for regular expression support
#include <vector>
#include <memory> // for std::make_shared and std::shared_ptr
#include <string>
#include <cstring> // for C's strcmp (see below)
#include <optional> // for std::optional
#include <iostream>
#include <filesystem> // for filesystem support

class program_input{
public:
  virtual ~program_input() { } // necessary to properly deallocate memory
  virtual bool read() = 0;
};

class yob_baby_name_file: public program_input{
private:
	std::string fname_;
	unsigned year_;
public:
	yob_baby_name_file(std::string fname, unsigned year){
		fname_=fname;
		year_=year;
	}
	bool read() override{
		std::cout << "Reading yob_baby_name_file " << fname_ << " for year " << year_ << "\n";
		return true;
	}
};

using all_inputs_type = std::vector<std::shared_ptr<program_input>>;

std::vector<bool> read_all_inputs(all_inputs_type& ai){
	std::vector<bool> retval;
	retval.reserve(ai.size());
	for (long unsigned int i=0; i<ai.size(); i++){
		try{
			retval.push_back(ai[i]->read());
		}
		catch(...){
			retval.push_back(false);
		}
	}
	return std::move(retval);
}

std::ostream& output_usage(std::ostream& os, char *argv[]){
	os << "Usage: " << argv[0] << " -d <directory>\n";
	return os;
}

int main(int argc, char *argv[]){
	namespace fs = std::filesystem;
	using namespace std;
	if(argc == 1){
		output_usage(std::cerr, argv) << "\tNOTE: Invalid argument(s) provided\n";
		return 1;
	}
	
	optional<string> scan_directory;
	for (int args_pos=1; args_pos < argc; ++args_pos){
		if(!strcmp(argv[args_pos],"-d")){
			if(args_pos+1 >= argc){
				output_usage(std::cerr, argv) << "\tNOTE: The -d option appears without a <directory> argument.\n";
				return 2;
			}
			else{
				++args_pos;
				scan_directory = argv[args_pos];
				continue;
			}
		}
		else{
			output_usage(std::cerr, argv) << "\tNOTE: Invalid argument(s) provided\n";
		}
	}
	
	all_inputs_type all_inputs;
	for (auto& entry : fs::recursive_directory_iterator(scan_directory.value())){
		if (!fs::is_regular_file(entry))
			continue;
		static regex const baby_name_file_regex( R"(yob(\d{4}).txt)" );
		smatch mr; // variable to hold regex matched results
		string const fname = entry.path().filename(); // only match the filename
		if (regex_match(fname, mr, baby_name_file_regex)){
			// regex_match() only returns true when the match is successful
			// you will be writing code in here below
			// for now use the following cout to see that it actually matches...
			all_inputs.push_back(make_shared<yob_baby_name_file>(fname, std::stoul(mr[1].str(), nullptr, 0)));
			//cout << "DEBUG: Match found: " << fname << '\n';
		}
	}
	
	read_all_inputs(all_inputs);

}