/* Napište program, který při stisknutí tlačítka začne LED blikat s frekvencí 1 Hz (1x za sekundu). Při dalším stisknutí tlačítka blikání zastaví.
 *  
 */
#define PIN_TL 3  
#define ZAKMIT 20
#define LED 7

bool StavTl;
bool PredchoziStavTl;
bool Blikani = false;
bool StavLed = LOW;  // Ukládání stavu LED
unsigned long PosledniZmenaTl;
unsigned long PosledniZmenaLed;
unsigned long interval = 500;

void setup() {
  pinMode(PIN_TL, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  PredchoziStavTl = digitalRead(PIN_TL);  // Inicializace predchoziho stavu
}

void loop() {
  StavTl = digitalRead(PIN_TL);

  // Detekce stisku tlačítka s odstraňováním zákmitů
  if (StavTl != PredchoziStavTl && millis() >= PosledniZmenaTl + ZAKMIT) {
    PredchoziStavTl = StavTl;
    PosledniZmenaTl = millis();

    if (StavTl == LOW) {
      Blikani = !Blikani;  // Přepnutí stavu blikání
    }
  }

  // Blikání LED, pokud je zapnuto
  if (Blikani) {
    if (millis() - PosledniZmenaLed >= interval) {
      PosledniZmenaLed = millis();
      StavLed = !StavLed;  // Přepnutí stavu LED
      digitalWrite(LED, StavLed);
    }
  } else {
    StavLed = LOW;  // Vypnutí LED, když blikání není zapnuto
    digitalWrite(LED, StavLed);
  }
}
