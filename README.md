# CPlusPlus-App-Design
Repository for C++ application design related projects and files

Audrey Schaffert
CIS 025 Object Oriented Programming Using C++ 

Application Project: Limited polyphonic synthesizer 

I plan to build a basic subtractive synthesizer with envelope, polyphony, filter, and MIDI functionality. It will be "limited" in the sense that it will not have any LFOs or effect capabilities. The project will build as a standalone app to be used on the desktop (not a VST as originally planned). 

Completed Modules:
Module 1, Module 2, Module 3, Module 4, Module 5, Module 6, Module 7, Midterm, Module 8, Module 9 ... 

Instructions for application use: 
TBD 

***

Instructions per Assignment 9: 

My program for module 8 validates the input for three sets of parameters of synthesized sound. First, it checks that the number of voices (of the synth) is more than zero but less than 9, or between 1 and 8. Second, it checks that each of the parameters for the envelope, using the standard Attack, Sustain, Decay, Release, or ASDR format, are entered either as a fraction of a beat or as a duration in seconds, for each parameter, while also being nonempty. Special utility functions are used to find the slash ('/') character to indicate a fraction, detect any alphabetic characters to indicate a time input in seconds, and convert input taken as strings to decimal values of type double. Lastly, the program checks to see whether the waveform selected by the user is one of the listed options (Sine, Sawtooth, Square, or Triangle), and is nonempty. Note that the program does not reflect the final design of my application in that it omits processing of these stored parameters, but is only for the purposes of demonstrating input validation for I/O within the terminal. Thank you! 

Were I to incorporate AI directly into my application, I would opt for a classification, not a recommendation or generation feature. That is, the feature would, from the characteristics of the sound the user has already selected, crafted, modulated, etc, provide a more or less elementary type or classification for it, as in: What analog instrument or VST patch profile does the sound resemble? How might it fit into or serve a function within a broader mix? What is its sound design category?
One challenge of incorporating such a feature would be, the training data would need to be assimilable/comparable to the sort of vectors defined by the parameters set by the user within the application, which I intend to be very limited, with only basic detuning, enveloping, and filtering capabilities. In principle, the feature would need to process many, many existing synth patches or sounds, locate them within a vector space using only the dimensions just mentioned, and use the distribution and shape of this vector space to make determinations as to similarity. 
With the belief that such AI features should be purely optional, the user would only see such AI or machine learning powered classifications if they pushed some button within the user interface, which would then display the closest approximate category for the sound, possibly with additional information on its use within a mix, within existing music genres, and examples of similar patches/sounds. 
This feature would fit into the existing architecture of my application rather simply and easily, with each finished synth patch representing a different vector, with each of the vector's dimensions set by the values stored for all relevant parameters (each maintained within instances of the three separate classes, Oscillator, Voice, and Synth). The real challenges for implementation would arise from gathering and processing the training data appropriately, and from writing algorithms that would make meaningful comparisons from the distances and proximities between the vectors representing that training data, comparisons with real musical, i.e. creative and cultural, semantic relevance. 
