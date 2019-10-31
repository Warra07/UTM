/*
 * State.h
 *
 *  Created on: 29 oct. 2019
 *      Author: GIGABYTE
 */

#ifndef STATE_H_
#define STATE_H_
#include <string>
#include <map>
#include "Transition.h"

using namespace std;

class State {
public:
	State(bool final_state=0):final_state(final_state){
	};
	virtual ~State(){};
	void insertTransition(string initial_state, char input_symbol, string next_state,  char output_symbol,
			 char direction) {
		//TODO inserer une transition dans le map transitions.
		
		if(!hasInputSymbol(input_symbol))
		 {
			transitions.insert({input_symbol, Transition(initial_state, input_symbol, next_state, output_symbol, direction)}) ;
		}

            else throw "ERROR : we are in a deterministic turing machine, there can only be one transition for a particular state and input";
	}
	

	bool hasInputSymbol(char input_symbol) {
		//TODO Check si le symbol en entrer est deja dans la map de transition.
		if(transitions.find(input_symbol) == transitions.end()) {
			return 0;
		}
		return 1;
	}

	string transitioning(Tape& tape) {
		//TODO transitionner de l'etat actuel au nextstate, modifier la tape et déplacer l'entete
		// si aucune transition dans la liste des transitions n'est trouvé, reject
		 auto it = transitions.find(tape.getHeadInput());
				 if (it != transitions.end())
				 {
			             tape.setHeadInput(it->second.getOutputSymbol());
				     tape.moveHead(it->second.getDirection());

				     return it->second.getNextState() ;
				 }
                                else throw "ERROR : no transition found " ;
             }

	bool isFinalState() const {
		return final_state;
	}

	void setFinalState(bool finalState = 0) {
		final_state = finalState;
	}

private:
	bool final_state =0;
	map<char, Transition> transitions;
};

#endif /* STATE_H_ */
