/*
Ryan Lebeau
22/01/2018
Assignment One
COMP 3400
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct employee
{
  unsigned id;
  string name;
  double salary;
};

istream& operator >>(istream& is, employee& e)
{
  is >> e.id;
  is >> e.name;
  is >> e.salary;
  
  return is;
}

ostream& operator <<(ostream& os, employee const& e)
{
  cout<<e.id<<","<<e.name<<","<<e.salary;
  return os;
}

ostream& operator <<(ostream& os, vector<employee> const& v)
{
  for(auto i:v){
	cout<<"("<<i<<")";
  }
  return os;
}

int main(){
	vector<employee> employees;
	employee data = employee();
	
	//read in data to vector
	while(cin >> data){
		employees.push_back(data);
	}

	// abort if we did not reach the end-of-file, i.e., an error occurred...
	if (!cin.eof()){
		cerr << "ERROR: Invalid input. Aborting." << endl;
		return 1;
	}

	// output the employee records read in...
	cout << "     RAW_DATA: " << employees << endl;
	
	// create a local scope for some short-lived variables...
	{
		//sort by name
		vector<employee> employees_copy = employees;
		stable_sort(employees_copy.begin(), employees_copy.end(), [](employee const &e1, employee const &e2){return (e1.name < e2.name);});
		// output data...
		cout << "      BY_NAME: " << employees_copy << endl;
	}
	
	//sort by salary
	stable_sort(employees.begin(), employees.end(), [](employee const &e1, employee const &e2){return (e1.salary < e2.salary);});
	// output data...
	cout << "    BY_SALARY: " << employees << endl;
	
	//find range from 20k to 30k
	auto low_end = find_if(employees.begin(), employees.end(), [](employee const &e){
		if(e.salary >= 20000.0 && e.salary <= 30000.0)
			return true;
		else
			return false;
	});
	auto high_end = find_if(low_end, employees.end(), [](employee const &e){
		if(e.salary > 30000.0)
			return true;
		else
			return false;
	});
	//adjust salary between range
	for(auto i=low_end; i!=high_end; ++i){
		i->salary *= 1.02;
	}
	// output data...
	cout << "SALARY_ADJUST: " << employees << endl;
	
	reverse(low_end, high_end);
	// output data...
	cout << "AFTER_REVERSE: " << employees << endl;
}