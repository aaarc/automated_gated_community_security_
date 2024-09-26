#include <Keypad.h>
#include "NewPing.h"
#include <Servo.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include <DHT11.h>

Servo myservo;
DHT11 dht11(A0);
LiquidCrystal_I2C lcd(0x27,16,2);

  
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','4','7','*'},
  {'2','5','8','0'},
  {'3','6','9','#'},
  {'A','B','C','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void print_pin_digits(int a)
{
  String g="";
  for(int i=0;i<a;i++)
  {
    g=g+"*";
  }
  lcd.setCursor(0,1);
  lcd.print(g);
}
NewPing s(10,12,400);
float temp,hum,c;

float get_dist()
{
  float t=s.ping();
  float d=0;
  d=((t/2)*c);
  return d;
}


void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(12,INPUT);
  temp=dht11.readTemperature();
  hum=dht11.readHumidity();
  c=(0.0001*(331.4+(0.0606*temp)+(0.00124*hum)));
  myservo.attach(11);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Welcome!"); 
}
int start_state=0;
int code=8909;
String input_code_str="",received_code_str="";
int input_code=0,received_code=0,received_count=0;
int count_input=0;
int input_code_ready=0;
int received_code_ready=0;
int wrng_attempt=0;
int control=0;
int arr[]={8767,4645,6464,6546,4234};
int flag=0;

void start_motor()
{
    myservo.write(0); 
    delay(500);
    myservo.write(90); // pause             
    delay(3500);
    myservo.write(150);    
    delay(500);    
    myservo.write(90);      
 
}

int firstCheck(int input_code)
{
  if(received_code_ready==1)
    {
       if(input_code==received_code)
    {
      //Serial.print("PASSED!");
      //start_motor();
      return 1;
      wrng_attempt=0;
    }
    else{
      Serial.print("WRONG PIN!");
      lcd.clear();
      lcd.print("WRONG PIN!"); 
      wrng_attempt=wrng_attempt+1;
    }
    }
    else{
         if(input_code==code)
    {
      Serial.print("PASSED");

      return 1;
      
      wrng_attempt=0;
    }
    else{
      Serial.print("WRONG PIN");
      lcd.clear();
      lcd.print("WRONG PIN!"); 
      return 0;
      wrng_attempt=wrng_attempt+1;
    }
    }
}

int secondCheck(int input_code)
{
  int i=0;
  int size=sizeof(arr)/sizeof(arr[0]);
  Serial.println(input_code);
  for(i=0;i<size;i++)
  {
    if(input_code==arr[i])
    {
      Serial.print("Level-2");

      return 1;
    }
  }
  Serial.print("Level-2 fail");
  lcd.clear();
  lcd.print("WRONG PIN!"); 
  return 0;
}
int iter_count=0;
void loop(){
  char customKey = customKeypad.getKey();
   if(iter_count<=75)
  {
      if(get_dist()>=100)
  {
      lcd.noBacklight();
    
  }
  else
  {
      lcd.backlight();
  }
  iter_count=0;
  }
  iter_count++;
  if(Serial.available())
  { char receivedChar = Serial.read(); 
  //Serial.println(receivedChar);
  // Serial.println(received_code_str);
    if(received_count<=6)
    {
      received_code_str+=receivedChar;
      received_count+=1;
      if(received_count==6)
      { received_code=received_code_str.toInt();
        received_count=0;
        code=received_code;
        received_code_ready=1;
        received_code_str="";
        Serial.print(received_count);
        Serial.println(received_code_ready);
        Serial.print(received_code);
      }
    }
    
  }

  if (customKey){
    if(customKey=='A')
    {
      control=0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Pin:");
      start_state=1;
      input_code_str="";
      count_input=0;
    }
    else if(customKey=='B')
    {
      Serial.println("Enter the 2nd pin");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Pin 2:");
      control=1;
      start_state=1;
      input_code_str="";
      count_input=0;
    }
      else if(customKey=='C' && start_state==1)
    {
      start_state=0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Cleared");
      delay(500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Welcome!");
      
      input_code_str="";
      count_input=0;
       input_code_ready=0;
      
    }
      else if(customKey=='D' && start_state==1)
    {
      start_state=0;
    }
      else if(customKey=='#' && start_state==1)
    {
      start_state=0;
    }
      else if(customKey=='*' && start_state==1)
    {
      start_state=0;
    }
    else if(customKey && start_state==1 && count_input<=4)
    {
      // Serial.print("input : ");
      // Serial.print(customKey);
      // Serial.print("\n input string");
      // Serial.print(input_code_str);
       lcd.setCursor(0,0);
      lcd.print("Enter Pin:");
      count_input++;
      print_pin_digits(count_input);
      input_code_str+=customKey;
      if(count_input==4)
      {
        input_code_ready=1;
        count_input=0;
        start_state=0;
      }
    }
    
  }
  if(input_code_ready==1)
  {
    input_code=input_code_str.toInt();
    if(control==0)
    {
      int n=firstCheck(input_code);
      if(n==1)
        flag+=1;
      else
        wrng_attempt+=1;
      Serial.print(control);
    }
    else
    {
      int m=secondCheck(input_code);
      if(m==1)
        flag+=1;
      else
        wrng_attempt+=1;
      Serial.print(control);
    }
    Serial.println(wrng_attempt);
  	if(flag==2)
    {

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Welcome");
      lcd.setCursor(0,1);
      lcd.print("Back!!");
      start_motor();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Welcome!");
      wrng_attempt=0;
    }
    input_code_ready=0;
    if(wrng_attempt>=3)
    {
      digitalWrite(13,HIGH);
      delay(2000);
      digitalWrite(13,LOW);
    }
      
  }
  delay(20);

}