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
	    	cout << "ERROR : Too many arguments, check for spaces ?" << endl;
	    	return 1;

	    } else if(argc < 3) {
	    cout << "ERROR : Not enough arguments." << endl;
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
	    	try{
	    	TuringMachine tm = TuringMachine(fileName, parameters);
	    	tm.runTuringMachine(input);
	    	} catch(char const  *msg) {
	    	     cerr << msg << endl;};
	    }

	return 0;
}
