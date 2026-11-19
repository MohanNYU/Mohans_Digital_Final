//Mohan saluja is a bit of a nerd
//setting up the uadio library right here
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=64,203
AudioEffectWaveshaper    waveshape1;     //xy=200,135
AudioEffectBitcrusher    bitcrusher1;    //xy=203,265
AudioMixer4              mixer1;         //xy=359,211
AudioOutputI2S           i2s1;           //xy=492,213
AudioConnection          patchCord1(waveform1, waveshape1);
AudioConnection          patchCord2(waveform1, 0, mixer1, 1);
AudioConnection          patchCord3(waveform1, bitcrusher1);
AudioConnection          patchCord4(waveshape1, 0, mixer1, 0);
AudioConnection          patchCord5(bitcrusher1, 0, mixer1, 2);
AudioConnection          patchCord6(mixer1, 0, i2s1, 0);
AudioConnection          patchCord7(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=433,371
// GUItool: end automatically generated code


int bypass[2] = {34, 33};
bool buttonState[2] = {LOW, LOW};
bool lastButtonState[2] = {LOW, LOW};
bool buttonOn[2] = {false, false};

float WAVESHAPE_EXAMPLE[17] = {};

int knobOld = -1;
int knobNew = analogRead(A13);


void setup(){
AudioMemory(12); //always include this when using the Teensy Audio Library even if you don't know what it is yet!

sgtl5000_1.enable();
sgtl5000_1.volume(0.5);
waveform1.begin(WAVEFORM_SINE); //25 - 28 this is my test tone
waveform1.frequency(1000);

pinMode(A11, OUTPUT);

}

void loop(){
//I'm removing the mixer stuff right now to focus on the waveshaper

waveform1.amplitude(0.8); //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones
// updateWaveTable(b);

int b = map(analogRead(A13), 0, 1023, 0, 20);
int c = map(analogRead(A13), 0, 1023, 0, 255);
updateWaveTable(b);

digitalWrite(A11, c);

}

void updateWaveTable(float a)
{

for(int i = 0; i<17; i++)
{
  float z = (i/(8.5)) - 1;
  float x = tanh(a * z);
  WAVESHAPE_EXAMPLE[i] = x;
}

waveshape1.shape(WAVESHAPE_EXAMPLE, 17);

}

