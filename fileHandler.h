#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Coordinates.h"
#include "Config.h"
using namespace std;

bool clearRecent() {
	remove("recent_sim.temp");
	return true;
}

bool saveRecent(string text) {
	ofstream ofs("recent_sim.temp", ofstream::app);
	ofs << text;
	ofs.close();

	return true;
}

bool writeResults(string filename) {
	ifstream infile("recent_sim.temp");
	ofstream outfile("User_Results/" + filename + ".txt");
	string content = "";
	int i;

	for (i = 0; infile.eof() != true; i++) //get content of recent_sim into string
		content += infile.get();

	i--;
	content.erase(content.end() - 1);     //erase last character

	infile.close();

	outfile << content;                 //output string into the user's preferred file
	outfile.close();
	clearRecent();
	return true;
}


bool readConfig(Config& information) {
	ifstream ifs;
	ifs.open("config.ini", ifstream::in);
	if (!ios::failbit) {
		ifs.close();
		cout << "ERROR: Loading failed." << endl;
		return false;
	}
	if (ifs.eof()) {
		ifs.close();
		cout << "ERROR: File is empty." << endl;
		return false;
	}
	if (!ifs.good()) {
		ifs.close();
		cout << "ERROR: File couldn't be found. Either it was deleted, or has access issues." << endl;
		return false;
	}
	char c;

	c = ifs.get();
	string temp = "";
	while (c != '\n' and !ifs.eof()) {
		temp += c;
		c = ifs.get();
	}
	information.gen = stoi(temp);

	temp = "";
	c = ifs.get();
	while (c != '\n') {
		temp += c;
		c = ifs.get();
	}
	information.cell_no = stoi(temp);

	temp = "";
	Coordinates tempCord;
	c = ifs.get();
	while (ifs.good()) {

		temp = "";
		while (c != ' ' and !ifs.eof()) {
			temp += c;
			if (c == ' ')
				break;
			c = ifs.get();
		}
		tempCord.x = stoi(temp);

		temp = "";
		c = ifs.get();
		while (c != '\n' and !ifs.eof()) {
			temp += c;
			if (c == ' ')
				break;
			c = ifs.get();
		}
		tempCord.y = stoi(temp);
		temp = "";
		information.positions.push_back(tempCord);
		c = ifs.get();
	}
	ifs.close();
	return true;

}


bool writeConfig(Config information) {
	ofstream ofs("config.ini", ofstream::out);

	ofs << information.gen << endl;
	ofs << information.cell_no << endl;
	for (int i = 0; i < information.positions.size(); i++)
		ofs << information.positions[i].x << " " << information.positions[i].y << endl;


	ofs.close();

	return true;
}
