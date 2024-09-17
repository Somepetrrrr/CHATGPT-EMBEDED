/*Deklarujte prom. "citac" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 0 až 100000.
Deklarujte prom. "frekvence" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 1 až 20.
Vytvořte program, který bude pomocí časovače blikat integrovanou LED frekvencí 1 Hz se střídou 10 %.
Po stisku tlačítka se vypíše čas běhu programu v ms a sestupná sekvence čísel od M do 0, kde M je dob běhu programu v celých sekundách.
Pokud bude M větší než 120, místo sekvence čísel vypište "prilis dlouha sekvence".
*/
#include <TimerOne.h>
#define PIN_TL 3
#define ZAKMIT 20
unsigned long citac;
byte frekvence = 1;
int strida = 10;
int LED = LED_BUILTIN;
bool StavLed = LOW;
bool StavTl;
bool PredchoziStavTl = HIGH;
unsigned long StartBehu;
unsigned long PosledniZmena;
unsigned long CasBehu;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(PIN_TL, INPUT_PULLUP);
  Timer1.initialize(1000000/frekvence * strida / 100);
  Timer1.attachInterrupt(LedBlink);
  Serial.begin (9600);
  StartBehu = millis();
}

void loop() {
  StavTl = digitalRead(PIN_TL);
  if(StavTl!=PredchoziStavTl&&millis()>=PosledniZmena + ZAKMIT){
    PredchoziStavTl = StavTl;
    PosledniZmena = millis();
    if(StavTl == LOW){
      CasBehu = millis()-StartBehu;
      Serial.println(CasBehu);

      int M = CasBehu / 1000;
      if(M>120){
        Serial.println("prilis dlouha sekvence");
      }else{
        for(int i = M;i > 0; i--){
          Serial.println(i);
          
        }
      }
    }
    
  }
  
}
void LedBlink(){
  StavLed = !StavLed;
  digitalWrite(LED, StavLed);
}
