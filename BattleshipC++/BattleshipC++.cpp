// BattleshipC++.cpp : Defines the entry point for the application.
//

#include "BattleshipC++.h"
#include "Helper.h"
#include <iostream>
#include <string>
#include "UserInteract.h"

using namespace std;

int main()
{
	std::string myinput;
	output_format("Hello and welcome to C++ battleship.\nType --load <filename> to load a file,"
				  " --guess <guesses in x#, x#... format where x is a group of letters and # is a number\n"
				  "--exit or --quit to quit.  Finally you can query the array loaded by typing in x#.\n"
				  "--help will get you this text again.");
	while (true) {						// Main loop, forced out when quit or exit is put in.
		cin >> myinput;
		//evaluate_input(myinput, )
	}
	return 0;
}
