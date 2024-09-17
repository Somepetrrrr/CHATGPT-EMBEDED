/*Načítejte čísla z konzole tak dlouho, dokud nebude zadáno číslo - 1.

Po zadání -1 (konec zadávání) vypište:
největší zadané číslo
nejmenší zadané číslo (-1 nepočítejte)
počet zadaných čísel (bez - 1)
a průměrnou hodnotu zadaných čísel (bez -1).
*/
int cislo;
long pocet = 0;
long soucet = 0;
int max = -32000;  
int min = 32000;  
float prumer;

void setup() {
  Serial.begin(9600);  
}

void loop() {
  if (Serial.available() > 0) {
    cislo = Serial.parseInt();
  

    if (cislo == -1) {
      Serial.println("Konec zadávání čísel.");
      Serial.print("Největší číslo: ");
      Serial.println(max);
      Serial.print("Nejmenší číslo: ");
      Serial.println(min);
      Serial.print("Počet čísel: ");
      Serial.println(pocet);
      Serial.print("Průměrná hodnota: ");
      Serial.println(prumer);
      while (true);
    }

    Serial.print("Zadané číslo: ");
    Serial.println(cislo);

    if (cislo > max) {
      max = cislo;
    }
    if (cislo < min) {
      min = cislo;
    }

    pocet++;
    soucet += cislo;
    prumer = soucet / pocet;
  }
}


