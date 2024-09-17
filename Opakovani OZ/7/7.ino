/*/*Deklarujte prom. se vhodným datových typem, která bude sloužit pro ukládání čísel 0 až 1000 a výchozí hodnotu bude mít 0.
  Každých 100 ms přičtěte k dané prom. 3. Pokud bude hodnota proměnné mezi 15 a 37 vč., vypište hodnotu prom.
  do konzole. Pokud bude hodnota mimo rozsah, nevypíšete nic.
  Pokud bude hodnota prom. v uvedeném rozsahu, ale bude stisknuto tlačítko, vypíšete do konzole místo čísla "_".
  Stačí prostá detekce stavu tlačítka, netřeba řešit zákmity ani používat přerušení.
  Pokud prom. přesáhne hodnotu 60, nastaví se na 0.
*/
#define PIN_TL 3
bool StavTl;
unsigned long promena = 0;
unsigned long PosledniMillis;

void setup() {
  pinMode(PIN_TL, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  StavTl = digitalRead(PIN_TL);
  if (millis() - PosledniMillis >= 500) {
    PosledniMillis = millis();
    promena += 3;
    if (promena >= 15 && promena <= 37) {
      if (StavTl == LOW) {
        Serial.println("_");
      } else {
        Serial.println(promena);
      }

    }
    if (promena > 60) {
      promena = 0;
    }

  }

}
