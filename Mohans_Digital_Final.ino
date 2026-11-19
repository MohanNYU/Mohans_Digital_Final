//Mohan saluja is a bit of a nerd

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=88,128
AudioEffectWaveshaper    waveshape1;     //xy=323,134
AudioMixer4              mixer1;         //xy=698,290
AudioOutputI2S           i2s1;           //xy=844,291
AudioConnection          patchCord1(waveform1, waveshape1);
AudioConnection          patchCord2(waveform1, 0, mixer1, 1);
AudioConnection          patchCord3(waveshape1, 0, mixer1, 0);
AudioConnection          patchCord4(mixer1, 0, i2s1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=684,110
// GUItool: end automatically generated code



float dist[257];
float drive[257];



void setup(){
AudioMemory(12); //always include this when using the Teensy Audio Library even if you don't know what it is yet!

sgtl5000_1.enable();
sgtl5000_1.volume(0.5);
waveform1.begin(WAVEFORM_SINE); //25 - 28 this is my test tone
waveform1.frequency(1000);
waveform1.amplitude(0.2); //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones

pinMode(A14, OUTPUT);
pinMode(36, INPUT);

}

void loop(){

// int c = map(analogRead(A13), 0, 1023, 0, 255); // LEDS
// analogWrite(A14, c); // LEDS

if(digitalRead(36) == HIGH)
{

 mode1();

} else {
  // waveform1.amplitude(0.0f);
  mixer1.gain(0, 0.0);
  mixer1.gain(1, 0.5);

  
  }


}


void mode1(){
  float b = map(analogRead(A13), 0, 1023, 0, 20); //tanh constant

  updateWaveTable1(b);

  mixer1.gain(0, 1.0);
  mixer1.gain(1, 0.0);


}


void updateWaveTable1(float a)
{

for(int i = 0; i<257; i++)
{
  float z = (i/(128.5)) - 1;
  float x = tanh(a * z);
  dist[i] = x;
}

waveshape1.shape(dist, 257);

}


