#include <Arduino.h>
#include "SoundReader.h"
#include "Process.h"

static const int FRAME_SIZE = 512;
static short frame[FRAME_SIZE];

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  unsigned long t0 = millis();
  while (!Serial && millis() - t0 < 2000) {}

  if (!SoundReader_begin(16000, FRAME_SIZE)) {
    Serial.println("SoundReader_begin FAILED");
    while (1) {}
  }

  Process_begin(200.0f, 4.0f, 2000, 250);
  Serial.println("Ready — clap near the mic.");
}

void loop() {
  int available = SoundReader_available();
  if (available > 0) {
    int n = SoundReader_read(frame, FRAME_SIZE);
    if (n > 0) {
      if (Process_detectClap(frame, n)) {
        Serial.println("CLAP DETECTED!");
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      }
    }
  }
  // no delay(); keep up with audio
}
