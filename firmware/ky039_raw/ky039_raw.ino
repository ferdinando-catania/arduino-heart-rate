#define samples 22


 int somma=0;
 int media=0;
 long unsigned start_cont=0;
 long unsigned end_cont=0;
 int Tc=20;
 


void setup() {
  Serial.begin(9600);

}



int sum (){
  
 float somma=0;
for(int i=0; i<samples; i++){
 somma += analogRead(A0);

}
return somma/samples;
}


void loop() {


  int sample=sum();
  Serial.println(analogRead(A0));
  
  delay(20);

}
