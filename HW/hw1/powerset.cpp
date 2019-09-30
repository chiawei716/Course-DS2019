#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

void powerset(const vector<string>&, int size = 1);			// Get all subset of one set
void subset(const vector<string>&, const vector<string>&, int, int);	// Get subset in specific size 
void splitString(const string&, vector<string>&, const string&);	// Split string into vector

int main(){

	string str;		// input string
	vector<string> set;	// input set
	
	// Keep reading til EOF
	while(true){
		getline(cin, str);
		if(cin.eof()) break;
		splitString(str, set, " ");	// split the input strings
		cout<<"{}";	// always empty one
		powerset(set);	// print out all subsets	
	}
	
	return 0;
}

// Split string into vector
void splitString(const string& str, vector<string>& set, const string& token){

	// empty set
	set.clear();

	int start = 0;
	int end = str.find(token);
	
	// check until end of string
	while(end != string::npos){
		set.push_back(str.substr(start, end - start));
		start = end + token.length();
		end = str.find(token, start);
	}
	if(start != str.length())
		set.push_back(str.substr(start));
}

// Powerset
void powerset(const vector<string>& set, int size){
	if(size > set.size()) {
		cout << "\n";
		return;
	}
	vector<string> empty;
	subset(set, empty, 0, size++);
	powerset(set, size);
}

// Find all subset in specific size
void subset(const vector<string>& set, const vector<string>& lastSubset, int start, int left){
	if(set.size() - start < left) return;
	
	// include set[start]
	vector<string> newSubset;
	newSubset.assign(lastSubset.begin(), lastSubset.end());
	newSubset.push_back(set.at(start));
	if(left == 1){
		cout << "{" << newSubset.at(0);
		for(int i = 1; i < newSubset.size(); i++)
			cout << " " << newSubset.at(i);
		cout << "}";
	}
	else
		subset(set, newSubset, start + 1, left - 1);

	// reset
	newSubset.clear();
	newSubset.assign(lastSubset.begin(), lastSubset.end());

	// not include set[start]
	subset(set, newSubset, start + 1, left);

	return;
}
