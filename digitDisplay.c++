//library for keypad
#include <Keypad.h>  

//Keypad values
const uint8_t rows = 4; //read only rowa
const uint8_t columns = 4; //read only columns
const char keys[rows][columns] = //read only keys
{ {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','display'},
  {'*','0','#','clear'}
};

uint8_t cPins [columns] = {7,6,5,4}; //declaring column pins
uint8_t rPins [rows] = {11,10,9,8}; //declaring row pins
Keypad keypad = Keypad( makeKeymap(keys), rPins, cPins, rows, columns);

//read only decoder values
const uint8_t A = 0;
const uint8_t B = 1;
const uint8_t C = 2;
const uint8_t D = 3;

uint8_t i = 0;  //read-write counter

//register specifications
bool shiftReg[] = {HIGH,HIGH,LOW};  
const uint8_t regInput = 13;
const uint8_t regCLK = 12;

//function for displaying on 7 segment display
void displayDigit(){ 
  char key = keypad.getKey();  	//chek for key
  if (key != NO_KEY){ 			//if key pressed
    digitalWrite(regInput, shiftReg[i]);   //next data to shift 
    digitalWrite(regCLK, HIGH);	//clk high
    
    if (key == '0'){
      digitalWrite(A,LOW);
      digitalWrite(B,LOW);
      digitalWrite(C,LOW);
      digitalWrite(D,LOW);}
    
    else if (key == '1'){
      digitalWrite(A,HIGH);
      digitalWrite(B,LOW);
      digitalWrite(C,LOW);
      digitalWrite(D,LOW);}
    
    else if (key == '2'){
      digitalWrite(A,LOW);
      digitalWrite(B,HIGH);
      digitalWrite(C,LOW);
      digitalWrite(D,LOW);}
    
    else if (key == '3'){
      digitalWrite(A,HIGH);
      digitalWrite(B,HIGH);
      digitalWrite(C,LOW);
      digitalWrite(D,LOW);}
    
    else if (key == '4'){
      digitalWrite(A,LOW);
      digitalWrite(B,LOW);
      digitalWrite(C,HIGH);
      digitalWrite(D,LOW);}
    
    else if (key == '5'){
      digitalWrite(A,HIGH);
      digitalWrite(B,LOW);
      digitalWrite(C,HIGH);
      digitalWrite(D,LOW);}
    
    else if (key == '6'){
    digitalWrite(A,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(D,LOW);}
      		
    else if (key == '7'){
    digitalWrite(A,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    digitalWrite(D,LOW);}
    
    else if (key == '8'){
      digitalWrite(A,LOW);
      digitalWrite(B,LOW);
      digitalWrite(C,LOW);
      digitalWrite(D,HIGH);}
    
    else if (key == '9'){
    digitalWrite(A,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(C,LOW);
    digitalWrite(D,HIGH);}

    digitalWrite(12,LOW);  //clk low
    i++;  //increase count
    if(i==3){
    	i=0;  //reset count
    }}}

void setup(){
  configurePins();
  initShitfReg();}

void loop(){
displayDigit();}

void configurePins(){
  //Configure pins
  pinMode(0, OUTPUT);  //Control bit 0 of decoder
  pinMode(1, OUTPUT);  //Control bit 1 of decoder
  pinMode(2, OUTPUT);  //Control bit 2 of decoder
  pinMode(3, OUTPUT);  //Control bit 3 of decoder
  pinMode(regCLK, OUTPUT); //Clock of shift register
  pinMode(regInput, OUTPUT); //Data for shift register
   //Start all in zeros
  digitalWrite(0,LOW);
  digitalWrite(1,LOW);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(regCLK,LOW); 
  digitalWrite(regInput,LOW);
}

void initShitfReg(){
  digitalWrite(regInput,HIGH);  //data high
  delay(50);    //wait 50 ms
  digitalWrite(regCLK,HIGH);  //clk high
  delay(50);	//wait 50 ms
  digitalWrite(regCLK,LOW);   //clk low
  //----
  digitalWrite(regInput,HIGH);  //data high
  delay(50);	//wait 50 ms
  digitalWrite(regCLK,HIGH);  //clk high
  delay(50);	//wait 50 ms
  digitalWrite(regCLK,LOW);	  //clk low
  //---
  digitalWrite(regInput,LOW);   //data low
  delay(50);	//wait 50 ms
  digitalWrite(regCLK,HIGH);  //clk high
  delay(50);	//wait 50 ms
  digitalWrite(regCLK,LOW);	  //clk low
}
