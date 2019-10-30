//============================================================================
// Name        : UTM.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "TuringMachine.h"
using namespace std;
#include <fstream>
#include <iterator>
#include <map>

int main(int argc, char *argv[]) {

	map<string, bool> parameters;
	string input;
	string fileName;
	parameters.insert({"-steps", 0});
	parameters.insert({"-state", 0});
	parameters.insert({"-tape", 0});

	    if(argc > parameters.size() + 3) {
	    	cout << "ERROR : Too many arguments, check for spaces ?";
	    	return 1;

	    } else if(argc < 3) {
	    cout << "ERROR : Too few arguments.";
	    return 1;
	    }
	    else {
	    	for (int i = 1; i < argc - 2; ++i){
	    		if(parameters.find(argv[i]) == parameters.end() ){
	    			cout << "ERROR : Unrocognized parameter '" << argv[i] << "'." << endl;
	    			return 1;

	    		} else {
	    			parameters[argv[i]] = true;
	    		}
	    	}

	    	fileName = argv[argc - 2];
	    	input = argv[argc - 1];

	    	TuringMachine tm = TuringMachine(fileName, parameters);
	    }

	 ofstream myfile1;
	  myfile1.open ("example.tm");
	  myfile1 << "Writing this to a file.\n";
	  myfile1.close();

	string line;
	  ifstream myfile ("example.tm");
	  if (myfile.is_open())
	  {
	    while ( getline (myfile,line) )
	    {
	      cout << line << '\n';
	    }
	    myfile.close();
	  }

	  else cout << "Unable to open file";




	cout << "!!!Hddddello World!!!" << endl; // prints !!!Hello World!!!
	cin >> line;
	return 0;
}
