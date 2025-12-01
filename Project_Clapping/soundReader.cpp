#include "SoundReader.h"
#include <PDM.h>

static short* s_buffer        = nullptr;
static volatile int s_samples = 0;
static int s_bufCapacity      = 0;

static void onPDMdata() {
  int bytesAvailable = PDM.available();
  int bytesToRead    = min(bytesAvailable, s_bufCapacity * (int)sizeof(short));
  if (bytesToRead <= 0) return;
  PDM.read(s_buffer, bytesToRead);
  s_samples = bytesToRead / 2; // 2 bytes per int16
}

bool SoundReader_begin(int sampleRateHz, int bufferSamples) {
  static short staticBuf[1024];
  if (bufferSamples > (int)(sizeof(staticBuf) / sizeof(staticBuf[0]))) return false;

  s_buffer      = staticBuf;
  s_bufCapacity = bufferSamples;
  s_samples     = 0;

  PDM.onReceive(onPDMdata);
  const char channels = 1;
  return PDM.begin(channels, sampleRateHz);
}

// --- NEW: how many samples are ready
int SoundReader_available() {
  return s_samples;  // volatile read is fine (brief)
}

// --- NEW: copy samples out safely and consume them
int SoundReader_read(short* dst, int maxSamples) {
  if (s_samples <= 0) return 0;

  noInterrupts();
  int n = s_samples;
  s_samples = 0;        // consume
  interrupts();

  if (n > maxSamples) n = maxSamples;
  for (int i = 0; i < n; ++i) dst[i] = s_buffer[i];
  return n;
}
