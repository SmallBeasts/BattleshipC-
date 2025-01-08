#include "Mygameclass.h"
#include <iostream>
#include "Helper.h"
#include "UserInteract.h"

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

bool MyGame::loadFile(int board = 0) {
	/* Load and read in the file*/
	std::vector<int> * tmpboard;
	if (!this->filestream.is_open()) {							// File is not open
		return false;
	}

	// Read in the dimensions
	this->filestream >> this->rows;
	this->filestream >> this->cols;

	if (this->rows <= 0 || this->cols <= 0 || this->rows > std::numeric_limits<int16_t>::max() || this->cols > std::numeric_limits<int16_t>::max()) {
		output_format("Rows or columns are invalid!");
		closeFile();
		return false;
	}

	if (board == 0) {
		tmpboard = &mine;
	}

	tmpboard->resize(rows * cols);									// Resize the vector to the correct size.
	// Read in the board data row by row
	for (int i = 0; i < rows; ++i) {
		std::string line;
		if (!std::getline(filestream, line)) {
			output_format("The file appears to be corrupt in the data.");
			closeFile();
			return false;
		}
		
		// A line is read in now parse the columns
		std::istringstream linestream(line);
		std::string value;
		for (int j = 0; j < cols; ++j) {
			if (!std::getline(linestream, value, ',')) {
				output_format("Invalid data.");
				closeFile();
				return false;
			}
			// Convert the string to an int and store it in the vector at the correct location
			tmpboard->at(i * cols + j) = std::stoi(value);
		}
	}
	return true;
}

int convertRowtoInt(const std::string& row) {
	int result = 0;
	for (char ch : row) {
		if (ch >= 'A' && ch <= 'Z') {
			result = result * 26 + (ch - 'A');
		}
		else {
			output_format("Invalid row format.");
		}
	}
}
bool MyGame::queryArray(const std::string& myquery, int board = 0) {			// Query the data by converting and checking the string, board = 0 for mine
	if (myquery.empty()) {														// Empty query returns false and error
		output_format("Invalid query.");
		return false;
	}
	std::vector<int>* tmpboard;													// Assign tmpboard to a board for later.
	if (board == 0) {
		tmpboard = &mine;
	}
	// Convert the query to row int format
	std::stringstream ss(myquery);
	std::string cell;
	int tmpcol = 0;																// This will hold the column number later
	int myrow = 0;																// This will hold the row number later
	std::ostringstream myOutput;												// This string will contain the output for the function
	while (std::getline(ss, cell, ',')) {										// Parse the string for commas
		size_t i = 0;
		tmpcol = 0;																// Initialize for each query
		while (i < cell.size() && isalpha(cell[i])) {
			++i;
		}

		if (i == 0 || i == cell.size()) {
			output_format("The query is in invalid format.");
			return false;
		}

		std::string tmprow = cell.substr(0, i);								// Get only the letters
		tmpcol = std::stoi(cell.substr(i));									// Get the numbers and convert it directly to a column number.

		// Convert the letters into base 26 row number
		myrow = 0;															// Initialize for each query
		for (char ch : tmprow) {
			if (ch >= 'A' && ch <= 'Z') {									// Valid letter
				myrow = myrow * 26 + (ch - 'A');							
			}
		}
		if (myrow > rows || tmpcol > cols) {								// Add OOB to the output string and print error line
			std::ostringstream tmpresult;
			tmpresult << "Out of bounds at Row(" << myrow << ") and column (" << tmpcol << ")" << std::endl;
			output_format(tmpresult.str());
			myOutput << "OOB,";
			return false;
		}
		else {
			myOutput << tmpboard->at(myrow * cols + tmpcol) << ',';
		}
	}	// While loop concludes
	std::string result = myOutput.str();
	output_format(result.substr(0, result.size() - 1));
}



