#include <iostream> 

int main() {
	// Fields: id, topic, genre, mood, label 
	int ids[5] {54113, 53851, 53853, 53854, 53855}; // 1st, 2nd, 4th, 6th, 8th 
	std::string topics[5] {"star trek (TV)", "athena (myth)", "overcoming adversity", "dracula (literature)", "isaac newton (scientist)"}; 
	std::string genre[5] {"lounge", "salsa", "grunge", "christian rock", "grunge"};
	std::string mood[5] = {"mournful", "tense", "introspective", "motivated", "gloomy"}; 
	std::string label[5] = {"full fake", "full fake", "full fake", "full fake", "full fake"}; 
	
	std::string * ptr = &genre[0]; 
	int elem = sizeof(ids)/sizeof(ids[0]);
	
	// Iterating through 3 of 5 fields for all 5 records, using both index and pointer notation 
	// Because the fields are different lengths, the spacing is inconsistent 
	for (int i = 0; i < elem; i++) {
		std::cout << "ID:" << ids[i] << " | Topic: " << topics[i] << " | Genre: " << *ptr++ << std::endl; 
	}
	
	return 0; 
}