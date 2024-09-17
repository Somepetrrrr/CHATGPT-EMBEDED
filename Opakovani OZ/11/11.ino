/*Deklarujte prom. "frekvence" se vhodným datovým typem a vložte do ní číslo 152.
Pomocí while cyklu vypisujte hodnotu proměnné a snižujte její hodnotu o 1 tak dlouho, dokud nebude menší než  105.
*/
int frekvence = 152;
void setup() {

}

void loop() {
while (frekvence > 105){
  frekvence --;
  Serial.print(frekvence);
}
}
