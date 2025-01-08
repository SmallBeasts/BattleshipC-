#ifndef MYGAMECLASS_H
#define MYGAMECLASS_H

#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <limits>
#include <sstream>

class MyGame {
public:
	MyGame();
	MyGame(const std::string& filename);
	~MyGame();

	bool openFile();
	void closeFile();
	bool loadFile(int board = 0);
	bool MyGame::queryArray(const std::string& myquery, int board = 0);

private:
	std::fstream filestream;
	const std::string filename;
	int rows;
	int cols;
	bool loaded;
	std::vector<int> mine;					// Storage for the board mine
	std::vector<int> opp;					// Storage for the board opponent
	std::vector<int> my_shots;				// Storage for the board only including my shots
	std::vector<int> opp_shots;				// Storage for the board only including opponents
};

#endif // !MYGAMECLASS_H
