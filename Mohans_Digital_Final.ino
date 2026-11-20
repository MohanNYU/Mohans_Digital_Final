//Mohan saluja is a bit of a nerd

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=55,236
AudioFilterStateVariable filter1;        //xy=106,53
AudioEffectWaveshaper    waveshape1;     //xy=286,73
AudioEffectFreeverb      freeverb1;      //xy=316,311
AudioEffectWaveshaper    waveshape2;     //xy=318,229
AudioEffectWaveshaper    waveshape3;     //xy=458,131
AudioMixer4              mixer1;         //xy=698,290
AudioFilterStateVariable filter2;        //xy=777,382
AudioOutputI2S           i2s1;           //xy=833,178
AudioOutputUSB           usb1;           //xy=903,348
AudioConnection          patchCord1(i2s2, 0, waveshape2, 0);
AudioConnection          patchCord2(i2s2, 0, freeverb1, 0);
AudioConnection          patchCord3(i2s2, 0, filter1, 0);
AudioConnection          patchCord4(filter1, 2, waveshape1, 0);
AudioConnection          patchCord5(waveshape1, waveshape3);
AudioConnection          patchCord6(freeverb1, 0, mixer1, 2);
AudioConnection          patchCord7(waveshape2, 0, mixer1, 1);
AudioConnection          patchCord8(waveshape3, 0, mixer1, 0);
AudioConnection          patchCord9(mixer1, 0, i2s1, 0);
AudioConnection          patchCord10(mixer1, 0, i2s1, 1);
AudioConnection          patchCord11(mixer1, 0, filter2, 1);
AudioConnection          patchCord12(mixer1, 0, filter2, 0);
AudioConnection          patchCord13(filter2, 2, usb1, 0);
AudioConnection          patchCord14(filter2, 2, usb1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=684,110
// GUItool: end automatically generated code




//FROM HERE IS THE WAVE FORM GENERATOR TEST CODE
// AudioSynthWaveform       waveform1;      //xy=106,170
// AudioEffectWaveshaper    waveshape2;     //xy=318,229
// AudioEffectWaveshaper    waveshape1;     //xy=323,134
// AudioEffectFreeverb      freeverb1;      //xy=323,310
// AudioMixer4              mixer1;         //xy=698,290
// AudioOutputI2S           i2s1;           //xy=844,291
// AudioConnection          patchCord1(waveform1, waveshape1);
// AudioConnection          patchCord2(waveform1, waveshape2);
// AudioConnection          patchCord3(waveform1, freeverb1);
// AudioConnection          patchCord4(waveshape2, 0, mixer1, 1);
// AudioConnection          patchCord5(waveshape1, 0, mixer1, 0);
// AudioConnection          patchCord6(freeverb1, 0, mixer1, 2);
// AudioConnection          patchCord7(mixer1, 0, i2s1, 0);
// AudioConnection          patchCord8(mixer1, 0, i2s1, 1);
// AudioControlSGTL5000     sgtl5000_1;     //xy=684,110
// GUItool: end automatically generated code



float dist[257]; //the distortion setting
float dist2[257]; //the distortion setting phase 2
float drive[257]; //the overdrive/light shaping setting

// #define PI 3.1415926535897932384626433832795;

void setup(){
AudioMemory(12); //always include this when using the Teensy Audio Library even if you don't know what it is yet!

sgtl5000_1.enable();
sgtl5000_1.volume(0.5);
// waveform1.begin(WAVEFORM_SINE); //25 - 28 this is my test tone
// waveform1.frequency(1000);
// waveform1.amplitude(0.2); //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones

pinMode(A14, OUTPUT);
pinMode(36, INPUT);

//sgtl5000_1.volume(1);
sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
}

void loop(){

// int c = map(analogRead(A13), 0, 1023, 0, 255); // LEDS
// analogWrite(A14, c); // LEDS

if(digitalRead(36) == HIGH) //mode selector
{

 mode1();

} else {
  // waveform1.amplitude(0.0f);

mode2();
  
  }

filter2.frequency(20.0f); //weird sub frequency attenuation

}


void mode1(){
  float b = map(analogRead(A13), 0, 1023, 0, 50); //tanh constant

  updateWaveTable1(b);

  mixer1.gain(0, 0.5); //lower the damn volume
  mixer1.gain(1, 0.0); //adjusting mixer gain
  mixer1.gain(2, 0.0);


}


void updateWaveTable1(float a)
{

filter1.frequency(300);

for(int i = 0; i<257; i++)
{
  float z = (i/(128.5)) - 1;
  float x = (2/PI) * atan(a * z); //soft atan distortion
  float y = tanh(a * z); //hard tanh distortion
  dist[i] = x; 
  dist2[i] = y;
}

waveshape1.shape(dist, 257); //wave shaping application
waveshape3.shape(dist2, 257); //wave shaping application


}

void mode2(){

float b = map((float) analogRead(A13), 0, 1023, 0, 3); //verb constant

  mixer1.gain(0, 0.0); //readjusting mixer gain
  mixer1.gain(1, 1.0);
  // mixer1.gain(2, 1.0);


for(int i = 0; i<257; i++)
{
  float z = (i/(128.5)) - 2;
  float x = (2/PI) * atan(3.0f * z); //soft distortion using arctan modeling
  drive[i] = x;
}

waveshape2.shape(drive, 257); //shaping

if(b <= .5){
  mixer1.gain(2, 0.0);
} else{
  mixer1.gain(2, 1.0);
freeverb1.roomsize(b); //reverb controlled by b knob
freeverb1.damping(b);
}
}
