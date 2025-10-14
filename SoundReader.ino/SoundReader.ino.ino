// this file contains PDM libaries and methodes we need to set in order to read sounds from microphone

//Includes:

#include <Arduino.h>
#include <PDM.h>

// Init
short sampleBuffer[512];     // buffer for raw audio samples
volatile int samplesRead = 0; // number of samples read

void onPDMdata();

void setup()
{
  Serial.begin(115200);
  unsigned long t0 = millis();
  while(!Serial && millis() - t0 < 2000 ){}

  Serial.println("Starting microphone...");
  
  //configure mic settings
  static const char channels = 1;
  static const int frequency = 16000;

  PDM.onReceive(onPDMdata);

  //starting the mic
  if(!PDM.begin(channels, frequency))
  {
    Serial.println("Failed to start PDM!!!");
    while(1){};
  }

  Serial.println("Microphone started successfully!!!");

}

void loop() {
  if(samplesRead > 0)
  {
    noInterrupts();
    int n = samplesRead;
    samplesRead = 0;
    interrupts();

    Serial.println("Samples: ");
    Serial.println(n);

    for(int i = 0; i <= 10; i++)
    {
      Serial.println(sampleBuffer[i]);
    }
    Serial.println("---------");
  }

}


void onPDMdata() 
{
  // this function will be called automatically when mic has data ready
  int bytesAvailable = PDM.available(); //how many bytes we can read
  int bytesToRead = min(bytesAvailable, (int)sizeof(sampleBuffer));

  PDM.read(sampleBuffer, bytesToRead);  //read data into the buffer
  samplesRead = bytesToRead / 2;  // 2 bytes per 16 bit sample
}