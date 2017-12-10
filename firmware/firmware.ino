/*
  Blink
 
 Turns an LED on for one second, then off for one second, repeatedly.
 
 Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
 it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
 the correct LED pin independent of which board is used.
 If you want to know what pin the on-board LED is connected to on your Arduino
 model, check the Technical Specs of your board at:
 https://www.arduino.cc/en/Main/Products
 
 modified 8 May 2014
 by Scott Fitzgerald
 modified 2 Sep 2016
 by Arturo Guadalupi
 modified 8 Sep 2016
 by Colby Newman
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Blink
 */
#include <HardwareSerial.h>
#include <LiquidCrystal.h>

#define NUMBEROFDIVIDERS 15
#define BASEFREQ 16.0e6
#define UPBUTTON 3
#define DOWNBUTTON 2
const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

uint8_t divider = 0;

void setDeviderOutputs(uint8_t value)
{
 uint8_t realValue = 0;
 
 if (value & 0x01)
 {
   realValue |= 0x08;
 }
 if (value & 0x02)
 {
   realValue |= 0x04;
 }
 if (value & 0x04)
 {
   realValue |= 0x02;
 }
 if (value & 0x08)
 {
   realValue |= 0x01;
 }
 PORTC = 0x00;
 PORTC |= (realValue << 2);
 
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.

  pinMode(A2, OUTPUT); //D
  pinMode(A3, OUTPUT); //C
  pinMode(A4, OUTPUT); //B
  pinMode(A5, OUTPUT); //A

  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);

  lcd.begin(16, 2);
  lcd.print("hello, world!");
  setDeviderOutputs(0);
  
  
}


// the loop function runs over and over again forever
void loop() {
  
  static unsigned long lcdUpdateTimer = 0;
  
  
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  
  
  

  
  if (digitalRead(UPBUTTON) == LOW) 
  {
    divider++;
    delay(40);
    while (digitalRead(UPBUTTON) == LOW);
    delay(40);
    
    if (divider > NUMBEROFDIVIDERS)
    {
      divider = NUMBEROFDIVIDERS;
    }
    
  }
  
  if (digitalRead(DOWNBUTTON) == LOW) 
  {
    if (divider > 0)
    {
      divider--;
    }
    delay(40);
    while (digitalRead(DOWNBUTTON) == LOW);
    delay(40);
  }
  
  if ((millis() - lcdUpdateTimer) > 200)
  {
    lcdUpdateTimer = millis();
    lcd.clear();
    
    if ((divider == 0 ) || ( divider == 1))
    {
      lcd.setCursor(7,0);
      lcd.print ("OFF ");
      
    } else {
      lcd.setCursor(7,0);
      //lcd.print(divider);
      float freq = round(BASEFREQ * 100/pow(2,divider));
      lcd.print(freq/100.0);
    }
    
    lcd.setCursor(0,1);
    lcd.print ("UP          DOWN");
    setDeviderOutputs(divider);
    
      
    
  }
  delay(100);
  
  
  
}

