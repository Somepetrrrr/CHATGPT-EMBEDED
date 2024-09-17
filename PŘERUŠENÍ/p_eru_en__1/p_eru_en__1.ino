/*Připojte k Arduinu tlačítko na pin 2. Pomocí ext. přerušení reagujte na stisk tlačítka.
Blikejte zelenou LED frekvencí 2 Hz. Po stisku tlačítka přestane zelená LED blikat a rozsvítí se červená LED.
Po dalším stisku červená LED zahsne a zelená se rozbliká.
Ošetřete zákmity.
*/


#define PIN_TL 2
#define ZAKMIT 20
#define LEDZ 7
#define LEDR 8

int f = 2;  // Frekvence v Hz
bool ZBLINK = true;  // Flag pro blikání LED
bool StavTl;
bool PredchoziStavTl;
unsigned long PosledniZmenaTl;
unsigned long PosledniBlink;

void setup() {
  pinMode(PIN_TL, INPUT_PULLUP);
  pinMode(LEDZ, OUTPUT);
  pinMode(LEDR, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(PIN_TL), ObsluhaTl, CHANGE);

  Serial.begin(9600);
}

void loop() {
  unsigned long interval = 1000 / (2 * f);  // Vypočítaný interval pro blikání

  // Blikání zelené LED
  if (ZBLINK && millis() - PosledniBlink >= interval) {
    PosledniBlink = millis();
    digitalWrite(LEDZ, !digitalRead(LEDZ));  // Přepnutí stavu LED
  }
  
  // Pokud není zelená LED nastavena na blikání, zajistí, aby byla zhasnutá
  if (!ZBLINK) {
    digitalWrite(LEDZ, LOW);
  }
}

void ObsluhaTl() {
  StavTl = digitalRead(PIN_TL);
  
  // Ošetření zákmity
  if (StavTl != PredchoziStavTl && millis() >= PosledniZmenaTl + ZAKMIT) {
    PredchoziStavTl = StavTl;
    PosledniZmenaTl = millis();

    if (StavTl == LOW) {  // Tlačítko je stisknuté
      ZBLINK = !ZBLINK;  // Přepíná mezi stavem blikání a červenou LED
      digitalWrite(LEDR, !ZBLINK);  // Rozsvítí nebo zhasne červenou LED
    }
  }
}
