/*Deklarujte prom. "jas" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 0 až 100. Výchozí hodnota bude 50.
Připojte k Arduinu dvě tlačítka na piny D2 a D3 (ext. přerušení).
Připojte LED na pin umožňující PWM a nastavte jas LED tak, aby odpovídal proměnné "jas".
V prom. "jas" je uvedeno, na kolik % max. svitu LED svítí.
Při stisku jednoho tlačítka dojde ke zvýšení jasu o 10 až do max. hodnoty 100 a při stisku druhého tlačítka ke snížení jasu až do min. hodnoty 0.
Stisky tlačítek řešte ext. přerušením. Každé tl. musí mít své prom. pro detekci zákmitů.
Po startu Arduina tedy LED svítí na 50 % a podle toho, jaké tlačítko je stisknuto se její jas bude zvyšovat nebo snižovat.
Ovšem nikdy nebude mimo hodnoty 0 až 100.
*/
#define PIN_TL1 2
#define PIN_TL2 3
#define ZAKMIT 20
#define PIN_LED 9

int jas = 50;
int zmena = 10;

bool StavTl1;
bool StavTl2;
bool PredchoziStavTl1 = HIGH;
bool PredchoziStavTl2 = HIGH;

unsigned long PosledniZmena1;
unsigned long PosledniZmena2;

void setup() {
  pinMode (PIN_TL1, INPUT_PULLUP);
  pinMode (PIN_TL2, INPUT_PULLUP);
  pinMode (PIN_LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_TL1), ObsluhaTl1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_TL2), ObsluhaTl2, CHANGE);

  analogWrite(PIN_LED, jas * 255 / 100);
  Serial.begin(9600);
}

void loop() {
}
void ObsluhaTl1(){
  StavTl1 = digitalRead(PIN_TL1);
  if(StavTl1!=PredchoziStavTl1 && millis()>= PosledniZmena1 + ZAKMIT){
    PredchoziStavTl1 = StavTl1;
    PosledniZmena1 = millis();
    if(StavTl1 == LOW && jas <100){
      jas = jas + zmena;
      analogWrite(PIN_LED, jas * 255 / 100);
 
    }
  }
}
void ObsluhaTl2(){
    StavTl2 = digitalRead(PIN_TL2);
  if(StavTl2!=PredchoziStavTl2 && millis()>= PosledniZmena2 + ZAKMIT){
    PredchoziStavTl2 = StavTl2;
    PosledniZmena2 = millis();
    if(StavTl2 == LOW && jas > 0){
      jas = jas - zmena;
      analogWrite(PIN_LED, jas * 255 / 100);
 
    }
  }
}
