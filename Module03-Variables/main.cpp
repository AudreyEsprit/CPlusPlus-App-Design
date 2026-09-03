#define _USE_MATH_DEFINES 
#include <iostream> 
#include <string> 

constexpr int bufferSize {512}; 
constexpr int frequency {220}; //A3 in equal temperament 
constexpr int duration {3}; // Duration in seconds 
constexpr int sampleRate {44100}; 

int main() {
	std::string waveform {"Sine"}; 
	bool isNoteOn {false}; 
	float phase {0.0f};
	double pi = M_PI; 
	float phaseIncrement = (frequency * 2.0f * pi) / sampleRate;
	
	std::cout << "Here are some of the variables needed for the synth I'm building" << std::endl; 
	std::cout << "Buffer size: " << bufferSize << std::endl;
	std::cout << "Frequency: " << frequency << std::endl;
	std::cout << "Duration: " << duration << std::endl;
	std::cout << "Waveform: " << waveform << std::endl;
	std::cout << "isNoteOn: " << isNoteOn << std::endl;
	std::cout << "Phase: " << phase << std::endl; 
	std::cout << "Pi: " << pi << std::endl;
	std::cout << "Phase Increment: " << phaseIncrement << std::endl; 
	
	return 0; 
}