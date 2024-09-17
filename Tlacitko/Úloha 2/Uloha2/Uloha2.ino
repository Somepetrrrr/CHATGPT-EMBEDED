/*Napište program, který bude počítat, kolikrát bylo tlačítko stisknuto. Výsledek se bude vypisovat na sériový monitor.
 */
 #define PIN_TL 3 
 #define ZAKMIT 20

 bool StavTl;
 bool PredchoziStavTl;
 unsigned long PosledniZmenaTl;
 unsigned long PocetStisku;



void setup() {
  pinMode (PIN_TL, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  StavTl = digitalRead(PIN_TL);
  if(StavTl != PredchoziStavTl && millis()>= PosledniZmenaTl + ZAKMIT) {
    PredchoziStavTl = StavTl;
    PosledniZmenaTl = millis();
    if(StavTl == LOW){
      PocetStisku ++;
  }else{
    Serial.println(PocetStisku);
  }

}
}
