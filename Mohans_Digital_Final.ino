//Mohan saluja is a bit of a nerd
//setting up the uadio library right here

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=69,201
AudioEffectWaveshaper    waveshape1;     //xy=200,135
AudioEffectBitcrusher    bitcrusher1;    //xy=203,265
AudioMixer4              mixer1;         //xy=359,211
AudioOutputI2S           i2s1;           //xy=492,213
AudioConnection          patchCord1(i2s2, 0, mixer1, 1);
AudioConnection          patchCord2(i2s2, 0, waveshape1, 0);
AudioConnection          patchCord3(i2s2, 0, bitcrusher1, 0);
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


float WAVESHAPE_EXAMPLE[17] = {
  -0.6,
  -0.579,
  -0.549,
  -0.488,
  -0.396,
  -0.320,
  -0.228,
  -0.122,
  0,
  0.0,
  0.0,
  0.3,
  0.4,
  0.488,
  0.588,
  0.599,
  0.6

  //   -0.588,
  // -0.588,
  // -0.588,
  // -0.588,
  // -0.396,
  // -0.320,
  // -0.228,
  // -0.122,
  // 0,
  // 0.100,
  // 0.100,
  // 0.100,
  // 0.100,
  // 0.100,
  // 0.100,
  // 0.100,
  // 0.100
};


void setup(){
AudioMemory(12); //always include this when using the Teensy Audio Library even if you don't know what it is yet!

sgtl5000_1.enable();
sgtl5000_1.volume(0.5);
sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);

// waveform1.begin(WAVEFORM_SINE); //25 - 28 this is my test tone
// waveform1.frequency(2000);

}

void loop(){

// waveform1.amplitude(0.0); //amplitude (volume) can be 0 to 1 and this is usually a good volume for headphones

checkButton(0);
checkButton(1);

if(buttonOn[0] == true)
{mixer1.gain(0, 1);
mixer1.gain(1, 0);
mixer1.gain(2, 0);}

else if(buttonOn[1] == true)
{
mixer1.gain(0, 0);
mixer1.gain(1, 0);
mixer1.gain(2, 1);
}
else{
mixer1.gain(1, 1);
mixer1.gain(0, 0);
mixer1.gain(2, 0);
}

// mixer1.gain(0, 0);
// mixer1.gain(1, 0);
// mixer1.gain(2, 1);




bitcrusher1.bits(
  map(analogRead(A13), 0, 1027, 0, 16)
  // 16
);
bitcrusher1.sampleRate(
  map(analogRead(A13), 0, 1027, 0, 441000)
  // 441000
);

waveshape1.shape(WAVESHAPE_EXAMPLE, 17);


}

void checkButton(int x) //Checks butts and sends mid notes booya
{
  lastButtonState[x] = buttonState[x];
  buttonState[x] = digitalRead(bypass[x]);

  if (lastButtonState[x] == LOW and buttonState[x] == HIGH) {
    buttonOn[x] = !buttonOn[x];
    delay(5);

  } else if (buttonState[x] == LOW and lastButtonState[x] == HIGH) {
    delay(5);
  }
}
