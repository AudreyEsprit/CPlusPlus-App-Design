#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdint> 
#include <cmath>

constexpr int bufferSize {512}; 
constexpr int sampleRate {44100}; 

class SineOscillator {
	public:
		float getSample(float freq) {
			float phaseIncrement = (freq * 2.0f * M_PI) / sampleRate;
			
			float rawSine = std::sin(phase);
			
			phase += phaseIncrement;
			if (phase >= 2.0f * M_PI) {
				phase -= 2.0f * M_PI; 
			}
			return rawSine;
		}
		void dummyExample() {
			float cap = 2.0f * 2 * M_PI; // One full cycle/period
			for (int p = 0; p < cap; p++) {
				std::cout << getSample(220) << std::endl; 
			}
		}
	private: 
		float phase {0.0f}; 
};

class Voice {
	public:
		// Constructor (not used in actual synth design, added for purposes of assignment) 
		Voice(float gainRampSpeed) {
			// Implicit "this pointer" to match the rampSpeed member variable of that specific instantiation/object 
			rampSpeed = gainRampSpeed;
		}
		// Mutator (not yet incorporated in synth design) 
		void changeRampSpeed(float newRampSpeed) {
			float old = rampSpeed; 
			rampSpeed = newRampSpeed; 
			std::cout << "You changed this voice's attack and release setting from " << old << " to " << rampSpeed << std::endl; 
		}
		// Accessor 
		float readRampSpeed() {
			return rampSpeed;
		}
		
		void noteOn(float freq) {
			targetFrequency.store(freq);
			gate.store(true);
			isActive.store(true); 
		}
		void noteOff() {gate.store(false); } 
		std::atomic<bool> isActive {false}; 
		int currentNote {-1}; 
		// Calls oscillator.getSample() and applies gain adjustments, envelope 
		float renderNextSample() {
			float adjustedSample;
			// A case of accessing or getting, not for output to the user, but for a subsequent call to the oscillator object it owns
			float freq = targetFrequency.load();
			float rawSample = oscillator.getSample(freq);
			
			// Another case of accessing/getting, to check for current gate (key press) and apply gain adjustments 
			bool noteState = gate.load(); 
			if (noteState) {
				if (currentGain < 1.0f) {
					currentGain += rampSpeed; 
					if (currentGain > 1.0f) currentGain = 1.0f;
				}
			}
			else {
					if (currentGain > 0.0f) { 
						currentGain -= rampSpeed; 
						if (currentGain < 0.0f) currentGain = 0.0f;
					}
			}
			adjustedSample = rawSample * currentGain * 0.2f; 
			
			if (!noteState && currentGain <= 0.0f) {
				isActive.store(false); 
			}
			
			return adjustedSample;
		}
	private:
		SineOscillator oscillator; 
		std::atomic<float> targetFrequency {0.0f};
		std::atomic<bool> gate {false}; 
		float currentGain {0.0f};
		// Private attribute (member variable) set by constructor 
		float rampSpeed; 
};

int main() {
	Voice voiceOne(0.05); 
	Voice voiceTwo(0.1);

	std::cout << "First voice's attack/release setting: " << voiceOne.readRampSpeed() << std::endl;
	voiceOne.changeRampSpeed(0.005);
	std::cout << "First voice's new attack/release setting: " << voiceOne.readRampSpeed() << std::endl; 
	
	std::cout << "\n";
	
	SineOscillator oscillator; 
	oscillator.dummyExample();
	std::cout << "The full live synth converts numbers like the above (44,100 a second) to actual audio played through your speakers or output device!" << std::endl;
	
	return 0; 
}
