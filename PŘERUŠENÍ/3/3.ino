/* Připojte k Arduinu tlačítko na pin 2. Pomocí ext. přerušení reagujte na stisk tlačítka.
Pokud bude mezi stiskem a uvolněním tlačítka více než 500 ms, vypíše se do konzole "dlouhy stisk", jinak "kratky stisk".
Ošetřete zákmity.
*/
#define PIN_TL 2
#define ZAKMIT 20

bool StavTl;
bool PredchoziTl = HIGH;  // Výchozí stav tlačítka je HIGH, protože je používán INPUT_PULLUP
unsigned long PosledniZmenaTl = 0;
unsigned long CasStisku = 0;
unsigned long DobaStisku = 0;

void setup() {
  pinMode(PIN_TL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_TL), ObsluhaTl, CHANGE);
  Serial.begin(9600);
}

void loop() {
  // Hlavní smyčka může být prázdná, protože vše je řízeno přerušením
}

void ObsluhaTl() {
  StavTl = digitalRead(PIN_TL);
  
  if (StavTl != PredchoziTl && millis() >= PosledniZmenaTl + ZAKMIT) {
    PredchoziTl = StavTl;
    PosledniZmenaTl = millis();

    if (StavTl == LOW) {
      CasStisku = millis();  // Uložení času stisku tlačítka
    } else {
      DobaStisku = millis() - CasStisku;  // Vypočítání doby stisku tlačítka

      if (DobaStisku > 500) {
        Serial.println("Dlouhy stisk");
      } else {
        Serial.println("Kratky stisk");
      }
    }
  }
}
