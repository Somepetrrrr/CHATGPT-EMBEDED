#include <TimerOne.h>
#define PIN_TL 3
#define ZAKMIT 20

int StavLed = LOW; // Použití int místo bool
int StavTl;
int PredchoziStavTl = HIGH;
unsigned long PosledniZmenaTl = 0;
int led = LED_BUILTIN;
int f = 2;
int strida = 20;

void setup() {
  pinMode(led, OUTPUT);
  Timer1.initialize(1000000 / f * strida / 100); // Nastavení periody na základě frekvence a střídy
  Timer1.attachInterrupt(blinkLED); 
  attachInterrupt(digitalPinToInterrupt(PIN_TL), ObsluhaTl, CHANGE);
  Serial.begin(9600);
}

void loop() {
  // Prázdná smyčka
}

void blinkLED() {
  StavLed = !StavLed; // Přepínání mezi LOW a HIGH
  digitalWrite(led, StavLed);
  
  // Aktualizace periody na základě stavu LED (zapnuto/vypnuto)
  if (StavLed == HIGH) {
    Timer1.setPeriod(1000000 / f * strida / 100);
  } else {
    Timer1.setPeriod(1000000 / f * (100 - strida) / 100);
  }
}

void ObsluhaTl() {
  StavTl = digitalRead(PIN_TL);
  
  if (StavTl != PredchoziStavTl && millis() >= PosledniZmenaTl + ZAKMIT) {
    PredchoziStavTl = StavTl;
    PosledniZmenaTl = millis();
    
    if (StavTl == LOW) {
      f++;
      if (f > 5) {
        f = 2;
      }
      if (StavLed == HIGH) {
        Timer1.setPeriod(1000000 / f * strida / 100);
      } else {
        Timer1.setPeriod(1000000 / f * (100 - strida) / 100);
      }
    }
  }
}
