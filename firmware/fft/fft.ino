#include <arduinoFFT.h>

#define samples 128
#define sampling_frequency 200 //50Hz 

arduinoFFT FFT=arduinoFFT();
unsigned int sampling_period_us;
unsigned long microseconds;
double vReal[samples];         
double vIm[samples];


void setup() {

  Serial.begin(115000);
  sampling_period_us=round((1/sampling_frequency)*1000000);
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -
}




void loop() {


for(int i=0; i<samples; i++){

  microseconds=micros();
  vReal[i]=analogRead(A1);
  vIm[i]=0;
  while( micros() < (microseconds + sampling_period_us) ) { };
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal,vIm, samples, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vIm,samples);

  for(int i=0; i<samples/2; i++){
    Serial.println(vReal[i],1);
  }


  while(1);
}


}
