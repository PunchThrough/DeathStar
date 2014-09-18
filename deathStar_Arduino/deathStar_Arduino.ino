/*
  DeathStar plush toy
   
  This sketch is intended to be used with the
  LightBlue Bean
  
  NOTE: This sketch is not a low-power sketch.
   
  This example code is in the public domain.
*/ 
 
//All the tones that we will use in the song 
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

//The pin that the buzzer is soldered to
const int buzzerPin = 0;

int counter = 0;

const int amountOfTones=160;

//An array of the song, beginning to end. It goes: tone, duration, tone, duration...
int tones[amountOfTones] ={a, 500, a, 500, a, 500, f, 350, cH, 150, a, 500, f, 350, cH, 150, a, 650, 0, 500, eH, 500, eH, 500, eH, 500, fH, 350, cH, 150, gS, 500, f, 350, cH, 150, a, 650, 0, 500, 
aH, 500, a, 300, a, 150, aH, 500, gSH, 325, gH, 175, fSH, 125, fH, 125, fSH, 250, 0, 325, aS, 250, dSH, 500, dH, 325, cSH, 175, cH, 125, b, 125, cH, 250, 0, 350,
f, 250, gS, 500, f, 350, a, 125, cH, 500, a, 375, cH, 125, eH, 650, 0, 500, 
aH, 500, a, 300, a, 150, aH, 500, gSH, 325, gH, 175, fSH, 125, fH, 125, fSH, 250, 0, 325, aS, 250, dSH, 500, dH, 325, cSH, 175, cH, 125, b, 125, cH, 250, 0, 350,
f, 250, gS, 500, f, 375, cH, 125, a, 500, f, 375, cH, 125, a, 650, 0, 650};

void setup()
{
  //Setup the buzzer
  pinMode(buzzerPin, OUTPUT);

  // initialize serial communication at 57600 bits per second:
  Serial.begin(57600);
}
 
void loop()
{
  //Read the acceleration from the Beans accelerometer
  AccelerationReading accel = {0, 0, 0};
  accel = Bean.getAcceleration();
  
  int totalAccel=abs(accel.yAxis)+abs(accel.xAxis)+abs(accel.zAxis);

  //The acceleration reads to ~300 when it's laying still due to gravity. To prevent it from always playing we set the limit to 400
  if(totalAccel>400){
    //tones[counter] = the tone that needs to be played
    //tones[counter+1] = the duration
    beep(tones[counter],tones[counter+1]);

    if(counter>amountOfTones-3){
      //Reset the counter when it has reached the end of the tones array
      counter=0;
    }
    else{
      counter+=2;
    }
}

  delay(25);
}
 
void beep(int note, int duration)
{
  //If note==0 no tone should be played
  if(note==0){
    delay(duration);
  }
  else{
    //Play tone on buzzerPin
    tone(buzzerPin, note, duration);
    delay(duration);
  
    //Stop tone on buzzerPin
    noTone(buzzerPin);
  }
}
