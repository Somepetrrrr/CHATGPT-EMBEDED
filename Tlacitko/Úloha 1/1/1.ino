/*Úloha 1: Zapnutí/Vypnutí LED
Napište program, který při každém stisknutí tlačítka přepne stav LED (zapne/vypne).
*/
#define PIN_TL 3  
#define ZAKMIT 20
bool StavTl;
bool StavLed = LOW;
bool PredchoziStavTl;
unsigned long PosledniZmenaTl;



void setup() {
  pinMode (PIN_TL, INPUT_PULLUP);
  pinMode (LED_BUILTIN, OUTPUT);
  Serial.begin (9600);

 
}

void loop() {
  StavTl = digitalRead (PIN_TL);
  if (StavTl != PredchoziStavTl && millis() >= PosledniZmenaTl + ZAKMIT) {
    PredchoziStavTl = StavTl;
    PosledniZmenaTl = millis();
    if (StavTl == LOW){
      StavLed = !StavLed;

    }else{
      Serial.println (StavLed);
    }
  }


}
