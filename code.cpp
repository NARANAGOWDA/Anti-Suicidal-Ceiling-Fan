#include <SoftwareSerial.h>
SoftwareSerial mySerial(8,7);
#include <HX711_ADC.h> 
#include <LiquidCrystal_I2C.h> 
HX711_ADC LoadCell(4, 5); 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
int taree = 6;
int a = 0;
float b = 0;

void setup() {
   mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  
  pinMode (taree, INPUT_PULLUP);
  LoadCell.begin(); 
  LoadCell.start(1000); 

  LoadCell.setCalFactor(375); // Calibarate your LOAD CELL with 100g weight
  lcd.begin(); // begins connection to the LCD module
  lcd.backlight(); // turns on the backlight
  lcd.setCursor(1, 0); // set cursor to first row
  lcd.print("ANTISUCIDALCEILINGFAN"); 
  lcd.setCursor(0, 1); // set cursor to first row
delay(1000);
lcd.clear();
}
void loop() { 
  lcd.setCursor(1, 0); // set cursor to first row
  lcd.print("weight"); // print out to LCD 
  LoadCell.update(); // retrieves data from the load cell
  float i = LoadCell.getData(); // get output value
 if (i<0)
 {
  i = i * (-1);
  lcd.setCursor(0, 1);
  lcd.print("-");
   lcd.setCursor(8, 1);
  lcd.print("-");
 }
 else
 {
   lcd.setCursor(0, 1);
  lcd.print(" ");
   lcd.setCursor(8, 1);
  lcd.print(" ");
 }
  
  lcd.setCursor(1, 1); // set cursor to secon row
  lcd.print(i, 1); // print out the retrieved value to the second row
  lcd.print("g ");
  float z = i/28.3495;
  lcd.setCursor(9, 1);
  lcd.print(z, 2);
  lcd.print("mg ");

  if (i>=500)
  {
    i=0;
    
  lcd.setCursor(0, 0); // set cursor to secon row
  lcd.print("  Over Loaded   "); 
  delay(200);

 mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+916366276021\"\r"); 
     delay(1000);
     mySerial.println("EMERGENCY!!!\n SOME ONE IS TRYING TO HANG TO CEILING FAN NO 1");// The SMS text you want to send
     delay(1000);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);

  
  }
  if (digitalRead (taree) == LOW)
  {
    lcd.setCursor(0, 1); // set cursor to secon row
    lcd.print("   Taring...    ");
    LoadCell.start(1000);
    lcd.setCursor(0, 1);
    lcd.print("                ");
  
  }
}
  