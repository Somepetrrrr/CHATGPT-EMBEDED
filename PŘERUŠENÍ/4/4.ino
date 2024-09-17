/*Připojte k Arduinu tlačítko na pin 2 a LED. Pomocí ext. přerušení reagujte na stisk tlačítka.
Pokud bude tlačítko stisknuto, bude LED blikat frekvencí 4 Hz se střídou 20 %. Po uvolnění tlačítka, LED bude zhasnuta.
Ošetřete zákmity.
*/
#define PIN_TL 2
#define ZAKMIT 20

bool StavTl;
bool PredchoziTl = HIGH;  
bool TlStisk = false;
unsigned long PosledniZmenaTl = 0;
unsigned long PosledniCas;
int f = 4;
int s = 20; 
int perioda = 1000 / f;
int DobaZapnuti = perioda * s /100;

void setup() {
  pinMode(PIN_TL, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_TL), ObsluhaTl, CHANGE);
  Serial.begin(9600);
}

void loop() {
  if (TlStisk == true){
    if (millis() - PosledniCas >= perioda){
      PosledniCas = millis();
      digitalWrite (LED_BUILTIN, HIGH);
    }
      if (millis() - PosledniCas >= DobaZapnuti){
      digitalWrite (LED_BUILTIN, LOW);
    }
    
    
    
  }else{
    digitalWrite (LED_BUILTIN, LOW);
  }

}

void ObsluhaTl(){
  StavTl = digitalRead(PIN_TL); 
  if (StavTl != PredchoziTl && millis() >= PosledniZmenaTl + ZAKMIT) {
    PredchoziTl = StavTl;
    PosledniZmenaTl = millis();
    if (StavTl == LOW){
      TlStisk = true;
    }else{
      TlStisk= false;
    }
    
  }
}
