/*Deklarujte prom. "frekvence" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 1 až 20. 
 * Výchozí hodnota bude 2.
Připojte k Arduinu dvě tlačítka na piny D2 a D3 (ext. přerušení).
Pomocí millis() blikejte integrovanou LED frekvencí podle prom. "frekvence" se střídou 50 %.
Při stisku jednoho tlačítka dojde ke zvýšení frekvence blikání až do max. hodnoty 10 Hz a při stisku druhého tlačítka
ke snížení frekvence až do min. hodnoty 1 Hz.
Stisky tlačítek řešte ext. přerušením. Každé tl. musí mít své prom. pro detekci zákmitů.
*/
#define PIN_TL1 2
#define PIN_TL2 3
#define ZAKMIT 20

bool StavLed = LOW;
byte frekvence = 2;  // Výchozí hodnota frekvence
int LED = LED_BUILTIN;

unsigned long PosledniMillis = 0;
unsigned long PosledniZmena1 = 0;
unsigned long PosledniZmena2 = 0;

bool StavTl1;
bool StavTl2;
bool PredchoziStav1 = HIGH;
bool PredchoziStav2 = HIGH;


void setup() {
  pinMode (PIN_TL1, INPUT_PULLUP);
  pinMode (PIN_TL2, INPUT_PULLUP);
  pinMode (LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_TL1), ObsluhaTl1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_TL2), ObsluhaTl2, CHANGE);
  Serial.begin(9600);
}

void loop() {
  int interval = 1000/frekvence/2;
  if(millis() - PosledniMillis >= interval){
    PosledniMillis = millis();
    StavLed = !StavLed;
    digitalWrite(LED, StavLed);
  }
}
void ObsluhaTl1(){
  StavTl1 = digitalRead(PIN_TL1);
  if(StavTl1 != PredchoziStav1 && millis() >= PosledniZmena1 + ZAKMIT){
     PredchoziStav1 = StavTl1;
     PosledniZmena1 = millis();
     if(StavTl1 == LOW && frekvence < 10){
      frekvence ++;
        
     }
  }
}
void ObsluhaTl2(){
  StavTl2 = digitalRead(PIN_TL2);
  if(StavTl2 != PredchoziStav2 && millis() >= PosledniZmena2 + ZAKMIT){
     PredchoziStav2 = StavTl2;
     PosledniZmena2 = millis();
     if(StavTl2 == LOW && frekvence > 1){
      frekvence --;
        
     }
  }
  
}
