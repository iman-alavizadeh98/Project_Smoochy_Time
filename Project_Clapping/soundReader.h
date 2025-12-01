#ifndef SOUNDREADER_H
#define SOUNDREADER_H

#include <Arduino.h>

bool SoundReader_begin(int sampleRateHz = 16000, int bufferSamples = 512);

// NEW: query how many samples are ready (0 if none)
int  SoundReader_available();

// NEW: copy up to maxSamples into dst; returns number copied (0 if none)
int  SoundReader_read(short* dst, int maxSamples);

// (Optional utility you already had)
// int  SoundReader_pollAndPrint();

#endif
