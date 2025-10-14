#ifndef PROCESS_H
#define PROCESS_H

#include <Arduino.h>

// Initializes the clap detection parameters
void Process_begin(float noiseRMS = 200.0f, float rmsMargin = 4.0f, int peakMinAbs = 2000, unsigned long refractoryMs = 250);

// Feeds a new frame of audio data and returns true if a clap was detected
bool Process_detectClap(const short* samples, int n);

#endif // PROCESS_H
