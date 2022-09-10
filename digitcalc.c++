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

const uint8_t cPins [columns] = {7,6,5,4}; //declaring column pins
const uint8_t rPins [rows] = {11,10,9,8}; //declaring row pins
Keypad keypad = Keypad( makeKeymap(keys), rPins, cPins, rows, columns);

//inputs and result
uint8_t x = 0;
uint8_t y = 0;
uint8_t result = 0; 

//read only decoder configurations
const uint8_t decoderIn1 = 0;
const uint8_t decoderIn2 = 1;
const uint8_t decoderIn3 = 2;
const uint8_t decoderIn4 = 3;

//register specifications
bool shiftReg[] = {HIGH,HIGH,LOW};  
const uint8_t regInput = 13;
const uint8_t regCLK = 12;

//read-write counter
uint8_t i = 0;  

//function for displaying on 7 segment display
void displayDigit(char key){  
    if (key == '0'){
      digitalWrite(decoderIn1,LOW);
      digitalWrite(decoderIn2,LOW);
      digitalWrite(decoderIn3,LOW);
      digitalWrite(decoderIn4,LOW);}
    
    else if (key == '1'){
      digitalWrite(decoderIn1,HIGH);
      digitalWrite(decoderIn2,LOW);
      digitalWrite(decoderIn3,LOW);
      digitalWrite(decoderIn4,LOW);}
    
    else if (key == '2'){
      digitalWrite(decoderIn1,LOW);
      digitalWrite(decoderIn2,HIGH);
      digitalWrite(decoderIn3,LOW);
      digitalWrite(decoderIn4,LOW);}
    
    else if (key == '3'){
      digitalWrite(decoderIn1,HIGH);
      digitalWrite(decoderIn2,HIGH);
      digitalWrite(decoderIn3,LOW);
      digitalWrite(decoderIn4,LOW);}
    
    else if (key == '4'){
      digitalWrite(decoderIn1,LOW);
      digitalWrite(decoderIn2,LOW);
      digitalWrite(decoderIn3,HIGH);
      digitalWrite(decoderIn4,LOW);}
    
    else if (key == '5'){
      digitalWrite(decoderIn1,HIGH);
      digitalWrite(decoderIn2,LOW);
      digitalWrite(decoderIn3,HIGH);
      digitalWrite(decoderIn4,LOW);}
    
    else if (key == '6'){
    digitalWrite(decoderIn1,LOW);
    digitalWrite(decoderIn2,HIGH);
    digitalWrite(decoderIn3,HIGH);
    digitalWrite(decoderIn4,LOW);}
      		
    else if (key == '7'){
    digitalWrite(decoderIn1,HIGH);
    digitalWrite(decoderIn2,HIGH);
    digitalWrite(decoderIn3,HIGH);
    digitalWrite(decoderIn4,LOW);}
    
    else if (key == '8'){
      digitalWrite(decoderIn1,LOW);
      digitalWrite(decoderIn2,LOW);
      digitalWrite(decoderIn3,LOW);
      digitalWrite(decoderIn4,HIGH);}
    
    else if (key == '9'){
    digitalWrite(decoderIn1,HIGH);
    digitalWrite(decoderIn2,LOW);
    digitalWrite(decoderIn3,LOW);
    digitalWrite(decoderIn4,HIGH);}

    digitalWrite(regCLK,LOW);  //clk low
    i++;  //increase count
    if(i==3){
    	i=0;  //reset count
    }}


void setup(){

// decoder initialization
pinMode(decoderIn1, OUTPUT);  //Control bit 0 of decoder
pinMode(decoderIn2, OUTPUT);  //Control bit 1 of decoder
pinMode(decoderIn3, OUTPUT);  //Control bit 2 of decoder
pinMode(decoderIn4, OUTPUT);  //Control bit 3 of decoder
pinMode(regCLK, OUTPUT); //Clock of shift register
pinMode(regInput, OUTPUT); //Data for shift register
//starting  with low decoder values
digitalWrite(decoderIn1,LOW);
digitalWrite(decoderIn2,LOW);
digitalWrite(decoderIn3,LOW);
digitalWrite(decoderIn4,LOW);
digitalWrite(regCLK,LOW); 
digitalWrite(regInput,LOW);

  digitalWrite(regInput,HIGH);  //register input on
  delay(10);    //0.1s
  digitalWrite(regCLK,HIGH);  //register clock and latch on
  delay(10);	//0.1s
  digitalWrite(regCLK,LOW);  
  //
  digitalWrite(regInput,HIGH);  
  delay(10);	//0.1s
  digitalWrite(regCLK,HIGH);  
  delay(10);	//0.1s
  digitalWrite(regCLK,LOW);	 
  //
  digitalWrite(regInput,LOW);  
  delay(10);	//0.1s
  digitalWrite(regCLK,HIGH);  
  delay(10);	//0.1s
  digitalWrite(regCLK,LOW);	 }

void loop(){
  //get input from keypad
char input = keypad.getKey();
if (input!=NO_KEY){
//on pressed
digitalWrite(regInput, shiftReg[i]);
digitalWrite(regCLK, HIGH);
// -- for
  for(i=0;i<3;i++){
  displayDigit(input);
  i++;}
  //end-for 
} //end-if
}//end-loop
