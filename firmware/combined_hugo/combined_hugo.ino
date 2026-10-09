
int sensorPin = 0;
float raw;
int threshold=150;
int BPM;
float nmax=0;
int wmax=1;
int c;
float val[40]={};
float media=0;
float t[100]={};
int pek;
float mai;
float save;
float hbeat;
float hbeatma[3]={};
float hbeatfi;
int a=0;
unsigned long timer;
unsigned long start; 
int stat;
void setup() {
   Serial.begin(9600);
   start=millis();
}
void loop ()
{
  raw=analogRead(sensorPin);
  
  if(raw < threshold){
    stat=0;
    raw=0;
    BPM=0;
    start=millis();
    nmax=0;
    delay(1000);
    Serial.println("No data");
    a=0;
    c=0;
 }
 
 else{
  stat=1;
  if(c==0){
  timer=millis();
  }
  c=1;
 }
 pek=1;
   if(stat==1){
   val[39]=raw;
   for (int i=0;i<39;i++){
      val[i]=val[i+1];
    }
    
      for (int i=0;i<40;i++){
      media=media+val[i];
      
    }
      media=media/40;
      t[99]=media;
      for (int i=0;i<99;i++){
        t[i]=t[i+1];
      }
      mai=t[50];
      for (int i=0; i<99;i++){
        if (t[i]>mai || t[0]==0 ){
          pek=0;
        }
      }

      
      if(pek==1){
        if(millis()-start>500){
          nmax++;
          if(a==0 || nmax>3 && nmax>1){
            hbeat=nmax*60/((millis()-timer)/1000);
            hbeatma[2]=hbeat;
            for (int i=0;i<2;i++){
              hbeatma[i]=hbeatma[i+1];
            }
          }
          if(nmax<10 && a==0){
            Serial.println("Collecting data");
            
          }
          else{
          
            for (int i=0;i<3;i++){
              hbeatfi=hbeatfi+hbeatma[i];
            }
            Serial.println(hbeatfi/3);
          }
          start= millis();
              }
          }
      if (nmax>15){
        a=1;
        nmax=0;
        timer=millis();
      }
      }
  hbeatfi=0;
  media=0;
  //Serial.println(nmax);
} 
