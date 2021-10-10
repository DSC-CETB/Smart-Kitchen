/* 
 *  SID TASK - 3
 *  Automated Fire Alarm Sensor
 *  Swaraj Samal
 *  1901106563
 *  B.Tech 3rd year Instrumentation and Electronics Engineering
*/


#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
 
LiquidCrystal lcd(13,12,11,10,9,8) ;
SoftwareSerial SIM900(4,3);

int FLAME = 4;
int SMOKE = 5;
int RELAY = 6;
int ALARM = 7;
String textForSMS;

void setup()
{
  Serial.begin(9600);
  SIM900.begin(9600);
  Serial.println("Flame/Smoke Detection");
  pinMode(FLAME, INPUT);//FLAME input pin
  pinMode(ALARM, OUTPUT);//ALARM output pin
  pinMode(SMOKE, INPUT);//SMOKE input pin
  pinMode(RELAY, OUTPUT);//RELAY Output pin
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Fire/Smoke Alarm");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("  WARMING UP ! ");
  delay(2000); // allow the MQ-2 sensor to warm up (preferably 2 to 5 mins), here 2 secs for demonstration purposes
  lcd.clear();
}

void loop()
{
 

  if(digitalRead(FLAME) == HIGH)
  {
    digitalWrite(ALARM,HIGH);// set the buzzer ON
    digitalWrite(RELAY,HIGH);
    Serial.println("Fire Detected!!!");
    lcd.setCursor(0,1);
    lcd.print("FIRE  HAZARD!!");
    textForSMS =  "\nFlame Detected, Fire Hazard!!";  
    sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("message sent."); 
    delay(5000);
  }else{
    digitalWrite(ALARM,LOW); // Set the buzzer OFF
    Serial.println("All Good :)");
    lcd.setCursor(0,1);
    lcd.print("All Good :)");
  }

 
  if(digitalRead(SMOKE) == HIGH){
    delay(1000);
    if(digitalRead(SMOKE) == HIGH){ 
      digitalWrite(RELAY,HIGH);
      lcd.setCursor(0,0);
      lcd.print("SMOKE DETECTED! ");
      digitalWrite(ALARM , HIGH);
      textForSMS =  "\nGas or Smoke Detected!!, Fire Hazard!!!";  
      sendSMS(textForSMS);
      Serial.println(textForSMS);
      Serial.println("message sent."); 
      delay(5000);
    }
    else{
      lcd.setCursor(0,0);  
      lcd.print("False Alarm");
    }
  }
else{
  lcd.setCursor(0,0);
  lcd.print("All Good :)");
  digitalWrite(ALARM, LOW);
}
delay(1000);
lcd.clear();
}


void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(1000);
 SIM900.println("AT + CMGS = \"+91XXXXXXXXXX\"");  // X is mobile no. here
 
  delay(1000);
  SIM900.println(message);                        
  delay(1000);
  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(1000); 
  SIM900.println();
  delay(100);                                     // give module time to send SMS                               
}
