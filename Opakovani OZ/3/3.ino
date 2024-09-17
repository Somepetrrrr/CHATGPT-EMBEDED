/*Deklarujte prom. "citac" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 0 až 100000.
Deklarujte prom. "frekvence" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 1 až 20.
Vytvořte program, který bude pomocí časovače blikat LED připojenou na pin D5 frekvencí 1 Hz (střída 50 %).
Po stisku tlačítka se zvýší hodnota prom. "citac" o 1. Pokud bude hodnota prom. "citac" násobkem 5 (prakticky po každém 5. stisku tl.),
pomocí millis() 3x blikněte integrovanou LED frekvencí 2 Hz.
Pokud dojde k dlouhému stisku tlačítka (>500 ms), "citac" se nastaví na 0. Obsluhu tlačítka řešte ext. přerušením.
*/
#include <TimerOne.h>
unsigned long citac = 0;  // Minimální datový typ, který pokryje rozsah 0 až 100000
byte frekvence = 1;       // Minimální datový typ, který pokryje rozsah 1 až 20
int LED = 7;
int PIN_LED = 5;  // LED na pinu D5
int PIN_TL = 3;      // Pin tlačítka
bool StavLed = LOW;
bool StavTl;
bool PredchoziStavTl = HIGH;
unsigned long PosledniZmenaTl = 0;
unsigned long CasStisku;
unsigned long DobaStisku;
unsigned long ZAKMIT = 20; // Ochrana proti zákmitům tlačítka
bool LedBlinkK = false;     // Indikátor pro blikání integrované LED
unsigned long posledniMillis = 0;
unsigned long PosledniZmena;
int blik = 0;
void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(PIN_TL, INPUT_PULLUP);
  Timer1.initialize(1000000/frekvence/2);
  Timer1.attachInterrupt(LedBlink);
  attachInterrupt(digitalPinToInterrupt(PIN_TL), ObsluhaTl, CHANGE);
  Serial.begin(9600);

}

void loop() {
  if(LedBlinkK){
    if(millis() - posledniMillis >= 250){
      posledniMillis = millis();
      digitalWrite (LED, !digitalRead(LED));
      blik++;
      if(blik >=6){
        LedBlinkK = false;
        blik = 0;
        digitalWrite(LED,LOW);
        
      }
    }
    
    
  }
}
void LedBlink() {
  StavLed = !StavLed;
  digitalWrite(PIN_LED, StavLed);

  
}
void ObsluhaTl(){
  StavTl = digitalRead(PIN_TL);
  if(StavTl!=PredchoziStavTl && millis()>= PosledniZmena + ZAKMIT){
    PredchoziStavTl = StavTl;
    PosledniZmena = millis();
    if(StavTl == LOW){
      citac ++;
      CasStisku = millis();
      if(citac % 5 == 0){
        LedBlinkK = true;
      }
    }else{
      DobaStisku = millis() - CasStisku;
      if(DobaStisku > 500){
        citac = 0;
        
      }
    }
  }
  Serial.println(citac);
}
