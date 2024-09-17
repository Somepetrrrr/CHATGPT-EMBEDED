/*/*Deklarujte prom. "citac" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 0 až 100000.
Deklarujte prom. "frekvence" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 1 až 20.
Vytvořte program, který bude pomocí časovače blikat integrovanou LED frekvencí 1 Hz (střída 50 %).
Po krátkém stisku tlačítka se frekvence blikání zvýší o 1 Hz do max. hodnoty 10 Hz. 
Pokud LED bliká frekv. 10 Hz, další stisk tl. nastaví frekvenci na 1 Hz.
Pokud dojde k dlouhému stisku tlačítka (>500 ms), frekvence se nastaví na 1 Hz rovnou. Obsluhu tlačítka řešte ext. přerušením.
*/
#include <TimerOne.h>
#define PIN_TL 3
#define ZAKMIT 20
unsigned long citac;
byte frekvence = 1;
int LED = 7;
bool StavLed = LOW;
bool StavTl;
bool PredchoziStavTl = HIGH;
unsigned long PosledniZmena;
unsigned long CasStisku;
unsigned long DobaStisku;
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(PIN_TL, INPUT_PULLUP);
  Timer1.initialize(1000000/frekvence/2);
  Timer1.attachInterrupt(blinkLED);
  attachInterrupt(digitalPinToInterrupt(PIN_TL),ObsluhaTl,CHANGE);
  Serial.begin(9600);
}

void loop() {
}
void blinkLED(){
  StavLed = !StavLed;
  digitalWrite(LED, StavLed);
}
void ObsluhaTl(){
  StavTl = digitalRead(PIN_TL);
  if(StavTl != PredchoziStavTl && millis()>= PosledniZmena + ZAKMIT){
    PredchoziStavTl = StavTl;
    PosledniZmena = millis();
    if(StavTl == LOW){
      frekvence ++;
      CasStisku = millis();
      if(frekvence > 10){
        frekvence = 1;
      }

  }else{
    DobaStisku = millis() - CasStisku;
    Serial.println(DobaStisku);
    if(DobaStisku > 500){
      frekvence = 1;
    }
  }
  
}
  Timer1.setPeriod(1000000/frekvence/2);
  Serial.println(frekvence);
}
