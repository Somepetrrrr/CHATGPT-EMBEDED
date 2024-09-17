/*Deklarujte prom. "citac" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 0 až 100000.
Deklarujte prom. "frekvence" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 1 až 20.
Vytvořte program, který bude pomocí časovače blikat LED připojenou na pin D5 frekvencí 1 Hz (střída 50 %).
Po stisku tlačítka se zvýší hodnota prom. "citac" o 1. Pokud bude hodnota prom.
"citac" násobkem 5 (prakticky po každém 5. stisku tl.), pomocí millis() 3x blikněte integrovanou LED frekvencí 2 Hz.
Pokud dojde k dlouhému stisku tlačítka (>500 ms), "citac" se nastaví na 0. Obsluhu tlačítka řešte ext. přerušením.
*/
#include <TimerOne.h>

unsigned long citac = 0;  // Minimální datový typ, který pokryje rozsah 0 až 100000
byte frekvence = 1;       // Minimální datový typ, který pokryje rozsah 1 až 20
int LED = LED_BUILTIN;
int LED_PIN_D5 = 5;  // LED na pinu D5
int PIN_TL = 3;      // Pin tlačítka
bool StavLed = LOW;
bool StavTl;
bool PredchoziStavTl = HIGH;
unsigned long PosledniZmenaTl = 0;
unsigned long CasStisku;
unsigned long DobaStisku;
unsigned long ZAKMIT = 20; // Ochrana proti zákmitům tlačítka
bool LedBlink = false;     // Indikátor pro blikání integrované LED
unsigned long posledniMillis = 0;
int blikCount = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LED_PIN_D5, OUTPUT);
  pinMode(PIN_TL, INPUT_PULLUP);
  Timer1.initialize(500000);  // Nastavení frekvence na 1 Hz (500ms perioda, 50% střída)
  Timer1.attachInterrupt(blinkLED);
  attachInterrupt(digitalPinToInterrupt(PIN_TL), ObsluhaTl, CHANGE);
  Serial.begin(9600);
}

void loop() {
}

void ObsluhaTl() {
  StavTl = digitalRead(PIN_TL);
  if (StavTl != PredchoziStavTl && millis() >= PosledniZmenaTl + ZAKMIT) {
    PredchoziStavTl = StavTl;
    PosledniZmenaTl = millis();

    if (StavTl == LOW) {
      citac++;
      CasStisku = millis();
      if (citac % 5 == 0) {
        LedBlink = true;
      }
    } else {
      DobaStisku = millis() - CasStisku;
      if (DobaStisku > 500) {
        citac = 0;
      }
    }
  }
}

void blinkLED() {
  // Přepínání stavu LED na pinu D5
  StavLed = !StavLed;
  digitalWrite(LED_PIN_D5, StavLed);

  // Blikání integrované LED
  if (LedBlink == true) {
    if (millis() - posledniMillis >= 250) {  // 2 Hz = 500 ms perioda, takže 250 ms na každý stav
      posledniMillis = millis();
      digitalWrite(LED, !digitalRead(LED));  // Přepnutí integrované LED
      blikCount++;
      if (blikCount >= 6) {  // 3 bliknutí (každý 2 Hz cyklus má 2 stavy)
        LedBlink = false;
        blikCount = 0;
        digitalWrite(LED, LOW);  // Vypnutí integrované LED po dokončení blikání
      }
    }
  }
}
