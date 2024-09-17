// Příjmout číslo a zpět poslat o 5 větší.
int cislo;

void setup() {
  Serial.begin(9600);

}

void loop() {
  if(Serial.available()>0){
 
cislo = Serial.parseInt();
Serial.println(cislo + 5);

}
   
  }
//delay(200);