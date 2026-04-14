# Project Smoochy Time

A small Arduino Nano 33 BLE Sense project that detects claps using the built-in microphone and toggles the LED.

---

## What it does

The board continuously reads audio from the microphone and analyzes it in small chunks.  
If the sound matches the pattern of a clap, the built-in LED toggles.

---

## How clap detection works

Each audio frame is processed using **two main features**:

### 1. RMS (Root Mean Square)
- Measures the overall energy (loudness) of the sound  
- Helps filter out quiet background noise  

### 2. Peak amplitude
- Finds the strongest spike in the signal  
- Claps usually have a sharp, sudden peak  

---

### Detection rule

A clap is detected only when **both conditions are true**:

- RMS is significantly higher than the background noise  
- Peak amplitude is above a minimum threshold  

Additionally, there is a cooldown:

### 3. Cooldown (refractory period)
- After detecting a clap, the system waits ~250 ms  
- Prevents one clap (or echoes) from being counted multiple times  

---

## Why use both RMS and Peak?

- Only RMS → loud continuous sounds could trigger  
- Only Peak → random spikes could trigger  

Combining both:
- RMS ensures the sound is loud enough  
- Peak ensures the sound is sharp  

→ makes detection more reliable

---

## Structure

```
Project_Clapping/
├── Project_Clapping.ino.ino
├── soundReader.h/.cpp
├── Process.h/.cpp
```

- soundReader → handles microphone input  
- Process → calculates RMS + Peak and detects claps  

---

## Hardware

- Arduino Nano 33 BLE Sense  
- (uses built-in mic + LED)

---

## Run

1. Open the `.ino` file in Arduino IDE  
2. Select Arduino Nano 33 BLE Sense  
3. Upload  
4. Open Serial Monitor (115200)  
5. Clap
