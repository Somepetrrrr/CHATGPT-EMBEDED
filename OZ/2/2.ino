/*Deklarujte prom. "citac" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 0 až 100000.
+Vytvořte program, který bude pomocí časovače blikat integrovanou LED 1 Hz se střídou 10 %.
Po stisku tlačítka se vypíše čas běhu programu v ms a sestupná sekvence čísel od M do 0, kde M je dob běhu programu v celých sekundách.
Pokud bude M větší než 120, místo sekvence čísel vypište "prilis dlouha sekvence".
*/
#include <TimerOne.h>

unsigned long citac;
byte frekvence = 1;
int strida = 10;
int LED = LED_BUILTIN;
unsigned long StartBehu;
bool StavLed = LOW;

int PIN_TL = 3;  // Definice pinu tlačítka
bool StavTl;
bool PredchoziStavTl = HIGH;
unsigned long PosledniZmena = 0;
unsigned long CasBehu;
unsigned long ZAKMIT = 20;  // Ochrana proti zákmitům tlačítka

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(PIN_TL, INPUT_PULLUP);
  Timer1.initialize(1000000 / frekvence * strida / 100);
  Timer1.attachInterrupt(blinkLED);
  StartBehu = millis();
  Serial.begin(9600);
}

void loop() {
  StavTl = digitalRead(PIN_TL);  // Čtení stavu tlačítka
  if (StavTl != PredchoziStavTl && millis() >= PosledniZmena + ZAKMIT) {
    PredchoziStavTl = StavTl;
    PosledniZmena = millis();
    
    if (StavTl == LOW) {
      CasBehu = millis() - StartBehu;
      Serial.println(CasBehu);

      int M = CasBehu / 1000;  // Převod milisekund na sekundy
      if (M > 120) {
        Serial.println("Prilis dlouha sekvence");
      } else {
        for (int i = M; i >= 0; i--) {
          Serial.println(i);
        }
      }
    }
  }
}

void blinkLED() {
  StavLed = !StavLed;  // Přepnutí stavu LED
  digitalWrite(LED, StavLed);
  
  if (StavLed == LOW) {
    Timer1.setPeriod(1000000 / frekvence * strida / 100);
  } else {
    Timer1.setPeriod(1000000 / frekvence * (100 - strida) / 100);
  }
}
