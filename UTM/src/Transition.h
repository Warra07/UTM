/*
 * Transition.h
 *
 *  Created on: 29 oct. 2019
 *      Author: GIGABYTE
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_
#include <string>

using namespace std;

class Transition {
public:
	Transition(string initial_state, char input_symbol, char output_symbol,
			char direction, string next_state): initial_state(initial_state), input_symbol(input_symbol),
			output_symbol(output_symbol),
			direction(direction),
			next_state(next_state) {};
	virtual ~Transition();

	const char& getDirection() const {
		return direction;
	}

	void setDirection(const char &direction) {
		this->direction = direction;
	}

	const char& getInputSymbol() const {
		return input_symbol;
	}

	void setInputSymbol(const char &inputSymbol) {
		input_symbol = inputSymbol;
	}

	const string& getNextState() const {
		return next_state;
	}

	void setNextState(const string &nextState) {
		next_state = nextState;
	}

	const char& getOutputSymbol() const {
		return output_symbol;
	}

	void setOutputSymbol(const char &outputSymbol) {
		output_symbol = outputSymbol;
	}

	const string& getInitialState() const {
		return initial_state;
	}

	void setInitialState(const string &initialState) {
		initial_state = initialState;
	}

private:
	char input_symbol, output_symbol, direction;
	string initial_state, next_state;
};

#endif /* TRANSITION_H_ */
