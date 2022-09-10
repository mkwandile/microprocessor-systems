#include <cstdint>
# include <iostream>

//group 1 leds
const uint8_t LED_A=12;
const uint8_t LED_B=11;
const uint8_t LED_C=10;

//group 2 leds
const uint8_t LED_D=5;
const uint8_t LED_E=4;
const uint8_t LED_F=3;

//button
const uint8_t BTN=2;

//directions
uint8_t LEFT=0;
uint8_t RIGHT=1;
uint8_t direction=LEFT;

//potentiometers
const uint8_t PTM_1=A0;
const uint8_t PTM_2=A1;
const uint8_t PTM_3=A2;

//brightness levels
int bright_1=0;
int bright_2=0;
int bright_3=0;

void setup(){
  //declaring led for outputs
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_D, OUTPUT);
  pinMode(LED_E, OUTPUT);
  pinMode(LED_F, OUTPUT);
  
  //declaring input button and allows it to read voltage
  pinMode(BTN, INPUT_PULLUP);
  
}

void loop(){
  //brightness levels divided by 4 due to analog input
  bright_1=analogRead(PTM_1)/4;  
  bright_2=analogRead(PTM_2)/4;
  bright_3=analogRead(PTM_3)/4;  
  
  if(digitalRead(BTN)==0){
    direction=direction==LEFT?RIGHT:LEFT;
  }
    if(direction==RIGHT){
// right side leds: on  
  digitalWrite(LED_A, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_C, LOW);    
  digitalWrite(LED_D, HIGH);
  digitalWrite(LED_E, HIGH);
  digitalWrite(LED_F, HIGH);

  //right side leds: adjust brightness 
  analogWrite(LED_D, bright_1);
  analogWrite(LED_E, bright_2);
  analogWrite(LED_F, bright_3);
      delay(3); //0.003s delay
    }
 
  // left side leds: on
  else{
 digitalWrite(LED_D, LOW);
  digitalWrite(LED_E, LOW);
  digitalWrite(LED_F, LOW);
  digitalWrite(LED_A, HIGH);
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_C, HIGH); 
    
   //left side led: adjust brightness
  analogWrite(LED_A, bright_1);
  analogWrite(LED_B, bright_2);
  analogWrite(LED_C, bright_3);
     delay(3); //0.003s delay
  }
}