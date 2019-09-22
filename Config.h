#pragma once
#include <iostream>
#include "Coordinates.h"
#include <vector>
using namespace std;
class Config {
public:
	int gen;
	int cell_no;
	vector <Coordinates> positions;

	Config() {
		gen = 0;
		cell_no = 0;
	}

	Config(int Gen, int Cell_No, vector <Coordinates> Position) : gen(Gen), cell_no(Cell_No) {
		positions = Position;
	}

	void addPosition(int x, int y) {
		Coordinates temp(x, y);
		positions.push_back(temp);
	}
};