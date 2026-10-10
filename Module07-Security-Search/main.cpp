#include <iostream> 
#include <vector> 
#include <string>
#include <utility> // Need for std::swap 

// Structs are templates for objects with several related specially defined variables, not just one single mutable value 
struct Record {
	int ID; 
	std::string name; 
	std::string title; 
}; 

Record* binarySearch(std::vector<Record>* ptrToRecords, int size, int target) {
	int low = 0, high = size - 1;
	while (low <= high) {
		int center = low + (high - low)/2;
		if (ptrToRecords->at(center).ID = target) return &(ptrToRecords->at(center)); 
		if (ptrToRecords->at(center).ID < target) low = center + 1; 
		else high = target - 1;
	}
	// Failure mode
	return nullptr;
}

class User {
	// Like private access but extends to all derived classes 
	protected: 
		std::string username; 
		
	public: 
		// Constructor with unusual syntax (direct member initialization) 
		User(std::string name) : username(name) {}
		void displayRecords(std::vector<Record>* ptrToRecords) {
			for (int r = 0; r < ptrToRecords->size(); r++) {
				Record currentRecord = ptrToRecords->at(r);
				std::cout << "ID: 000" << currentRecord.ID << std::endl;
				std::cout << "Name: " << currentRecord.name << std::endl;
				std::cout << "Title: " << currentRecord.title << std::endl;
				std::cout << "\n";
			}
		}
		void sortByID(std::vector<Record>* ptrToRecords, int size) {
			for (int e = 0; e < size - 1; e++) {
				if (ptrToRecords->at(e).ID > ptrToRecords->at(e+1).ID) {
					// Swap two elements
					std::swap(ptrToRecords->at(e), ptrToRecords->at(e+1));
				}
			}
		} 
}; 

// Specifying public inheritance 
class Admin : public User {
	public: 
		Admin(std::string name) : User(name) {}
		void addRecord(std::vector<Record>* ptrToRecords, std::string name, std::string title) {
			// ID of last record in records vector, plus one: 
			// First, read off the last element in the collection using .back() method, then specify its ID variable 
			int lastID = ptrToRecords->back().ID;
			int newID = lastID + 1; 
			Record newRecord = {newID, name, title};
			// Append the newly created record to the end of the existing collection vector using .push_back method 
			ptrToRecords->push_back(newRecord); 
			
			// Probably redundant but: Check to ensure all records are sorted (numerically by ID) for binary search prerequisite 
			sortByID(ptrToRecords, ptrToRecords->size()); 
		} 
		void deleteRecord(std::vector<Record>* ptrToRecords) {
			std::string IDNumString;
			std::cout << "Enter the ID number of the record you would like to delete: " << std::endl; 
			std::getline(std::cin, IDNumString); 
			int IDNum = std::stoi(IDNumString);
			Record* searchResult = binarySearch(ptrToRecords, ptrToRecords->size(), IDNum);
			if (searchResult != nullptr) {
				std::cout << "You would like to delete record number " << IDNum << " associated with " << searchResult->name << " and " << searchResult->title << "?" << std::endl;
				std::cout << "Enter 'Y' to confirm, and any other key to delete another record: " << std::endl; 
				std::string answer; 
				std::getline(std::cin, answer);
				if (!answer.empty() && answer[0] == 'y' || answer[0] == 'Y') {
					int indexForDeletion = IDNum - 1; 
					ptrToRecords->erase(ptrToRecords->begin() + indexForDeletion);
				}
			}
			else {
				std::cout << "Record not found, try again." << std::endl;
			}
			// Check to ensure all records are sorted 
			sortByID(ptrToRecords, ptrToRecords->size());
		}
};

int main() {
	std::vector<Record> recordsCollection = {
		{0001, "Analind Angalee", "Director of Operations"},
		{0002, "Whirlwindia Wintress", "CEO of Bosses"},
		{0003, "Lint Prospero", "Chief Special Ops Recruitment Officer"}
	};
	
	// Test case: create an Admin user, add a record, delete a record: 
	Admin authority("Mod"); 
	authority.displayRecords(&recordsCollection); 
	authority.addRecord(&recordsCollection, "Auntie Hallifax", "Costumes Inspector"); 
	authority.displayRecords(&recordsCollection); 
	authority.deleteRecord(&recordsCollection);
	authority.displayRecords(&recordsCollection); 
}