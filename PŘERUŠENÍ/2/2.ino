/* 
Připojte k Arduinu tlačítko na pin 2. 
Pomocí ext. přerušení reagujte na stisk tlačítka.
Při stisku tlačítka vypište do konzole, o kolikátý stisk se jedná (v rámci běhu programu). 
Po uvolnění tlačítka přepněte stav int. LED a vypište, jak dlouho bylo tlačítko stisknuto.
Ošetřete zákmity.
*/
#define PIN_TL 2
#define ZAKMIT 20
bool TlStisknuto = false;
bool StavTl;
bool StavLed;
bool PredchoziStavTl;
unsigned long PosledniZmenaTl;
unsigned long PocetStisku;
unsigned long CasStisku;


void setup() {
  pinMode (PIN_TL, INPUT_PULLUP);
  pinMode (LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_TL), ObsluhaTl, CHANGE);

  Serial.begin (9600)

}

void loop() {

}

void ObsluhaTl (){
  StavTl = digitalRead (PIN_TL);
  StavLed = digitalRead (LED_BUILTIN);
  if (StavTl != PredchoziStavTl && millis() >= PosledniZmenaTl + ZAKMIT){
    PredchoziStavtl = StavTl;
    PosledniZmenaTl = millis();

    if(StavTl == LOW){
      CasStisku = millis();
      PocetStisku ++;
      TlStisknuto = true;
    }else{
      DobaStisku = millis() - CasStisku;
      StavLed = !StavLed;
      Serial.println ("Stisknuto po dobu: ")
      Serial.print (DobaStisku);
      
    }
  }
}
