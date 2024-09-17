/*Vytvořte pole 10 čísel a naplňte jej čísly podle svého uvážení ("náhodná čísla").
Pomocí cyklu for vypište všechna čísla z pole nejprve od 0. po 9., pak od 9. po 0. a nakonec sečtěte všechna čísla v poli a výsledek vypište.

*/
int soucet = 0; // Inicializace proměnné soucet

void setup() {
  Serial.begin(9600);
  int pole[10] = {6, 9, 8, 7, 1, 2, 0, 8, 3, 5}; // Vytvoření a naplnění pole

  // Výpis čísel od 0. po 9. prvek
  for (int i = 0; i < 10; i++) {
    Serial.print(pole[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Výpis čísel od 9. po 0. prvek
  for (int i = 9; i >= 0; i--) {
    Serial.print(pole[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Sečtení všech čísel v poli
  for (int i = 0; i < 10; i++) {
    soucet += pole[i];
  }
  Serial.print("Soucet: ");
  Serial.println(soucet);
}

void loop() {
  // Prázdná smyčka loop, protože vše se děje v setup()
}
