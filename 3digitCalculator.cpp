//library for keypad
#include <Keypad.h> 
#include <LiquidCrystal.h>

//input and result from calculations
String x, y ;
uint8_t result = 0;
char operate ; 

//boolean values
bool present = false;
bool next = false;
bool last = false;

//read-write counter
uint8_t i = 0;  

//lcdisplay
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);

//Keypad values
const uint8_t rows = 4; //read only rowa
const uint8_t columns = 4; //read only columns
char keys[rows][columns] = { //read only keys
{'1','2','3','+'},
{'4','5','6','-'},
{'7','8','9','C'}, //C is clear
{'*','0','#','D'}}; //D is display

//column and row pin declarations
uint8_t cPins [columns] = {7,6,5,4};
uint8_t rPins [rows] = {11,10,9,8}; 

//keypad
Keypad keypad = Keypad( makeKeymap(keys), rPins, cPins, rows, columns);

//read only decoder configurations
const uint8_t decoderIn1 = 0;
const uint8_t decoderIn2 = 1;
const uint8_t decoderIn3 = 2;
const uint8_t decoderIn4 = 3;

//register specifications
bool shiftReg[] = {HIGH,HIGH,LOW};  
const uint8_t regInput = 13;
const uint8_t regCLK = 12;

//display to 7 segment display
void displayDigits(char key){  
digitalWrite(regInput, shiftReg[i]);
digitalWrite(regCLK, HIGH);

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
if(i>3){
lcd.clear();
lcd.print("Overflow!");
i=0;  //reset count
}}

void digit(uint8_t num){
if (num>=10)
digit(num/10);

uint8_t n = num%10;
char m = '0'+n;
displayDigits(m);}

void clearLED(){
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
digitalWrite(regCLK,LOW);

digitalWrite(regCLK,LOW);  //clk low
i++;  //increase count
if(i>3){
i=0;  //reset count
}}

void setup(){
//2 lines of 16 characters each
lcd.begin(16,2);

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
delay(20);
digitalWrite(regCLK,HIGH);  //register clock and latch on
delay(20);
digitalWrite(regCLK,LOW);  
//
digitalWrite(regInput,HIGH);  
delay(20);
digitalWrite(regCLK,HIGH);  
delay(20);	
digitalWrite(regCLK,LOW);	 
//
digitalWrite(regInput,LOW);  
delay(20);
digitalWrite(regCLK,HIGH);  
delay(20);
digitalWrite(regCLK,LOW);

//lcd instructions
lcd.setCursor(0,0);
lcd.print("The program ");
lcd.setCursor(2,1);
lcd.print("has started.");}

void loop(){
//get input from keypad
char input = keypad.getKey();
if (input){
if(input=='0'||input=='1'||input=='2'||input=='3'||input=='4'||input=='5'||input=='6'||input=='7'||input=='8'||input=='9'){
if(present==false){
x=x+input;
lcd.clear();
lcd.print("Input 1: ");
lcd.setCursor(2,1);
lcd.print(x);
displayDigits(input); }

else{
y = y + input;
clearLED();
clearLED();
clearLED();
delay(20);
lcd.clear();
lcd.print("Input 2: ");
lcd.setCursor(2,1);
lcd.print(y); 
displayDigits(input);
last = true;  } }
  
else if((input == '+'||input=='-')&& present == false){
present=true;
operate = input;
clearLED();
clearLED();
clearLED();
delay(20);
lcd.clear();
lcd.setCursor(2, 1);
lcd.print(operate); }

else if (input == 'D' && last == true){
if(operate == '+'){
result = x.toInt() + y.toInt();}

else if (operate == '-'){
if(result<0){
  lcd.print("Negative!");
  clearLED();
  clearLED();
  clearLED();
  result = y.toInt() - x.toInt();}
  else
  result = x.toInt() - y.toInt(); }

clearLED();
clearLED();
clearLED();
delay(20);
digit(result);
lcd.clear();
lcd.setCursor(2,0);
lcd.print(" = ");
lcd.setCursor(2,8);
lcd.print(result); }

else if(input=='C'){
clearLED();
clearLED();
clearLED();
delay(20);
lcd.clear();
present = false;
last = false;
x = "";
y = "";
result = 0;
operate = '\0';}}}//end-loop