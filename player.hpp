#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
class player
{
	friend class game;
public: 

	// ctors
	player() : username(""), speed(-1) {};
	player(string u, float s) : username(u), speed(s) {};
	player(const player& p) : username(p.username), speed(p.speed) {};

	// setters/getters
	void setUsername(string s) { username = s; }
	
	string getUsername() const { return username; }
	
	 
	player operator=(const player& p) {
		username = p.username;
		speed = p.speed;
		return *this;
	}

	friend ostream& operator<<(ostream& out, player p);
	friend istream& operator>>(istream& in, player p);

private:
	string username;
	float speed; // in WPM		
};


