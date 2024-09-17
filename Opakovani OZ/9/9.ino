/*Deklarujte prom. "jas" se vhodným datovým typem (min. použitelným), když obsahem proměnné budou čísla 0 až 100. Výchozí hodnota bude 50.
Připojte k Arduinu dvě tlačítka na piny D2 a D3 (ext. přerušení).
Připojte LED na pin umožňující PWM a nastavte jas LED tak, aby odpovídal proměnné "jas".
V prom. "jas" je uvedeno, na kolik % max. svitu LED svítí.
Při stisku jednoho tlačítka dojde ke zvýšení jasu o 10 až do max. hodnoty 100 a při stisku druhého tlačítka ke snížení jasu až do min. hodnoty 0.
Stisky tlačítek řešte ext. přerušením. Každé tl. musí mít své prom. pro detekci zákmitů.
Po startu Arduina tedy LED svítí na 50 % a podle toho, jaké tlačítko je stisknuto se její jas bude zvyšovat nebo snižovat.
Ovšem nikdy nebude mimo hodnoty 0 až 100.
*/
#define PIN_TL1 3
#define PIN_TL2 2
#define LED 9
#define ZAKMIT 20

bool StavTl1;
bool StavTl2;
bool PredchoziStavTl1 = HIGH;
bool PredchoziStavTl2 = HIGH;

unsigned long PosledniZmenaTl1;
unsigned long PosledniZmenaTl2;

int jas = 50;
int zmena = 10;


void setup() {
  pinMode(PIN_TL1, INPUT_PULLUP);
  pinMode(PIN_TL2, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_TL1),Obsluha1,CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_TL2),Obsluha2,CHANGE);

  analogWrite(LED, 255/100*jas);
  

}

void loop() {
Serial.println(jas);
}
void Obsluha1(){
  StavTl1 = digitalRead(PIN_TL1);
  if(StavTl1!= PredchoziStavTl1 && millis()>= PosledniZmenaTl1 + ZAKMIT){
    PredchoziStavTl1 = StavTl1;
    PosledniZmenaTl1 = millis();
    if(StavTl1 == LOW && jas < 100){
      jas = jas + zmena;
      analogWrite(LED, 255/100 * jas);
      
    }
  }
  
  
}
void Obsluha2(){
   StavTl2 = digitalRead(PIN_TL2);
  if(StavTl2!= PredchoziStavTl2 && millis()>= PosledniZmenaTl2 + ZAKMIT){
    PredchoziStavTl2 = StavTl2;
    PosledniZmenaTl2 = millis();
    if(StavTl2 == LOW && jas > 0){
      jas = jas - zmena;
      analogWrite(LED, 255/100 * jas);
      
    }
  } 
}
