#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <fstream>
#include "player.hpp"
#include "game.hpp"
using namespace std;

bool emptyFile(fstream& pFile) {
	return pFile.peek() == fstream::traits_type::eof();
}

void printHighScores(vector<player> users) {
	cout << "Username\t\tAverage Speed\t\tHigh Score\n";
	cout << "----------------------------------------------------------\n";	
	
	if (users.empty())	
		throw "No player data available.";		
	else			
		throw "unimplemented";
	
}

ostream& operator<<(ostream& out, player p) {
	out << p.username;
	return out;
}

istream& operator>>(istream& in, player p) {
	in >> p.username >> p.speed;
	return in;
}

int main() {
	srand(time(nullptr));

	
	fstream textFile;	
	try {
		textFile.open("textfile.txt", ios::in);
		if (textFile.fail())		
			throw -1;		
	}
	catch(int i){ cout << "File didn't open correctly, restart the game\n"; }
			

	game g;	
	g.game::loadTextLibrary(textFile);

	int entry = 0;
	
	cout << "\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "\t\t\t\t\t\tGET READY TO SPEEDTYPE!\n";
	cout << "\t\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~\n";

	do { 
		cout << "Select an option: \n1. New Game\n2. Exit Game\n";
		cin >> entry;
		switch (entry) {
		
		case 1:
			try {
				clear();
				g.game::readUser();			
				g.game::startGame();
			
				cout << "Would you like to play again?\n" << "press 'y' for yes and 'n' for no" << endl;
				char entry;
				do {
					cin >> entry;
					if (entry == 'y')
						g.startGame();
					else if (entry == 'n') {
						clear();
						break;
					}
					else
						cout << "Invald entry, please type 'y' for a new game and 'n' to return to the main menu. \n";

				} while (entry != 'y' && entry != 'n');
			} catch (const char* s) { cout << s << endl; }

			break;

		case 2: break; // exit program

		default: cout << "INVALID ENTRY PLEASE ENTER A VALID ENTRY" << endl;
			cin >> entry;
			break;
		}

	} while (entry != 2);	


	textFile.close();
	
	return 0;
}



