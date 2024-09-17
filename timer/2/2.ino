/*Rozblikejte pomocí přerušení od časovače integrovanou LED frekvencí 2 Hz. Po stisku tlačítka se zvýší frekvence blikání o 1 Hz až do max. hodnoty 5 Hz. 
 *Následující stisk (po dosažení 5 Hz) nastaví frekvcenci blikání opět na 2 Hz).
 */
#include <TimerOne.h>
#define PIN_TL 3
#define ZAKMIT 20
bool StavLed;
bool StavTl;
bool PredchoziStavTl;
unsigned long PosledniZmenaTl;
int led = LED_BUILTIN;
int f = 2;


void setup() {
  pinMode(led, OUTPUT);
  Timer1.initialize(1000000 / f / 2);
  Timer1.attachInterrupt(blinkLED); 
  attachInterrupt(digitalPinToInterrupt(PIN_TL), ObsluhaTl, CHANGE);
  Serial.begin(9600);
  
}

void loop() {

}

void blinkLED(){
  StavLed = digitalRead(led);
  StavLed = !StavLed;
  Timer1.setPeriod(1000000 / f / 2);
  digitalWrite(led,StavLed);
}
void ObsluhaTl(){
  StavTl = digitalRead(PIN_TL);
  if (StavTl != PredchoziStavTl && millis() >= PosledniZmenaTl + ZAKMIT) {
    PredchoziStavTl = StavTl;
    PosledniZmenaTl = millis();
    
    if (StavTl == LOW) {
      f++;
      if (f > 5) {
        f = 2;
      }
      Timer1.setPeriod(1000000 / f / 2); // Přepočítá periodu na základě nové frekvence
    }
  }
}
