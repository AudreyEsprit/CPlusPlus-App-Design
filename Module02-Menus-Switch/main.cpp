#include <iostream>
#include <string> 
using namespace std;

void changeWaveform() {
	cout << "Select a waveform: " << "" << endl; 
}

void changePitch() {
	cout << "Select a pitch: " << "" << endl; 
}

void changeNumofVoices() {
	cout << "Select number of voices (1-8): " << "" << endl; 
}

void changeDetuneAmount() {
	cout << "Select detune amount (0-1.0): " << "" << endl; 
}

void changeFilterType() {
	cout << "Select a filter type: " << "" << endl; 
}

void changeFilterCutoff() {
	cout << "Select a filter cutoff frequency (0-1.0): " << "" << endl; 
}

void changeFilterResonance() {
	cout << "Select resonance amount (0-100%): " << "" << endl; 
} 

int main() {
	int choice {0}; 
	
	while (choice != 8) {
		cout << "\n" << "^*^*^*^ MINI SYNTH ^*^*^*^" << endl; 
		cout << "MENU: Select from the following options by entering 1 - 7. Enter 8 to exit." << endl;
		cout << "_1_ Change Waveform" << endl;
		cout << "_2_ Change Pitch" << endl; 
		cout << "_3_ Change Number of Voices" << endl;
		cout << "_4_ Change Detune Amount" << endl;
		cout << "_5_ Change Filter Type" << endl;
		cout << "_6_ Change Filter Cutoff Frequency" << endl; 
		cout << "_7_ Change Filter Resonance Amount" << endl; 
		cout << "_8_ Close and Exit" << endl; 
		cin >> choice; 
		
		switch (choice) {
			case 1: 
				changeWaveform(); 
				break;
			case 2: 
				changePitch();
				break;
			case 3: 
				changeNumofVoices();
				break;
			case 4:
				changeDetuneAmount();
				break;
			case 5: 
				changeFilterType();
				break;
			case 6:
				changeFilterCutoff();
				break;
			case 7:
				changeFilterResonance();
				break;
			case 8:
				cout << "Synth Closed. Bye!" << endl;
				break;
			default:
				cout << "Invalid input. Try again" << endl; 
		}
	}
	
	return 0; 
} 