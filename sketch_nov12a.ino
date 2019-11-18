#define LDRpin A0 // pin where we connected the LDR and the resistor
#include "dht.h"
#define dht_apin D0// Analog Pin sensor is connected to
#define sensorPin D1// capactitive touch sensor - Arduino Digital pin D1
#define relay1 D5
#define relay2 D6
#define relay3 D7
#define relay4 D8
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "xc7nYifRdUR2PWH81QRLf2CPDYNaQpvB";
char ssid[] = "bocah12";
char pass[] = "123456789";
int ledPin = 13; // Output display LED (on board LED) - Arduino Digital pin D13
dht DHT;
int LDRValue = 0;     // result of reading the analog pin

volatile byte relayState = LOW;

void setup() {
  Serial.begin(9600); 
  delay(500);
  pinMode(ledPin, OUTPUT);  
  pinMode(sensorPin, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
}

void loop() {
  dht();
  LDR();
  TOUCH();
}

//batas cahaya 30 

void dht(){
  DHT.read11(dht_apin);
  if (DHT.temperature >= 30){
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  }else{
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  }
  Serial.print("temperature = ");
  Serial.print(DHT.temperature); 
  Serial.println("C  ");
}
void LDR(){
  LDRValue = analogRead(LDRpin);
  if (LDRValue <= 200){
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    //Serial.println("GELAP");
  }else{
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    //Serial.println("TERANG");
  }
  Serial.println(LDRValue);
}
void TOUCH(){
  int senseValue = digitalRead(sensorPin);
  if (senseValue == HIGH){
    digitalWrite(ledPin, HIGH);
    Serial.println("TOUCHED");
  }
  else{
    digitalWrite(ledPin,LOW);
    Serial.println("not touched");
  } 
}
