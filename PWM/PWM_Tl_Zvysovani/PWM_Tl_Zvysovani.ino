/*Napište program, který při každém stisknutí tlačítka zvýší jas LED (PWM). 
 *Po dosažení maximální intenzity (255) se při dalším stisknutí tlačítka jas opět sníží na minimum (0).
 */
#define PIN_TLACITKO 2       
#define PIN_LED 9            
#define CAS_ZAKMITU 20       

volatile int jas = 0;                    // Počáteční jas LED (0-255)
volatile int krokJasu = 51;              // Krok změny jasu (pro pět kroků až do 255)
volatile bool stavTlacitka = HIGH;      
volatile bool predchoziStavTlacitka = HIGH; 
unsigned long predchoziZmenaTlacitka = 0;  

void setup() {
  pinMode(PIN_LED, OUTPUT);          
  pinMode(PIN_TLACITKO, INPUT_PULLUP); 
}

void loop() {
  // Přečti stav tlačítka
  stavTlacitka = digitalRead(PIN_TLACITKO);
  
  // Zkontroluj, zda došlo ke změně stavu tlačítka a zda od poslední změny uplynul CAS_ZAKMITU
  if (stavTlacitka != predchoziStavTlacitka && millis() >= predchoziZmenaTlacitka + CAS_ZAKMITU) {
    predchoziStavTlacitka = stavTlacitka;
    predchoziZmenaTlacitka = millis();
    
    if (stavTlacitka == LOW) {
      jas += krokJasu;
      
      if (jas > 255) {
        jas = 0;  
      }

      analogWrite(PIN_LED, jas); // Nastaví PWM hodnotu pro LED
    }
  }
}
