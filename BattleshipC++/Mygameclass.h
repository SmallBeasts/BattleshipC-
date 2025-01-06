#ifndef MYGAMECLASS_H
#define MYGAMECLASS_H

#include <fstream>
#include <string>

class MyGame {
public:
	MyGame();
	MyGame(const std::string& filename);
	~MyGame();

	bool openFile();
	void closeFile();

private:
	std::fstream filestream;
	const std::string filename;
	bool loaded;

};

#endif // !MYGAMECLASS_H
