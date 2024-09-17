/*Deklarujte prom. "frekvence" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 1 až 20. 
 * Výchozí hodnota bude 2.
Připojte k Arduinu dvě tlačítka na piny D2 a D3 (ext. přerušení).
Pomocí millis() blikejte integrovanou LED frekvencí podle prom. "frekvence" se střídou 50 %.
Při stisku jednoho tlačítka dojde ke zvýšení frekvence blikání až do max. hodnoty 10 Hz a při stisku druhého tlačítka
ke snížení frekvence až do min. hodnoty 1 Hz.
Stisky tlačítek řešte ext. přerušením. Každé tl. musí mít své prom. pro detekci zákmitů.
*/
#define PIN_TL1 3
#define PIN_TL2 2
byte frekvence = 2;
bool StavLed = LOW;
bool StavTl1;
bool StavTl2;
int LED = 7;
bool PredchoziStavTl1 = HIGH;
bool PredchoziStavTl2 = HIGH;
unsigned long PosledniMillis;
unsigned long PosledniZmenaTl1;
unsigned long PosledniZmenaTl2;


void setup() {
pinMode(PIN_TL1, INPUT_PULLUP);
pinMode(PIN_TL2, INPUT_PULLUP);
pinMode(LED, OUTPUT);
attachInterrupt(digitalPinToInterrupt(PIN_TL1),ObsluhaTl1,CHANGE);
attachInterrupt(digitalPinToInterrupt(PIN_TL2),ObsluhaTl2,CHANGE);

Serial.begin(9600);
}

void loop() {
  int perioda = 1000 / frekvence / 2;
  if(millis() - PosledniMillis >= perioda){
    PosledniMillis = millis();
    StavLed = !StavLed;
    digitalWrite(LED, StavLed);  
    Serial.println(frekvence); 
  }
}
void ObsluhaTl1(){
  StavTl1 = digitalRead(PIN_TL1);
  if(StavTl1!=PredchoziStavTl1&&millis()>=PosledniZmenaTl1){
    PredchoziStavTl1 = StavTl1;
    PosledniZmenaTl1 = millis();
    if(StavTl1 == LOW && frekvence < 10){
      frekvence ++;
    }
  }
  
}
void ObsluhaTl2(){
    StavTl2 = digitalRead(PIN_TL2);
  if(StavTl2!=PredchoziStavTl2&&millis()>=PosledniZmenaTl2){
    PredchoziStavTl2 = StavTl2;
    PosledniZmenaTl2 = millis();
    if(StavTl2 == LOW && frekvence > 1){
      frekvence --;
    }
  }
}
