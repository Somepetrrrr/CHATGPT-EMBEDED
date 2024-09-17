/*Pomocí millis() postupně zvyšujte jas LED od 0 do 100 % tak, aby celá změna trvala 2 s. Po dosažení 100% jasu se bude jas 2 s snižovat až do 0.
Po dosažení 0 se jas bude opět zvyšovat, atd. Celá změna od 0 na 100 % a zpět na 0 bude trvat 4 s.
*/
#define PIN_LED 9
unsigned long PosledniMillis;
int jas = 0;
int krok = 1;
int doba = 20; // 2000/100%


void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(9600);
  analogWrite(PIN_LED, jas);
}

void loop() {
  if(millis()-PosledniMillis>=doba){
    PosledniMillis = millis();
    jas = jas + krok;
    if(jas>=100 || jas <=0){
      krok = -krok;
    }
    analogWrite(PIN_LED, jas *255 / 100);
  }
  
}
