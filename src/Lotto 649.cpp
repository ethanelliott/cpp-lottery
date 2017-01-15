//============================================================================
// Name        : Lotto.cpp
// Author      : Ethan Elliott
// Version     :
// Copyright   : (c) Ethan Elliott 2015
// Description :
//============================================================================

//*********************************//   Ethan's Base Code   //*********************************//
/*
 (c)Copyright Ethan Elliott 2015

 Everything I will ever need in a c++ program.

 Contains base functions and vaiables for all programs, including a library of
 functions for other c++ programs.

 Use as the base include in all c++ prpograms.
 */
#ifndef ETHANLIB_H
#define ETHANLIB_H

//Main Class Macro
//Used to start the main function of the specified class. NOTE! This macro can only be called once.
#ifndef MAINCLASS_MACRO
#define MAINCLASS_MACRO

#define START_MAIN_CLASS(_ClassName_) \
	int main() \
	{ \
		Timer *m_a;  \
		System *m_s; \
		m_a = new Timer(); \
		m_s = new System(); \
		_ClassName_ *base = new _ClassName_(); \
		try  \
		{ \
			m_a->Start(); \
			m_a->Reset(); \
			throw(base->Main()); \
		} \
		catch(int e) \
		{ \
			m_a->Stop(); \
			m_s->Colour(m_s->white, m_s->black); \
			cout << "\nProgram returned " << e << ". Duration: " << m_a->Get() << "s \n"; \
			m_s->Pause(""); \
			return e; \
		} \
		return 0; \
	}
#endif

//Defines
#define DEFAULT_RETURN_VAL 0

//Includes
//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <limits>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <algorithm>
#include <vector>
#include <stdarg.h>

using namespace std;

typedef long double lodo;
typedef int colour;

class System {
private:
	HANDLE getConsole() {
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}
public:
	System(void) {

	}
	enum {
		black = 0,
		blue,
		green,
		aqua,
		red,
		purple,
		yellow,
		white,
		grey,
		lightBlue,
		lightGreen,
		lightAqua,
		lightRed,
		lightPurple,
		lightYellow,
		brightWhite
	};
	void Cls() {
		system("cls");
	}	//Cls

	void Pause(string text) {
		cout << "\n" << text;
		getch();
	}	//Pause

	void Title(string title) {
		stringstream x;
		x << "Title " << title;
		system(x.str().c_str());
	}

	void Resize(int Width, int Height) {
		_SMALL_RECT Rect;
		Rect.Top = 0;
		Rect.Left = 0;
		Rect.Bottom = Height - 1;
		Rect.Right = Width - 1;

		_COORD coord;
		coord.X = Width;
		coord.Y = Height;

		SetConsoleScreenBufferSize(getConsole(), coord);
		SetConsoleWindowInfo(getConsole(), TRUE, &Rect);
	}
	void CMDColour(char background = '0', char foreground = 'f') {
		stringstream x;
		x << "color " << background << foreground;
		system(x.str().c_str());
	}
	void Colour(colour background = 0, colour foreground = 15) {
		colour x;
		x = ((background * 16) + foreground);
		SetConsoleTextAttribute(getConsole(), x);
	}
};

string Round(const double input, const int decDigits) {
	stringstream out;
	out << fixed;
	out.precision(decDigits);
	out << input;
	return out.str();
}

bool MakeChoice(string question) {
	bool isDone = false;
	bool r = false;
	cout << "\n" << question << " [y / n]\n";
	while (!isDone) {
		switch (getch()) {
		case 'y':
			isDone = true;
			r = true;
			break;
		case 'n':
			isDone = true;
			r = false;
			break;
		default:
			isDone = false;
			break;
		}
	}
	return r;
}

string ntostr(double x) {
	stringstream z;
	z << x;
	return z.str();
}	//itostr

double strtod(string x) {
	return atof(x.c_str());
}	//strtoi

int RND(int seed, int max) {
	srand(time(NULL));
	srand((rand()) % 100 + seed);
	srand((rand()) % max + seed * 3);
	srand((rand()) % 100 + seed * 2);
	srand((rand()) % max + seed);
	srand((rand()) % 100 + seed * 3);
	srand((rand()) % max + seed * 2);
	return (rand() % max + 1);
}	//RND

class Timer {
	//Timer class
	//Allows for timing of events, without stopping the program
	//Uses ETime differences to calculate elapsed time to thousandth of a second.
private:
	bool Running;		//Clock is running
	double start;		//Start Time
	double stopTime;	//Stop Time
	double accumulatedTime;
	double ETime() {
		return (clock() * 0.001);
	}
public:
	Timer(void) {
		Running = false;
		start = 0;
		stopTime = 0;
		accumulatedTime = 0;
	}
	void Start() {
		if (!Running) {
			start = ETime();
			Running = true;
		}
	}
	void Stop() {
		double temp = Get();
		if (Running) {
			accumulatedTime = temp;
			Running = false;
		}
	}
	void Reset() {
		start = ETime();
		accumulatedTime = 0;
	}
	double Get() {
		double result;
		double currentTime = ETime();
		if (Running) {
			result = ((currentTime - start) + accumulatedTime);
		} else {
			result = accumulatedTime;
		}
		return result;
	}
	bool isRunning() {
		return Running;
	}
};

#endif // ETHANLIB_H

//*********************************//   END Ethan's Base Code   //*********************************//

const int NumOfDraws = 50;
#define DrawSize 6

class Lotto649 {
	System *sys;
	Timer *timer;
	int Draw[DrawSize];

public:
	Lotto649(void) {
		sys = new System();
		timer = new Timer();
		srand(time(0));
	}
	int Main() {
		bool isDone = false;
		int dupe = 0;
		string duplicate = "";
		Initialize();
		while (!isDone) {
			sys->Cls();
			dupe = 0;
			duplicate = "";
			for (int u = 0; u < NumOfDraws; u++) {
				duplicate = "";
				FillArrayRandom(Draw, (sizeof(Draw) / sizeof(Draw[0])));
				Sort(Draw, (sizeof(Draw) / sizeof(Draw[0])));
				if (CheckArray(Draw, (sizeof(Draw) / sizeof(Draw[0])),
						duplicate) > 0) {
					sys->Colour(sys->black, sys->lightRed);
					PrintArray(Draw, (sizeof(Draw) / sizeof(Draw[0])));
					cout << "\t*Duplicate(s): " << duplicate;
					dupe++;
				} else {
					sys->Colour(sys->black, sys->lightGreen);
					PrintArray(Draw, (sizeof(Draw) / sizeof(Draw[0])));
				}
				cout << "\n";
			}
			sys->Colour(sys->black, sys->lightGreen);
			cout << "Number of Draws: " << NumOfDraws << ".\n";
			cout << "Number of Draws with duplicates: " << dupe << ".\n";
			cout << "Percentage of draws without duplicates: "
					<< (((double) (NumOfDraws - dupe) / (double) NumOfDraws)
							* 100) << "%\n";
			isDone = !MakeChoice("Would you like to draw again?");
		}
		return 0;
	}
private:
	void Initialize() {
		sys->Resize(45, 20);
		sys->Title("Ethan's Lotto 649 Simulation");
		sys->Colour(sys->black, sys->lightGreen);
		sys->Cls();
	}
	void FillArrayRandom(int * Array, int arraySize) {
		Timer *ra;
		ra = new Timer();
		ra->Start();
		ra->Reset();
		for (int a = 1; a < 10; a++) {
			for (int z = 0; z <= arraySize; z++) {
				Sleep(2);
				Array[z] = RandomNumber((ra->Get() + (z * (z + a) * a)), 49, 1);
			}
		}
		Array[0] = RandomNumber(ra->Get() * Array[1] + Array[arraySize], 49, 1);
		ra->Stop();
		delete ra;
	}

	void PrintArray(int * Array, int arraySize) {
		for (int a = 0; a < arraySize; a++) {
			if (!((a + 1) == arraySize)) {
				cout << Array[a] << ",\t";
			} else {
				cout << Array[a];
			}
		}
	}

	int CheckArray(int * Array, int arraySize, string &storeNum) {
		int count = 0;
		int oldDupe = 0;
		stringstream d;
		for (int i = 0; i < arraySize; i++) {
			if (i == 0) {
				if (Array[i] == Array[i + 1]) {
					if (!(Array[i] == oldDupe)) {
						d << Array[i];
						d << ", ";
						count++;
					}
				}
			} else if (i == (arraySize - 1)) {
				if (Array[i] == Array[i - 1]) {
					if (!(Array[i] == oldDupe)) {
						d << Array[i];
						d << ", ";
						count++;
					}
				}
			} else {
				if (Array[i] == Array[i + 1] || Array[i] == Array[i - 1]) {
					if (!(Array[i] == oldDupe)) {
						d << Array[i];
						d << ", ";
						count++;
					}
				}
			}
			oldDupe = Array[i];
		}
		storeNum = d.str();
		return count;
	}

	void Sort(int* Array, const int ARRAY_SIZE = 0) {
		for (int x = (ARRAY_SIZE - 1); x >= 0; x--) {
			for (int x = (ARRAY_SIZE - 1); x >= 0; x--) {
				if (x != 0) {
					if (Array[x] < Array[x - 1]) {
						int oldVal = 0;
						oldVal = Array[x - 1];
						Array[x - 1] = Array[x];
						Array[x] = oldVal;
					}
				}
			}
		}
	}

	int RandomNumber(int seed, int max, int min) {
		time_t now = time(0);
		tm * ltm = localtime(&now);
		Sleep(2);
		srand(
				(rand() % 100) * ltm->tm_sec
						* (seed + (rand() % 1000 + 1) * (ltm->tm_sec + rand())));
		return ((rand() % max) + min);
	}	//RND
};

START_MAIN_CLASS(Lotto649);

