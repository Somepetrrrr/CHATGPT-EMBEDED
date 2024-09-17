/*Napište program, který rozpozná dlouhý a krátký stisk tlačítka. Pokud bude tlačítko stisknuto déle než 1 sekundu, LED se rozsvítí na 2 sekundy. 
Pokud bude stisknuto krátce (méně než 1 sekundu), LED se rozsvítí na 0.5 sekundy.
*/


#define PIN_TL 3
#define LED 7
#define ZAKMIT 20

bool StavTl;
bool PredchoziStavTl;
bool LedZapnuta = false;
unsigned long PosledniZmena;
unsigned long CasStisku;
unsigned long DobaStisku;
unsigned long CasRozsviceni;

void setup() {
  pinMode(PIN_TL, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  PredchoziStavTl = HIGH;  
}

void loop() {
  StavTl = digitalRead(PIN_TL);
  if (StavTl != PredchoziStavTl && millis() >= PosledniZmena + ZAKMIT) {
    PredchoziStavTl = StavTl;
    PosledniZmena = millis();

    if (StavTl == LOW) {
      CasStisku = millis();  // Uložení času stisku
    } else {
      DobaStisku = millis() - CasStisku;  // Výpočet délky stisku

      if (DobaStisku >= 1000) {  // Pokud stisk trval déle než 1 sekundu
        digitalWrite(LED, HIGH);
        LedZapnuta = true;
        CasRozsviceni = millis();  // Uložení času, kdy se LED rozsvítila
        Serial.println("Dlouhy Stisk, LED sviti na 2 sekundy.");
      } else {  // Pokud stisk trval méně než 1 sekundu
        digitalWrite(LED, HIGH);
        LedZapnuta = true;
        CasRozsviceni = millis();  // Uložení času, kdy se LED rozsvítila
        Serial.println("Kratky Stisk, LED sviti na 0.5 sekundy.");
      }
    }
  }

  // Kontrola, zda je LED zapnutá a zda uplynul čas na její vypnutí
  if (LedZapnuta) {
    if (DobaStisku >= 1000 && millis() - CasRozsviceni >= 2000) {
      digitalWrite(LED, LOW);  // Zhasnutí LED po 2 sekundách
      LedZapnuta = false;
    } else if (DobaStisku < 1000 && millis() - CasRozsviceni >= 500) {
      digitalWrite(LED, LOW);  // Zhasnutí LED po 0.5 sekundě
      LedZapnuta = false;
    }
  }
}
