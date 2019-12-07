/*
 * TuringMachine.h
 *
 *  Created on: 29 oct. 2019
 *      Author: GIGABYTE
 */

#ifndef TURINGMACHINE_H_
#define TURINGMACHINE_H_
#include <map>
#include <string>
#include "Tape.h"
#include "State.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <set>


using namespace std;

class TuringMachine {
public:
	TuringMachine(string fileName, map<string, bool>& parameters) {

		//TODO initialiser la machine de turing selon le fichier en parametre
		/*
		 * Verifier toutes erreur de syntax possibble et renvoyer une exception si une
		 * erreur de syntax est trouvé.
		 * firstState : stocke le nom de l'etat initial
		 *
		 * states: la liste de tout les etats de la machine sont contenue dans un map, chaque
		 * element du map contient comme clé le nom de l'etat, et comme element un objet State.
		 * Ne pas ajouter un element qui existe deja dans le map.
		 *
		 * pour chaque element dans states, ajouter les transitions lié à un etat dans le map "transitions"
		 * de l'objet State, Si une clé dans le map transitions existe deja, renvoyer une exception (nous somme
		 * dans un cas deterministe, il ne peut y'avoir qu'une seul transition pour un etat et un input en particulier).
		 *
		 *De plus si la machine ne contient aucun etat ou aucune transition, renovyer une exception.
		 */


		this->parameters = parameters;


		map<string, string> patternMatcher;

		patternMatcher.insert({"initial", "\\((.*?)\\)"});
		patternMatcher.insert({"state","\\((.*?),([TF])\\)"});
		patternMatcher.insert({"blank", "\\((.)\\)"});
		patternMatcher.insert({"symbol", "\\((.),([TF])\\)"});
		patternMatcher.insert({"transition", "\\((.*?),(.),(.*?),(.),([RL])\\)"});



		 string line;
		  ifstream myfile (fileName);
		  if (myfile.is_open())
		  {
		    while ( getline (myfile,line) )
		    {

		      std::regex head("^(.*?)\\(\\b");

		      std::smatch matches;

		      if(std::regex_search(line, matches, head)) {
			        string match = matches.str(1);

			        if(patternMatcher.find(match) == patternMatcher.end()) {

			        	throw "ERROR : unkown turing machine component : " + match + " at line : " + line;

			        } else {

					      string bodyReg = patternMatcher[match];
					      std::regex body(bodyReg);

					      std::smatch bodyMatches;

					      if(std::regex_search(line, bodyMatches, body)) {

					    	  if (match == "initial") {
					    	    this->firstState = bodyMatches.str(1);

					    	    if(states.find(bodyMatches.str(1)) == states.end()) {
					    	      this->states.insert({bodyMatches.str(1), State(0)});
					    	     }
					    	   }


					    	  else if (match == "state") {
					    		  //string finalState_symbol = bodyMatches.str(2);
								  bool finalState = bodyMatches.str(2)[0] == 'T' ? true : false;

					    	    if(states.find(bodyMatches.str(1)) == states.end()) {
					    	    this->states.insert({bodyMatches.str(1), State(finalState)});
					    	    } else {

					    	      this->states[bodyMatches.str(1)].setFinalState(finalState);
					    	    }
					    	  }


					    	  else if (match == "blank"){
					    	    this->blank = bodyMatches.str(1)[0];
					    	    this->alphabet_symbols.insert(this->blank);
					    	  }




					    	  else if (match == "symbol") {


					    	    if(this->alphabet_symbols.find(bodyMatches.str(1)[0]) == this->alphabet_symbols.end()) {

					    	    if(bodyMatches.str(2)[0] == 'T') {
					    	      this->input_symbols.insert(bodyMatches.str(1)[0]);
					    	    }

					    	    this->alphabet_symbols.insert(bodyMatches.str(1)[0]);
					    	    } else {
					    	      if(bodyMatches.str(2)[0] == 'F') {
					    	        this->input_symbols.erase(bodyMatches.str(1)[0]);
					    	      }
					    	    }
					    	  }







					    	  else if (match ==  "transition") {
					    	    if(states.find(bodyMatches.str(1)) == states.end()) {
					    	      this->states.insert({bodyMatches.str(1), State(false)});
					    	    }
					    	    if(this->states[bodyMatches.str(1)].hasInputSymbol(bodyMatches.str(2)[0])) {
					    	    	throw "ERROR : Deterministic turing machine have only one transition per (state,symbol) found 2 at ("
									+ bodyMatches.str(1) + "," + bodyMatches.str(2)[0] + ").";
					    	    }
					    	    this->states[bodyMatches.str(1)].insertTransition(bodyMatches.str(1), bodyMatches.str(2)[0],
					    	    		bodyMatches.str(3),  bodyMatches.str(4)[0],
					    	                           bodyMatches.str(5)[0]);

					    	    if(this->alphabet_symbols.find(bodyMatches.str(2)[0]) == this->alphabet_symbols.end()) {
					    	      this->alphabet_symbols.insert(bodyMatches.str(2)[0]);
					    	      this->input_symbols.insert(bodyMatches.str(2)[0]);
					    	    }
					    	    if(this->alphabet_symbols.find(bodyMatches.str(4)[0]) == this->alphabet_symbols.end()) {

					    	      this->alphabet_symbols.insert(bodyMatches.str(4)[0]);
					    	      this->input_symbols.insert(bodyMatches.str(4)[0]);

					    	    }
					    	  }



					      } else {
					    	  throw "ERROR : unrecognized " + match + " argument at line : " + line;
					      }

			        }


		      } else {
		    	  throw  "ERROR: no matching for line : " + line;
		      }

		    }
		    myfile.close();
		  }

		  else throw "ERROR : Unable to open file";



		  if(this->firstState == "") {
			  throw "ERROR: initial State missing";
		  }



	}
	void runTuringMachine(string input) {

		string state = this->firstState;

		for(char character: input){
			auto it = input_symbols.find(character);
			if(it == input_symbols.end()) {
				string err = "ERROR: Character ";
				err += character;
				err += " not in input symbols.";
				throw err;
			}
		}


		tape = new Tape(input, 0, this->blank);

		while(!(this->states[state].isFinalState())) {

			if( this->parameters["-steps"]) {
				this->states[state].showCurrentTransition(tape->getHeadInput(), state);
			}

			state = this->states[state].transitioning(*tape);

		}




		if(this->parameters["-state"]) {
			cout << "Final State: " << state << endl;
		}

		if (this->parameters["-tape"]) {

			string regexString = "([^";
			regexString += this->blank;
			regexString += "].*[^";
			regexString += this->blank;
			regexString += "]|[^";
			regexString += this->blank;
			regexString += "])";


		      std::regex reg(regexString);


		      std::smatch bodyMatches;
		      tape->setInput(blank + tape->getInput() + blank);
		     if(std::regex_search(tape->getInput(), bodyMatches, reg)) {
		    	 cout << "Final Tape : " << bodyMatches.str(1) << endl;
		     } else {
		    	 cout << "Final Tape : " << tape->getInput() << endl;
		     }
		}
	}
	virtual ~TuringMachine(){};


private:
Tape* tape;
map<string, State> states;
string inputs;
string firstState = "";
char blank='B';
map<string, bool> parameters;
set<char> input_symbols, alphabet_symbols;

};



#endif /* TURINGMACHINE_H_ */
