//#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Thread.h>


LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

String str1;
String str2;
byte setting_input=0;
int default_true = 1;
int default_false = 2;
byte scrolling0 = default_false;
byte scrolling1 = default_false;
byte scrolling_direction0 = default_false;//left - right
byte scrolling_direction1 = default_false;//left - right
int scrolling_speed0 = 1000;//ms
int scrolling_speed1 = 1000;//ms
String space = " ";
int ebob = 0;
int delaycount=0;
int row1_mod;
int row0_mod;

Thread myThread0 = Thread();
Thread myThread1 = Thread();


void setup()
{
  Serial.begin(9600);

  // initialize the lcd 
  lcd.init();
  // set up the LCD's number of columns and rows:
  lcd.backlight();
  myThread0.onRun(rowZero);
  myThread1.onRun(rowOne);
}


void loop()
{
  
    Serial.print("PLEASE ENTER SETTING NUMBER: ");
    while(Serial.available() == 0)
    {
      
    }
    setting_input = Serial.parseInt();
    Serial.println(setting_input);
  

  switch(setting_input){

    case 10:
      Serial.println("10 – PRINT THIS STATUS SCREEN");
      Serial.println("LCD ROW 0 (UP)");
      Serial.print("1 – TEXT : ");
      Serial.println(str1);
      Serial.print("2 – SCROLLING STATUS : ");
      if(scrolling0 == default_false){
        Serial.println("DISABLED");
      }
      else if(scrolling0 == default_true){
        Serial.println("ENABLED");
      }
      Serial.print("3 – SCROLLING DIRECTION : ");
      if(scrolling_direction0 == default_false){
        Serial.println("LEFT");
      }
      else if(scrolling_direction0 == default_true){
        Serial.println("RIGHT");
      }
      Serial.print("4 – SCROLLING SPEED (MS): ");
      Serial.println(scrolling_speed0);
      Serial.println("LCD ROW 1 (DOWN)");
      Serial.print("5 – TEXT :");
      Serial.println(str2);
      Serial.print("6 – SCROLLING STATUS : ");
      if(scrolling1 == default_false){
        Serial.println("DISABLED");
      }
      else if(scrolling1 == default_true){
        Serial.println("ENABLED");
      }
      Serial.print("7 – SCROLLING DIRECTION : ");
      if(scrolling_direction1 == default_false){
        Serial.println("LEFT");
      }
      else if(scrolling_direction1 == default_true){
        Serial.println("RIGHT");
      }
      Serial.print("8 – SCROLLING SPEED (MS): ");
      Serial.println(scrolling_speed1);
      
       ebobBul(); 
       row0_mod= scrolling_speed0 / ebob;  
       row1_mod= scrolling_speed1 / ebob; 
       lcd.setCursor(0,0);
       lcd.print(str1);   
       lcd.setCursor(0,1);
       lcd.print(str2);
       lcd.setCursor(0,0); 
      while(Serial.available() == 0)
      {   
          
         delay(ebob);
        delaycount++;
        if(delaycount% row0_mod==0){
           rowZero();
          }
       if(delaycount% row1_mod==0){
         //Serial.print(ebob);
           rowOne();
          }
       
        
      }
           
      break;
    case 1:
      Serial.println("PLEASE ENTER TEXT FOR ROW 0: ");
      while (Serial.available() == 0){  
              
      }
      str1 = Serial.readString();
      if (str1.length() < 16)
      {
        while(str1.length() != 16)
        {
          str1.concat(space);
          //Serial.print(str1.length());
        }
      }
      //Serial.print(str1);
      //Serial.print(str1.length());
      break;
    case 2:
      Serial.print("PLEASE ENTER 2 TO DISABLE OR 1 TO ENABLE SCROLLING: ");
      while (Serial.available() == 0)
      {
        
      }
      scrolling0 = Serial.parseInt();
      Serial.println(scrolling0);
      break;
    case 3:
      Serial.print("PLEASE ENTER 2 FOR LEFT AND 1 FOR RIGHT SCROLLING DIRECTION: ");
      while (Serial.available() == 0)
      {
        
      }
      scrolling_direction0 = Serial.parseInt();
      Serial.println(scrolling_direction0);
      break;
    case 4:
      Serial.print("PLEASE ENTER SCROLLING SPEED FOR ROW 0 (MS): ");
      while (Serial.available() == 0)
      {
        
      }
      scrolling_speed0 = Serial.parseInt();
      Serial.println(scrolling_speed0);
      break;
    case 5:
      Serial.println("PLEASE ENTER TEXT FOR ROW 1: ");
      while (Serial.available() == 0)
      {
        
      }
      str2 = Serial.readString();
      if (str2.length() < 16)
      {
        while(str2.length() != 16)
        {
          str2.concat(space);
          //Serial.print(str1.length());
        }
      }
      break;
    case 6://input al
      Serial.print("PLEASE ENTER 2 TO DISABLE OR 1 TO ENABLE SCROLLING: ");
      while (Serial.available() == 0)
      {
        
      }
      scrolling1 = Serial.parseInt();
      Serial.println(scrolling1);
      break;
    case 7:
      Serial.print("PLEASE ENTER 2 FOR LEFT AND 1 FOR RIGHT SCROLLING DIRECTION: ");
      while (Serial.available() == 0)
      {
        
      }
      scrolling_direction1 = Serial.parseInt();
      Serial.println(scrolling_direction1);
      break;
    case 8:
      Serial.print("PLEASE ENTER SCROLLING SPEED FOR ROW 1 (MS): ");
      while (Serial.available() == 0)
      {
        
      }
      scrolling_speed1 = Serial.parseInt();
      Serial.println(scrolling_speed1);
      break;
    default:
      printf("Default ");
      break; 
  }
       
}

void rowZero()
{
  if(scrolling0 == default_true)
      {
        lcd.setCursor(0,0);
        lcd.print(str1);
        if(Serial.available() == 0)
        {
          
          if(scrolling_direction0 == default_false)
          {
            csl1();
            lcd.setCursor(0,0);
            lcd.print(str1);
          }
          else if(scrolling_direction0 == default_true)
          {
            csr1();
            lcd.setCursor(0,0);
            lcd.print(str1);
          }
        }
      }
}

void rowOne()
{
  if(scrolling1 == default_true)
      {
        lcd.setCursor(0,1);
        lcd.print(str2);
        if(Serial.available() == 0)
        {
          
          if(scrolling_direction1 == default_false)
          {
            csl2();
            lcd.setCursor(0,1);
            lcd.print(str2);
          }
          else if(scrolling_direction1 == default_true)
          {
            csr2();
            lcd.setCursor(0,1);
            lcd.print(str2);
          }
        }
      }
}

void csl1()//circular shift left for row0
{
  char temp = str1.charAt(0);
  int index = 0;
  int char_index = 1;
  
  while(char_index < str1.length() )
  {
    str1.setCharAt(index , str1.charAt(char_index));
    index++;
    char_index++;
  }
  str1.setCharAt(str1.length() - 1 , temp);
}

void csr1()//circular shift right for row0
{
  char temp = str1.charAt(str1.length()-1);
  for(int i=str1.length()-1;i>0;i--){
    str1.setCharAt(i,str1.charAt(i-1));
  }
  str1.setCharAt(0,temp);
}

void csl2()//circular shift left for row1
{
  char temp = str2.charAt(0);
  int index = 0;
  int char_index = 1;
  
  while(char_index < str2.length() )
  {
    str2.setCharAt(index , str2.charAt(char_index));
    index++;
    char_index++;
  }
  str2.setCharAt(str2.length() - 1 , temp);
}

void csr2()//circular shift right for row1
{
  char temp = str2.charAt(str2.length()-1);
  for(int i=str2.length()-1;i>0;i--){
    str2.setCharAt(i,str2.charAt(i-1));
  }
  str2.setCharAt(0,temp);
}

void ebobBul()
{
    for(int i=1; i <= scrolling_speed0 && i <= scrolling_speed1; ++i)
    {
        if(scrolling_speed0%i==0 && scrolling_speed1%i==0)
            ebob = i;
    }
}
