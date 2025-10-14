#include "Process.h"
#include <math.h>

// internal state
static float g_noiseRMS = 0.0f;
static float g_rmsMargin = 0.0f;
static int   g_peakMinAbs = 0;
static unsigned long g_refractoryMs = 0;
static unsigned long g_lastClap = 0;

// helper: compute RMS (root mean square)
static float computeRMS(const short* x, int n) {
  double sumSq = 0.0;
  for (int i = 0; i < n; ++i) {
    double v = (double)x[i];
    sumSq += v * v;
  }
  double meanSq = sumSq / (double)n;
  return (float)sqrt(meanSq);
}

// helper: compute absolute peak
static int computePeakAbs(const short* x, int n) {
  int maxVal = 0;
  for (int i = 0; i < n; ++i) {
    int v = abs(x[i]);
    if (v > maxVal) maxVal = v;
  }
  return maxVal;
}

void Process_begin(float noiseRMS, float rmsMargin, int peakMinAbs, unsigned long refractoryMs) {
  g_noiseRMS = noiseRMS;
  g_rmsMargin = rmsMargin;
  g_peakMinAbs = peakMinAbs;
  g_refractoryMs = refractoryMs;
  g_lastClap = 0;
}

bool Process_detectClap(const short* samples, int n) {
  float rms = computeRMS(samples, n);
  int peak  = computePeakAbs(samples, n);
  unsigned long now = millis();

  bool loudEnough = (rms > g_noiseRMS * g_rmsMargin);
  bool hasPeak    = (peak > g_peakMinAbs);
  bool cooldown   = (now - g_lastClap > g_refractoryMs);

  if (loudEnough && hasPeak && cooldown) {
    g_lastClap = now;
    return true;
  }
  return false;
}
