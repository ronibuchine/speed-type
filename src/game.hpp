#pragma once
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include "player.hpp"
#include <algorithm>
#include <conio.h>
#include "Windows.h"

using namespace std;
using namespace chrono_literals; // ns, us, ms, s, h, etc.
using chrono::system_clock;

void clear() {
	system("CLS");
}

class game
{
public:	
	game() : gameTime(0), paragraph(""), sampleTexts(), user() {}
	game(float t, string s, vector<string> v, player p) : gameTime(t), paragraph(s), sampleTexts(v), user(p) {}
	game(const game& g) : gameTime(g.gameTime), paragraph(g.paragraph), sampleTexts(g.sampleTexts), user(g.user) {}

	void setGameTime(float t) { gameTime = t; }
	void setParagraph(string p) { paragraph = p; }
	void setSampleTexts(vector<string> v) { sampleTexts = v; }
	void setUser(player p) { user = p; }
	float getGameTime() { return gameTime; }
	string getParagraph() { return paragraph; }
	vector<string> getSampleTexts() { return sampleTexts; }
	player getUser() { return user; }

	void readUser() {	
		cout << "Please enter your username:\n";
		cin >> user.username;			
	}

	void startGame() {
		clear();
		displayInstructions();
		Sleep(100);
		clear();
		gameCountdown();
		generateRandomText();
	
		cout << "\033[32m" << paragraph << "\033[0m" << endl;

		userInput();
		cout << "\n\nCongratulations " << user.username << "! You typed " << countWords() << " words in " << gameTime << " seconds. \nYour speed was " << user.speed << " WPM!\n"  << endl;	
	}

	void loadTextLibrary(fstream& textFile) {			
		char curr = textFile.get();
	
		for (int i = 0; !textFile.eof(); i++) {				
			sampleTexts.resize(sampleTexts.size() + 1);
			while (curr != '~') {		// '~' is delimiting character in text file				
				sampleTexts[i] = sampleTexts[i] + curr;
				curr = textFile.get();		
			}			
			curr = textFile.get(); curr = textFile.get(); // read '~' and '\n'		
		}	
	}
	

	void generateRandomText() {
		paragraph = sampleTexts[rand() % sampleTexts.size()];
	}

	void displayInstructions() {
		cout << "After the countdown a paragraph will be displayed below, type as fast as you can and don't make mistakes!" << endl;
		cout << "\n";
		cout << "\t\t\t\t----------------------------------\n";
		cout << "\t\t\t\t------------GOOD LUCK-------------\n";
		cout << "\t\t\t\t----------------------------------\n";
	}

	void gameCountdown() {
		cout << '3' << endl;
		Sleep(100);
		cout << '2' << endl;
		Sleep(100);
		cout << '1' << endl;
		Sleep(100);
		cout << "GO" << endl;
		Sleep(100);
	}

	void userInput() {
		/* main gameplay algorithm */
		float words = countWords();
		auto start = chrono::high_resolution_clock::now();
		char input;

		for (int i = 0; i < paragraph.size(); i++) {
			input = _getch();
			if (input != '\b')
				cout << input;
			else {		
				i--;
				continue;
			}

			while (input != paragraph[i]) {		
				if (_getch() == '\b')
				{	
					cout << '\b' << ' ' << '\b';
					i--;
					break;
				}
				else
					continue;
			}
		}
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
		gameTime = static_cast<float>(duration.count());
		user.speed = words / (gameTime / 60);
	}
	
	float countWords() {
		float wordcount = 0;

		for (char c : paragraph) 	
			if (c == ' ' || c == '.')
				wordcount++;
		
		return wordcount;
	}
	


private:
	float gameTime;
	string paragraph;
	vector<string> sampleTexts;
	player user;
	
};

