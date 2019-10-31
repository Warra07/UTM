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
	Tape(string input, int head_pos, char blank): input(input), head_pos(head_pos), blank(blank) {};
	virtual ~Tape(){};

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
		if(direction == 'L') {

			if(head_pos == 0) {
				input.insert(0,1, blank);
			} else {
				head_pos--;
			}

		} else if (direction == 'R') {

			if(head_pos == input.length() - 1) {
				input.insert(input.length(),1, this->blank);

			}
			head_pos++;


		} else {
			throw "ERROR : Direction unknown";
		}

	}

private:
	string input;
	int head_pos = 0;
	char blank='B';
};

#endif /* TAPE_H_ */
