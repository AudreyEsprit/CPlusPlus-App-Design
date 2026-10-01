#include <iostream> 
#include <fstream> 
#include <sstream>
#include <string> 
#include <vector> 
#include "AddPenguin.h" 

bool askYesNo(const std::string& prompt) {
	std::cout << prompt << " (Y/N)" << std::endl;
	std::string addAnswer;
	std::getline(std::cin, addAnswer); 
	return !addAnswer.empty() && (addAnswer[0] == 'y' || addAnswer[0] == 'Y');
}

void addPenguinRecord() {
	std::cout << "Input values for the following four fields to add an additional Penguin record: ... " << std::endl; 
	std::cout << "Species: " << std::endl; 
	std::string species; 
	std::getline(std::cin, species); 
	std::cout << "Island: " << std::endl; 
	std::string island; 
	std::getline(std::cin, island); 
	std::cout << "Culmen Length (mm): " << std::endl; 
	std::string culmenLength;
	std::getline(std::cin, culmenLength); 
	std::cout << "Culmen Depth (mm): " << std::endl;
	std::string culmenDepth; 
	std::getline(std::cin, culmenDepth); 
	
	// How many fields/columns in penguins_size.csv ? Must calculate to preserve alingment with csv file 
	std::ifstream inputFile("penguins_size.csv"); 
	std::string fieldLabels; 
	std::vector<std::string> fields; 
	if (std::getline(inputFile, fieldLabels)) {
		std::stringstream ss(fieldLabels);
		std::string fieldName; 
		while (std::getline(ss, fieldName, ',')) {
			fields.push_back(fieldName); 
		}
	}
	int numFields = fields.size(); 
	int missingFields = numFields - 4;
	
	std::ofstream outf("penguins_size.csv", std::ios::app); 
	if (!outf) {
		return;
	}
	outf << species << ',' << island << ',' << culmenLength << ',' << culmenDepth;

	for (int f = 0; f < missingFields; f++) {
		outf << ",NA";
		if (f == (missingFields - 1)) {
			outf << "\n"; 
		}
	}
}
	
void displayPenguins() {
	std::cout << "Indicate how many records you would like to display:" << std::endl; 
	std::string numRowsString; 
	std::getline(std::cin, numRowsString);
	int numRows = std::stoi(numRowsString); 
	
	std::ifstream inputFile("penguins_size.csv");
	for (int r = 0; r < numRows; r++) {
		std::string line; 
		std::getline(inputFile, line);
		std::cout << line << std::endl; 
	}
}
	
void averageCulmenLength() {
	std::cout << "Indicate how many penguins' culmen lengths you would like to average:" << std::endl;
	std::string numString;
	std::getline(std::cin, numString);
	int numRequested = std::stoi(numString);
	
	std::ifstream inputFile("penguins_size.csv");
	std::string line; 
	std::getline(inputFile, line);
	
	std::vector<std::vector<std::string>> records; 
	
	for (int cl = 0; cl < numRequested; cl++) {
		std::getline(inputFile, line);
		std::stringstream ss(line);
		std::string cell; 
		std::vector<std::string> singleRow;
		
		while (std::getline(ss, cell, ',')) {
			singleRow.push_back(cell);
		}
		records.push_back(singleRow); 
	}
	
	float culmenLengthsTotal = 0.0f;
	int counted = 0; 
	for (int r = 0; r < records.size(); r++) {
		try {
            culmenLengthsTotal += std::stof(records[r][2]);
            counted++;
        } catch (const std::exception&) {
			// NA etc, skip 
        }
	}
	float culmenLengthAverge = culmenLengthsTotal/counted;
	std::cout << "Average length of culmen of queried penguins: " << culmenLengthAverge << std::endl; 
}

int main() {
	bool againAdd = askYesNo("Add Penguin Record?"); 
	while (againAdd) {
		std::cout << "You chose to add an additional record for a penguin..." << std::endl;
		addPenguinRecord();
		againAdd = askYesNo("Add another record?");
	}
	
	bool againDisplay = askYesNo("Display Penguin Records?");
	while (againDisplay) {
		std::cout << "You chose to add an additional record for a penguin..." << std::endl;
		displayPenguins();
		againDisplay = askYesNo("Display records again?");
	}

	bool againCalcAvg = askYesNo("Calculate Average of Penguin Culmen Lengths?");
	while (againCalcAvg) {
		std::cout << "You chose to calculate the average culmen lengths of the penguins..." << std::endl;
		averageCulmenLength();
		againCalcAvg = askYesNo("Calculate another average?"); 
	}
	
	std::cout << "Terminating program. Goodbye!" << std::endl; 
	return 0; 
}