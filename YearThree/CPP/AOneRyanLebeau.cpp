/*
Ryan Lebeau
22/01/2018
Assignment One
COMP 3400
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
	string input;
	bool inQuotes = false;
	cout<<"Please enter a string:"<<endl;
	getline(cin, input);
	//loops through each character in the array
	for(unsigned int i=0;i<input.length();i++){
		//if a double quote was reached
		if(input.at(i)=='\"')
			inQuotes = !inQuotes;
		//if not inside a double quote change punct to whitespace
		else if(!inQuotes && (input.at(i)=='.' || input.at(i)==',' || input.at(i)=='-' ||
				input.at(i)=='?' || input.at(i)=='\'')){
			input.at(i) = ' ';
		}
	}
	cout<<endl<<input<<endl;
}
