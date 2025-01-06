#include "Mygameclass.h"
#include <iostream>

MyGame::MyGame() : filestream(), filename(""), loaded(false) {}

MyGame::MyGame(const std::string& filename) : filename(filename), loaded(false) {
	openFile();
}

MyGame::~MyGame() {
	closeFile();
}

bool MyGame::openFile() {
	if (this->filestream.is_open()) {
		this->closeFile();
	}
	if (this->filename.empty()) {
		return false;
	}
	this->filestream.open(this->filename, std::ios::in);		// Opens for reading now
	if (this->filestream.is_open()) {
		this->loaded = true;
		return true;
	}
	else {
		return false;
	}
}

void MyGame::closeFile() {
	if (this->filestream.is_open()) {
		this->filestream.close();
		this->loaded = false;
	}
}



