#define interval 20
#define reliability 30
#define samples 22             //To get a smoother output , take an average of say 20 last readings from the sensor. Here's how I do it. I define a constant telling how many readings I want

long cont = 0;
double start_time = 0;
double end_time = 0;
float HR = 0;
float HR_calibrata = 0;
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {

   
  Serial.begin(9600);
  lcd.begin(16, 2);


}

int difference_samples() {
  float first_sample = read_sample();
  delay(interval);                                             // sampling rate = 1/interval = 50Hz , interval= 20ms= 0.02sec
  float second_sample = read_sample();
  float difference = second_sample - first_sample;

  return difference;
}

float read_sample() {                                        // Smoothing filter with samples-samples , in this way we also remove the 50Hz of artifical light
  float sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(A0);
  }
  return sum / samples;
}


void loop() {


if( HR_calibrata < 50 || HR_calibrata > 150) {
     lcd.setCursor(0,0);
     lcd.print("THE SENSOR IS    ");
     lcd.setCursor(0,1);
     lcd.print("NOT WORKING    ");
}
  

  float difference = difference_samples();
  if (difference > 0) {
    while (difference > 0) {
      difference = difference_samples();

    }
    cont++;

    if (cont == 1)
    {
      start_time = millis();
    }
  }
  else {
    while (difference <= 0) {
      difference = difference_samples();


    }
    cont++;
    if (cont == 1)  {
      start_time = millis();
    }
  }

  if (cont == reliability) {

    end_time = millis();


    HR = (cont * 30000) / (end_time - start_time);
    HR_calibrata = HR*0.21-12.56;

   // Serial.println(HR_calibrata);
     

     cont = 0;
  } else { HR_calibrata ==20; }
   
    if( HR_calibrata < 50 || HR_calibrata > 150) {
     lcd.setCursor(0,0);
     lcd.print("THE SENSOR IS    ");
     lcd.setCursor(0,1);
     lcd.print("NOT WORKING    ");
} else {
  
     lcd.setCursor(0,0);
     lcd.print("SENSOR= KY-039");
     lcd.setCursor(0,1);
     lcd.print("HR= ");
     lcd.print(HR_calibrata);
     lcd.print(" BPM");
}
  
  }

  
