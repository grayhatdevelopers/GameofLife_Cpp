// Game_Of_Life.cpp : This file contains the 'main' function. Program execution begins and ends there.

//     _____                                         __     _        _    __        
//    / ____|                                       / _|   | |      (_)  / _|       
//   | |  __    __ _   _ __ ___     ___      ___   | |_    | |       _  | |_    ___ 
//   | | |_ |  / _` | | '_ ` _ \   / _ \    / _ \  |  _|   | |      | | |  _|  / _ \
//   | |__| | | (_| | | | | | | | |  __/   | (_) | | |     | |____  | | | |   |  __/
//    \_____|  \__,_| |_| |_| |_|  \___|    \___/  |_|     |______| |_| |_|    \___|
//                                                                                  
//    A simple implementation of Conway's Game of Life, using C++ and the Windows Terminal.
//    Created by Saad Bazaz.
//    FAST-NUCES University, Islamabad, Pakistan.                                           
                                                         


#include <iostream>
#include "fileHandler.h"
using namespace std;

int neighborCheck(Coordinates fromAlive, int index, vector<Coordinates> alive) {
	int neighbor_count = 0;
	for (int i = 0; i < alive.size(); i++) {
		if (i == index) continue;

		if (neighbor_count > 4) {
			break;
		}
		if (fromAlive.x - 1 == alive[i].x and fromAlive.y - 1 == alive[i].y) neighbor_count++;
		if (fromAlive.x == alive[i].x and fromAlive.y - 1 == alive[i].y) neighbor_count++;
		if (fromAlive.x + 1 == alive[i].x and fromAlive.y - 1 == alive[i].y) neighbor_count++;
		if (fromAlive.x - 1 == alive[i].x and fromAlive.y == alive[i].y) neighbor_count++;
		if (fromAlive.x + 1 == alive[i].x and fromAlive.y == alive[i].y) neighbor_count++;
		if (fromAlive.x - 1 == alive[i].x and fromAlive.y + 1 == alive[i].y) neighbor_count++;
		if (fromAlive.x == alive[i].x and fromAlive.y + 1 == alive[i].y) neighbor_count++;
		if (fromAlive.x + 1 == alive[i].x and fromAlive.y + 1 == alive[i].y) neighbor_count++;

	}
	cout << " Cell " << fromAlive.x << " , " << fromAlive.y << " has " << neighbor_count<<" neighbors." << endl;
	return neighbor_count;
}


bool checkBirth(Coordinates possibleChild, int index, vector<Coordinates> alive) {
	if (3 == neighborCheck(possibleChild, index, alive)) {
		return true;
	}
	return false;
}

bool checkLife(Coordinates possibleDeath, int index, vector<Coordinates> alive) {
	int count = neighborCheck(possibleDeath, index, alive);
	if (count > 3 or count <2) {
		return false;
	}
	return true;
}

int searchAlive(Coordinates neighbor, vector<Coordinates> alive) {
	for (int i = 0; i < alive.size(); i++) {
		if (neighbor.x == alive[i].x and neighbor.y == alive[i].y) {
			return i;
		}
	}
	return -1;
}

int searchAlive(int x, int y, vector<Coordinates> alive) {
	for (int i = 0; i < alive.size(); i++) {
		if (x == alive[i].x and y == alive[i].y) {
			return i;
		}
	}
	return -1;
}

int main()
{
	//Graphic and Intro
	cout << "\n		 _____                                         __      _        _    __\n		/ ____|                                       / _|    | |      (_) / _|\n		| |  __    __ _   _ __ ___     ___      ___   | |_    | |       _  | |_    ___\n		| | |_ |  / _` | | '_ ` _ \\   / _ \\    / _ \\  |  _|   | |      | | |  _|  / _ \\\n		| |__| | | (_| | | | | | | | |  __/   | (_) | | |     | |____  | | | |   |  __ /\n		 \_____ | \\__, _| |_| |_| |_| \\___ |    \\___/  |_|     |______| |_| |_|   \\___ |\n" << endl << endl;

	cout << "Welcome to John Conway's 'Game of Life', developed by FAST student Saad Ahmed Bazaz." << endl;
	cout << "Would you like to load the existing save file or create a new one?  ( L / C )" << endl;
	clearRecent();
	char userOption;
	bool wrong_input;
	Config userConfig;
	do {
		cin >> userOption;

		switch (userOption) {
		case 'L': //loading config.ini from file system
		case 'l':
			wrong_input = false;
			if (!readConfig(userConfig)) {
				cout << "There was an error reading the file. Please create a new file..." << endl;
				wrong_input = true;
			}
			else
				cout << "File loaded successfully!" << endl;
			break;

		case 'C': //creating or overwriting config.ini in file system
		case 'c':
			wrong_input = false;
			cout << endl;
			cout << "----------------- NEW CONFIGURATION -----------------" << endl;
			cout << "How many generations would you like to run to?" << endl;
			int gen;
			cin >> gen;
			userConfig.gen = gen;
			cout << endl;

			cout << "How many cells would be alive in the beginning?" << endl;
			int cell;
			cin >> cell;
			userConfig.cell_no = cell;
			cout << endl;

			int tempx, tempy;
			for (int i = 0; i < cell; i++) {
				cout << "Enter X coordinate of Cell #" << i + 1 << ": ";
				cin >> tempx;
				cout << "Enter Y coordinate of Cell #" << i + 1 << ": ";
				cin >> tempy;
				cout << endl;

				Coordinates TempCoordinate(tempx, tempy); //creating a temporary coordinate object which can be pushed into the Positions vector
				userConfig.positions.push_back(TempCoordinate);
			}

			if (writeConfig(userConfig)) {
				cout << "User Configuration successfully written to file." << endl;
			}
			else
				cout << "There was an error saving the configuration." << endl;
			break;


		default:
			cout << "Please enter L or C. ";
			wrong_input = true;
		}

	} while (wrong_input);

	//Preview simulation settings
	cout << "___________________________________________" << endl << endl;
	cout << "Preview your initial simulation settings..." << endl;
	cout << "Generations: " << userConfig.gen << endl;
	cout << "Number of starting cells: " << userConfig.cell_no << endl << endl;

	//for (int i=0; i<userConfig.positions.size(); i++)
	//	cout << userConfig.positions[i].x << " " << userConfig.positions[i].y<<endl;

	cout << "Enter E to run the simulation." << endl;
	cout << "Need to change some settings before running the simulation? Restart the program." << endl;
	cout << "If you'd like to exit, enter Z." << endl;
	cin >> userOption;

	if (userOption == 'z' or userOption == 'Z') {
		cout << "Thank you for using this program!" << endl;
		exit(1);
	}
	else if (userOption == 'E' or userOption == 'e') {

			vector <Coordinates> alive;
			vector <Coordinates> neighbors;
			
			//swap(alive[0], alive[2]);
			//std::iter_swap(alive.begin(), alive.begin() + 1);
			cout << endl;
			cout << "INITIALIZATION..." << endl;
			for (int i = 0; i < userConfig.cell_no; i++) {		//initialize alive cells with userConfig values
				alive.push_back(userConfig.positions[i]);
				cout << "#" << i << ": " << "Cell ( " << alive[i].x << " , " << alive[i].y << " )";
				cout<<" will be born in the next generation."<< endl;
			}
			vector<Coordinates> tempBirth;
			vector<Coordinates> tempAlive;
			vector<int> deadCounter;
			
			bool Canvas[25][25] = { {0} };



			cin >> userOption;
		for (int i = 0; i < userConfig.gen; i++) {

			system("CLS");
			for (int i = 0; i < 25; i++) {
				for (int j = 0; j < 25; j++) {
					Canvas[i][j]=0;
				}
			}

			for (int i = 0; i < alive.size(); i++) {
				if (alive[i].x<=25 and alive[i].x>=0 and alive[i].y<=25 and alive[i].y>=0)
				Canvas[alive[i].x][alive[i].y] = 1;
			}



			string content;
			content = ("=========     GENERATION " + to_string((i + 1)));
			content+="     =========\n";


			//Display currently alive array
			for (int i = 0; i < alive.size(); i++) {
				content += "#";
				content += to_string(i); 
				content += (": Cell ( ");
				content += (to_string(alive[i].x) + " , " + to_string(alive[i].y));
				content += " )";
				content += " is alive! \n";
			}



			//Generation building logic............


			//clear neighbors and tempAlive
			neighbors.clear();
			tempAlive.clear();
			tempBirth.clear();
			deadCounter.clear();


			//Create new neighbors and check which values repeat exactly 3 times
			
			
			//Creating neighbors which do not conflict with Alive cells...
			for (int i = 0; i < alive.size(); i++) {
				if (searchAlive(alive[i].x - 1, alive[i].y - 1, alive) == -1) {
					Coordinates tempCoordinate(alive[i].x - 1, alive[i].y - 1);
					neighbors.push_back(tempCoordinate);
				}

				if (searchAlive(alive[i].x, alive[i].y - 1, alive) == -1) {
					Coordinates tempCoordinate(alive[i].x, alive[i].y - 1);
					neighbors.push_back(tempCoordinate);
				}

				if (searchAlive(alive[i].x + 1, alive[i].y - 1, alive) == -1) {
					Coordinates tempCoordinate(alive[i].x + 1, alive[i].y - 1);
					neighbors.push_back(tempCoordinate);
				}

				if (searchAlive(alive[i].x - 1, alive[i].y, alive) == -1) {
					Coordinates tempCoordinate(alive[i].x - 1, alive[i].y);
					neighbors.push_back(tempCoordinate);
				}
				
				if (searchAlive(alive[i].x + 1, alive[i].y, alive) == -1) {
					Coordinates tempCoordinate(alive[i].x + 1, alive[i].y);
					neighbors.push_back(tempCoordinate);
				}

				if (searchAlive(alive[i].x - 1, alive[i].y + 1, alive) == -1) {
					Coordinates tempCoordinate(alive[i].x - 1, alive[i].y + 1);
					neighbors.push_back(tempCoordinate);
				}

				if (searchAlive(alive[i].x, alive[i].y + 1, alive) == -1) {
					Coordinates tempCoordinate(alive[i].x, alive[i].y + 1);
					neighbors.push_back(tempCoordinate);
				}

				if (searchAlive(alive[i].x + 1, alive[i].y + 1, alive) == -1) {
					Coordinates tempCoordinate(alive[i].x + 1, alive[i].y + 1);
					neighbors.push_back(tempCoordinate);
				}
			}

			//Checking duplicates... if the value has been repeated 3 times that means it's surrounded by 3 live cells. So then push_back onto tempAlive vector
			int live_counter = 0;
			for (int i = 0; i < neighbors.size(); i++) {
				for (int j = i+1; j < neighbors.size(); j++) {
					if (neighbors[i].x == neighbors[j].x and neighbors[i].y == neighbors[j].y) {
						live_counter++;
						for (int k = j; k < neighbors.size() - 1; k++){
							neighbors[k] = neighbors[k + 1];
						}
						j--;
						neighbors.pop_back();

					}
				}
				cout << "Dead cell " << neighbors[i].x << " , " << neighbors[i].y << " has " << live_counter << " alive neighbors." << endl;
				if (live_counter == 2) {
					cout << neighbors[i].x << " , " << neighbors[i].y << " will be born in the next generation." << endl;
					tempBirth.push_back(neighbors[i]);
				}
				live_counter=0;
			}
			
			//Check for deaths and eliminate dead elements
			for (int i = 0; i < alive.size(); i++) {
				if (!checkLife(alive[i], i, alive)) {
					cout << alive[i].x<< " , "<< alive[i].y << " will die in the next generation." << endl;
					deadCounter.push_back(i); //saving indexes which will die

				}
			}


		for (int i = deadCounter.size()-1; i >=0; i--) { //starting from the last element, going down towards zero. As the deadCounter is arranged in ascending order, this prevents us from losing important index information when deleting values from "alive"
			for (int k = deadCounter[i]; k < alive.size()-1; k++)
				alive[k] = alive[k + 1]; //replacing the current value with the next one
		}

		for (int i = 0; i < deadCounter.size(); i++) {
			alive.pop_back();
		}

			//Append newly born cells to currently living cells
			alive.insert(alive.end(), tempBirth.begin(), tempBirth.end());

	

			content += '\n';
			char display = '_';
			for (int i = 0; i < 25; i++) {
				for (int j = 0; j < 25; j++) {
					if (Canvas[i][j]) content += 254;
					else content += '_';

					content += ' ';
				}
				content += '\n';
			}
			content += "\n \n";
			saveRecent(content);
			cout << content << endl;


			cout << "To skip to the end, enter S." << endl;
			cout << "Enter any other key to continue." << endl;
			cin >> userOption;
			if (userOption == 'S' or userOption == 's')
				break;
			//char** Canvas = new char* [50];
			//for (int i = 0; i < 50; i++) {
			//	Canvas[i] = new char[50];
			//}

			//cout << endl << endl << endl;
			//for (int i = 0; i < 50; i++) {
			//	//cout << "                                            loop1" << endl;
			//	for (int j = 0; j < 50; j++) {
			//		//cout << "loop2" << endl;
			//		Canvas[i][j] = live_cell;
			//		//cout << Canvas[i][j] << endl;
			//	}
			//	//cout << endl;
			//}

			//for (int i = 0; i < 50; i++) {
			//	//cout << "                                            loop1" << endl;
			//	for (int j = 0; j < 50; j++) {
			//		//cout << "loop2" << endl;
			//		cout<< Canvas[i][j];
			//		//cout << Canvas[i][j] << endl;
			//	}
			//	cout << endl;
			//	//cout << endl;
			//}


		}

	}
	cout << endl;
	cout << "-----------   SIMULATION COMPLETED   -----------" << endl;
	cout << "Would you like to save your results? ( Y / N )" << endl;

	cin >> userOption;
	if (userOption == 'y' or userOption == 'Y') {
		cout << "Enter the name of the file you wish to save: ";
		string _filename="results";
		cin.ignore();
		getline(cin, _filename);
		if (writeResults(_filename)) {
			cout << "Results saved successfully!" << endl;
		}
	}
	else if (userOption == 'n' or userOption == 'N') {
		clearRecent();
	}
	cout << endl;
	cout << "Thank you for using this program!" << endl<<endl<<endl;

}