/*Deklarujte prom. "zapnuti" a "vypnuti" se vhodným datovým typem (min. použitelným), když obsahem proměnných budou čísla 0 až 10.
V prom. "zapnuti" bude uložen počet stisknutí tlačítka potřebných pro rozsvícení integr. LED a v prom. 
"vypnuti" bude uložen počet stisknutí tlačítka potřebných pro zhasnutí integr. LED.
Pomocí ext. přerušení zajistěte rozsvícení LED po počtu stisku uvedených v prom. "zapnuti" a totéž pro zhasnutí.
Např. pokud bude v prom "zapnuti" 4 a ve "vypnuti" 2, tak po 4  stisknutích se LED rozsvítí a po dalších 2 zhasne.
*/
#define LED 7
#define PIN_TL 3
#define ZAKMIT 20
bool StavTl;
bool PredchoziStavTl = HIGH;
unsigned long PosledniZmena;
unsigned long pocetStisku;
bool StavLed = LOW;
byte zapnuti = 4;
byte vypnuti = 2;
void setup() {
  pinMode (LED, OUTPUT);
  pinMode (PIN_TL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_TL), ObsluhaTl, CHANGE);
  Serial.begin(9600);

}

void loop() {
}
void ObsluhaTl () {
  StavTl = digitalRead(PIN_TL);
  if(StavTl!=PredchoziStavTl && millis()>= PosledniZmena + ZAKMIT){
    PredchoziStavTl = StavTl;
    PosledniZmena = millis();
    if(StavTl == LOW){
    pocetStisku ++;
      if(pocetStisku == zapnuti && StavLed == LOW){
        pocetStisku = 0;
        StavLed = HIGH;
        digitalWrite(LED,StavLed);
      }
      if(pocetStisku == vypnuti && StavLed == HIGH){
        pocetStisku = 0;
        StavLed = LOW;
        digitalWrite(LED,StavLed);        
      }
      
      
    }
  }
}
