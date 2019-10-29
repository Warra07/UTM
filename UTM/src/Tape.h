/*
 * Tape.h
 *
 *  Created on: 29 oct. 2019
 *      Author: GIGABYTE
 */

#ifndef TAPE_H_
#define TAPE_H_
#include <string>

using namespace std;

class Tape {
public:
	Tape(string input, int head_pos, char blank): input(input), head_pos(head_pos), blank(blank){};
	virtual ~Tape();

	int getHeadPos() const {
		return head_pos;
	}

	void setHeadPos(int headPos = 0) {
		head_pos = headPos;
	}

	const string& getInput() const {
		return input;
	}

	void setInput(const string &input) {
		this->input = input;
	}
	void setHeadInput(char inp) {
		input[head_pos] = inp;
	}

	char getHeadInput() {
		return input[head_pos];
	}

	void moveHead(char direction) {
		//TODO déplacer la téte a la direction demandé, jeté une exception
		// si la direction est inconnu.
	}

private:
	string input;
	int head_pos = 0;
	char blank='B';
};

#endif /* TAPE_H_ */
