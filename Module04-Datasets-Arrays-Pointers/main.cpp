#include <iostream> 
#include <fstream>
#include <sstream> 
#include <string> 
#include <vector>

int main() {
	std::ifstream inputFile("penguins_size.csv"); 
	
	std::string columnLabels; 
	std::vector<std::string> columns; 

	// Reading column labels (first line) from inputFile 
	if (std::getline(inputFile, columnLabels)) {
		std::stringstream ss(columnLabels);
		std::string columnName; 
		while (std::getline(ss, columnName, ',')) {
			columns.push_back(columnName); 
		}
	}
	
	std::string line; 
	std::vector<std::vector<std::string>> records; 
	
	// Reading in the first 8 records as a 2 dimensional array (std::vector) 
	for (int i = 0; i < 8; i++) {
		std::getline(inputFile, line);
		
		std::stringstream ss(line);
		std::string cell; 
		std::vector<std::string> singleRow;
		
		while (std::getline(ss, cell, ',')) {
			singleRow.push_back(cell);
		}
		records.push_back(singleRow); 
	}
	
	// Iterating through column labels using pointers
	std::string * ptr = &columns[0]; 
	std::cout << "First four fields:" << std::endl;
	for (int cl = 0; cl < 4; cl++) {
		if (cl > 0) std::cout << ", ";
		std::cout << *ptr++; 
	}
	
	std::cout << "\n" << "\n"; 

	for (size_t r = 0; r < records.size(); r++) {
		for (size_t e = 0; e < 4; e++) {
			std::cout << columns[e] << ": " << records[r][e] << std::endl; 
		}
		std::cout << "\n"; 
	}
	
	return 0; 
}