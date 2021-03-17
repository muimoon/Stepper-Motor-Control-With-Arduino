#include "Stepper.h"
#define STEPS  32   

volatile boolean TurnDetected; 
volatile boolean rotationdirection;

const int PinCLK=3 ;
const int PinDT=2;
const int PinSW=1;

int RotaryPosition=0;

int PrevPosition;
int StepsToTake;


Stepper small_stepper(STEPS, 4, 6, 5, 7);


unsigned long previousMillis=0 ;
unsigned long interval = 100L;
int ledState = HIGH;

int ledR=A5;
int ledV=A4;

int a=7,b=6,c=5,d=4;
int T=0;
int V=0;                                                                                                                        
int sens=0;
String Sens="";
int x=0;

int But1=A0;
int But2=A1;
int But3=A2;
int But4=A3;


char * text1[] = 
{
   "      MENU",
   "      SENS",
   "    VITESSE",
   "     MARCHE",
   "     MANUEL"
};
int text1Bit = 0;

char * text2[] = 
{
   "1_SENS",
   "2_VITESSE",
   "3_DEMARRER ?",
   "4_MANUEL"
};
int text2Bit = 0;

char * text3[] = 
{
   "     GAUCHE",
   "     DROITE"
};
int text3Bit = 0;

char * text4[] = 
{
   "Vitesse 1",
   "Vitesse 2",
   "Vitesse 3"
};
int text4Bit = 0;

#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);

void isr ()  {
  delay(4);  // delay for Debouncing
  if (digitalRead(PinCLK))
    rotationdirection= digitalRead(PinDT);
  else
    rotationdirection= !digitalRead(PinDT);
  TurnDetected = true;
}

void setup() {

Serial.begin(9600);

  pinMode(A5,OUTPUT);
  pinMode(A4,OUTPUT);
  
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);

    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("    MAKER 3.0");
    lcd.setCursor(0, 1);
    lcd.print("       PAR");
    delay(1500);
    lcd.clear();
    
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print(" ZEHRAOUI WALID");
    lcd.setCursor(0, 1);
    lcd.print("  TAIATI  IDIR");
    delay(2000);
    lcd.clear();
    
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("CONTROLE MOTEUR");
    lcd.setCursor(0, 1);
    lcd.print("      PAP");
    delay(2000);
    lcd.clear();

pinMode(PinCLK,INPUT);
pinMode(PinDT,INPUT);  
pinMode(PinSW,INPUT);
digitalWrite(PinSW, HIGH);
attachInterrupt (0,isr,FALLING);
}



void loop() {
    small_stepper.setSpeed(600); //Max seems to be 700
  if (!(digitalRead(PinSW))) {   // check if button is pressed
    if (RotaryPosition == 0) {  // check if button was already pressed
    } else {
        small_stepper.step(-(RotaryPosition*50));
        RotaryPosition=0; // Reset position to ZERO
      }
    }

  // Runs if rotation was detected
  if (TurnDetected)  {
    PrevPosition = RotaryPosition; // Save previous position in variable
    if (rotationdirection) {
      RotaryPosition=RotaryPosition-1;} // decrase Position by 1
    else {
      RotaryPosition=RotaryPosition+1;} // increase Position by 1

    TurnDetected = false;  // do NOT repeat IF loop until new rotation detected

    // Which direction to move Stepper motor
if(text1Bit!=4){
  digitalWrite(PinSW,HIGH);
}else{
}
if(text1Bit==4){ 

Serial.print("PinCLK = ");Serial.print(digitalRead(PinCLK));Serial.print(" ;  PinDT = ");Serial.println(digitalRead(PinDT));
  
  digitalWrite(ledV,LOW); 

  if( millis() - previousMillis >= interval) {
    previousMillis = millis();
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
     digitalWrite(ledR,ledState);  
    }
      
    if ((PrevPosition + 1) == RotaryPosition) { // Move motor CW
      StepsToTake=50; 
      small_stepper.step(StepsToTake);
      lcd.setCursor(0, 1);
      lcd.print("  Sens = DROITE");
    }

    if ((RotaryPosition + 1) == PrevPosition) { // Move motor CCW
      StepsToTake=-50;
      small_stepper.step(StepsToTake);
      lcd.setCursor(0, 1);
      lcd.print("  Sens = GAUCHE");
    }
      
  }
 
 }
  
                              // Controle LEDs                 
  if(text1Bit==3){
    digitalWrite(ledV,LOW);
    
    
  if( millis() - previousMillis >= interval) {
    previousMillis = millis();
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
     digitalWrite(ledR,ledState);  
    }
    if(V==0){
      digitalWrite(ledR,HIGH);
    }
    
  }
                              // Eteindre les Broches Du moteur à l'arret
  if(text1Bit != 3){
    for(int x=4;x<=7;x++){
  digitalWrite(x,LOW);
  }
}
 if(V==0){
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
 }
                               // Vitesse
  if(V==1){
    T=15;
  }
    if(V==2){
      T=8;
    }
      if(V==3){
        T=2;
      }
                                // Choix Vitesse
if(text1Bit==2){
      if(digitalRead(But4) == LOW){
     do{}while(digitalRead(But4) == LOW);
     
     text4Bit++;
     if(text4Bit>2){
      text4Bit=2;
     }
     MENU_V();
      }
      if(digitalRead(But1) == LOW){
     do{}while(digitalRead(But1) == LOW);
     
     text4Bit--;
     
     if(text4Bit<=0){
      text4Bit=0;
     }
     MENU_V();
      }
  if(text4Bit==0){
   
     if(digitalRead(But2) == LOW){
     V=1;
     }   
  }
  if(text4Bit==1){
     if(digitalRead(But2) == LOW){
     V=2;
     }
  }
  if(text4Bit==2){
     if(digitalRead(But2) == LOW){
     V=3;
     }
  }
}

   if(text2Bit==1){
    MENU_V;
      
   }
                               // OK
  if(text1Bit==0){
    if(text2Bit==0){
      if(digitalRead(But2)==LOW){
      lcd.clear();
      text1Bit=1;
      MENU_S();
      }
    }
    if(text2Bit==1){
      if(digitalRead(But2)==LOW){
      lcd.clear();
      text1Bit=2;
      MENU_V();
    }
  }
    if(text2Bit==2){
      if(digitalRead(But2)==LOW){
      lcd.clear();
      text1Bit=3;
      MENU_D();
    }
  }
   if(text2Bit==3){
      if(digitalRead(But2)==LOW){
      lcd.clear();
      text1Bit=4;
      MENU_M();
    }
  }
 }
                               // Retour
  if(text1Bit!=0){
      
        if(digitalRead(But3)==LOW){
      lcd.clear();
      text1Bit=0;
      MENU1();
  }
        
 }
                               // MENU
if(text1Bit == 0){
MENU1();
}
                               //Démarrage 
if(text1Bit==3){
  
    if(sens==0){
      Gauche();
    }else if(sens==1){
      Droite();
    }
  }

                               //Sens de rotation 
  if(text1Bit==1){
    if(text3Bit==0){
    if(digitalRead(But2)==LOW){
      do{}while (digitalRead(But2)==LOW);
      sens=0;
    }
    
    } 
      

    if(text3Bit==1){
    if(digitalRead(But2)==LOW){
      do{}while (digitalRead(But2)==LOW);
      sens=1;
    }
    
  }
  
    }
                               //Liste MENU vitesse
  if(text1Bit==2){
    if(text4Bit==0){
      if(V == 1){
        MENU_V();
        lcd.setCursor(0,1);
        lcd.print("Vitesse 1 *");                              
      }else{
        MENU_V();
        lcd.setCursor(10,1);
        lcd.print(" ");
      }
    }
    if(text4Bit==1){
      if(V == 2){
        MENU_V();
        lcd.setCursor(0,1);
        lcd.print("Vitesse 2 *");
      }else{
        MENU_V();
        lcd.setCursor(10,1);
        lcd.print(" ");
      }
    }
    if(text4Bit==2){
      if(V == 3){
        MENU_V();
        lcd.setCursor(0,1);
        lcd.print("Vitesse 3 *");
      }else{
        MENU_V();
        lcd.setCursor(10,1);
        lcd.print(" ");
      }
    }
  }
                               //Liste MENU Sens
  if(text1Bit==1){
    digitalWrite(3,HIGH);
    if(text3Bit==0){
      if(sens==0){
        
        MENU_S();
        lcd.setCursor(0,1);
        lcd.print("     GAUCHE *");
      }else{
        MENU_S();
        lcd.setCursor(12,1);
        lcd.print(" ");
      }
    }
    if(text3Bit==1){
      if(sens==1){
        
        MENU_S();
        lcd.setCursor(0,1);
        lcd.print("     DROITE *");
      }else{
        MENU_S();
        lcd.setCursor(12,1);
        lcd.print(" ");
      }
    }
  }else{
    digitalWrite(3,LOW);
  }
  if(text1Bit==1){
    if(digitalRead(But4)==LOW){
 
      text3Bit=1;
      MENU_S();
    
       
    }
  }
  if(text1Bit==1){  
    if(digitalRead(But1)==LOW){
           
           text3Bit=0;
           MENU_S();
         
    }
   }   
    
   
}
                               // Menu PRINCIPALE :
void MENU1(){
  digitalWrite(ledV,HIGH);
  digitalWrite(ledR,LOW);
  
  lcd.setCursor(0, 0);
  lcd.print(text1[text1Bit]);
  lcd.setCursor(0, 1);
  lcd.print(text2[text2Bit]);  

if(text1Bit==0){
 
  if(digitalRead(But4) == LOW){
    do{}while(digitalRead(But4) == LOW);
    
  lcd.clear();
  text2Bit++;
  if (text2Bit>3){
  text2Bit=3;  
  }
  }
    if(digitalRead(But1) == LOW){
    do{}while(digitalRead(But1) == LOW);
  
  lcd.clear();
  text2Bit--;
  if (text2Bit<0){
  text2Bit=0;  
   }
  }
 }
}
                               // Menu SENS :
void MENU_S(){
  lcd.setCursor(0, 0);
  lcd.print(text1[text1Bit]);
  lcd.setCursor(0, 1);
  lcd.print(text3[text3Bit]);
    
}
                               // Menu VITESSE :
void MENU_V(){
 
  lcd.setCursor(0, 0);
  lcd.print(text1[text1Bit]);
  lcd.setCursor(0, 1);
  lcd.print(text4[text4Bit]);
  }
                               // Menu DEMARRER :
void MENU_D(){

  lcd.setCursor(0, 0);
  lcd.print(text1[text1Bit]);
  if(sens==0){
   Sens="G"; 
  }else{
    Sens="D";
  }
  lcd.setCursor(0, 1);
  lcd.print("sens =");lcd.print(Sens);lcd.print(" /");lcd.print("Vit =");lcd.print(V);
  
}
                               // Menu MARCHE :
void MENU_M(){
  lcd.setCursor(0, 0);
  lcd.print(text1[text1Bit]);
  
}

                               // Sens de rotation Droite :
void Droite(){
  for(int x=4;x<=7;x++){
  digitalWrite(x,LOW);
  delay(T);
  digitalWrite(x,HIGH);
}
}
                               // Sens de rotation Gauche :
void Gauche(){ 
  for(int x=7;x>=4;x--){
  digitalWrite(x,LOW);
  delay(T);
  digitalWrite(x,HIGH);
}
}
