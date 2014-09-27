/*
  This sketch programs a LightBlue Bean to play the Imperial March and turn on an LED when moved
     
  NOTE: This is not a low-power sketch.
   
  This example code is in the public domain.
*/ 
 
//All the tones that we will use in the song 
const int c = 261, d = 294, e = 329, f = 349, g = 391, gS = 415,
a = 440, aS = 455, b = 466, cH = 523, cSH = 554, dH = 587, dSH = 622, 
eH = 659, fH = 698, fSH = 740, gH = 784, gSH = 830, aH = 880;

const int buzzerPin = 0;
const int ledPin = 5;

const int amountOfTones=160;
//"counter" is used to keep track of where in the song we are
int counter = 0; 

// When acceleration change goes beyond this threshold, the LED will blink.
#define accelerationThreshold 150    
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
  // Initial acceleration reading
  previousAccel = Bean.getAcceleration(); 
}
 
void loop()
{
  // Get the current acceleration with a conversion of 3.91×10-3 g/unit.
  AccelerationReading currentAccel = Bean.getAcceleration();   
  
  // Find the difference between the current acceleration and that of 200ms ago.
  int accelDifference = getAccelDifference(previousAccel, currentAccel);  
  // Update previousAccel for the next loop. 
  previousAccel = currentAccel;   
  
  // Check if the Death Star has been moved beyond our threshold
  if(accelDifference > accelerationThreshold){   
    //Turn on the LED
    digitalWrite(ledPin, HIGH); 
    
    //tones[counter] = the tone that needs to be played and tones[counter+1] = the duration
    beep(tones[counter],tones[counter+1]);  
    
    if(counter>amountOfTones-3){
      //Reset the counter when it has reached the end of the tones array
      counter=0; 
    }
    else{
      counter+=2;
    }
  Bean.sleep(25);
  }
  else{ 
   // If the Death Star isn't moving, turn off the LED
   digitalWrite(ledPin, LOW);
    Bean.sleep(200);
  }
}
 
//This function plays the tones on the piezo buzzer
void beep(int note, int duration)
{
  //If note==0 no tone should be played
  if(note==0){
    delay(duration);
  }
  else{
    //Play tone on piezo buzzer
    tone(buzzerPin, note, duration); 
    delay(duration);
    //Stop tone on buzzerPin
    noTone(buzzerPin); 
  }
}

// This function calculates the difference between two acceleration readings
int getAccelDifference(AccelerationReading readingOne, AccelerationReading readingTwo){
  int deltaX = abs(readingTwo.xAxis - readingOne.xAxis);
  int deltaY = abs(readingTwo.yAxis - readingOne.yAxis);
  int deltaZ = abs(readingTwo.zAxis - readingOne.zAxis);
  // Return the magnitude
  return deltaX + deltaY + deltaZ;   
}
