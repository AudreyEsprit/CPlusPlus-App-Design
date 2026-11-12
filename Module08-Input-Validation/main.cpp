// Check input for: type, range, format, and filled/unfilled
#include <iostream> 
#include <string> 
#include <vector> 
#include <array> 
#include <algorithm> 
#include <cctype> // Needed for isalpha() check for format validation 

struct EnvelopeParameter {
	bool tempoInSeconds {false};
	double tempoValue {0.0};
};

int main() {
	// Type and range check: number of voices 
	std::cout << "Please select the number of voices (1-8)" << std::endl; 
	int numVoices; 
	bool validInput {false}; 
	while (!validInput) {
		if (std::cin >> numVoices && numVoices < 9 && numVoices > 0) {
			validInput = true; 
			std::cout << "You selected " << numVoices << " voices" << std::endl;
		}
		else {
			std::cout << "Invalid input, please try again." << std::endl;
		}
	}
	
	/* 
	Another solution is to accept input as a string
	std::string inputAsString;
	std::getline(std::cin, inputAsString);
	Then convert to desired type eg integer
	int inputAsInt = std::stio(inputAsString); 
	*/
	
	// Format check: ASDR values as either seconds or fractions of beat 
	std::cout << "Please input envelope parameters, one at a time (If in seconds, include 's', 'sec' or some other alphabetic characters in input. If fraction of beat, select a value between 32/1 and 1/64)" << std::endl; 
	std::string attack, sustain, decay, release; 
	std::vector<std::string*> ptrsToParameters = {&attack, &sustain, &decay, &release};
	std::array<std::string, 4> parameterNames = {"Attack", "Sustain", "Decay", "Release"};
	std::array<EnvelopeParameter, 4> envelopeParameterObjects; 
	for (std::size_t i = 0; i < ptrsToParameters.size(); i++) {
		while (true) {
			std::cout << parameterNames[i] << ": " << std::endl; 
			std::string& input = *ptrsToParameters[i];
			// If input stream closes or crashes
			if (!std::getline(std::cin, input)) return 0; 
			
			if (input.empty()) {
				std::cout << "Input cannot be empty, try again." << std::endl; 
				continue; 
			}
			
			// Two separate possible cases, validating, fraction or time input in seconds
			try {
				// Case 1: Fractional input, with '/' character 
				std::size_t slashPos = input.find('/'); 
				if (slashPos != std::string::npos) {
					double numer = std::stod(input.substr(0, slashPos));
					double denom = std::stod(input.substr(slashPos + 1));
					if (denom == 0.0) {
						std::cout << "Invalid entry. Denominator cannot be zero. Try again" << std::endl;
						continue;
                    }
					envelopeParameterObjects[i].tempoInSeconds = false;
					envelopeParameterObjects[i].tempoValue = numer / denom; 
					std::cout << parameterNames[i] << " stored as " << envelopeParameterObjects[i].tempoValue << " beats" << std::endl;
					break; 
				}
				
				// Case 2: Time input in seconds 
				bool any_alphabetic = std::any_of(ptrsToParameters[i]->begin(), ptrsToParameters[i]->end(), [](unsigned char ch) {
					return std::isalpha(ch);
					});
					
				// Input in seconds, chopped off alphabetic characters
				double rawVal= std::stod(input);
				if (any_alphabetic) {
					envelopeParameterObjects[i].tempoInSeconds = true; 
					envelopeParameterObjects[i].tempoValue = rawVal; 
					std::cout << "Envelope parameter input in time units (seconds), stored as " << envelopeParameterObjects[i].tempoValue << " seconds" << std::endl; 
					break; 
				} else {
					std::cout << "Please include 's' for seconds or '/' for a beat fraction" << std::endl;
				}
			} catch (const std::exception&) {
				std::cout << "Error with input, invalid format. Please set the envelope parameter as either a fraction of a beat, or a duration in seconds" << std::endl; 
            }
		}
	}
	
	// Required field: waveform selection 
	// How to check if input was empty/input storing variable ends up empty 
	std::cout << "Please select a waveform (Sine, Sawooth, Square, or Triangle)" << std::endl; 
	std::string waveformSelection; 
	bool validInputCheck {false}; 
	while (!validInputCheck) {
		std::getline(std::cin, waveformSelection); // Is this valid? 
		if (!waveformSelection.empty() && waveformSelection != "sine" && waveformSelection != "Sine" && waveformSelection != "sawtooth" && waveformSelection != "Sawtooth"
			&& waveformSelection != "square" && waveformSelection != "Square" && waveformSelection != "triangle" && waveformSelection != "Triangle") {
				std::cout << "Invalid input, try again" << std::endl; 
			}		
		else {
			validInputCheck = true; 
			std::string waveform = waveformSelection; 
			std::cout << "You selected " << waveformSelection << " as the waveform" << std::endl; 
		}
	}
	return 0;
}