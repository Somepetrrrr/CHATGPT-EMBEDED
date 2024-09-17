/*Deklarujte prom. "zapnuti" a "vypnuti" se vhodným datovým typem (min. použitelným), když obsahem proměnných budou čísla 0 až 10.
V prom. "zapnuti" bude uložen počet stisknutí tlačítka potřebných pro rozsvícení integr. LED a v prom. 
"vypnuti" bude uložen počet stisknutí tlačítka potřebných pro zhasnutí integr. LED.
Pomocí ext. přerušení zajistěte rozsvícení LED po počtu stisku uvedených v prom. "zapnuti" a totéž pro zhasnutí.
Např. pokud bude v prom "zapnuti" 4 a ve "vypnuti" 2, tak po 4  stisknutích se LED rozsvítí a po dalších 2 zhasne.
*/
#define PIN_TL 3
#define ZAKMIT 20

byte zapnuti = 4;
byte vypnuti = 2;
int LED = 7;
bool StavLed = LOW;
bool StavTl;
bool PredchoziStavTl = HIGH;
unsigned long PosledniZmenaTl = 0;
unsigned int PocetStisku = 0;

void setup() {
  pinMode(LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_TL), ObsluhaTl, CHANGE);
  Serial.begin(9600);
}

void loop() {
}

void ObsluhaTl(){
  StavTl = digitalRead(PIN_TL);
  if (StavTl != PredchoziStavTl && millis() >= PosledniZmenaTl + ZAKMIT) {
    PredchoziStavTl = StavTl;
    PosledniZmenaTl = millis();

    if (StavTl == LOW) {
      PocetStisku++;

      if (PocetStisku == zapnuti && StavLed == LOW) {
        digitalWrite(LED, HIGH);
        StavLed = HIGH;
        PocetStisku = 0;  
      }
     else if (PocetStisku == vypnuti && StavLed == HIGH) {
        digitalWrite(LED, LOW);
        StavLed = LOW;
        PocetStisku = 0;  
      }
    }
  }
}
