#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// SDA A4
// SCL A5
const int trigPin = 2;  
const int echoPin = 3;  
long duration;
float distanceCm;
float distanceInch;
//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display



int sample_distance() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.155;
  return distance;
}





void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("REVERSE VENDING");
  lcd.setCursor(0,1);
  lcd.print("    MACHINE    ");
}

void loop() {

  int distanceCm = sample_distance();
  //Serial.println(distanceCm);


  if (distanceCm<10){
    lcd.init(); 
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("   The bin is   ");
    lcd.setCursor(0,1);
    lcd.print("      full      ");
  }
  else if (distanceCm>10){
    lcd.init(); 
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("REVERSE VENDING");
    lcd.setCursor(0,1);
    lcd.print("    MACHINE    ");
}
  else if (Serial.available()){
    char read = Serial.read();
    Serial.print(read);
    if (read=='A'){
      lcd.init(); 
      lcd.clear();
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print(" Credit is added");
      lcd.setCursor(0,1);
      lcd.print(" To your account");
      delay(5000);
    }
  }
}
