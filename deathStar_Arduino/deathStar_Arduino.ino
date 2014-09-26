/*
  This sketch programs a LightBlue Bean to play the Imperial March and turn on an LED when moved
     
  NOTE: This is not a low-power sketch.
   
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

const int buzzerPin = 0;
const int ledPin = 5;

const int amountOfTones=160;
int counter = 0; //"counter" is used to keep track of where in the song we are

#define accelerationThrehsold 150    // When acceleration change goes beyond this threshold, the LED will blink.
AccelerationReading previousAccel;

//An array of the song, beginning to end. It goes: tone, duration, tone, duration...
int tones[amountOfTones] ={a, 500, a, 500, a, 500, f, 350, cH, 150, a, 500, f, 350, cH, 150, a, 650, 0, 500, eH, 500, eH, 500, eH, 500, fH, 350, cH, 150, gS, 500, f, 350, cH, 150, a, 650, 0, 500, 
aH, 500, a, 300, a, 150, aH, 500, gSH, 325, gH, 175, fSH, 125, fH, 125, fSH, 250, 0, 325, aS, 250, dSH, 500, dH, 325, cSH, 175, cH, 125, b, 125, cH, 250, 0, 350,
f, 250, gS, 500, f, 350, a, 125, cH, 500, a, 375, cH, 125, eH, 650, 0, 500, 
aH, 500, a, 300, a, 150, aH, 500, gSH, 325, gH, 175, fSH, 125, fH, 125, fSH, 250, 0, 325, aS, 250, dSH, 500, dH, 325, cSH, 175, cH, 125, b, 125, cH, 250, 0, 350,
f, 250, gS, 500, f, 375, cH, 125, a, 500, f, 375, cH, 125, a, 650, 0, 650};

void setup()
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  previousAccel = Bean.getAcceleration(); // Initial acceleration reading
}
 
void loop()
{
  AccelerationReading currentAccel = Bean.getAcceleration();   // Get the current acceleration with a conversion of 3.91×10-3 g/unit.
  
  int accelDifference = getAccelDifference(previousAccel, currentAccel);   // Find the difference between the current acceleration and that of 200ms ago.
  previousAccel = currentAccel;                                            // Update previousAccel for the next loop. 
   
  if(accelDifference > accelerationThrehsold){   // Check if the Death Star has been moved beyond our threshold
    digitalWrite(ledPin, HIGH); //Turn on the LED
    
    beep(tones[counter],tones[counter+1]);  //tones[counter] = the tone that needs to be played and tones[counter+1] = the duration
    
    if(counter>amountOfTones-3){
      counter=0; //Reset the counter when it has reached the end of the tones array
    }
    else{
      counter+=2;
    }
  }
  else{ // If the Death Star isn't moving, turn off the LED
   digitalWrite(ledPin, LOW);
  }
  Bean.sleep(25);
}
 
//This function plays the tones on the piezo buzzer
void beep(int note, int duration)
{
  //If note==0 no tone should be played
  if(note==0){
    delay(duration);
  }
  else{
    tone(buzzerPin, note, duration); //Play tone on piezo buzzer
    delay(duration);
    noTone(buzzerPin); //Stop tone on buzzerPin
  }
}

// This function calculates the difference between two acceleration readings
int getAccelDifference(AccelerationReading readingOne, AccelerationReading readingTwo){
  int deltaX = abs(readingTwo.xAxis - readingOne.xAxis);
  int deltaY = abs(readingTwo.yAxis - readingOne.yAxis);
  int deltaZ = abs(readingTwo.zAxis - readingOne.zAxis);
  return deltaX + deltaY + deltaZ;   // Return the magnitude
}
