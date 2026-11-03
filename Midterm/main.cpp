#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector>
#include <string> 
#include <cstdlib>
#include <ctime>   
#include <algorithm> // Needed for case conversion in binary search
#include <cctype> 
#include <utility> // Needed for std::swap 

struct Book {
	std::string Title; 
	std::string Author; 
	std::string Publisher; 
	int ISBN; 
	int libraryID; 
	int loanStatus; 
};

enum LoanStatus {
	AVAILABLE, // 0, etc
	ONLOAN, 
	ONHOLD
};

Book* binarySearch(std::vector<Book>* ptrToBooks, int size, std::string target) {
	// Case conversion for comparison purposes
	std::transform(target.begin(), target.end(), target.begin(), [](unsigned char c) {
		return std::tolower(c);
    });
	int low = 0, high = size - 1;
	while (low <= high) {
		int center = low + (high - low)/2;
		std::string searchedTitle = ptrToBooks->at(center).Title;
		std::transform(searchedTitle.begin(), searchedTitle.end(), searchedTitle.begin(), [](unsigned char c) {
			return std::tolower(c);
		});
		if (searchedTitle == target) return &(ptrToBooks->at(center)); 
		if (searchedTitle < target) low = center + 1; 
		else high = center - 1;
	}
	// Failure mode
	return nullptr;
}

// User class containing search and display records permissions
class User {
	protected: 
		std::string username; 
		
	public:  
		User(std::string name) : username(name) {}
		void displayBooks(std::vector<Book>* ptrToBooks) {
			for (int r = 0; r < ptrToBooks->size(); r++) {
				Book currentBook = ptrToBooks->at(r);
				std::cout << "Item ID: " << currentBook.libraryID << std::endl;
				std::cout << "Title: " << currentBook.Title << std::endl;
				std::cout << "Author: " << currentBook.Author << std::endl;
				std::cout << "Loan Status: " << currentBook.loanStatus << std::endl;
				std::cout << "\n";
			}
		}
	void sortByTitle(std::vector<Book>* ptrToBooks, int size) {
		for (int e = 0; e < size - 1; e++) {				
			if (ptrToBooks->at(e).Title > ptrToBooks->at(e+1).Title) {
				std::swap(ptrToBooks->at(e), ptrToBooks->at(e+1));
			}
		}
	} 
};

class Admin : public User {
	public: 
		Admin(std::string name) : User(name) {}
		void addBook(std::vector<Book>* ptrToBooks, std::string title, std::string author, std::string publisher, int ISBN, int loanStatus) {
			srand(time(0)); 
			int randGenID = (rand() % 1000) + 1; 
			Book newBook = {title, author, publisher, ISBN, randGenID, loanStatus};
			ptrToBooks->push_back(newBook); 
			
			sortByTitle(ptrToBooks, ptrToBooks->size()); 
			
			std::ofstream outf("library_database.csv", std::ios::app); 
			if (!outf) {
				return;
			}
			outf << title << ',' << author << ',' << publisher << ',' << ISBN << ',' << randGenID << ',' << loanStatus;
		} 
		void deleteBook(std::vector<Book>* ptrToBooks) {
			std::string searchedTitle;
			std::cout << "Enter the title of the book you would like to delete: " << std::endl; 
			std::getline(std::cin, searchedTitle); 
			Book* searchResult = binarySearch(ptrToBooks, ptrToBooks->size(), searchedTitle);
			if (searchResult != nullptr) {
				std::cout << "You would like to delete the book " << searchResult->Title << " by " << searchResult->Author << " with library ID number " << searchResult->libraryID << "?" << std::endl;
				std::cout << "Enter 'Y' to confirm, and any other key to delete another record: " << std::endl; 
				std::string answer; 
				std::getline(std::cin, answer);
				if (!answer.empty() && answer[0] == 'y' || answer[0] == 'Y') {
					int indexForDeletion = searchResult - ptrToBooks->data(); 
					ptrToBooks->erase(ptrToBooks->begin() + indexForDeletion);
				}
			}
			else {
				std::cout << "Book not found, try again." << std::endl;
			}
			// Check to ensure all records are sorted 
			sortByTitle(ptrToBooks, ptrToBooks->size());
		}
};

int main() {
	std::vector<Book> recordsCollection = {};
	
	Admin authority("Moderator"); 
	authority.addBook(&recordsCollection, "Works of Love", "Soren Kierkegaard", "Harper Perennial", 61713279, 1); 
	authority.addBook(&recordsCollection, "Henry and June", "Anais Nin", "Mariner Books Classics", 015640057X, 0);
	authority.addBook(&recordsCollection, "Programming and Metaprogramming in the Human Biocomputer", "Julian Press", 0000000, 1);
	authority.displayBooks(&recordsCollection); 
	authority.deleteBook(&recordsCollection);
	authority.displayBooks(&recordsCollection); 
}