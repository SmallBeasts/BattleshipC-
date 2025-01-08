#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>


class Matrix {
private:
    int rows;
    int columns;
    std::vector<int> data; // Flat vector to hold the matrix elements

public:
    // Constructor
    Matrix() : rows(0), columns(0) {}

    // Accessors for rows and columns
    int getRows() const { return rows; }
    int getColumns() const { return columns; }

    // Method to load matrix dimensions and data from a file
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        // Read dimensions
        file >> rows;
        file >> columns;
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Skip to the next line

        if (rows <= 0 || columns <= 0) {
            throw std::invalid_argument("Invalid dimensions in file");
        }

        // Resize the vector to match the dimensions
        data.resize(rows * columns);

        // Read matrix data row by row
        for (int i = 0; i < rows; ++i) {
            std::string line;
            if (!std::getline(file, line)) {
                throw std::runtime_error("Insufficient data in file");
            }

            std::istringstream lineStream(line);
            std::string value;
            for (int j = 0; j < columns; ++j) {
                if (!std::getline(lineStream, value, ',')) {
                    throw std::runtime_error("Invalid row format");
                }
                data[i * columns + j] = std::stoi(value);
            }
        }

        file.close();
    }

    // Method to access elements (const and non-const overloads)
    int& at(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= columns) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[row * columns + col];
    }

    const int& at(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= columns) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[row * columns + col];
    }

    // Method to display the matrix
    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                std::cout << at(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    try {
        Matrix matrix;

        // Load dimensions and data from a file
        matrix.loadFromFile("matrix_data.txt");

        // Display the matrix
        matrix.display();

        // Access an element
        std::cout << "Element at (1, 2): " << matrix.at(1, 2) << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
